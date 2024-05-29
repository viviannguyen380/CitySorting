#ifndef DataList_h
#define DataList_h
#include "Data.h" 
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iomanip>

template<typename T>
class DataList{
private:
  class Node{
  public:
    Node(T* element);
    T data;
    Node* previous;
    Node* next;
  };
public:
  class Iterator{
  public:
    Iterator();
    const T get() const;
    void next();
    void previous();
    bool equals(Iterator other) const;
  private:
    Node* position;
    DataList* container;
    friend class DataList;
  };
  DataList();
  DataList(const DataList& other);
  ~DataList();
  void free();
  void copy(const DataList& other);
  DataList& operator=(const DataList& other);
  void push_back(T* element);
  void insert(const Iterator& iter,  T& element);
  Iterator erase(const Iterator& iter);
  Iterator begin();
  Iterator end();
  void selection_sort_name();
  void selection_sort_number();
  void print();
  int get_size() const;
  private:
    int size;
    Node* first;
    Node* last;
 };

//Node Class
//Node Iterator
template<typename T>
DataList<T>::Node::Node(T* element){
    data=*element;
    previous=nullptr;
    next=nullptr;
}

//Iterator Class
//Iterator Constructor
template<typename T>
DataList<T>::Iterator::Iterator(){
    position=nullptr;
    container=nullptr;
}

// @return the position of the Data
template<typename T>
const T DataList<T>::Iterator::get() const{
    return position->data;
}
//Iterator Functions
//set position to the next Node
template<typename T>
void DataList<T>::Iterator::next(){
    position=position->next;
}

/* 
 * if the position is empty, 
 * set position to the last stored Data
 * else set positon to the Node before
 */
template<typename T>
void DataList<T>::Iterator::previous(){
    if (position==nullptr){
        position=container->last;
    }
    else{
        position=position->previous;
    }
}

// @returns if a position is equal to another position
template<typename T>
bool DataList<T>::Iterator::equals(Iterator other) const{
    return position==other.position;
}

//DataList Class
//DataList Constructor(s)
template<typename T> 
DataList<T>::DataList(){  //Default Constructor
    first=nullptr;
    last=nullptr;
    size=0;
}
template <typename T>    //Overload Constructor
DataList<T>::DataList(const DataList& other){
   copy(other);
}
template <typename T> 
DataList<T>::~DataList(){  //Destructor
   free();
}

//DataList Functions
//Deletes linked list, prevents memory leak
template <typename T>
void DataList<T>::free(){
   Node* to_delete = first;
   while (to_delete != nullptr){
      Node* next_to_delete = to_delete->next;
      delete to_delete;
      to_delete = next_to_delete;
   }
}
//Copy DataList to another Linked List
template <typename T>
void DataList<T>::copy(const DataList& other){
   Node* just_copied = nullptr;
   Node* next_to_copy = other.first;
   first = nullptr;
   last = nullptr;
   while (next_to_copy != nullptr){
      Node* copy = new Node(next_to_copy->data);
      copy->previous = just_copied;
      if (just_copied == nullptr){
         first = copy;
      } else{
         just_copied->next = copy;
      }
      if (next_to_copy == other.last){
         last = copy;
      }
      next_to_copy = next_to_copy->next;
      just_copied = copy;
   }
}
// Operator Overload
template <typename T>
DataList<T>& DataList<T>::operator=(const DataList& other)
{
   if (this != &other){
      free();
      copy(other);
   }      
}
// Adds a new elemnt to the end of the Linked List
template<typename T>
void DataList<T>::push_back(T* element){
    Node* new_node=new Node(element);
    if (last==nullptr){
        first=new_node;
        last=new_node;
    } else{
        new_node->previous=last;
        last->next=new_node;
        last= new_node;
    }
  size++;
}
// Insert new element into a specific itter (position)
template<typename T>
//should be const before element
void DataList<T>::insert(const Iterator& iter,  T& element){
    if (iter.position==nullptr){
        push_back(&element);
        return;
    }
    Node* after= iter.position;
    Node* before=after->previous;
    Node* new_node=new Node(&element);
    new_node->previous=before;
    new_node->next=after;
    after->previous=new_node;
    if (before==nullptr){
        first=new_node;
    } else{
        before->next=new_node;
    }
  size++;
}
// Erase element from the iter (position) given
template<typename T>
typename DataList<T>::Iterator DataList<T>::erase(const Iterator& iter){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Node* remove=iter.position;
    Node* before=remove->previous;
    Node* after= remove->next;
    if (remove==first){
        first=after;
    } else{
        before->next=after;
    }
    if (remove==last){
        last=before;
    } else{
        after->previous=before;
    }
    delete remove;
    Iterator r;
    r.position=after;
    r.container=this;
    size--;
    return r;
}
// Sets position to the beginning of the list
template<typename T>
typename DataList<T>::Iterator DataList<T>::begin(){
    Iterator iter;
    iter.position=first;
    iter.container=this;
    return iter;
}
// Sets position to the end of the list
template<typename T>
typename DataList<T>::Iterator DataList<T>::end(){
    Iterator iter;
    iter.position=nullptr;
    iter.container=this;
    return iter;
}
// Selection Sort Algorithim
// Sort by Name
template <typename T>
void DataList<T>::selection_sort_name(){
  Node* curr=first; 
  Node* advancer;
  Node* smallest;
  while (curr!= nullptr){
    //the advancer compares every node's data with the smallest
    advancer=curr->next;
    smallest=curr;
    string first_name=smallest->data.get_word();
    while ((advancer)!=nullptr){
      if (advancer!=nullptr && advancer->data.get_word() <first_name){
        smallest=advancer;
        first_name=smallest->data.get_word();
      } 
      advancer=advancer->next;
    }
    //swap
    T data_temp=curr->data; 
    curr->data=smallest->data; 
    smallest->data=data_temp; 
    curr=curr->next; 
    
  }
}
//Sort by Population
template <typename T>
void DataList<T>::selection_sort_number(){
  Node* curr=first;
  Node* prev=nullptr;
  Node* advancer;
  Node* largest;
  Iterator pos=this->begin();
  while (curr!= nullptr){
    advancer=curr->next;
    largest=curr;
    Iterator adv_pos=this->begin();
    int num=largest->data.get_number();
    while (advancer!=nullptr){
      if (advancer!=NULL && advancer->data.get_number()>num){
        largest=advancer;
        num=largest->data.get_number();
      } 
      advancer=advancer->next;
    }
    Data data_temp=curr->data;
    curr->data=largest->data;
    largest->data=data_temp;  
    curr=curr->next;
  }
}

