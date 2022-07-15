/* lists.cpp */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#include "lists.h"
using namespace std;
/******************************************************************
***************************  NODE  ********************************
******************************************************************/
template <typename T> 
Node<T>::Node() :next(nullptr), prev(nullptr) {}
//{ next = nullptr; } //default 


template <typename T> 
Node<T>::Node(T & in_T):data(in_T), next(nullptr), prev(nullptr){}

template <typename T> //set next ptr to passed in node
void Node<T>::set_next(Node<T>* new_next)
{ next = new_next; }

template <typename T> //set next ptr to passed in node
void Node<T>::set_prev(Node<T>* new_prev)
{ prev = new_prev; }

template <typename T> //move to next node in list
Node<T>*& Node<T>::go_next()
{ return next; }

template <typename T> //move to next node in list
Node<T>*& Node<T>::go_prev()
{ return prev; }

template <typename T> 
bool Node<T>::display() const
{    cout << data; 
    return 1;       
}
/******************************************************************
****************************  DLL  ********************************
******************************************************************/
template <typename T> 
DLL<T>::DLL() :head(nullptr), tail(nullptr) {}//default contructor 

//template <typename T>
//DLL<T>::DLL(const DLL & source){}

template <typename T>
DLL<T>::~DLL()
{
    delete_list(head);
    head = tail = nullptr;
} 

template <typename T> 
bool DLL<T>::add(T & data)
{
    if(!head)
    {
        head = new Node<T>(data);
        head->set_next(nullptr);
        head->set_prev(nullptr);
        tail = head;
    }else{
        Node<T>* node = new Node<T>(data);
        node->set_next(nullptr);
        node->set_prev(nullptr);
        node->set_next(head);
        head->set_prev(node);
        head = node;
    }
    return 1; 
}

template <typename T> 
bool DLL<T>::remove(){ return 0;}

template <typename T>
bool DLL<T>::find(string & key){ return 0;}

template <typename T>
int DLL<T>::display_list() const
{
    if(!head) return 0;
    return display(head);    
}

template <typename T>
int DLL<T>::delete_list(Node<T>* & head)
{
    if(!head) return 0;
    Node<T>* hold = head->go_next();
    delete head;
    head = hold;
    return delete_list(head) +1;    
}

template <typename T>
int DLL<T>::display(Node<T>* head) const
{
    if(!head) return 0;
    head->display();
    cout <<"\n\n";
    return display(head->go_next()) +1;    
}
/******************************************************************
******************************************************************/

