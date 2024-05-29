#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

//default constructor initializes all data members
Data::Data() {
    int num = 0;
    int gp22 = 0;
    std::string words = "";
    std::string country = "";
    double gr_rate = 0.0;
    std::string test = "";
    int rank = 0;
}
//constructor used for the Data array parameters
Data::Data(int num, int gp22, std::string word, std::string country, double gr_rate, std::string type,
           int rank) {
    this->number = num;
    this->pop22 = gp22;
    this->city = word;
    this->country = country;
    this->growth_rate = gr_rate;
    this->type = type;
    this->rank = rank;

}

//Accessor Functions
// @returns global population in the year 2023
int Data::get_number() const {  
    return this->number;
}
// @returns for global population in the year 2022
int Data::get_pop22() const {
    return this->pop22;
}
// @returns for the city name
std::string Data::get_word() const {
    return this->city;
}
// @returns for the country name
std::string Data::get_country() const {
    return this->country;
}
// @returns for the growth rate
double Data::get_growth_rate() const {
    return this->growth_rate;
}
// @returns for the type
std::string Data::get_type() const {
    return this->type;
}
// @returns for the rank (in terms of population)
int Data::get_rank() const {
    return this->rank;
}

ostream& Data::operator<<(ostream& ofs){
  ofs << this->get_number() << ","
            << this->get_pop22() << ","
            << this->get_word() << ","
            << this->get_country() << ","
            << this->get_growth_rate() << ","
            << this->get_type() << ","
            << this->get_rank() << std::endl;
  return ofs;
}