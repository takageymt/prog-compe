#include <iostream>
#include <algorithm>
#include <vector>

typedef vector< vector<int> > Graph;

void warshallfloyd(Graph& G)
{
  for(int i = 0; i < G.size(); i++){
    for(int j = 0; j < G.size(); j++){
      for(int k = 0; k < G.size(); k++){
	G[j][k] = min(G[j][k], G[j][i] + G[i][k]);
      }
    }
  }
}
