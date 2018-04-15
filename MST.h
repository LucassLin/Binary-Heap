/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MST.h
 * Author: Lcc
 *
 * Created on 2017Âπ?Êú?Êó? ‰∏ãÂçà1:04
 */

#ifndef MST_H
#define MST_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#include <stdlib.h> 
using namespace std;

// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;
 
// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;
 
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
    
 
    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
      
    void set(int a)
    {
        vector<pair<int,iPair> > temp;
        for (int i=0; i<edges.size(); i++)
        {
            if((edges[i].second).second == a)
            {
                temp.push_back(edges[i]);
            }
        }
        int size = temp.size();
        int count = 0;
        vector< pair<int, iPair> >::iterator it;
        for (it=temp.begin(); it!=temp.end(); it++)
        {
            if(it->first < 0)
            {
                count++;
            }
        }
        if (count == size)
        {
            
            for (int i=0; i<edges.size(); i++)
            {
                if((edges[i].second).second == a)
                {   
                    edges[i].first = (rand() %100 + 1);
                    break;
                }
            }
        }
    }

    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
    int Num();
    int kruskal();
};


struct DisjointSets
{
    int *parent, *rnk;
    int n;
 
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
 
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
 
            //every element is parent of itself
            parent[i] = i;
        }
    }
 
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
 
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
 
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
 
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
 
// To represent Disjoint Sets
struct DisjointSets1
{
    int *parent, *rnk;
    int n;
 
    // Constructor.
    DisjointSets1(int n, vector<int> v)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
 
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i < v.size(); i++)
        {
            int a = v[i];
            rnk[i] = 0;
 
            //every element is parent of itself
            parent[i] = a;
        }
    }
 
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
 
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
 
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
 
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskal()
{
    int count = 0;
    sort(edges.begin(), edges.end());
 
    // Create disjoint sets
    DisjointSets ds(V);
 
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
 
        int set_u = ds.find(u);
        int set_v = ds.find(v);
 
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << " - " <<w << endl;
            count++;
            // Update MST weight
 
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    return count;
}
 
 /* Functions returns weight of the MST*/
int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result
 
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
 
    // Create disjoint sets
    DisjointSets ds(V);
 
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
 
        int set_u = ds.find(u);
        int set_v = ds.find(v);
 
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << " - " <<w << endl;
 
            // Update MST weight
            mst_wt += it->first;
 
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
 
    return mst_wt;
}



vector< pair<int, iPair> > MST(Graph g)
{
    vector< pair<int, iPair> > M;
        sort(g.edges.begin(), g.edges.end());
 
    // Create disjoint sets
    DisjointSets ds(g.V);
 
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=g.edges.begin(); it!=g.edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
 
        int set_u = ds.find(u);
        int set_v = ds.find(v);
 
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            M.push_back({w, {u, v}});
            // Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << " - " <<w << endl;
            
            // Update MST weight
            
 
            // Merge two sets
            ds.merge(set_u, set_v);
            
        }
    }
    return M;
}

vector< pair<int, iPair> > addkruskal(vector< pair<int, iPair> > edges, int num)
{
    DisjointSets ds(num);
    vector< pair<int, iPair> > hold;
    sort(edges.begin(), edges.end());
    int count = 0;
    
    while(hold.size()!= num-1)
    {
        int v = hold[count].second.second;
        int u = hold[count].second.first;
        int w = hold[count].first;
        
         int set_u = ds.find(u);
        int set_v = ds.find(v);
        
        if (set_u != set_v)
        {
            hold.push_back({w, {u, v}});
            // Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << " - " <<w << endl;
            
            // Update MST weight
            
 
            // Merge two sets
            ds.merge(set_u, set_v);
            
        }
    }
    return hold;
}

#endif /* MST_H */

