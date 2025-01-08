/* implementing dijkstra algorithm */
#include <iostream>
#include <climits>
#include <array>
#include <tuple>

// number of node 
const int N=8;

std::tuple<std::array<int, N>, std::array<int, N>> dijkstra_shortest_path(std::array<std::array<int, N>, N>&, int);
int min_vertex(const std::array<bool, N>&,const std::array<int, N>&);
void print_path(const std::array<std::string, N>&, const std::array<int, N>&, const std::array<int, N>&, int);
void rpp(const std::array<int, N> &, const std::array<std::string, N> &, int, int);

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
    
    int source = 0; // start from node A
    auto [previous, distance] = dijkstra_shortest_path(adj_matrix, source);
    print_path(label, previous, distance, source);

    std::cout << std::endl;
    return 0;
}
std::tuple<std::array<int, N>, std::array<int, N>> dijkstra_shortest_path(std::array<std::array<int,N>, N> &adj_matrix, int source){
    std::array<int, N> previous;
    std::array<int, N> distance;
    std::array<bool, N> visited;

    visited.fill(false);
    distance.fill(INT_MAX);
    previous.fill(0);

    distance[source] = 0;
    for (int i=0; i<N; ++i){
        int mV = min_vertex(visited, distance);
        visited[mV] = true;
        for (int j=0; j<N; ++j){
            int new_distance = distance[mV] + adj_matrix[mV][j];
            if (!visited[j] && adj_matrix[mV][j] != -1 && new_distance < distance[j]){
                distance[j] = new_distance;
                previous[j] = mV;
            }
        }
    }
    return {previous, distance}; 
}

int min_vertex(const std::array<bool, N> &visited,const std::array<int, N> &distance){
    int min = -1;
    for (int i=0; i<N; ++i){
        if (!visited[i] && (min == -1 || distance[i] < distance[min])){
            min = i;
        }
    }
    return min;
}

void print_path(const std::array<std::string, N> &label, const std::array<int, N> &previous, const std::array<int, N> &distance, int source){
    for (int i=source; i<N; ++i){
        std::cout << label[source] << " to " << label[i] << " :";
        std::cout << label[source];
        rpp(previous, label, source, i);
        std::cout << "\nwith distance of " << distance[i] << "\n\n";
    }
}
void rpp(const std::array<int, N> &previous, const std::array<std::string, N> &label, int source, int i){
    if (i == source) return;
    rpp(previous, label, source, previous[i]);
    std::cout << " -> " << label[i];
}
