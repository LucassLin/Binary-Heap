/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   event.h
 * Author: Lcc
 *
 * Created on 2017年3月11日, 下午6:56
 */

#ifndef EVENT_H
#define EVENT_H

class event{
	private:
		int time;
		int label;
		int source;
		int target;
	public:
                ~event();
                event();
                event(int t, int s, int tar, int l);
                
                void set_time(double add);
                
		int get_target();
		int get_time();
		int get_time() const;
                int get_label();
		int get_source();
                
		friend bool operator < (event& c1, event& c2);
		event operator= (event a);


		
};

void event::set_time(double add)
{
    this->time = this->time + add;
}

event::event()
{
	
}

event::~event()
{

}

event::event(int t, int s, int tar, int l)
{
    time = t;
    source = s;
    target = tar;
    label = l;
}

int event::get_time() 
{
	return time;
}

int event::get_time() const
{
	return time;
}

int event::get_label()
{
	return label;
}

int event::get_target()
{
	return target;
}

int event::get_source()
{
	return source;
}

event event::operator= ( event a)
{   
    
	this->time = a.time;
        this->source = a.source;
        this->target = a.target;
	this->label = a.label;
        return *this; 
}

bool operator < ( event& c1, event& c2)
{
	return (c1.get_time() < c2.get_time());
}




#endif /* EVENT_H */

