#include <gtest/gtest.h>

#include "../src/graph/graph.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Graph
struct Vertex {
  int id_ = 0;
  int in_degree_ = 0;
  int out_degree_ = 0;

  Vertex() = default;                          // Default constructor
  Vertex(int id) : id_(id) {}                  // Parameterized constructor
  Vertex(const Vertex &) = default;            // Copy constructor
  Vertex &operator=(const Vertex &) = default; // Copy assignment operator
  Vertex(Vertex &&) = default;                 // Move constructor
  Vertex &operator=(Vertex &&) = default;      // Move assignment operator

  // Destructor
  ~Vertex() = default;

  int id() const { return id_; }
  int inDegree() const { return in_degree_; }
  int outDegree() const { return out_degree_; }
  int netDegree() const { return out_degree_ - in_degree_; }

  bool operator==(const Vertex &other) const { return id_ == other.id_; }
  bool operator<(const Vertex &other) const { return id_ < other.id_; }
};

namespace std {
template <> struct hash<Vertex> {
  size_t operator()(const Vertex &v) const { return std::hash<int>{}(v.id()); }
};
} // namespace std

struct Edge {
  Vertex src{};

  Vertex dest{};
  double weight_ = 0.0;

  Edge() = default;

  Edge(const Vertex &source, const Vertex &destination, double weight)
      : src(source), dest(destination), weight_(weight) {}

  const Vertex &source() const { return src; }
  const Vertex &destination() const { return dest; }
  double weight() const { return weight_; }
  // important for equality checking
  bool operator==(const Edge &other) const {
    return src == other.src && dest == other.dest && weight_ == other.weight_;
  }
};

TEST(GraphTest, VertexAndEdgeSatisfyConcepts) {
  static_assert(std::move_constructible<Vertex>,
                "Vertex does not satisfy the std::move concept");
  static_assert(std::destructible<Vertex>,
                "Vertex does not satisfy the std::destructible concept");
  static_assert(
      std::default_initializable<Vertex>,
      "Vertex does not satisfy the std::default_initializable concept");
  static_assert(std::copy_constructible<Vertex>,
                "Vertex does not satisfy the std::copy_constructible concept");
  static_assert(
      Common::stl_container_storable<Vertex>,
      "Vertex does not satisfy the Common::stl_container_storable concept");
  static_assert(Common::Hashable<Vertex>,
                "Vertex does not satisfy the Common::Hashable concept");
  static_assert(Graphs::Identifiable<Vertex>,
                "Vertex does not satisfy the Graph::Identifiable concept");
  // Assert that Vertex satisfies the Vertex concept
  static_assert(Graphs::Vertex<Vertex>,
                "Vertex does not satisfy the Vertex concept");

  // Assert that Edge satisfies the GraphEdge concept with Vertex as the vertex
  // type
  static_assert(Graphs::GraphEdge<Vertex, Edge>,
                "Edge does not satisfy the GraphEdge concept with Vertex");
  static_assert(std::is_copy_constructible_v<Vertex>,
                "Vertex must be copy constructible");
  static_assert(std::is_copy_assignable_v<Vertex>,
                "Vertex must be copy assignable");
  static_assert(std::is_move_constructible_v<Vertex>,
                "Vertex must be move constructible");
  static_assert(std::is_move_assignable_v<Vertex>,
                "Vertex must be move assignable");
  // If the assertions pass, we can add a runtime assertion to confirm.
  SUCCEED() << "Vertex and Edge satisfy their respective concepts.";
}
// Test the constructor and isEmpty() method
TEST(GraphTest, ConstructAndIsEmpty) {
  Graphs::Graph<Vertex, Edge> graph;
  EXPECT_TRUE(graph.isEmpty());
  EXPECT_EQ(graph.getSize(), 0);
}

TEST(CycleDetectionTest, DirectedGraphPositiveCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  // Add edges: 1 -> 2 -> 3 -> 1
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v1, 1.0));

  EXPECT_TRUE(graph.detectCycle());
}

TEST(CycleDetectionTest, DirectedGraphNegativeCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  // Add edges: 1 -> 2 -> 3
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));

  EXPECT_FALSE(graph.detectCycle());
}

TEST(CycleDetectionTest, DirectedGraphDisconnectedPositiveCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  // Add edges: 1 -> 2 -> 3 -> 1 and 4 -> 5
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v1, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  EXPECT_TRUE(graph.detectCycle());
}

TEST(CycleDetectionTest, DirectedGraphDisconnectedNegativeCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  // Add edges: 1 -> 2 -> 3 and 4 -> 5
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  EXPECT_FALSE(graph.detectCycle());
}

TEST(CycleDetectionTest, UndirectedGraphPositiveCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  // Add edges: 1 - 2 - 3 - 1
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v1, 1.0));

  EXPECT_TRUE(graph.detectCycle());
}

