#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "include/fcfs.h"
#include "include/sjf.h"
#include "rr.h"

void ReadFile(std::string file_name)
{
    std::string file_path = "input.txt";

    std::ifstream file(file_path);

    if(file.is_open())
    {
        std::cout << "File opened succesfully!" << std::endl;

        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }

        file.close();
    }
    else
    {
        std::cerr << "Failed to open file!" << std::endl;
    }
}

int main()
{
    std::string filename = "input.txt";

    ReadFile(filename);

    return 0;
}