#ifndef File_Functions_h
#define File_Functions_h
#include <iostream>
#include <string>
#include "Data.h"
#include "DataList.h"
#include <fstream>
#include <sstream>

//prints the intro message
void intro();
//prompts to enter a file name and write the data to the file
template<typename T>
void saveToFile(DataList<T>* dataList, std::string choice);
// reads in from a file
template<typename T>
void read_from_file(DataList<T> *d, std::string file); 
// writes to a file
template<typename T>
void write_to_file(DataList<T> *d, std::string file);  

template<typename T>
void saveToFile(DataList<T>* dataList, std::string choice){
  if (choice == "Y" || choice == "y") {
    std::cout << "Enter a file name: " << std::endl;
    std::string f; std::cin>>f;
    write_to_file(dataList, f);
    std::cout << "Have a nice day!" << std::endl;
  } else{
    std::cout << "Have a nice day!" << std::endl;
  }
}
//reads data from a file
template<typename T>
void read_from_file(DataList<T> *d, std::string file){
    //open file
    std::ifstream ifs;
    ifs.open(file);
    //input validation
    while(ifs.fail()){
        std::cout << "Error, enter a valid file name:" << std::endl;
        std::cin >> file;
        ifs.open(file);
    }
    std::string line="";
    //use getline to separate the data into variables
    while (getline(ifs, line) && !line.empty()){
        std::stringstream ss;
        std::string numbers;
        std::string gp22;
        std::string words;
        std::string country;
        std::string growth_rate;
        std::string tests;
        std::string quote;
        std::string rank;

        ss.str(line);
        getline(ss, numbers, ',');
        getline(ss, gp22, ',');
        getline(ss, quote, '"');
        getline(ss, words, '"');
        getline(ss, quote, ',');
        getline(ss, quote, '"');
        getline(ss, country, '"');
        getline(ss, quote, ',');
        getline(ss, growth_rate, ',');
        getline(ss, quote, '"');
        getline(ss, tests, '"');
        getline(ss, quote, ',');
        getline(ss, rank, ',');
        //place data into a Data array
        Data *newUser = new Data(stoi(numbers), stoi(gp22),
                                 words, country, stod(growth_rate),
                                 tests, stoi(rank));
      typename DataList<Data>::Iterator iter=d->begin();
      bool inserted=false;
      for (int i=0; i<d->get_size(); i++){
        string country_name=newUser->get_country();
        string iter_name=iter.get().get_country();
        if ((newUser->get_country()<(iter.get().get_country())) || (newUser->get_country()==iter.get().get_country() && newUser->get_word()<iter.get().get_word())){
          d->insert(iter,*newUser);
            inserted=true;
            break;
        }
        iter.next();
      }
      if (inserted==false){
        d->push_back(newUser);
      }

        delete newUser;
    }
}
//write data back to a file, separated by a comma
template<typename T>
void write_to_file(DataList<T> *d, std::string file){
    std::ofstream ofs;
    ofs.open(file);
    typename DataList<T>::Iterator iter=d->begin();
    int testInd=1;
    while (!iter.equals(d->end())){
      testInd++;
      T curr=iter.get();
        ofs << curr.get_number() << ","
            << curr.get_pop22() << ","
            << curr.get_word() << ","
            << curr.get_country() << ","
            << curr.get_growth_rate() << ","
            << curr.get_type() << ","
            << curr.get_rank() << std::endl;
      iter.next();
          
    }
}

#endif 