TEST(CycleDetectionTest, UndirectedGraphNegativeCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  // Add edges: 1 - 2 - 3
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));

  EXPECT_FALSE(graph.detectCycle());
}

TEST(CycleDetectionTest, UndirectedGraphDisconnectedPositiveCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  // Add edges: 1 - 2 - 3 - 1 and 4 - 5
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v1, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  EXPECT_TRUE(graph.detectCycle());
}

TEST(CycleDetectionTest, UndirectedGraphDisconnectedNegativeCycle) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  // Add edges: 1 - 2 and 3 - 4
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));

  EXPECT_FALSE(graph.detectCycle());
}

TEST(GraphTest, GraphEqualityPositive) {
  Graphs::Graph<Vertex, Edge> graph1;
  Graphs::Graph<Vertex, Edge> graph2;

  graph1.setDirected(true);
  graph2.setDirected(true);

  Vertex v1(1), v2(2), v3(3);
  graph1.addVertex(v1);
  graph1.addVertex(v2);
  graph1.addVertex(v3);

  graph2.addVertex(v1);
  graph2.addVertex(v2);
  graph2.addVertex(v3);

  graph1.addEdge(Edge(v1, v2, 1.0));
  graph1.addEdge(Edge(v2, v3, 2.0));
  graph2.addEdge(Edge(v1, v2, 1.0));
  graph2.addEdge(Edge(v2, v3, 2.0));

  EXPECT_TRUE(graph1 == graph2);
}

TEST(GraphTest, GraphEqualityNegative) {
  Graphs::Graph<Vertex, Edge> graph1;
  Graphs::Graph<Vertex, Edge> graph2;

  graph1.setDirected(true);
  graph2.setDirected(true);

  Vertex v1(1), v2(2), v3(3);
  graph1.addVertex(v1);
  graph1.addVertex(v2);
  graph1.addVertex(v3);

  graph2.addVertex(v1);
  graph2.addVertex(v2);
  graph2.addVertex(v3);

  graph1.addEdge(Edge(v1, v2, 1.0));
  graph1.addEdge(Edge(v2, v3, 2.0));
  graph2.addEdge(Edge(v1, v2, 1.0));
  graph2.addEdge(Edge(v3, v1, 3.0)); // Different edge

  EXPECT_FALSE(graph1 == graph2);
}

TEST(GraphTest, GraphEqualityTakesWeightsIntoAccount) {
  Graphs::Graph<Vertex, Edge> graph1;
  Graphs::Graph<Vertex, Edge> graph2;

  graph1.setDirected(true);
  graph2.setDirected(true);

  Vertex v1(1), v2(2);
  graph1.addVertex(v1);
  graph1.addVertex(v2);
  graph2.addVertex(v1);
  graph2.addVertex(v2);

  // Add edges with different weights
  graph1.addEdge(Edge(v1, v2, 1.0));
  graph2.addEdge(Edge(v1, v2, 2.0)); // Different weight

  EXPECT_FALSE(graph1 == graph2);

  // Make weights identical
  graph2 = Graphs::Graph<Vertex, Edge>(); // Clear and rebuild the graph
  graph2.setDirected(true);
  graph2.addVertex(v1);
  graph2.addVertex(v2);
  graph2.addEdge(Edge(v1, v2, 1.0)); // Same weight
  EXPECT_TRUE(graph1 == graph2);
}

TEST(GraphTest, TransposeDirectedGraph) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 2.0));

  Graphs::Graph<Vertex, Edge> transposed = graph.transpose();

  // Expected transposed graph: 2 -> 1, 3 -> 2
  Graphs::Graph<Vertex, Edge> expectedTransposed;
  expectedTransposed.setDirected(true);
  expectedTransposed.addVertex(v1);
  expectedTransposed.addVertex(v2);
  expectedTransposed.addVertex(v3);
  expectedTransposed.addEdge(Edge(v2, v1, 1.0));
  expectedTransposed.addEdge(Edge(v3, v2, 2.0));

  EXPECT_TRUE(transposed == expectedTransposed);
}

TEST(GraphTest, TransposeUndirectedGraph) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 2.0));

  Graphs::Graph<Vertex, Edge> transposed = graph.transpose();

  // Transpose of an undirected graph is the same graph
  EXPECT_TRUE(graph == transposed);
}

TEST(GraphTest, TransposeUndirectedGraphIsSame) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(false);

  Vertex v1(1), v2(2), v3(3);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);

  // Add undirected edges
  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 2.0));
  graph.addEdge(Edge(v1, v3, 3.0));

  // Transpose of an undirected graph should be the same
  Graphs::Graph<Vertex, Edge> transposed = graph.transpose();
  EXPECT_TRUE(graph == transposed);
}

TEST(GraphPathTest, BreadthFirstSearchPathExists) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  auto path = graph.FindPathBreadthFirst(v1, v5);
  std::vector<Vertex> expectedPath = {v1, v2, v3, v4, v5};

  EXPECT_EQ(path, expectedPath);
}

