/* other.h */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#ifndef OTHER_H
#define OTHER_H 

#include <iostream>
#include <string>
#include <cstring>
#include <map>
using namespace std;

/******************************************************************
*************************  PLAY  **********************************
******************************************************************/
/*DATA MEMBERS:     string title        - play title
                 string playwright    - name of playwright
                 map <string,string> cast_list */
class Play
{
    public:
        Play();
        Play(const string title, const string playwright, 
             const map <string,string> & cast_list); 
   
        /* Job: print entire cast list 
        ** Ret: true if not empty, else false */ 
        bool view_cast() const;

        /* Job: finds actor playing given role
        ** Args: role to lookup
        ** Ret: actor playing it */ 
        string search_cast_list(const string role);

    protected:
        string title;
        string playwright;
        map <string,string> cast_list;
};

#endif
