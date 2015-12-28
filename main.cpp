#include <iostream>
#include <stdio.h>
#include "Queue.h"

int main(){
	int Arr,Ser,Wait;
	int i=1;
	Waiting_queue *w_queue;
	demand input;
	w_queue = new Waiting_queue();
	printf("Input:\n");
	printf("\tArrive time\tService time\tAllowable waiting time\n");
	while(1){
		printf("Client %d: ", i);
		scanf("%d", &Arr);
		if(Arr == -1) break;
		scanf(" %d %d", &Ser, &Wait);
		input.arrival_time = Arr;
		input.service_time = Ser;
		input.allowable_waiting_time = Wait;
		input.number = i;
		w_queue->insert(input);
		i++;
	}

	printf("Output:\n");
	printf("\tServed or not\tDeparture time\n");
	w_queue->print_scheduling_result();
}