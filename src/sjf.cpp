#include <iostream>
#include <fstream>
#include <limits.h>
#include <unistd.h>
#include <sstream>

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
}

void Sjf::execute()
{
    int time            = 0;   //time variable to keep track of the time
    int shortest_index  = 0;  //variable to keep track of the index of the process with the shortest burst time
    int smaller_burst   = INT_MAX;    //variable to keep track of the smaller burst time
    int process_counter = arrival_time.size();  //auxiliary variable to keep track of the number of processes
    int num_processes   = arrival_time.size();    //number of processes

    std::vector<int> aux_arrival_time;
    std::vector<int> aux_burst_time;

    aux_arrival_time.push_back(arrival_time[0]);
    aux_burst_time.push_back(burst_time[0]);

    while(process_counter)    //while loop to keep the program running until all the processes are reordered in ascending order
    {
        smaller_burst = burst_time[0];
        for(int i = 0; i < process_counter; i++)
        {
            std::cerr << "process_counter: " << process_counter << std::endl;   //debugging
            std::cerr << "i: " << i << std::endl;   //debugging
            sleep(1);   //debugging
            /*
                if statement to check if the arrival time of the process is less than the current time 
                and if the burst time of the process is less than the smaller burst time
            */
            if(arrival_time[i] <= time && burst_time[i] < smaller_burst)
            { 
                smaller_burst = burst_time[i];

                time = time + smaller_burst;
                shortest_index = i;

                aux_arrival_time.push_back(arrival_time[i]);    //pushing back the arrival and burst times of the process with the shortest burst time
                aux_burst_time.push_back(burst_time[i]);    //pushing back the arrival and burst times of the process with the shortest burst time

                arrival_time.erase(arrival_time.begin() + shortest_index);   //erasing the arrival time of the process with the shortest burst time
                burst_time.erase(burst_time.begin() + shortest_index);   //erasing the burst time of the process with the shortest burst time

                i--;
                process_counter--;
            }
        }
    }

    for(int i = 0; i < num_processes; ++i)
    {
        /*
        here it's calculated the completion time for the processes
        the operator std::max in this case is ensuring that the time calculated is never below 0 (zero)
        */
        int waiting = std::max(0, completion_time[i-1] - aux_arrival_time[i]);
        completion_time[i] = waiting + aux_burst_time[i] + aux_arrival_time[i];
    }

    for (int i = 0; i < num_processes; ++i) 
    {
        turnaround_time[i] = completion_time[i] - aux_arrival_time[i];  //total turnaround time equals to how much time it took to complete minus in what time the process arrived
        waiting_time[i]    = turnaround_time[i] - aux_burst_time[i];    //total waiting time is given how much the process passe in queur until completion
        response_time[i]   = waiting_time[i] - aux_arrival_time[i];     //total response time equals to the time the process waited to be executed for the first time minus the time of it's arrival

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