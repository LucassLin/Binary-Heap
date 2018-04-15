/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SysQueue.h
 * Author: Lcc
 *
 * Created on 2017年3月9日, 下午3:23
 */

#ifndef SYSQUEUE_H
#define SYSQUEUE_H

#include <iostream>
#include <vector>
#include <queue>

#include "event.h"
using namespace std;


class SysQueue{
    private:
        vector<int> my_vector;
        queue<int> my_queue;
        int currentsize;
        
    public:
        SysQueue(int n);
        void push(int x);
        int pop();
        bool check(int x);
        int front();//check time
        bool isEmpty();
        int size();
        queue<int> q();
        vector<int> v();
      
};

SysQueue::SysQueue(int n)
{
    my_vector.reserve(n);
    currentsize = 0;
    for(int i=0; i<n; i++)
    {
        my_vector.push_back(0);
    }
}

queue<int> SysQueue::q()
{
    return my_queue;
}

vector<int> SysQueue::v()
{
    return my_vector;
}

int SysQueue::size()
{
    return my_queue.size();
}

bool SysQueue::isEmpty()
{
    if(my_queue.size() == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

int SysQueue::front()
{
    return my_queue.front();
}

void SysQueue::push(int x)
{
    my_queue.push(x);
    my_vector[x] = 1;
    currentsize++;
}

int SysQueue::pop()
{
    int a = my_queue.front();
    my_vector[a] = 0;
    my_queue.pop();
    currentsize--;
    return a;
}

bool SysQueue::check(int x)
{
    if(my_vector[x] == 0)
    {
        return false;
    }
    if(my_vector[x] == 1)
    {
        return true;
    }
}


#endif /* SYSQUEUE_H */
