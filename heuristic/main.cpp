#include "heuristic_methods.hpp"
#include <iostream>
#include <vector>

int main(void){
    /* -------- -> 11, 9, 20, 20, 9, 11, 21, 14 
                -> 2, 9, 2, 2, 9, 2, 3, 5   
     */
    std::vector<int> s = {{2, 9, 2, 2, 9, 2, 3, 5}};
    BinPacking b(s); // create object
    b.ff();
    b.print_result();
    b.bf();
    b.print_result();
    b.ffd();
    b.print_result();

    JobScheduling js(s);
    js.solve();
    js.print_result();

    return 0;
}
    // std::vector<int> e_s = {{2, 6, 6, 5, 8, 1, 2, 1, 9}};
    // std::vector<int> j = {{3, 7, 8, 6, 5, 4}};
