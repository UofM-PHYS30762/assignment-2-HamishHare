// PHYS30762 Programming in C++
// Assignment 2

// Program to compute mean, standard deviation and standard
// error of a chosen set of courses. Data is read from file.

// Hamish Hare -- adapted from skeleton code.

#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>
#include<limits>
#include<vector>
#include<string>
#include<tuple>
#include<numeric>
#include<algorithm>
#include<sstream>
using std::string; using std::vector;

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

// .. Split each course entry into component parts
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

// .. Filter a course list by given year
vector<course_tuple> filter_course_info(vector<course_tuple>& course_info,
                                        int year)
{
  vector<course_tuple> filtered_info;
  // Apply a filter that selects elements where the first digit of the 5
  // digit course code is equal to the given year
  copy_if(course_info.begin(), course_info.end(), std::back_inserter(filtered_info),
          [year](course_tuple& info){return std::get<1>(info)/10000 == year;});
  return filtered_info;
}


// .. Print out a (formatted) list of given courses
int print_formatted_course_list(vector<course_tuple>& course_info)
{
  if(course_info.size()==0) return 0;
  else
  {
    std::ostringstream course_name_stream;
    string course_name;

    std::cout<<"======================================="<<std::endl;
    std::cout<<"                COURSES"<<std::endl;
    std::cout<<"======================================="<<std::endl;

    // Iterate over all courses
    int course_code{0};
    string course_title;
    vector<course_tuple>::iterator course_entry;
    for(course_entry=course_info.begin(); course_entry<course_info.end();
        ++course_entry)
    {
      // Create the full course name
      course_code = std::get<1>(*course_entry);
      course_title = std::get<2>(*course_entry);
      course_name_stream<<"PHYS "<<course_code<<" "<<course_title<<std::endl;
      course_name = course_name_stream.str();
      course_name_stream.str(""); // clear stream
      // Output the name
      std::cout<<course_name;
    }
    std::cout<<"======================================="<<std::endl;
    return 1;
  }
}

// .. Get the user to choose which year(s) of courses they would like
string get_valid_selection()
{
  string user_input;
  bool valid{false};
  std::cout<<"Which year of courses would you like? (choose a year 1-4 or 'all'): ";
  // Prompt the user for input until a valid choice is given
  do
  {
    getline(std::cin, user_input);
    if(!(user_input == "1" || user_input == "2" || user_input == "3"
         || user_input == "4" || user_input == "all"))
    {
      std::cout<<"Please enter one of the allowed choices (1, 2, 3, 4 or all): ";
    }
    else valid = true;
  }while(!valid);

  // Return the output
  std::cout<<"You entered "<<user_input<<std::endl;
  return user_input;
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

// .. Print out the statistics for the selected courses
int print_statistics(double mean, double standard_deviation,
                     double error_on_mean)
{
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout<<std::setprecision(1);
  std::cout<<"Mean grade of selection: "<<mean<<std::endl;
  std::cout<<"Standard deviation: "<<standard_deviation<<std::endl;
  std::cout<<"Standard error on mean: "<<error_on_mean<<std::endl;
  std::cout<<"======================================="<<std::endl;
  return 0;
}

// Main function
int main()
{
  // Get filename from user
  // alstring data_file_name;
  string data_file_name{"courselist.dat"};
  // std::cout<<"Enter data filename: ";
  // TODO: Validation
  // std::getline(std::cin, data_file_name);

  // Open file (you must check if successful)
  //std::ifstream course_stream(data_file);

  // Read in all the lines from the file
  vector<string> all_file_lines = read_lines_from_file(data_file_name);
  size_t num_courses_total{all_file_lines.size()};

  // Split each line into grade, course code, and course title
  vector<course_tuple> all_course_details = get_course_info(all_file_lines);

  // Close file
  //course_stream.close();

  // Get the course selection, filtered either by year or 'all'
  string year_selection = get_valid_selection();
  vector<course_tuple> filtered_course_details;
  if (year_selection=="all")
  {
    filtered_course_details = all_course_details;
  }
  else
  {
    filtered_course_details = filter_course_info(all_course_details,
                                                 std::stoi(year_selection));
  }

  // Sort the course list appropriately
  // TODO

  // Print out list of all courses (correctly formatted)
  print_formatted_course_list(filtered_course_details);

  // Print number of courses requested
  size_t num_courses_filtered{filtered_course_details.size()};
  std::cout<<"Number of courses selected: "<<num_courses_filtered
           <<"/"<<num_courses_total<<std::endl;

  // Compute mean, standard deviation and standard error of mean
  // vector<double> test{1.0, 2.0, 3.0, 4.0};
  vector<double> filtered_grades = extract_grades(filtered_course_details);
  double mean{compute_mean(filtered_grades)};
  double standard_deviation{compute_standard_deviation(filtered_grades)};
  double error_on_mean = compute_error_on_mean(standard_deviation, num_courses_filtered);

  // Print out the statistics
  print_statistics(mean, standard_deviation, error_on_mean);

  // Free memory

  return 0;
}
