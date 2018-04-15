/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Lcc
 *
 * Created on 2017Âπ?Êú?Êó? ‰∏äÂçà8:58
 */

#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <queue>
#include <algorithm>


#include "BinaryHeap.h"
#include "SysQueue.h"
#include "event.h"
#include "MST.h"
#include "PQ.h"
//
//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int number_of_attackers = atoi(argv[1]);
    int number_of_sysadmins = atoi(argv[2]);
    int number_of_nodes = atoi(argv[3]);
    int random_seed = atoi(argv[4]);
   // int number_of_nodes = 100;
   // int number_of_attackers = 20;
   // int number_of_sysadmins = 20;
   // int random_seed = 1234;
    
    
    //Construct network
    int E = 0;  
    for(int i=0; i<number_of_nodes-1; i++){
        for (int j=0; j<i-1;j++){
            E++;
        }
    }
    Graph g(number_of_nodes, E);
    for(int i=0; i<number_of_nodes-1; i++){
        for (int j=0; j<i-1;j++){
            srand(random_seed);
            int ran = (rand() %221) - 120;
            g.addEdge(i,j,ran);
        }
    }
    for(int i=0; i<number_of_nodes; i++)
    {
        g.set(i);
    } 
    vector< pair<int, iPair> > hold;
    for (int i=0; i<g.edges.size(); i++)
    {
        if (g.edges[i].first > 0)
        {
            hold.push_back(g.edges[i]);
        }
    }
    Graph graph(number_of_nodes, hold.size());
    graph.edges = hold;
    //original graph
//    int io = graph.kruskal();
//    cout << "dao di shi bu shi" <<io <<endl;
    vector< pair<int, iPair> > M;

    M = MST(graph);
    Graph MST(M.size()+1,M.size());
    MST.edges = M;
    //minimum spanning tree network constructed, save as MST
    int kk=0;
    for(int i=0; i<MST.edges.size();i++)
    {
        kk = kk + MST.edges[i].first;
    }
    
    int clock = 0;
    int count_attack = 0;
    PQ p;
    SysQueue system(number_of_nodes);
    
    //initialize attacks
    for(int i=0; i<number_of_attackers; i++)
    {
        int time = (rand()%901)+100;
        int source = rand()%(number_of_attackers + 1);
        int target = rand()%(number_of_nodes + 1);
        //cout << "time is " <<time;
        event h(time, source, target,1);
        p.insert(h);
    }

    clock = 100;
    
    
    
    
    for(int i=0; i<number_of_sysadmins; i++)
    {
        int time = (rand()%1001)+1000;
        int source = rand()%(number_of_attackers + 1);
        int target = rand()%(number_of_nodes + 1);
        //cout << "time is " <<time;
        event h(time, source, target,3);
        p.insert(h);
    }
    
    

    //loop
    int count_fix = 0;
    while(count_attack < 2000){
        event h = p.pop();
////       cout << "count attack is " <<count_attack;
////            //cout <<"event time is " << h.get_time() <<endl;
            if (h.get_label() == 1)//attack
            {
                cout << "attack(" << h.get_time() << ", " <<h.get_source() <<", " <<h.get_target() << ")\n";
                clock = h.get_time();
                system.push(h.get_target());
                count_attack++;
                event newevent((rand()%901)+100+clock,rand()%(number_of_attackers + 1),rand()%(number_of_nodes + 1),1);
                p.insert(newevent);
            }
            if (h.get_label() == 2)//build
            {
                vector<int>V;
                vector<int>VV;
                //cout << "missing node:";
                queue<int>m = system.q();
                int verticeDeleted = 0;
                vector<int> sysVec = system.v();
                for(int i=0; i<number_of_nodes;i++)
                {
                        if(sysVec[i] == 1)
                        {
                            V.push_back((i));
                            verticeDeleted++;
                            //cout <<i <<" ";
                        }
                        else
                        {
                            VV.push_back(i);
                        }
                }
               // cout << endl;
                
                //remaining Graph
                Graph deletedGraph(number_of_nodes,0);
                for(int i=0; i<graph.edges.size();i++)
                {
                    int a = graph.edges[i].second.first;
                    int b = graph.edges[i].second.second;
                    if( std::find(V.begin(), V.end(), a) != V.end() )
                    {;}
                    else if( std::find(V.begin(), V.end(),b ) != V.end() )
                    {;}
                    else
                    {
                        deletedGraph.edges.push_back(graph.edges[i]);
                    }
                }
                int currentMST = deletedGraph.kruskalMST();
                
                int vertice = number_of_nodes - verticeDeleted;
                int verticeD = number_of_nodes*0.2;
              //  cout << "vertice is " << vertice <<endl;
                Graph deleted(number_of_nodes,0);
                for(int i=0; i<MST.edges.size(); i++)
                {
                    int a = MST.edges[i].second.first;
                    int b = MST.edges[i].second.second;
                    if( std::find(V.begin(), V.end(), a) != V.end() )
                    {;}
                    else if( std::find(V.begin(), V.end(),b ) != V.end() )
                    {;}
                    else
                    {
                        deleted.edges.push_back(MST.edges[i]);
                    }
                }
                int kk = deleted.kruskal();
                if (deleted.edges.size()==0)
                {
                    cout << "No tree possible\n";
                }
                else{
                    if(kk!=vertice-1)
                    {   int weight = 0;
                        for(int i=0; i<deleted.edges.size(); i++)
                        {
                           weight = weight + deleted.edges[i].first; 
                        }
                        cout << "Rebuilt tree cost is " <<currentMST<<endl;
                        cout << "MST cost is " << weight <<endl;
                    }

                    else
                    {
                        int cuurentMST = deletedGraph.kruskalMST();
                        int rebuildcost = 0;
                        for(int i=0; i<vertice;i++)
                        {
                            rebuildcost = rebuildcost + deletedGraph.edges[i].first;
                        }
                        cout << "MST cost is " <<currentMST <<endl;
                        cout << "Rebuild cost is " <<rebuildcost <<endl;
                    }
                }
                
            }
            if (h.get_label() == 3)//fix
            {
                if(!system.isEmpty())
                {
                    int a = system.pop();
                    cout << "fix(" <<h.get_time() <<"," << a <<")\n";
                    count_fix++;
                }
                clock = h.get_time();
                event ni(clock+(rand()%1001)+2000,h.get_source(),0,3);
                p.insert(ni);
                
                event n(clock+20,0,0,2);
                p.insert(n);
            }
    }
    return 0;
}
