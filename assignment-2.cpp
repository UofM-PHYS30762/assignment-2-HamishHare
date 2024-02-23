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
#include<cstring> // TEMP
//#include<sstream>

// Helper functions
// .. Read in all the lines from a file and return as a vector of strings
//std::vector<std::string> read_lines_from_file(char& filename)
int read_lines_from_file()
{
  char data_file[100];
  std::strcpy(data_file, "courselist.dat");

  // Open file (you must check if successful)
  std::ifstream course_stream(data_file);

  std::string current_line;
  std::vector<std::string> all_lines;
  while (std::getline(course_stream, current_line))
  {
    all_lines.push_back(current_line);
  }
  //return all_lines;
  return 0;
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
  //std::cout<<"Enter data filename: ";
  //std::cin>>data_file;

  // Open file (you must check if successful)
  //std::fstream course_stream(data_file);
  //std::ifstream course_stream(data_file);

  // TEST: read lines from file
  int test = read_lines_from_file();

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
