#include <iostream>

struct demand{
	int number;
	int arrival_time;
	int service_time;
	int allowable_waiting_time;
	int starttime;
};
typedef struct demand demand;

class Waiting_queue
{
public:
	Waiting_queue();
	void sort();
	void insert(demand &);
	void scheduling();
	void print_scheduling_result();

private:
	demand *queue;
	int front;
	int rear;
	bool full_flag;
	int size;
};