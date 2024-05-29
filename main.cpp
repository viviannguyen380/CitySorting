#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Data.h"
#include "DataList.h"
#include "File_Functions.h"
using namespace std::chrono;
//read in File.txt (contains all the cities)
int main() {
   intro(); //greet user
    std::cout << "Would you like to use the program? (Y/N):" << std::endl;
    std::string choose;
    std::cin >> choose;
    DataList<Data>*d=nullptr;
    if (choose == "Y"|| choose == "y") {
       //create a dynamically allocated linked list to store information in
       d= new DataList<Data>();
       std::cout << "Enter a valid file name: " << std:: endl;
       std::string file; std::cin>>file;
       read_from_file(d, file);
 
       d->print();
       string select="";
       while (select!="n" && select!="N"){
         std::cout << "Would you like to use Selection Sort (S) or Remove (R)? (S/R):" << std::endl;
         std::string choice; std::cin>>choice;
      
        //use selection sort
        if (choice == "S" || choice == "s"){
            std::cout << "Would you like to sort by the 2023 Population (P) or by City (C)? (P/C):" << std::endl;
            std::string choices; std::cin >> choices;
            if (choices=="C"|| choices=="c"){
             d->selection_sort_name();
            }
            else{
             d->selection_sort_number();
            }
             d->print();
           }
          //use remove
           else{
             if (d!=nullptr){
               string toRemove="";
               cout<<"Enter a city name to remove: ";
               cin>>toRemove;
               typename DataList<Data>::Iterator iter = d->begin();
         
               bool found=false;
               while (!iter.equals(d->end())){  //as long as iter doesn't reach end
                 Data data=iter.get();
                   if (iter.get().get_word()==toRemove){
                     found=true;
                     break;
                }
               iter.next();
              }
        if (found==true){
          d->erase(iter);
          d->print();
        } else {
          cout<<"Invalid City name"<<endl;
        }
      }
    }
        cout<<"Would you like to repeat? Y/N ";
        cin>>select;
  } 
}
  //option to save to a file
      std::cout << "Would you like to save to a file? " << std::endl;
      std::string c; std::cin>>c;
      saveToFile(d,c);
      delete d;
      return 0;
}