/* other.cpp */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#include "other.h"
using namespace std;
#define MAX_STR 200
/******************************************************************
*************************  PLAY  **********************************
******************************************************************/
Play::Play() :title("none"), playwright("none")
{ cast_list.insert({"none","none"}); }

Play::Play(const string t, const string p, 
           const map <string,string> & cast)
     :title(t), playwright(p), cast_list(cast) {}

bool Play::view_cast() const
{
    if(cast_list.empty()) return 0;
    cout <<"\n============ Cast List for " << title 
         <<" ============\n\t\tby "<< playwright <<"\n========"
         <<"==========================================\n"
         <<"\n  Role\t\t\t\tActor\n";
    for(auto it = cast_list.begin(); it != cast_list.end(); ++it)
    {
        cout <<"  "<< it->first <<"\t\t"<< it->second <<"\n";
    }
    cout <<"\n==================================================\n";
    return 1;
}

string Play::search_cast_list(const string role)
{
    map <string,string> ::iterator it;

    string actor;
    for(it = cast_list.find(role); it != cast_list.end(); ++it)
    {
        actor =  it->first ; //<< '\t' << it->second << '\n';
    }            
    return actor;
}
