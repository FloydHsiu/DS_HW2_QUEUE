#include <iostream>
#include "Queue.h"

void swap(demand&, demand&);

Waiting_queue::Waiting_queue(){
	front = 0;
	rear = 0;
	full_flag = false;
	size = 10;
	queue = new demand[size];
}

void Waiting_queue::sort(){
	for(int i=0; i<rear; i++){
		for(int j=i+1; j<rear; j++){
			if(queue[i].arrival_time > queue[j].arrival_time){
				swap(queue[i], queue[j]);
			}
		}
	}
}

void Waiting_queue::insert(demand &input){
	if(full_flag && ((rear+1)%size== front)) // full
	{
		demand *temp = new demand[2*size];
		for(int i=0; i<size; i++){
			temp[i].number = queue[i].number;
			temp[i].arrival_time = queue[i].arrival_time;
			temp[i].service_time = queue[i].service_time;
			temp[i].allowable_waiting_time = queue[i].allowable_waiting_time;
		}
		delete[] queue;
		queue = temp;
		size *= 2;
	}
	queue[rear].number = input.number;
	queue[rear].arrival_time = input.arrival_time;
	queue[rear].service_time = input.service_time;
	queue[rear++].allowable_waiting_time = input.allowable_waiting_time;
	full_flag = true;
}

/*void Waiting_queue::scheduling(){
	int depart_time;
	int last_service = 0;
	int pre_depart_time;
	this->sort();
	queue[0].starttime = queue[0].arrival_time;
	pre_depart_time = 0;
	depart_time = queue[0].arrival_time + queue[0].service_time;
	for(int i=1; i< rear; i++){
		if(depart_time > queue[i].arrival_time + queue[i].allowable_waiting_time){
			//if can cut or not.
			if(pre_depart_time > queue[i].arrival_time){
				if((pre_depart_time + queue[i].service_time) <= queue[last_service].arrival_time + queue[last_service].allowable_waiting_time){
					//can cut
					queue[last_service].starttime = pre_depart_time;
					queue[i].starttime = queue[last_service].starttime + queue[i].service_time;
					swap(queue[i], queue[last_service]);
					last_service = i;
					pre_depart_time = queue[i].starttime;
					depart_time = queue[i].starttime + queue[i].service_time;
				}
				else{
					//no cut
					queue[i].starttime = -1;
				}
			}
			else{
				if((queue[i].arrival_time + queue[i].service_time) <= (queue[last_service].arrival_time + queue[last_service].allowable_waiting_time)){
					//can cout
					queue[last_service].starttime = pre_depart_time;
					queue[i].starttime = queue[last_service].starttime + queue[i].service_time;
					swap(queue[i], queue[last_service]);
					last_service = i;
					pre_depart_time = queue[i].starttime;
					depart_time = queue[i].starttime + queue[i].service_time;
				}
				else{
					//no cut
					queue[i].starttime = -1;
				}

			}
		}
		else{
			if(queue[i].arrival_time > depart_time){
				queue[i].starttime = queue[i].arrival_time;
				pre_depart_time = depart_time;
				depart_time = queue[i].starttime + queue[i].service_time;
				last_service = i;
			}
			else{
				queue[i].starttime = depart_time;
				pre_depart_time = depart_time;
				depart_time = queue[i].starttime + queue[i].service_time;
				last_service = i;
			}
		}
	}
}*/

void Waiting_queue::print_scheduling_result(){
	this->scheduling();
	for(int i=0; i<rear; i++){
		if(queue[i].starttime != -1) printf("Client %d:\tYes\t%d\n", i+1, queue[i].starttime+queue[i].service_time);
		else printf("Client %d:\tNo\n", i+1);
	}
}

void Waiting_queue::scheduling(){
	int now=0;
	int at,st,awt;
	int last;
	int *start;
	this->sort();
	for(int i=0; i<rear; i++){
		at = queue[i].arrival_time;
		st = queue[i].service_time;
		awt = queue[i].allowable_waiting_time;
		start = &queue[i].starttime;
		if(now <= at + awt){//順利排在後面
			if(now < at){
				*start = at;
				now = *start + st;
				last = i;
			}
			else{
				*start = now;
				now = *start + st;
				last = i;
			}
		}
		else{//插隊
			now -= queue[last].service_time;
			if(now > at){
				*start = now;
				if(*start + st <= queue[last].arrival_time + queue[last].allowable_waiting_time){
				queue[last].starttime = *start + st;
				now = queue[last].starttime + queue[last].service_time;
				}
				else{
					*start = -1;
					now = queue[last].starttime + queue[last].service_time;
				}
			}
			else{
				*start = at;
				if(*start + st <= queue[last].arrival_time + queue[last].allowable_waiting_time){
				queue[last].starttime = *start + st;
				now = queue[last].starttime + queue[last].service_time;
				}
				else{
					*start = -1;
					now = queue[last].starttime + queue[last].service_time;
				}
			}
		}
		printf("%d\n", *start);
	}
}

void swap(demand &d1, demand &d2){
	demand temp;
	temp.number = d1.number;
	temp.arrival_time = d1.arrival_time;
	temp.service_time = d1.service_time;
	temp.allowable_waiting_time = d1.allowable_waiting_time;
	d1.number = d2.number;
	d1.arrival_time = d2.arrival_time;
	d1.service_time = d2.service_time;
	d1.allowable_waiting_time = d2.allowable_waiting_time;
	d2.number = temp.number;
	d2.arrival_time = temp.arrival_time;
	d2.service_time = temp.service_time;
	d2.allowable_waiting_time = temp.allowable_waiting_time;
}