/*
Output:

  (R, Z, B) (Q, Y, A) (P, X)

*/

#include <iostream>
#include <vector>
#include <map>


using namespace std;
/*
  y (5) -> x (4)
  x (4) -> a (3) -> b (1) -> c (0)
  b (1) -> d (0)
  e (5) -> f (4) -> a (3) -> g (2) -> b (1)
*/

/*
  [
    2 => (c, d)
    1 => (b)
    0 => (a)
  ]
*/
 class Graph {
  
  map<char, vector<char>> mapping;
  map<char, bool> visited;
  bool isCyclic;
  
  
  public:
    Graph() {
     isCyclic = false;
   }
  
  void addEdges(char from, char to) {
    if (mapping[from].size() == 0) {
      vector<char> edges;
      edges.push_back(to);
      mapping[from] = edges;
    } else {
     mapping[from].push_back(to);
    }
  }
  
  // void removeEdges(char from, char to) {
    
  // }
  
  public:
    map<int, vector<char>> getOrderOfExecution() {
      map<int, vector<char>> result;
      
        // for (auto it = mapping.begin(); it != mapping.end(); it++) {
        //   cout << it->first << ": ";
        //   for (int i = 0; i < it->second.size(); i++) {
        //     cout << it->second[i] << ", ";
        //   }
        //   cout << endl;
        // }
      
      for (auto i = mapping.begin(); i != mapping.end(); i++) {
        if (isCyclic) {
          map<int, vector<char>> emptyResult;
          cout << "isCyclic" << endl;
          return emptyResult;
        }
        cout << i->first  << endl;
         dfs(i->first, result);
      }
      
      return result;
    }
   
   private:
    int dfs(char node, map<int, vector<char>> &result) {
      
      if (visited[node]) {
        // Check for cyclic 
        isCyclic = true;
        return 0;
      }
      
      visited[node] = true;
      //cout << node << endl;
      
      if (mapping[node].size() == 0) {
        if (result[0].size() == 0) {
          vector<char> res;
          res.push_back(node);
          result[0] = res;
        } else {
          // Check for duplicate before adding node
          result[0].push_back(node);
        }
        visited[node] = false;
        return 1;
      }
      
      int maxLevel = 0;
      
      for (int i = 0; i < mapping[node].size(); i++) {
        char nextnode = mapping[node][i];
        if (isCyclic)
          return 0;
        else {
          int val = dfs(nextnode, result);
          maxLevel = max(val, maxLevel);
        }
      }
      
      if (result[maxLevel].size() == 0) {
          vector<char> res;
          res.push_back(node);
          result[maxLevel] = res;
        } else {
          // Check for duplicate before adding node
          auto it = g.find(result[maxLevel].begin(), result[maxLevel].end(), node);
          if (this.isValidNode(node))
        	result[maxLevel].push_back(node);
      }
      
      visited[node] = false;
      
      return maxLevel + 1;
  }
};

int main() {
  
  // std::cout << "Hello world" << std::endl;
  Graph g;
  g.addEdges('P', 'Q');
  g.addEdges('P', 'R');
  g.addEdges('Q', 'R');
  g.addEdges('X', 'Y');
  g.addEdges('X', 'Z');
  g.addEdges('Y', 'Z');
  g.addEdges('A', 'B');
  
  map<int, vector<char>> result = g.getOrderOfExecution();
  
  if (result.size() == 0)
    cout << "empty" << endl;
  
  for (auto it = result.begin(); it != result.end(); it++) {
    cout << it->first << ": ";
    for (int i = 0; i < it->second.size(); i++) {
      cout << it->second[i] << ", ";
    }
    cout << endl;
  }
  
  return 0;
}
