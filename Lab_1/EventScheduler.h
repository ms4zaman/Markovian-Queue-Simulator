//----------------------------------------------------------------------------------------------------------------------
// By: Mohammad Saad Zaman
// ECE 358 Lab 1
// UW ID: 20432404
//----------------------------------------------------------------------------------------------------------------------

#include <queue>
#include "Distribution.h"

#define ARRIVAL 1
#define DEPARTURE 2
#define OBSERVER 3

struct Event{
	int type;
	double time;
};

struct CompareTime {
	bool operator() (const Event &e1, Event &e2) {
		return e1.time > e2.time;
	}
};

class EventScheduler{
public:
	EventScheduler(double i_simulationTime, double i_packetLength,
		double i_transmissionRate, double i_rho);
	double getPacketLambda();
	void setObserverTimes();
	void setPacketArrivalTimes();
	void pushEvent(int i_type, double i_time);
	void popEvent();
	Event getEvent();
	bool isQueueEmpty();

protected:
	double simulationTime;
	double packetLength;
	double transmissionRate;
	double rho;
	double packetLambda;
	double observerAlpha;

private:
	std::priority_queue<Event, std::vector<Event>, CompareTime> queue;
};