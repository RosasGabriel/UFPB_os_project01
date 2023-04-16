#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <string>

class Fcfs {
public:
  Fcfs();
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

#endif  // FCFS_H