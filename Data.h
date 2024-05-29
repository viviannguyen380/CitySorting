#ifndef LAB3_DATA_H
#define LAB3_DATA_H

#include <string>
#include <iostream>
using namespace std;
class Data {

public:
  Data(); // default constructor
  Data(int num, int gp22, std::string word, std::string country, double gr_rate,
       std::string type, int rank); // constructor for array->overloaded
 // ~Data();
  // getters for all the data members
  int get_number() const;
  int get_pop22() const;
  std::string get_word() const;
  std::string get_country() const;
  double get_growth_rate() const;
  std::string get_type() const;
  int get_rank() const;

  // not necessary because only for merge sort operator
  bool operator<(Data b); // overloads the < sign
  //bool operator >(Data b);
  //Data& operator=(const Data& d);

  // sorting functions are listed below:
//not sorting functions, but are operators (inequalities functions)
  bool sort_words(Data a, Data b);   // sorts the city names alphabetically
  bool sort_numbers(Data a, Data b); // sorts the population sizes numerically
  ostream& operator<<(ostream& os);

//private attributes of each Data object representing a city
private:
  int number;
  int pop22;
  std::string city;
  std::string country;
  double growth_rate;
  std::string type;
  int rank;
};

#endif // LAB3_DATA_H