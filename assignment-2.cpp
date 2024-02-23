// PHYS30762 Programming in C++
// Assignment 2

// Program to compute mean, standard deviation and standard
// error of a chosen set of courses. Data is read from file.

// Hamish Hare -- adapted from skeleton code.

#include<iostream>
#include<iomanip>
#include<fstream>
//#include<cmath>
#include<math.h>

#include<vector>
#include<string>
using std::string; using std::vector;
#include<numeric>
//#include<sstream>

// Constants
typedef std::tuple<double, int, string> course_tuple;

// Functions
// .. Read in all the lines from a file and return as a vector of strings
vector<string> read_lines_from_file(string file_name)
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
  vector<string> all_lines;
  while (std::getline(course_stream, current_line))
  {
    all_lines.push_back(current_line);
  }
  // Close file
  course_stream.close();
  return all_lines;
}

// Split each course entry into component parts
vector<course_tuple> get_course_info(vector<string> &all_lines)
{
  vector<course_tuple> all_courses_info;
  // Iterate over all the lines in the file and add a course detail
  // tuple to the all_courses_info vector:
  double grade;
  int course_code;
  string course_title;
  vector<string>::iterator line_entry;
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
vector<double> extract_grades(vector<course_tuple>& course_info)
{
  // TODO:
  // - Validation? Maybe check for empty vector first?
  vector<double> all_grades;
  // Iterate over all course entries to extract the grade
  double grade;
  vector<course_tuple>::iterator course_entry;
  for(course_entry=course_info.begin(); course_entry<course_info.end();
      ++course_entry)
  {
    grade = std::get<0>(*course_entry);
    all_grades.push_back(grade);
  }
  return all_grades;
}

// .. Compute the mean of given scores
double compute_mean(vector<double>& grades)
{
  // TODO: Validation?
  if(grades.size()==0) return 0;
  else
  {
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    double mean = sum / grades.size();
    return mean;
  }
}

// .. Compute the standard deviation of given scores
double compute_standard_deviation(vector<double>& grades)
{
  // TODO: Validation?
  if(grades.size()==0) return 0;
  else
  {
    double mean = compute_mean(grades);
    // Compute the required sum of difference from the mean squared
    double summed_difference_squared{0};
    for(vector<double>::iterator grade=grades.begin();
        grade<grades.end(); ++grade)
    {
      summed_difference_squared += std::pow(*grade - mean, 2);
    }
    // Calculate the standard deviation
    double sqrt_term = (1.0/(grades.size()-1.0)) * summed_difference_squared;
    double standard_deviation = std::pow(sqrt_term, 0.5);
    return standard_deviation;
  }
}

// .. Compute the standard error on the mean
double compute_error_on_mean(double standard_deviation, size_t num_elements)
{
  // TODO: Validation?
  if(num_elements==0) return 0;
  else return standard_deviation/std::pow(num_elements, 0.5);
}

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
  vector<string> all_file_lines = read_lines_from_file(data_file_name);
  size_t num_courses{all_file_lines.size()};

  // Split each line into grade, course code, and course title
  vector<course_tuple> all_course_details = get_course_info(all_file_lines);

  // Close file
  //course_stream.close();

  // Print out list of all courses (correctly formatted)

  // Print number of courses requested

  // Compute mean, standard deviation and standard error of mean
  // TEST: Extract all grades and find mean
  vector<double> test{1.0, 2.0, 3.0, 4.0};
  // vector<double> all_grades = extract_grades(all_course_details);
  // double mean{compute_mean(all_grades)};
  double standard_deviation{compute_standard_deviation(test)};
  double error_on_mean = compute_error_on_mean(standard_deviation, test.size());

  // Free memory

  return 0;
}
