#include <iostream>
#include <fstream>

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

}

void Rr::displayResults()
{
    std::cout << "RR " << avg_turnaround_time << " " << avg_response_time << " " << avg_waiting_time << std::endl;
}