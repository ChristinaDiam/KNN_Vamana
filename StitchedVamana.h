#ifndef STITCHEDVAMANA_H
#define STITCHEDVAMANA_H

#include "medoid.h"
#include "VamanaIndexing.h"  // Include the old Vamana (from part 1)

// Stitched Vamana Indexing algorithm
vector <graph> StitchedVamana(vector<vector<float>> &nodes, float a, int L_small, int R_small, int R_stitched, int medoid);

#endif