#include <iostream>
#include <fstream>
#include <unistd.h>

#include "../include/rr.hpp"

#define QUANTUM 2

Rr::Rr()
{
    avg_turnaround_time = 0.0;
    avg_response_time   = 0.0;
    avg_waiting_time    = 0.0;
}

void Rr::readInputFile(const std::string& file_name)
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

void Rr::execute()
{
    const int num_processes = arrival_time.size();  //number of processes

    int time      = 0;   //time variable to keep track of the time
    int processed = 0;  //variable to keep track of the number of processes that are done

    float total_tunraround_time = 0.0;
    float total_waiting_time    = 0.0;
    float total_response_time   = 0.0;

    std::vector<int> remaining_time(burst_time);    //vector to save the remaining time of each process
    std::vector<int> completion_time(num_processes);    //vector to save the completion time of each process
    std::vector<int> turnaround_time(num_processes);    //vector to save the turnaround time of each process
    std::vector<int> waiting_time(num_processes);   //vector to save the waiting time of each process

   while (true)
   {
    bool done = true;   //variable to check if all the processes are done

    for(int i = 0; i < num_processes; ++i)
    {
        if(remaining_time[i] > 0)   //if there is a process that is not done
        {
            done = false;   //set done to false
            if(remaining_time[i] > QUANTUM) //if the remaining time of the process is greater than the quantum
            {
                time += QUANTUM;    //add the quantum to the time
                remaining_time[i] -= QUANTUM;   //subtract the quantum from the remaining time of the process
            }
            else
            {
                time += remaining_time[i];  //add the remaining time of the process to the time

                remaining_time[i]  = 0;  //set the remaining time of the process to zero
                completion_time[i] = time;  //set the completion time of the process to the time
                turnaround_time[i] = completion_time[i] - arrival_time[i];  //set the turnaround time of the process to the completion time minus the arrival time
                waiting_time[i] = turnaround_time[i] - burst_time[i];   //set the waiting time of the process to the turnaround time minus the burst time

                processed++;    //increment the number of processes that are done
            }
        }
    }
    
    if(done) break; //if all the processes are done, break the loop
   }

   this->completion_time = completion_time;
   this->turnaround_time = turnaround_time;
   this->waiting_time    = waiting_time;
   
   for(int i = 0; i < num_processes; ++i)
   {
       total_tunraround_time += turnaround_time[i]; //sum the turnaround time of all the processes
       total_waiting_time    += waiting_time[i];    //sum the waiting time of all the processes
       total_response_time   += waiting_time[i];    //sum the response time of all the processes
   }

    avg_turnaround_time = total_tunraround_time / num_processes;   //calculate the average turnaround time
    avg_response_time   = total_response_time / num_processes;   //calculate the average response time
    avg_waiting_time    = total_waiting_time / num_processes; //calculate the average waiting time
}

void Rr::displayResults()
{
    std::cout << "RR " << avg_turnaround_time << " " << avg_response_time << " " << avg_waiting_time << std::endl;
}