template<typename T>
void DataList<T>::print(){
  std::cout << "Would you like to see the top 10 (1), top 20 (2),"
            << "bottom 10 (3), or bottom 20 (4)?" << std::endl;
  std::cout << "Enter a number (1-4): " << std::endl;
  int n;
  std::cin>> n;
  std::cout << "     Pop23:    " << "Pop22:    " << " City:           "
            << "  Country:    " << "       Growth rate: " << " Type:  " 
            << " Rank: " << std::endl;
  if (n == 1) {    // Prints top 10
    Iterator iter=this->begin();
      for (int i = 0; i < 10; i++) {
        std::cout << i + 1 << ".";
        if (i + 1 < 10){ std::cout << " ";}
        cout<< std::left << std::setw(10) << iter.get().get_number() << std::left <<    std::setw(10)
            << iter.get().get_pop22() << std::left << std::setw(20) << iter.get().get_word() 
            << std::left << std::setw(22) << iter.get().get_country() <<std::left << std::setw(13)  
            << iter.get().get_growth_rate()<< std::setw(7) << iter.get().get_type() 
            << iter.get().get_rank() << std::endl;
        iter.next();
      }
    } else if (n == 2) {  // Print top 20
      Iterator iter=this->begin();
        for (int i = 0; i < 20; i++) {
          std::cout << i + 1 << ".";
          if (i + 1 < 10){ std::cout << " ";}
          cout<< std::left << std::setw(10) << iter.get().get_number() << std::left << std::setw(10)
              << iter.get().get_pop22() << std::left << std::setw(20) << iter.get().get_word() 
              << std::left << std::setw(22) << iter.get().get_country() <<std::left << std::setw(13)  
              << iter.get().get_growth_rate()<< std::setw(7) << iter.get().get_type() 
              << iter.get().get_rank() << std::endl;
          iter.next();
        }
    } else if (n == 3){  // Print bottom 10
      Iterator iter=this->end();
      for (int i = 0; i < 10; i++) {
        iter.previous();
        std::cout << i + 1 << ".";
        if (i + 1 < 10){ std::cout << " ";}
        if (i + 1 < 1000){ std::cout << "  ";}
        cout<<std::left << std::setw(10) << iter.get().get_number() << std::left << std::setw(10)
            << iter.get().get_pop22() << std::left << std::setw(20) << iter.get().get_word() 
            << std::left << std::setw(22) << iter.get().get_country() <<std::left << std::setw(13)  
            << iter.get().get_growth_rate()<< std::setw(7) << iter.get().get_type() 
            << iter.get().get_rank() << std::endl;
        }
    } else if (n == 4) { // Print bottom 20
        Iterator iter=this->end();
        for (int i = 0; i < 20; i++) {
          iter.previous();
          std::cout << i + 1 << ".";
          if (i + 1 < 10){ std::cout << " ";}
          if (i + 1 < 1000){ std::cout << "  ";}
          cout<<std::left << std::setw(10) << iter.get().get_number() << std::left << std::setw(10)
              << iter.get().get_pop22() << std::left << std::setw(20) << iter.get().get_word() 
              << std::left << std::setw(22) << iter.get().get_country() <<std::left << std::setw(13)  
              << iter.get().get_growth_rate()<< std::setw(7) << iter.get().get_type() 
              << iter.get().get_rank() << std::endl;
        }
    }
}

//Accessor Function
template<typename T>
int DataList<T>::get_size() const{
  return size;
}

#endif