TEST(GraphPathTest, BreadthFirstSearchPathDoesNotExist) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));

  auto path = graph.FindPathBreadthFirst(v1, v5);

  EXPECT_TRUE(path.empty());
}

TEST(GraphPathTest, DepthFirstSearchPathExists) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  auto path = graph.FindPathDepthFirst(v1, v5);
  std::vector<Vertex> expectedPath = {v1, v2, v3, v4, v5};

  EXPECT_EQ(path, expectedPath);
}

TEST(GraphPathTest, DepthFirstSearchPathDoesNotExist) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v3, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));

  auto path = graph.FindPathDepthFirst(v1, v5);

  EXPECT_TRUE(path.empty());
}

TEST(GraphPathTest, BreadthFirstSearchShortestPath) {
  Graphs::Graph<Vertex, Edge> graph;
  graph.setDirected(true);

  Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
  graph.addVertex(v1);
  graph.addVertex(v2);
  graph.addVertex(v3);
  graph.addVertex(v4);
  graph.addVertex(v5);

  graph.addEdge(Edge(v1, v2, 1.0));
  graph.addEdge(Edge(v2, v5, 1.0));
  graph.addEdge(Edge(v1, v3, 1.0));
  graph.addEdge(Edge(v3, v4, 1.0));
  graph.addEdge(Edge(v4, v5, 1.0));

  auto path = graph.FindPathBreadthFirst(v1, v5);
  std::vector<Vertex> expectedPath = {v1, v2, v5}; // BFS finds shortest path

  EXPECT_EQ(path, expectedPath);
}

TEST(GraphTest, TransposeGraphWithCycle) {
    Graphs::Graph<Vertex, Edge> graph;
    graph.setDirected(true);

    Vertex v1(1), v2(2), v3(3);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);

    // Create a cycle: 1 -> 2 -> 3 -> 1
    graph.addEdge(Edge(v1, v2, 1.0));
    graph.addEdge(Edge(v2, v3, 1.0));
    graph.addEdge(Edge(v3, v1, 1.0));

    Graphs::Graph<Vertex, Edge> transposed = graph.transpose();

    // Expected transposed graph: 1 <- 2 <- 3 <- 1
    Graphs::Graph<Vertex, Edge> expectedTransposed;
    expectedTransposed.setDirected(true);
    expectedTransposed.addVertex(v1);
    expectedTransposed.addVertex(v2);
    expectedTransposed.addVertex(v3);
    expectedTransposed.addEdge(Edge(v2, v1, 1.0));
    expectedTransposed.addEdge(Edge(v3, v2, 1.0));
    expectedTransposed.addEdge(Edge(v1, v3, 1.0));

    EXPECT_TRUE(transposed == expectedTransposed);
}

TEST(GraphTest, TopologicalSortDirectedGraph) {
    Graphs::Graph<Vertex, Edge> graph;
    graph.setDirected(true);

    Vertex v1(1), v2(2), v3(3), v4(4), v5(5);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(v4);
    graph.addVertex(v5);

    // Add edges to form a DAG: 1 -> 2, 1 -> 3, 3 -> 4, 2 -> 5
    graph.addEdge(Edge(v1, v2, 1.0));
    graph.addEdge(Edge(v1, v3, 1.0));
    graph.addEdge(Edge(v3, v4, 1.0));
    graph.addEdge(Edge(v2, v5, 1.0));

    auto result = graph.topologicalSort();
    ASSERT_TRUE(result.has_value());

    std::vector<Vertex> expectedOrder = {v1, v2, v3, v5, v4};
    EXPECT_EQ(result.value(), expectedOrder);
}

TEST(GraphTest, TopologicalSortCycleInDirectedGraph) {
    Graphs::Graph<Vertex, Edge> graph;
    graph.setDirected(true);

    Vertex v1(1), v2(2), v3(3);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);

    // Add edges to form a cycle: 1 -> 2 -> 3 -> 1
    graph.addEdge(Edge(v1, v2, 1.0));
    graph.addEdge(Edge(v2, v3, 1.0));
    graph.addEdge(Edge(v3, v1, 1.0));

    auto result = graph.topologicalSort();
    EXPECT_FALSE(result.has_value());
}

TEST(GraphTest, TopologicalSortUndirectedGraphFails) {
    Graphs::Graph<Vertex, Edge> graph;
    graph.setDirected(false);

    Vertex v1(1), v2(2), v3(3), v4(4);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(v4);

    // Add edges to form an undirected acyclic graph: 1 - 2, 1 - 3, 3 - 4
    graph.addEdge(Edge(v1, v2, 1.0));
    graph.addEdge(Edge(v1, v3, 1.0));
    graph.addEdge(Edge(v3, v4, 1.0));

    auto result = graph.topologicalSort();
    EXPECT_FALSE(result.has_value()); // Topological sort not valid for undirected graphs
}


