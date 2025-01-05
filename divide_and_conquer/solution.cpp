#include <iostream>
#include <queue>
#include <vector>

template <typename Compare>
void print_heap(std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Compare>);
void print_vector(const std::vector<std::vector<int>> &);

std::vector<std::vector<int>> pq(std::vector<std::vector<int>> &, int);
std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &, int);
std::vector<std::vector<int>> partition_caller(std::vector<std::vector<int>> &, int);
int partition(std::vector<std::vector<int>> &, int, int);
int compare(std::vector<int> &, std::vector<int>&);

int main(int argc, char **argv){
    std::vector<std::vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
    int k = 2;
        
    auto ans = kClosest(points, k);
    print_vector(ans);
    return 0;
}

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &points, int k){
    return pq(points, k);
    // return partition_caller(points, k);
}

std::vector<std::vector<int>> pq(std::vector<std::vector<int>> &points, int k){
    std::vector<std::vector<int>> ans;
    // heap comparator
    auto compare = [](const std::vector<int> &p1, const std::vector<int> &p2){
        return p2[0]*p2[0]+p2[1]*p2[1] > p1[0]*p1[0]+p1[1]*p1[1];
    };
    std::priority_queue<
        std::vector<int>, 
        std::vector<std::vector<int>>,
        decltype(compare)
     > heap(compare);

    // push points to heap
    for (auto &a : points){
        heap.push(a);
        // pop the exceed 
        if (heap.size() == k+1){
            heap.pop();
        }
    }
    while (!heap.empty()){
        ans.insert(ans.begin(), heap.top());
        heap.pop();
    }
    return ans;
}

std::vector<std::vector<int>> partition_caller(std::vector<std::vector<int>> &points, int k){
    int left = 0;
    int right = points.size() - 1;

    while (left <= right){
        int pivot = partition(points, left, right); 
        if (pivot < k)
            left = pivot+1;
        else if (k < pivot)
            right = pivot - 1;
        else 
            break;
    }
    return std::vector<std::vector<int>>(points.begin(), points.begin()+k);
}

int partition(std::vector<std::vector<int>> &points, int left, int right){
    /* code here */
    std::vector<int> t = points[left];
    
    int i = left + 1;
    int j = right;

    while (i<=j){
        while (i<=right && compare(points[i], t) <= 0) ++i;
        while (j>=left && compare(points[j], t) > 0) --j;
        if ( i < j) std::swap(points[i], points[j]);
        else std::swap(points[left], points[j]);
    }
    return j;
}

int compare(std::vector<int> &p1, std::vector<int> &p2){
    return (p1[0] * p1[0] + p1[1] * p1[1] - p2[0] * p2[0] - p2[1] * p2[1]);
}


template <typename Compare>
void print_heap(std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Compare> heap){
    while (!heap.empty()){
        const auto &top = heap.top();
        std::cout << "(" << top[0] << ", " << top[1] << ")" << std::endl;
        heap.pop(); 
    }
}
void print_vector(const std::vector<std::vector<int>> &vector){
    std::cout << "{" ;

    for (const auto &a : vector){
        std::cout << "{" << a[0] << ", " << a[1] << "}, ";
    }
    std::cout << "\b\b}" << std::endl;
}
