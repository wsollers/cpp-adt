#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <concepts>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../common/common.h"

namespace Graphs {

template <typename T>
concept Identifiable = requires(T obj) {
  {
    obj.id()
  } -> std::equality_comparable;  // Must have an id() method that's equality
                                  // comparable
} && Common::stl_container_storable<T> && Common::Hashable<T>;

template <typename T>
concept IdentifiableSortable = Identifiable<T> && requires(T obj) {
  { obj.id() } -> std::totally_ordered;  // ID must support <, <=, >, >=
};

// Concept for a Vertex
template <typename T>
concept Vertex = requires(T vertex) {
  // Must provide access to in-degree
  { vertex.inDegree() } -> std::convertible_to<int32_t>;
  // Must provide access to out-degree
  { vertex.outDegree() } -> std::convertible_to<int32_t>;
  // Must provide access to net-degree (out-degree - in-degree)
  { vertex.netDegree() } -> std::convertible_to<int32_t>;

  // Vertex must support equality comparison
  { vertex == vertex } -> std::convertible_to<bool>;
} && Identifiable<T>;
;

template <typename Vertex, typename Edge>
concept GraphEdge =
    requires(Vertex v, Edge edge) {
      //{ src } -> Identifiable;
      //{ dest } -> Identifiable;
      // src and dest should be of type Vertex
      { edge.source() } -> std::convertible_to<const Vertex &>;
      { edge.destination() } -> std::convertible_to<const Vertex &>;

      // Weight must be convertible to double
      { edge.weight() } -> std::convertible_to<double>;

      // Edge must support equality comparison
      { edge == edge } -> std::convertible_to<bool>;
    } && Common::stl_container_storable<Edge> &&
    Common::stl_container_storable<Vertex>;

template <typename VertexType, typename EdgeType>
  requires GraphEdge<VertexType, EdgeType>
class Graph {
 public:
  using AdjacencyList = std::unordered_map<VertexType, std::vector<EdgeType>>;

  Graph() {
    static_assert(Vertex<VertexType>,
                  "The Vertex type must satisfy the Vertex concept.");
    static_assert(GraphEdge<VertexType, EdgeType>,
                  "The Edge type must satisfy the GraphEdge concept.");
  }

  // Check if the graph is empty
  bool isEmpty() const { return adjList.empty(); }
  size_t getSize() const { return adjList.size(); }

  // Add a vertex to the graph
  void addVertex(const VertexType &vertex) {
    adjList.emplace(vertex, std::vector<EdgeType>{});
  }

  // Add an edge to the graph
  void addEdge(const EdgeType &edge) {
    adjList[edge.source()].push_back(edge);
    if (!directed) {
      adjList[edge.destination()].push_back(reverseEdge(edge));
    }
  }

  // Print the graph's adjacency list
  void printGraph() const {
    for (const auto &[vertex, edges] : adjList) {
      std::cout << vertex.id() << ": ";  // Assuming Vertex has an id() method
      for (const auto &edge : edges) {
        std::cout << "(" << edge.destination().id()
                  << ", weight: " << edge.weight() << ") ";
      }
      std::cout << "\n";
    }
  }

  // Set the graph as directed or undirected
  void setDirected(bool isDirected) { directed = isDirected; }

  bool detectCycle() const {
    // For directed graphs, use DFS to detect back edges
    if (directed) {
      std::unordered_set<VertexType> visited;
      std::unordered_set<VertexType> recursionStack;

      for (const auto &[vertex, _] : adjList) {
        if (detectCycleDirected(vertex, visited, recursionStack)) {
          return true;
        }
      }
    } else {
      // For undirected graphs, use DFS with parent tracking
      std::unordered_set<VertexType> visited;

      for (const auto &[vertex, _] : adjList) {
        if (!visited.count(vertex) &&
            detectCycleUndirected(vertex, visited, VertexType())) {
          return true;
        }
      }
    }

    return false;
  }

  // Equality operator: Compares two graphs for equality
  bool operator==(const Graph &other) const {
    if (directed != other.directed || adjList.size() != other.adjList.size()) {
      return false;
    }

    for (const auto &[vertex, edges] : adjList) {
      // Check if the vertex exists in the other graph
      auto it = other.adjList.find(vertex);
      if (it == other.adjList.end()) {
        return false;
      }

      // Compare edges for the vertex
      const auto &otherEdges = it->second;
      if (edges.size() != otherEdges.size() ||
          !std::is_permutation(edges.begin(), edges.end(),
                               otherEdges.begin())) {
        return false;
      }
    }

    return true;
  }

