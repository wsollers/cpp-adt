#ifndef GRAPH_H
#define GRAPH_H

#include <concepts>
#include <optional>

namespace Graphs {

// Concept for Identifiable types
template <typename T>
concept Identifiable = requires(T obj) {
    // Must have an id() method
    { obj.id() } -> std::equality_comparable; // ID must be equality comparable
};

template <typename T>
concept IdentifiableSortable = Identifiable<T> && requires(T obj) {
    { obj.id() } -> std::totally_ordered; // ID must support <, <=, >, >=
};

// Concept for a Vertex
template <typename T>
concept Vertex = requires(T vertex) {
    // Must provide access to in-degree
    { vertex.inDegree() } -> std::convertible_to<int>;
    // Must provide access to out-degree
    { vertex.outDegree() } -> std::convertible_to<int>;
    // Must provide access to net-degree (out-degree - in-degree)
    { vertex.netDegree() } -> std::convertible_to<int>;
};

template <typename T, typename Vertex>
concept GraphEdge = requires(T edge, Vertex v) {
    // Must provide access to the source and destination vertices
    { edge.source() } -> std::convertible_to<Vertex>;
    { edge.destination() } -> std::convertible_to<Vertex>;

    // Must optionally provide access to a weight (or no weight at all)
    { edge.weight() } -> std::convertible_to<std::optional<double>>;
};

template <typename Vertex, typename Edge>
requires GraphEdge<Edge, Vertex>
class Graph {
public:
    using AdjacencyList = std::unordered_map<Vertex, std::vector<Edge>>;

    // Add a vertex to the graph
    void addVertex(const Vertex& vertex) {
        adjList_.emplace(vertex, std::vector<Edge>{});
    }

    // Add an edge to the graph
    void addEdge(const Edge& edge) {
        adjList_[edge.source()].push_back(edge);
        if (!directed_) {
            adjList_[edge.destination()].push_back(reverseEdge(edge));
        }
    }

    // Print the graph's adjacency list
    void printGraph() const {
        for (const auto& [vertex, edges] : adjList_) {
            std::cout << vertex << ": ";
            for (const auto& edge : edges) {
                std::cout << "(" << edge.destination();
                if (edge.weight()) {
                    std::cout << ", weight: " << *edge.weight();
                }
                std::cout << ") ";
            }
            std::cout << "\n";
        }
    }

    // Set the graph as directed or undirected
    void setDirected(bool directed) {
        directed_ = directed;
    }

private:
    // Adjacency list representation
    AdjacencyList adjList_;
    bool directed_ = false;

    // Create a reverse edge for undirected graphs
    Edge reverseEdge(const Edge& edge) const {
        if constexpr (std::is_void_v<decltype(edge.weight())>) {
            return Edge(edge.destination(), edge.source());
        } else {
            return Edge(edge.destination(), edge.source(), *edge.weight());
        }
    }
};


} // namespace Graphs

#endif // GRAPH_H
