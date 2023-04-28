#include <iostream>
#include <fstream>
#include <limits.h>
#include <unistd.h>


#include "../include/sjf.hpp"

#define SHORTEST -1

Sjf::Sjf()
{
 avg_turnaround_time = 0.0;
 avg_response_time   = 0.0;
 avg_waiting_time    = 0.0;   
}

void Sjf::readInputFile(const std::string& file_name)  //method responsible to read the input file
{
    std::ifstream file(file_name);

    if (file.is_open()) 
    {
        int arrival, burst; //variables for saving the arrival and burst times

        /*
        while function using the extraction operator (>>) to set the first value on line to the arrival variable
        and the second value on the line to the burst variable
        then both of the variables are pushed back in their respective vectors
        */ 
        while (file >> arrival >> burst) {
            arrival_time.push_back(arrival);
            burst_time.push_back(burst);
        }
    file.close();
    } 
    else 
    {
        std::cerr << "Failed to open input file!" << file_name << std::endl;    //file open simple check
    }

    /*
    Bubble sort algorithm to sort the arrival and burst times in ascending order
    */
    for(int i = 0; i < arrival_time.size(); i++)
    {
        for(int j = 0; j < arrival_time.size(); j++)
        {
            /*
            if the arrival time of the current process is greater than the arrival time of the next process
            */
            if(arrival_time[j] > arrival_time[j+1] || (arrival_time[j] == arrival_time[j+1] && burst_time[j] > burst_time[j+1]))
            {
                int aux_arrival_time = arrival_time[j];
                int aux_burst_time = burst_time[j];

                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = aux_arrival_time;

                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = aux_burst_time;
            }
        }
    }
}

void Sjf::execute()
{
    /*
    Since the Bubble Sort algorithm was used on the readInputFile method to sort the arrival and burst times
    the first process to be executed is the one with the shortest burst time
    */

    const int num_processes = arrival_time.size();  //set the number of processes equals to the number of lines in the input file based on the arrival_time vector

    std::vector<int> completion_time(num_processes);
    std::vector<int> turnaround_time(num_processes);
    std::vector<int> waiting_time(num_processes);
    std::vector<int> response_time(num_processes);

    completion_time[0] = burst_time[0];

    for (int i = 1; i < num_processes; ++i) {
        /*
        here it's calculated the completion time for the processes
        the operator std::max in this case is ensuring that the time calculated is never below 0 (zero)
        */
        int waiting = std::max(0, completion_time[i-1] - arrival_time[i]);
        completion_time[i] = waiting + burst_time[i] + arrival_time[i];
    }

    for (int i = 0; i < num_processes; ++i) 
    {
        turnaround_time[i] = completion_time[i] - arrival_time[i];  //total turnaround time equals to how much time it took to complete minus in what time the process arrived
        waiting_time[i]    = turnaround_time[i] - burst_time[i];    //total waiting time is given how much the process passe in queur until completion
        response_time[i]   = waiting_time[i] - arrival_time[i];     //total response time equals to the time the process waited to be executed for the first time minus the time of it's arrival

        //to calculate the average time for each metric all the metrics from the processes are being added
        avg_turnaround_time += static_cast<float>(turnaround_time[i]);
        avg_waiting_time    += static_cast<float>(waiting_time[i]);
        avg_response_time   += static_cast<float>(response_time[i]);
    }

    //after adding all the metric values they must be divided by the number of processes to get the average value for the metrics below
    avg_turnaround_time /= static_cast<float>(num_processes);
    avg_waiting_time    /= static_cast<float>(num_processes);
    avg_response_time   /= static_cast<float>(num_processes);
}


void Sjf::displayResults()
{
    std::cout << "SJF " << avg_turnaround_time << " " << avg_response_time << " " << avg_waiting_time << std::endl;
}