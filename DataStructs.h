//
// Created by gustavobastos on 13/03/26.
//

#ifndef DA_PROJECT_1_DATASTRUCTS_H
#define DA_PROJECT_1_DATASTRUCTS_H

#include <string>

#include <vector>


struct submission{
    int id;
    int primary;
    int secondary = -1;
    std::string title="";
    std::string name="";
    std::string email="";

};

struct reviewer{
    int id;
    int primary;
    int secondary = -2;
    std::string name="";
    std::string email="";

};


struct int_node {
    int integer;
    bool is_sub=false;
};

bool operator< (const int_node& i1,const int_node& i2) ;
bool operator== (const int_node& i1,const int_node& i2);
/*
struct article {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string title="";
};

struct reviewer {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string name="";

};*/

struct assignment {
    const submission* a;
    const reviewer* rw;
};

struct failedAssignment {
    const submission* a;
    unsigned int missingSubmissions;
};



#endif //DA_PROJECT_1_DATASTRUCTS_H