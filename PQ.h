/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PQ.h
 * Author: Lcc
 *
 * Created on 2017年3月12日, 下午8:30
 */

#ifndef PQ_H
#define PQ_H

#include <queue>
#include "event.h"
#include <functional>
class PQ{
private:
        std::priority_queue<int, std::vector<int>, std::greater<int> > q;
        vector<event> vec;
        
    public:
        PQ();
        void insert(event x);
        event pop();
        vector<event> v();
        
};

PQ::PQ()
{
    
}

vector<event> PQ::v()
{
    return vec;
}

void PQ::insert(event x)
{
    vec.push_back(x);
    q.push(x.get_time());
}

event PQ::pop()
{
    int a = q.top();
    q.pop();
    for(int i=0; i<vec.size(); i++)
    {
        event h = vec[i];
        if( h.get_time() == a)
        {
            return vec[i];
        }
    }   
}
#endif /* PQ_H */

