#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <climits>

const int N=8;

struct Edge {
    int a, b, weight;
    Edge(int a, int b, int weight) : a(a), b(b), weight(weight){}
};

std::vector<struct Edge> kruskal_mst(const std::array<std::array<int, N>, N> &);
int find(int, std::array<int, N> &);
void unite(int, int, std::array<int, N> &, std::array<int, N> &);
void print_mst(const std::array<std::string, N> &,const std::vector<struct Edge> &);

int main(int argc, char **argv){
    std::array<std::string, N> label = {{"A", "B", "C", "D", "E", "F", "G", "H"}}; // node label

    // graph adjacent matrix
    std::array<std::array<int, N>, N> adj_matrix = {{
    //    a   b   c   d   e   f   g   h
        { 0,  1, -1,  5, -1,  2, -1, -1}, // a
        { 1,  0, -1, -1,  2, -1, -1, -1}, // b
        {-1, -1,  0, -1,  4, -1, -1,  1}, // c
        { 5, -1, -1,  0,  3, -1,  2, -1}, // d
        {-1,  2,  4,  3,  0, -1,  2, -1}, // e
        { 2, -1, -1, -1, -1,  0,  4, -1}, // f
        {-1, -1, -1,  2,  2,  4,  0,  5}, // g
        {-1, -1,  1, -1, -1, -1,  5,  0}  // h
    }}; 

    auto result = kruskal_mst(adj_matrix);
    print_mst(label, result);

    return 0;
}

std::vector<struct Edge> kruskal_mst(const std::array<std::array<int, N>, N> &adj_matrix){
    auto compare = [](const struct Edge &e1, const struct Edge &e2) -> bool{
        return e1.weight > e2.weight; // higher weight lower priority
    };
    // to store all edge sorted by weight
    std::priority_queue<struct Edge, std::vector<struct Edge>, decltype(compare)> pq(compare);
    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            // push edge to queue
            if (i != j && adj_matrix[i][j] != -1){
                pq.emplace(i, j, adj_matrix[i][j]); // push by constructor 
            }
        }
    } 

    std::array<int, N> parent;
    std::array<int, N> rank;
    for (int i=0; i<N; ++i){
        parent[i] = i;
        rank[i] = 0;
    }

    std::vector<struct Edge> mst;

    while (!pq.empty() && mst.size() < N-1){
        const auto &e = pq.top(); 

        int set_a = find(e.a, parent);
        int set_b = find(e.b, parent);

        if (set_a != set_b){
            mst.push_back(e);
            unite(set_a, set_b, parent, rank);
        }
        // std::cout << e.a << " to " << e.b << " is " << e.weight << std::endl;
        pq.pop();
    }
    return mst;
}

int find(int u, std::array<int, N> &parent){
    if (parent[u] != u){
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

// Union by rank
void unite(int u, int v, std::array<int, N> &parent, std::array<int, N> &rank){
    if (rank[u] < rank[v]){
        parent[u] = v;
    }else if (rank[u] > rank[v]){
        parent[v] = u;
    }else{
        parent[v] = u;
        ++rank[u];
    }
}

void print_mst(const std::array<std::string, N> &label, const std::vector<struct Edge> &mst){
    std::cout << "Edge \tWeight\n";
    for (const auto &e : mst){
        std::cout << label[e.a] << " - " << label[e.b] << " \t" << e.weight << " \n";
    }
}
