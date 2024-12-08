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
  Vertex() = default;

  Vertex(int id) : id_(id) {}

  // Copy constructor
  Vertex(const Vertex &) = default;

  // Move constructor
  Vertex(Vertex &&) = default;

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
