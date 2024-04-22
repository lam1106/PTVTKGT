#include <iostream>
#include <vector>
#include <algorithm>

template<typename T=int>
class edgeType {
private:
    char from;
    char to;
    T w;
public:
    edgeType(char a, char b, int c): from(a), to(b), w(c) {} 
    T getW() const { return w; }
    char getFrom() const { return from; }
    char getTo() const { return to; }
    bool operator < (const edgeType<T>& right) const {
        return w < right.getW();
    }
};

template<typename T>
void printMST(const std::vector<edgeType<T> >& mst) {
    for(size_t i = 0; i < mst.size(); ++i) {
        std::cout << "(" << mst[i].getFrom() << "," << mst[i].getTo() << "," << mst[i].getW() << ") ";
    }
    std::cout << std::endl;
}

int union_find(const int& from, std::vector<int>& arr){
    if(arr[from] == from){
        return from;
    }
    return union_find(arr[from], arr);
}

void union_set(const int& from, const int& to, std::vector<int>& arr){    
    arr[union_find(to, arr)] = arr[from];
}

template<typename T>
std::vector<edgeType<T> > kruskal(const std::vector<char>& nodes, std::vector<edgeType<T> >& edges){
    std::vector<edgeType<T> > mst;
    std::vector<int> arr(nodes.size());
    for (size_t i = 0; i < nodes.size(); ++i) {
        arr[i] = i;
    }
    std::sort(edges.begin(), edges.end());
    for(size_t j = 0; j < edges.size(); ++j){
        int from = edges[j].getFrom() - 'A';
        int to = edges[j].getTo() - 'A';
        T w = edges[j].getW();
        if( union_find(from, arr) != union_find(to, arr)){
            mst.push_back(edgeType<T>(edges[j].getFrom(), edges[j].getTo(), w));
            union_set(from, to, arr);
            std::cout << "Adding edge (" << edges[j].getFrom() << "," << edges[j].getTo() << "," << edges[j].getW() << ")" << std::endl;
            std::cout << "Current MST: ";
            printMST(mst);
        } else {
            std::cout << "Skipping edge (" << edges[j].getFrom() << "," << edges[j].getTo() << "," << edges[j].getW() << ") to avoid cycle" << std::endl;
        }
    }
    return mst;
}

int main() {    
	int num_vertices, num_edges;

	std::cout << "Enter the number of vertices: ";
	std::cin >> num_vertices;

  // Validate vertex count (should be positive)
	if (num_vertices <= 0) {
		std::cerr << "Error: Number of vertices must be positive." << std::endl;
		return 1;
	}

  	std::cout << "Enter the number of edges: ";
 	std::cin >> num_edges;

  // Validate edge count (should be non-negative)
  	if (num_edges < 0) {
    	std::cerr << "Error: Number of edges cannot be negative." << std::endl;
    	return 1;
  	}

  	std::vector<char> nodes(num_vertices);
  	for (int i = 0; i < num_vertices; ++i) {
    	nodes[i] = 'A' + i; // Assign node labels (A, B, C, ...)
  	}

  	std::vector<edgeType<int> > edges;
  	char from, to;
  	int weight;

    std::cout << "Enter edges (from to weight): " << std::endl;
    while (true) {
        std::cin >> from >> to >> weight;
//        if (from == '0' && to == '0' && weight == 0)
//            break;
        edges.push_back(edgeType<int>(from, to, weight));
    }
	std::sort(edges.begin(), edges.end()); // Sort edges by weight
	std::vector<edgeType<int> > mst_k = kruskal(nodes, edges);    
	std::cout << "Final MST: ";
	printMST(mst_k);
	return 0;

}

