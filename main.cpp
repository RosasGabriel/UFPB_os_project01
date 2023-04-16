#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "include/fcfs.hpp"
#include "include/sjf.hpp"
#include "include/rr.hpp"

int main() {
  Fcfs fcfs;
  std::string filename = "input.txt"; // Change this to the actual filename

  fcfs.readInputFile(filename);
  fcfs.execute();
  fcfs.displayResults();
  
  return 0;
}