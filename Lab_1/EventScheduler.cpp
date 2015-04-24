//----------------------------------------------------------------------------------------------------------------------
// By: Mohammad Saad Zaman
// ECE 358 Lab 1
// UW ID: 20432404
//----------------------------------------------------------------------------------------------------------------------
#include "EventScheduler.h"
using namespace std;

EventScheduler::EventScheduler(double i_simulationTime, 
	double i_packetLength, double i_transmissionRate, double i_rho){

	simulationTime = i_simulationTime;
	packetLength = i_packetLength;
	transmissionRate = i_transmissionRate;							
	rho = i_rho;
	packetLambda = getPacketLambda(); 
	observerAlpha = 3 * packetLambda;				
}
void EventScheduler::setObserverTimes(){
	Distribution observerDistribution(observerAlpha);				
	// Create a distribution object and initiatilze with first the random variable
	double observerTimeCounter = observerDistribution.getExpRV();	
	while (observerTimeCounter < simulationTime){
		// Queue the event of the observer	
		pushEvent(OBSERVER, observerTimeCounter);					
		observerTimeCounter += observerDistribution.getExpRV();		
	}
}
void EventScheduler::setPacketArrivalTimes(){
	Distribution packetArrivalDistribution(packetLambda);			
	double packetTimeCounter = packetArrivalDistribution.getExpRV();
	while (packetTimeCounter < simulationTime){
		// Queue event of the packet arrival
		pushEvent(ARRIVAL, packetTimeCounter);						
		packetTimeCounter += packetArrivalDistribution.getExpRV();	
	}
}
double EventScheduler::getPacketLambda(){
	return ((rho*transmissionRate) / packetLength);
}

bool EventScheduler::isQueueEmpty(){
	return queue.empty();
}

void EventScheduler::pushEvent(int i_type, double i_time){
	Event e;
	e.type = i_type;
	e.time = i_time;
	queue.push(e);
}

void EventScheduler::popEvent(){
	queue.pop();
}

Event EventScheduler::getEvent(){
	return queue.top();
}

