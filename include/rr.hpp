#ifndef RR_H
#define RR_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

class Rr    //Obs.: This Round Robin algorithm will be defined with quantum = 2
{
public:
  Rr();
  void readInputFile(const std::string& file_name); //method to read the input file and extract the data
  void execute();   //execute the fcfs algorithm
  void displayResults();    //method to print the output

private:
  std::vector<int> arrival_time;
  std::vector<int> burst_time;
  
  float avg_turnaround_time;
  float avg_response_time;
  float avg_waiting_time;
};



#endif // RR_H