========================================================================
    CONSOLE APPLICATION : Project Overview
By: 	  Mohammad Saad Zaman
UWID: 	  20432404
username: ms4zaman
Date: 	  Feb 6, 2015
========================================================================
The performance of a communication network is a key aspect of network engineering. Delay and packet loss ratio are two important performance metrics. The first metric is a measure of the time it takes the packet to reach its destination since it was generated. The second metric represents the percentage of data packets that are lost in the system. Delay and packet loss are components of the broader concept of Quality of Service (QoS) offered by a network to the users. In order to evaluate these performance statistics we shall simulate a Markovian FIFO networking queue. 

A Markovian arrival process means that the distribution of the time between successive arrivals (also called inter-arrival time) is identical for all inter-arrivals, is independent from one inter-arrival to another, and is exponentially distributed. The queue shall be highly flexible to a range of input parameters and will capture the packet arrivals and departures, throughput and loss packet probability.

To run the program 9 parameters are needed. Shown below is an example of the script 
for a M/D/1 queue with no buffer. A rho value from 0.25 to 0.95, step size of 0.1 with no buffer.

./ms4zamanLab1 [minRho] [maxRho] [simTime] [packetLength] [transRate] [bufExists] [bufSize] [stepSize] [filename.csv]

An example of this would look like:

./ms4zamanLab1 0.25 0.95 10000 12000 1000000 false 5 0.1 q3.csv

The buffersize parameter still needs a value even if the buffer does not exist and file format must be a csv.