  Graph transpose() const {
    if (!directed) {
      return *this;  // For undirected graphs, transpose is the same as the
                     // original graph
    }
    Graph transposedGraph;
    transposedGraph.setDirected(directed);

    for (const auto &[vertex, edges] : adjList) {
      transposedGraph.addVertex(
          vertex);  // Add the vertex to the transposed graph
      for (const auto &edge : edges) {
        // Reverse the edge: destination becomes source and vice versa
        transposedGraph.addEdge(
            EdgeType(edge.destination(), edge.source(), edge.weight()));
      }
    }

    return transposedGraph;
  }

  std::vector<VertexType> FindPathBreadthFirst(VertexType start,
                                               VertexType destination) const {
    std::unordered_map<VertexType, VertexType> parent;
    std::queue<VertexType> queue;
    std::unordered_set<VertexType> visited;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
      VertexType current = queue.front();
      queue.pop();

      if (current == destination) {
        // Reconstruct the path
        std::vector<VertexType> path;
        for (VertexType at = destination; at != start; at = parent[at]) {
          path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
      }

      for (const auto &edge : adjList.at(current)) {
        VertexType neighbor = edge.destination();
        if (!visited.count(neighbor)) {
          parent[neighbor] = current;
          visited.insert(neighbor);
          queue.push(neighbor);
        }
      }
    }

    return {};  // No path found
  }

  std::vector<VertexType> FindPathDepthFirst(VertexType start,
                                             VertexType destination) const {
    std::unordered_map<VertexType, VertexType> parent;
    std::stack<VertexType> stack;
    std::unordered_set<VertexType> visited;

    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
      VertexType current = stack.top();
      stack.pop();

      if (current == destination) {
        // Reconstruct the path
        std::vector<VertexType> path;
        for (VertexType at = destination; at != start; at = parent[at]) {
          path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
      }

      for (const auto &edge : adjList.at(current)) {
        VertexType neighbor = edge.destination();
        if (!visited.count(neighbor)) {
          parent[neighbor] = current;
          visited.insert(neighbor);
          stack.push(neighbor);
        }
      }
    }

    return {};  // No path found
  }

  std::optional<std::vector<VertexType>> topologicalSort() const {
    // Topological sort is only valid for directed graphs
    if (!directed) {
      return std::nullopt;  // Cannot perform topological sort on undirected
                            // graphs
    }

    // Handle directed graphs: Kahn's algorithm
    std::unordered_map<VertexType, int> inDegree;
    for (const auto &[vertex, edges] : adjList) {
      inDegree[vertex];  // Ensure all vertices are in the map
      for (const auto &edge : edges) {
        inDegree[edge.destination()]++;
      }
    }

    std::queue<VertexType> zeroInDegree;
    for (const auto &[vertex, degree] : inDegree) {
      if (degree == 0) {
        zeroInDegree.push(vertex);
      }
    }

    std::vector<VertexType> sortedOrder;

    while (!zeroInDegree.empty()) {
      VertexType current = zeroInDegree.front();
      zeroInDegree.pop();
      sortedOrder.push_back(current);

      for (const auto &edge : adjList.at(current)) {
        VertexType neighbor = edge.destination();
        inDegree[neighbor]--;
        if (inDegree[neighbor] == 0) {
          zeroInDegree.push(neighbor);
        }
      }
    }

    // Check for cycles in directed graphs
    if (sortedOrder.size() != adjList.size()) {
      return std::nullopt;  // Cycle detected
    }

    return sortedOrder;
  }

 private:
  AdjacencyList adjList;
  bool directed = false;

  // Helper function to reverse an edge
  EdgeType reverseEdge(const EdgeType &edge) const {
    return EdgeType(edge.destination(), edge.source(), edge.weight());
  }

  // Helper functin for detecting cycles in directed graphs
  bool detectCycleDirected(
      const VertexType &vertex, std::unordered_set<VertexType> &visited,
      std::unordered_set<VertexType> &recursionStack) const {
    if (!visited.count(vertex)) {
      visited.insert(vertex);
      recursionStack.insert(vertex);

      for (const auto &edge : adjList.at(vertex)) {
        const VertexType &neighbor = edge.destination();
        if (!visited.count(neighbor) &&
            detectCycleDirected(neighbor, visited, recursionStack)) {
          return true;
        }
        if (recursionStack.count(neighbor)) {
          return true;  // Back edge found
        }
      }
    }

    recursionStack.erase(vertex);
    return false;
  }

  // Helper function for detecting cycles in undirected graphs
  bool detectCycleUndirected(const VertexType &vertex,
                             std::unordered_set<VertexType> &visited,
                             const VertexType &parent) const {
    visited.insert(vertex);

    for (const auto &edge : adjList.at(vertex)) {
      const VertexType &neighbor = edge.destination();
      if (!visited.count(neighbor)) {
        if (detectCycleUndirected(neighbor, visited, vertex)) {
          return true;
        }
      } else if (neighbor != parent) {
        return true;  // Found a back edge
      }
    }

    return false;
  }
};

}  // namespace Graphs

#endif  // GRAPH_H
