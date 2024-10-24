#include "VamanaIndexing.h"
#include "printGraph.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int L, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, data.size(), R);

    // Find Medoid on Graph
    int s = Medoid(data, Graph);
    //int s = 8736;

    // Sigma (σ) is a random permutation of points 1..n (data size = n = the points in the dataset)
    vector<int> sigma = random_permutation(data);

    int size = data.size();
    for(int i = 0; i < size; i++){
        
        // Call Greedy Search giving arguments: x_0σ(i), s = medoid, k = 1 and L
        auto [result_set, visited_nodes] = GreedySearch(Graph, data[sigma[i]], data, s, 1, L);

        // Call Robust Prune to update out-neighbors of σ[i] (sigma[i])
        float a = 1.0;                       // Distance threshold a >= 1
        vector<int> V = result_set;          // Nearest Neighbors of sigma[i]

        Graph = RobustPrune(sigma[i], V, a, R, Graph);

        // For every Nearest Neighbor j of sigma[i]
        int Vsize = V.size();
        for(int j = 0; j < Vsize; j++){

            int NearNeighbor = V[j];

            // If the number of Nearest Neighbors j with sigma[i] (an extra neighbor) is greater that R
            int NNsize = Graph[NearNeighbor].size();
            if ( NNsize + 1 > R){

                // Create a vector with all the neighbors of the NearNeighbor (V[j])
                vector<int> neighbors(Graph[NearNeighbor].size());
                for (const edge& e : Graph[NearNeighbor]){
                    neighbors.push_back(e.first);
                }
                
                // Add sigma[i] to the neighbors
                neighbors.push_back(sigma[i]);

                // Call Robust Prune to update out-neighbors of NearNeighbor (V[j])
                Graph = RobustPrune(NearNeighbor, neighbors, a, R, Graph);

            }else{
                // Else add sigma[i] in the neighbors of NearNeighbor (V[j]) without pruning
                float distance = EuclideanDistance(data[NearNeighbor],data[sigma[i]]);

                Graph[NearNeighbor].emplace_back(sigma[i], distance);
            }
        }
    }
    return Graph;
}



// Function to create a random permutation of data
vector<int> random_permutation(const vector<vector<float>>& data){

    vector<int> s(data.size());

    int size = data.size();
    for(int i = 0; i <= size; ++i){
        s[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());

    // Suffle vector
    shuffle(s.begin(), s.end(), gen);

    return s;
}