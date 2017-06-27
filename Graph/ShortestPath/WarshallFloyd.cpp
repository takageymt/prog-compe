typedef vector< vector<int> > Graph;

bool warshallfloyd(Graph& graph)
{
  for(int i = 0; i < graph.size(); i++){
    for(int j = 0; j < graph.size(); j++){
      for(int k = 0; k < graph.size(); k++){
	graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
      }
      if(graph[j][j] < 0) return false;
    }
  }
  return true;
}
