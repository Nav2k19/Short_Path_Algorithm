//
//  main.cpp
//  lab7
//
//  Created by Kish Pillai on 4/27/21.
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>
#include <limits.h>
#include <set>
#include <vector>
#include "ArgumentManager.h"
class Graph
{
private:
    int V;
    vector<pair<int,int>> *Adjacency_List;
    
public:
    Graph(int Vertex);
    void Add_Edge(int v1, int v2, int Weight);
    
    void Dijkstra(int s,int e,ofstream& OFS);
};


Graph::Graph(int Vertex)
{
    V = Vertex;
    Adjacency_List = new vector<pair<int,int>> [Vertex];
}
void Graph::Add_Edge(int v1, int v2, int Weight)
{
    Adjacency_List[v1].push_back(make_pair(v2, Weight));
}
void Graph::Dijkstra(int a,int b, ofstream& OFS)
{
    //declare a Set object to store the vertices
    set<pair<int,int>> extract_Set;
    //vector to store the Distances between two verticies
    vector<int> dist(V,INT_MAX);
    
    extract_Set.insert(make_pair(0, a));
    dist[a] = 0;
    
    while (!extract_Set.empty()) {
        pair<int,int> temp = *(extract_Set.begin());
        
        extract_Set.erase(extract_Set.begin());
        
        int u = temp.second;
        
        //traverse the Adjacency List
        for(auto k = Adjacency_List[u].begin(); k !=  Adjacency_List[u].end(); k++)
        {
            int v = (*k).first;
            
            int Weight = (*k).second;
            
            if(dist[v]> dist[u] + Weight)
            {
                if(dist[v] != INT_MAX)
                {
                    extract_Set.erase(extract_Set.find(make_pair(dist[v], v)));
                }
                //update new value for vertex
                dist[v] = dist[u] + Weight;
                
                extract_Set.insert(make_pair(dist[v], v));
            }
        }
    }
    
    OFS<<dist[b-1]<<endl;
    
    /*cout<<"Minumum Distance from vertex  "<<s<<endl;
    
    for(int i = s; i<V; i++)
    {
        cout<<"Vertex: "<< i<<" Distance: "<<dist[i]<<endl;
    }*/
}


int main(int argc, char * argv[]) {
    ArgumentManager am(argc,argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream IFS(input);
    ofstream OFS(output);
    int m,n,x,y;
    //m is the number of verticies
    //n is the number of edges
    // use this as iterator when traversing through the graph
    //x is the starting vertex
    // y is the destination vertex
    int a,b;
    int W;
    
    IFS>>m>>n>>x>>y;
    
    Graph G(m);
    
    while(!IFS.eof())
    {
        
        for(int i = 1; i<=n; i++)
        {
            IFS>>a>>b>>W;
            G.Add_Edge(a,b,W);
        }
    }
    
    G.Dijkstra(x,y, OFS);
    
    //next input is a, b ,c
    //a is the start vertex
    //b is the destination vertex from a
    //c is the weight or Length from a to b
    IFS.close();
    OFS.close();
    return 0;
}
