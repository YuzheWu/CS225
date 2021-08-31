
#include <vector>
#include "edge.h"
#include <iostream>
#include <map>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
#include <map>
#include <queue>
#include <limits>

using namespace std;

class myComparator{
    public:
      int operator() (std::pair<Vertex, int> p1, std::pair<Vertex, int> p2){
            return p1.second > p2.second;
      }
  };

std::pair<int, std::vector<Vertex> >shortestPath_(Graph g, Vertex source, Vertex dest){
  int distances = 0;
  std::map<Vertex, Vertex> previous;
  priority_queue<std::pair<Vertex, int>, vector<std::pair<Vertex, int> >, myComparator> q;
  std::map<Vertex, int> node_to_dist;
  std::vector<Vertex> vertices = g.getVertices();
  for(Vertex & v : vertices){
    if(v != source){
      node_to_dist[v] = std::numeric_limits<int>::max();
    }else{
      node_to_dist[v] = 0;
    }
  }
  q.push(std::make_pair(source, 0));
  std::vector<Vertex> visited;
  while (q.top().first != dest){
    std::pair<Vertex, int> cur = q.top();
    // std::cout << cur.first << std::endl;
    q.pop();
    std::vector<Vertex> neighbors = g.getAdjacent(cur.first);
    // std::cout << neighbors.size() << std::endl;
    for(Vertex & v : neighbors){
      if(std::find(visited.begin(), visited.end(), v) == visited.end()){
        int cur_distance = node_to_dist[cur.first] + g.getEdgeWeight(cur.first, v);

        if(cur_distance < node_to_dist[v]){
          node_to_dist[v] = cur_distance;
          auto it = node_to_dist.find(v);
          q.push(*it);
          previous[v] = cur.first;
        }
      }
    }
    visited.push_back(cur.first);
  }
  distances = node_to_dist[dest];
  Vertex cur = dest;
  vector<Vertex> path;
  path.push_back(dest);
  while (previous[cur] != source){
    cur = previous[cur];
    path.push_back(cur);
  }
  std::reverse(path.begin(),path.end());
  return std::make_pair(distances, path);
}

int main() {
  //auto v = airport_file_to_vector("airports.dat.txt");
  // for(int i = 0; i < 5; i++) {
  //   cout << "this is ID  " << v[i][0]<< endl;
  //   cout << "this is name " << v[i][1]<< endl;
  //   cout << "this is longitude " << v[i][2]<< endl;
  //   cout << "this is latitude " << v[i][3]<< endl;
  // }
  /*
  auto info = route_file_to_pair("routes.dat.txt");
  cout << info[5].first << endl;
  cout << info[5].second << endl;
  for(unsigned long i = 0; i < v.size()-1;i++){
    if(info[5].first == v[i][0]){
      cout << "first" << v[i][1]<< endl;
      cout << "first" << v[i][2]<< endl;
      cout << "first" << v[i][3]<< endl;
    }
    if(info[5].second == v[i][0]){
      cout << v[i][1]<< endl;
      cout << v[i][2]<< endl;
      cout << v[i][3]<< endl;
    }
  }
  */
  Graph g = Graph(true,true);
  // g.insertVertex("a");
  // g.insertVertex("b");
  // g.insertVertex("c");
  // g.insertVertex("d");
  g.insertEdge("Siebel","Rantoul");
  g.setEdgeWeight("Siebel","Rantoul",21);
  g.insertEdge("Siebel","Bloomington");
  g.setEdgeWeight("Siebel","Bloomington",50);
  g.insertEdge("Rantoul","Kankakee");
  g.setEdgeWeight("Rantoul","Kankakee",57);
  g.insertEdge("Bloomington","Pontiac");
  g.setEdgeWeight("Bloomington","Pontiac",42);
  g.insertEdge("Kankakee","Pontiac");
  g.setEdgeWeight("Kankakee","Pontiac",53);
  g.insertEdge("Kankakee","Chicago");
  g.setEdgeWeight("Kankakee","Chicago",63);
  g.insertEdge("Pontiac","Chicago");
  g.setEdgeWeight("Pontiac","Chicago",40);
  g.insertEdge("Pontiac","Joliet");
  g.setEdgeWeight("Pontiac","Joliet",57);
  g.insertEdge("Joliet","Chicago");
  g.setEdgeWeight("Joliet","Chicago",51);
  g.insertEdge("Chicago","Cloud Gate");
  g.setEdgeWeight("Chicago","Cloud Gate",1);
  // g.print();
  // for (Vertex v : g.getAdjacent("b"))
  //   std::cout << v << std::endl;
  pair<int,vector<Vertex> > p = shortestPath_(g, "Siebel", "Cloud Gate");
  cout<<p.first<<endl;
  for(Vertex & v : p.second){
    cout<<v<<endl;
  }
  // int result = 20;
  // vector<Vertex> v;
  // v.push_back("a");
  // v.push_back("c");
  // v.push_back("d");
  return 0;


}
