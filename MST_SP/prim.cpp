#include <iostream>
#include <array>
#include <climits>

// number of node
const int N = 8;

std::array<int, N> prims_mst(const std::array<std::array<int, N>, N> &);
int min_distance(const std::array<int, N> &, const std::array<bool, N> &);
void print_mst(const std::array<std::string, N> &,const std::array<std::array<int, N>, N> &, const std::array<int, N> &);

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

    auto result = prims_mst(adj_matrix);
    print_mst(label, adj_matrix, result);

    return 0;
}

std::array<int, N> prims_mst(const std::array<std::array<int, N>, N> &adj_matrix){
    std::array<int, N> parent;
    std::array<int, N> distance; 
    std::array<bool, N> visited;

    distance.fill(INT_MAX);
    visited.fill(false);
 
    distance[0] = 0;
    parent[0] = -1;

    for (int i=0; i<N-1; ++i){
        int u = min_distance(distance, visited);
        visited[u] = true;

        for (int j=0; j<N; ++j){
            if (adj_matrix[u][j] != -1 && adj_matrix[u][j] != 0 && !visited[j] && adj_matrix[u][j] < distance[j]){
                parent[j] = u;
                distance[j] = adj_matrix[u][j];
            }
        }
    }
    return parent;
}

int min_distance(const std::array<int, N> &distance, const std::array<bool, N> &visited){
    int min = INT_MAX;
    int min_index;

    for (int i=0; i<N; ++i){
        if (!visited[i] && distance[i] < min){
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_mst(const std::array<std::string, N> &label, const std::array<std::array<int, N>, N> &adj_matrix, const std::array<int, N> &parent){
    std::cout << "Edge \tWeight\n";
    for (int i=1; i<N; ++i){
        std::cout << label[parent[i]] << " - " << label[i] << " \t" << adj_matrix[parent[i]][i] << " \n";
    }
}
