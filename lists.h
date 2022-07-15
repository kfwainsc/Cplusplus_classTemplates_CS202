/* lists.h */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#ifndef LISTS_H 
#define LISTS_H 

#include <memory>
#include <iostream> 
/******************************************************************
***************************  NODE  ********************************
******************************************************************/
template <typename T> 
class Node
{
    public:
        Node(); //default 
        Node(T & in_data); //new node made with data

        /* Job: set next ptr to passed in node 
        ** Ret: addr of next node */
        void set_next(Node<T>* new_next);
        
        /* Job: set prev ptr to passed in node 
        ** Ret: addr of prev node */
        void set_prev(Node<T>* new_prev);
    
        /* Job: get/check for next node
        ** Returns: next node, else nullptr */ 
        Node<T>*& go_next();

        /* Job: get/check for prev node
        ** Returns: previous node, else nullptr */ 
        Node<T>*& go_prev();

        /* Job: prints data contents of node, ostream op
        ** of the data class must be overloaded to work */
        bool display() const;

    protected:
        T data; // T placeholder for type chosen in implementation 
        Node<T>* next; 
        Node<T>* prev; 

};
/******************************************************************
***************************  DLL  *********************************
******************************************************************/
template <typename T> 
class DLL
{
    public:
        DLL(); //default
        //DLL(const DLL & source); //cc

        /* Job: release dynamic memory */ 
        ~DLL();

        /* Job: add reservation to list
        ** Ret: returns num guests added */
        bool add(T & data);

        /* Job: remove reservation from list
        ** Ret: successful true, else false */
        bool remove();

        /* Job: call node func to alter a reservation
        ** Ret: true if changes, else false  */
        bool find(std::string & key);

        /* Job: display all reservations in list
        ** Ret: true if not empty, else false */
        int display_list() const;

    protected:
        Node<T>* head;
        Node<T>* tail;

        /* Job: delete entire list recursively 
        ** Ret: count of items deleted */
        int delete_list(Node<T>* & head);

        /* Job: recursively print list
        ** Ret: count of items printed */
        int display(Node<T>* head) const;

};
/******************************************************************
******************************************************************/
#endif

