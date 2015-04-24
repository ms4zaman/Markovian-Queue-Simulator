========================================================================
    CONSOLE APPLICATION : Lab_1 Project Overview
By: 	  Mohammad Saad Zaman
UWID: 	  20432404
username: ms4zaman
Due Date: Feb 6, 2015
========================================================================

To run the program 9 parameters are needed. Shown below is an example of the script 
for a M/D/1 queue with no buffer. A rho value from 0.25 to 0.95, step size of 0.1 with no buffer.

./ms4zamanLab1 [minRho] [maxRho] [simTime] [packetLength] [transRate] [bufExists] [bufSize] [stepSize] [filename.csv]

An example of this would look like:

./ms4zamanLab1 0.25 0.95 10000 12000 1000000 false 5 0.1 q3.csv

The buffersize parameter still needs a value even if the buffer does not exist and file format must be a csv.