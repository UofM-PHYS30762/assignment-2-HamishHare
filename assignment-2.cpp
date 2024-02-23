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

// Constants
typedef std::tuple<double, int, string> course_tuple;

// Helper functions
// .. Read in all the lines from a file and return as a vector of strings
std::vector<string> read_lines_from_file(string file_name)
{
  // Open file
  // (Maybe open the file elsewhere and just pass the filestream by
  //  reference into this function, rather than the file name)
  std::ifstream course_stream(file_name);
  // TODO: Validation!
  // .. check for empty files
  // .. only include valid lines in return
  
  // Make each line (as a string) into a vector entry
  string current_line;
  std::vector<string> all_lines;
  while (std::getline(course_stream, current_line))
  {
    all_lines.push_back(current_line);
  }
  // Close file
  course_stream.close();
  return all_lines;
}

// Split each course entry into component parts
std::vector<course_tuple> get_course_info(std::vector<string> &all_lines)
{
  std::vector<course_tuple> all_courses_info;
  // Iterate over all the lines in the file and add a course detail
  // tuple to the all_courses_info vector:
  double grade;
  int course_code;
  string course_title;
  std::vector<string>::iterator line_entry;
  for(line_entry=all_lines.begin(); line_entry<all_lines.end(); ++line_entry)
  {
    // TODO:
    // - Validation
    // - Improve flexibility, rather than hardcoded splitting
    grade = std::stod((*line_entry).substr(0, 4));
    course_code = std::stoi((*line_entry).substr(5, 5));
    course_title =(*line_entry).substr(13);

    all_courses_info.push_back(std::make_tuple(grade, course_code, course_title));
  }
  
  return all_courses_info;
}

// .. Extract a vector of grades only from the vector of tuples
//    containing the full course info
//   (I am doing this to meet the marking criteria, which asks
//    for "Functions to calculate the mean and standard deviation
//    of an array and/or vector of real numbers", so rather than
//    just passing the vector of tuples and extracting the grade
//    I am extracting them here so that only the array of numbers
//    is passed in to the mean and std functions.)
std::vector<double> extract_grades(std::vector<course_tuple>& course_info)
{
  // TODO:
  // - Validation? Maybe check for empty vector first?
  std::vector<double> all_grades;
  // Iterate over all course entries to extract the grade
  double grade;
  std::vector<course_tuple>::iterator course_entry;
  for(course_entry=course_info.begin(); course_entry<course_info.end();
      ++course_entry)
  {
    grade = std::get<0>(*course_entry);
    all_grades.push_back(grade);
  }
  return all_grades;
}

// .. Compute the mean and standard deviation of given scores.
// TODO
// double compute_mean()
// {
  
// }

// Main function
int main()
{
  // Get filename from user
  string data_file_name;
  //string data_file_name{"courselist.dat"};
  std::cout<<"Enter data filename: ";
  // TODO: Validation
  std::getline(std::cin, data_file_name);

  // Open file (you must check if successful)
  //std::ifstream course_stream(data_file);

  // Read in all the lines from the file
  std::vector<string> all_file_lines = read_lines_from_file(data_file_name);
  size_t num_courses{all_file_lines.size()};

  // Split each line into grade, course code, and course title
  std::vector<course_tuple> all_course_details = get_course_info(all_file_lines);

  // Close file
  //course_stream.close();

  // Print out list of all courses (correctly formatted)

  // TEST: Extract all grades
  std::vector<double> all_grades = extract_grades(all_course_details);

  // Print number of courses requested

  // Compute mean, standard deviation and  standard error of mean

  // Free memory


  return 0;
}
