#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "include/fcfs.hpp"
#include "include/sjf.hpp"
#include "include/rr.hpp"

int main() {
  std::string file_name = "input.txt"; // Change this to the actual filename, if needed

  Fcfs fcfs;
  // Sjf sjf;
  Rr rr;

  fcfs.readInputFile(file_name);
  fcfs.execute();
  fcfs.displayResults();

  // sjf.readInputFile(file_name);
  // sjf.execute();
  // sjf.displayResults();

  rr.readInputFile(file_name);
  rr.execute();
  rr.displayResults();
  
  return 0;
}