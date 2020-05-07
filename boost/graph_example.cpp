#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <iostream>

// Boost::graph examples.
//
// See boost 1.65.0 documentation:
// https://www.boost.org/doc/libs/1_65_0/libs/graph/doc/adjacency_list.html
//
// Helpful tutorials:
// https://www.boost.org/doc/libs/1_65_0/libs/graph/doc/quick_tour.html
// https://www.boost.org/doc/libs/1_65_0/libs/graph/doc/using_adjacency_list.html
// https://www.technical-recipes.com/2015/getting-started-with-the-boost-graph-library
// https://www.informit.com/articles/article.aspx?p=25756&seqNum=7

using namespace boost;

// Directed graph with vertex data. The data is stored as bundled properties
// which are carried along with the graph (as opposed to external
// properties, which are maintained in maps).
//
// See Bundled Properties:
// https://www.boost.org/doc/libs/1_65_0/libs/graph/doc/bundles.html

struct VertexProperty {
    VertexProperty(int32_t id, const std::string& name) : id(id), name(name) {}
    VertexProperty() : id(), name() {}
    int32_t id;
    std::string name;
};

typedef adjacency_list<listS, listS, directedS, VertexProperty> DirectedGraph;

template <typename Graph>
class PropertyWriter {
   public:
    PropertyWriter(const Graph& g) : g(g){};

    template <typename Vertex>
    void operator()(std::ostream& out, const Vertex& v) {
        // Node header
        out << " [" << std::endl;
        // Vertex data
        out << "  label = \"ID: " << g[v].id << "\\l";
        out << "name: " << g[v].name << "\\l";
        out << "\"" << std::endl;
        // Node style
        out << "  shape = \"record\"" << std::endl;
        out << "  style = \"filled,rounded\" ]" << std::endl;
    }

   private:
    const Graph& g;
};

template <typename Graph>
void printGraph(Graph g) {
    typedef typename Graph::edge_iterator EdgeIterator;
    typedef typename Graph::vertex_iterator VertexIterator;

    // Print the number of edges
    std::cout << "Number of edges = " << num_edges(g) << "\n";

    // One liner for printing all vertice descriptors (line 2):
    //   1: std::pair<EdgeIterator, EdgeIterator> ei = edges(g);
    //   2: std::copy(ei.first, ei.second, std::ostream_iterator<typename Graph::edge_descriptor>{std::cout, "\n"});
    // When vertex container type is vecS, this handily prints the vertex indices.
    // However, when the container is listS, the vertex descriptors are pointers.

    // Print the edges
    std::pair<EdgeIterator, EdgeIterator> ei = edges(g);
    std::cout << std::endl << "Edge list:\n";
    for (auto edge = ei.first; edge != ei.second; ++edge) {
        typename Graph::vertex_descriptor srcVertexDescr = source(*edge, g);
        typename Graph::vertex_descriptor dstVertexDescr = target(*edge, g);
        std::cout << g[srcVertexDescr].id << " -> " << g[dstVertexDescr].id << std::endl;
    }

    // Print the number of vertices
    std::pair<VertexIterator, VertexIterator> vertIters = vertices(g);
    std::cout << std::endl << "Number of vertices = " << num_vertices(g) << "\n";

    // Print vertices and their associated data
    std::cout << std::endl << "Vertices list:\n";
    for (auto vertIter = vertIters.first; vertIter != vertIters.second; ++vertIter) {
        // *vertIter returns vertex_descriptor, which in case of vecS is an int index.
        typename Graph::vertex_descriptor vertDescr = *vertIter;
        std::cout << g[vertDescr].id << ": " << g[vertDescr].name << std::endl;
    }

    std::cout << std::endl;
}

void graph_with_vertex_data() {
    DirectedGraph g;
    std::array<DirectedGraph::vertex_descriptor, 6> vertices;

    vertices[0] = add_vertex(VertexProperty(0, "A"), g);
    vertices[1] = add_vertex(VertexProperty(1, "B"), g);
    vertices[2] = add_vertex(VertexProperty(2, "C"), g);
    vertices[3] = add_vertex(VertexProperty(3, "D"), g);
    vertices[4] = add_vertex(VertexProperty(4, "E"), g);
    vertices[5] = add_vertex(VertexProperty(5, "F"), g);

    add_edge(vertices[0], vertices[2], g);
    add_edge(vertices[2], vertices[4], g);
    add_edge(vertices[1], vertices[4], g);
    add_edge(vertices[3], vertices[5], g);
    add_edge(vertices[5], vertices[1], g);

    printGraph<DirectedGraph>(g);

    // Plot the graph to .dot.
    PropertyWriter<DirectedGraph> pw(g);
    std::ofstream out("graph_example_with_data.dot");
    boost::default_writer vw;
    boost::default_writer gw;
    write_graphviz(out, g, pw, vw, gw, get(&VertexProperty::id, g));

    // Remove edges and vertices.
    std::cout << "Remove edge (2, 4)." << std::endl;
    remove_edge(vertices[2], vertices[4], g);

    std::cout << "Remove vertex 5 and its edges." << std::endl;

    // IMPORTANT: When a vertex is removed, we must remove its edges as well!
    // Edges first, then the vertex itself.
    remove_edge(vertices[3], vertices[5], g);
    remove_edge(vertices[5], vertices[1], g);
    remove_vertex(vertices[5], g);

    std::cout << std::endl;

    printGraph<DirectedGraph>(g);
}

void basic_graph() {
    // Directed graph using adjacency_list.
    // Vertices and edges are stored in vector structures (boost::vecS selector),
    // hence vertex and edge descriptors are plain ints (indices).
    //
    typedef adjacency_list<vecS, vecS, directedS> SimpleDirectedGraph;
    SimpleDirectedGraph g;

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(1, 3, g);
    add_edge(2, 4, g);
    add_edge(2, 5, g);
    add_vertex(g);

    std::ofstream out("graph_example_simple.dot");
    write_graphviz(out, g);
}

int main() {
    basic_graph();
    graph_with_vertex_data();

    return 0;
}
