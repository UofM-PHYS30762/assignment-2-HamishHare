// PHYS30762 Programming in C++
// Assignment 2

// Program to compute mean, standard deviation and standard
// error of a chosen set of courses. Data is read from file.

// Hamish Hare -- adapted from skeleton code.

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>

#include<vector>
#include<string>
using std::string;
#include<cstring> // TEMP
//#include<sstream>

// Helper functions
// .. Read in all the lines from a file and return as a vector of strings
std::vector<string> read_lines_from_file(string file_name)
{
  // Open file
  // (Maybe open the file elsewhere and just pass the filestream by
  //  reference into this function, rather than the file name)
  std::ifstream course_stream(file_name);
  // TODO: Validation! e.g. empty files, etc.
  
  // Make each line (as a string) into a vector entry
  string current_line;
  std::vector<string> all_lines;
  while (std::getline(course_stream, current_line))
  {
    all_lines.push_back(current_line);
  }
  course_stream.close();
  return all_lines;
}

// .. Compute the mean and standard deviation of given scores.
// TODO

// Main function
int main()
{
  // Define variables
  //char data_file[100];
  // int number_courses;

  // Ask user to enter filename
  // TODO
  const string data_file_name{"courselist.dat"};
  //std::cout<<"Enter data filename: ";
  //std::cin>>data_file;

  // Open file (you must check if successful)
  //std::fstream course_stream(data_file);
  //std::ifstream course_stream(data_file);

  // Read in all the lines from the file
  std::vector<string> all_file_lines = read_lines_from_file(data_file_name);

  // Allocate memory for data 

  // Read data from file
  //e.g. 
  //for(int i{};i<Ndata;i++) 
  //  {
  //
  //  }

  // Close file
  //course_stream.close();

  // Print number of courses requested

  // Compute mean, standard deviation and  standard error of mean

  // Free memory


  return 0;
}
