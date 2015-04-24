//----------------------------------------------------------------------------------------------------------------------
// By: Mohammad Saad Zaman
// ECE 358 Lab 1
// UW ID: 20432404
//----------------------------------------------------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include "EventScheduler.h"
#include "Distribution.h"
using namespace std;

int main(int argc, const char * argv[])
{
	double i_minRho = stod(argv[1]);
	double i_maxRho = stod(argv[2]);
	double i_simulationTime = stod(argv[3]);
	double i_packetLength = stod(argv[4]);
	double i_transmissionRate = stod(argv[5]);
	string buffer(argv[6]);
	bool bufferLimitExist;
	double bufferSize = stod(argv[7]);
	double stepSize = stod(argv[8]);
	string fileName(argv[9]);

	if (buffer == "true" || buffer == "TRUE"){
		bufferLimitExist = true;
	}
	else if (buffer == "false" || buffer == "FALSE"){
		bufferLimitExist = false;
	}
	i_maxRho += 0.005; // In case of loss of precision from incrementing	
	ofstream outfile(fileName);

	outfile << "Rho,Lambda,Alpha,SimulationTime,PacketLength,TransmissionRate,";
	outfile <<"BufferExist,BufferSize,AvgNumberPackets,AvgSoujournTime,IdleProb,LossProb" << endl;

	while (i_minRho <= i_maxRho){
		EventScheduler scheduler(i_simulationTime, i_packetLength, i_transmissionRate, i_minRho);
		double packetLambda = scheduler.getPacketLambda();
		double observerAlpha = 3 * packetLambda;
		scheduler.setPacketArrivalTimes();
		scheduler.setObserverTimes();

		double n_Arrival = 0;				// Number of arrivals
		double n_Departure = 0;				// Number of departures
		double n_Observers = 0;				// Number of observers
		double idleCounter = 0;				// Idle counter
		double systemPacketCounter = 0;		// Counter for all packets within the system currently
		double generatedPacketCounter = 0;	// Counter for all packets generated
		double droppedPacketCounter = 0;	// Counter for all packets that are dropped
		double sojournTimeCounter = 0;		// Counter for all packets sojourn time

		double t_arrival = 0;		// Arrival time
		double t_departure = 0;		// Departure time
		double t_observer = 0;		// Observer time

		double serviceTime = 0;
		Distribution packetLengthDist(1 / i_packetLength);

		while (!scheduler.isQueueEmpty()){
			Event e = scheduler.getEvent();
			if (e.type == ARRIVAL){
				generatedPacketCounter++;
				if (bufferLimitExist && (n_Arrival - n_Departure >= bufferSize)){
					droppedPacketCounter++; // Dropped Packet, Buffer exists and is full
				}
				else {
					serviceTime = packetLengthDist.getExpRV() / i_transmissionRate;
					if (n_Arrival == n_Departure){
						t_departure = e.time + serviceTime; // Empty queue, serviced right away
					}
					else{
						t_departure += serviceTime;	// Departure time appended with service time
					}
					scheduler.pushEvent(DEPARTURE, t_departure); // Queue the departure event to the DES
					n_Arrival++;
					sojournTimeCounter += t_departure - e.time;
				}	
			}
			else if (e.type == DEPARTURE){
				n_Departure++;
			}
			else if (e.type == OBSERVER){
				systemPacketCounter += (n_Arrival - n_Departure);
				if (n_Arrival == n_Departure){
					idleCounter++;	// Queue is empty, Idle counter increment
				}
				n_Observers++;
			}
			scheduler.popEvent(); // Remove event from queue
		}
		double avgNumPackets = systemPacketCounter/n_Observers;
		double idleProbabilty = idleCounter/n_Observers;
		double lossPacketProbability = droppedPacketCounter/generatedPacketCounter;
		double avgSojournTime = sojournTimeCounter / n_Departure;

		outfile << i_minRho << "," << packetLambda << "," << observerAlpha << ",";
		outfile << i_simulationTime << "," << i_packetLength << "," << i_transmissionRate;
		outfile << "," << boolalpha << bufferLimitExist << "," << bufferSize << ",";
		outfile << avgNumPackets << "," << avgSojournTime << "," << idleProbabilty; 
		outfile << "," << lossPacketProbability << endl;
		i_minRho += stepSize;
	}
	return 0;
}


