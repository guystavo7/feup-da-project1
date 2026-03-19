
#ifndef DA_PROJECT_1_PARSER_H
#define DA_PROJECT_1_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "DataStructs.h"

using namespace std;

/*
struct submission{
    int id;
    int primary;
    int secondary = -1;
    string title="";
    string name="";
    string email="";
};

struct reviewer{
    int id;
    int primary;
    int secondary = -2;
//old parser
 //   string name;
 //   string email;
 //   int primary;
 //   int secondary = -2;
  
    string name="";
    string email="";
  
};
*/

struct params{
    vector<submission> submissions;
    vector<reviewer> reviewers;

    int MinReviewsPerSubmission;
    int MaxReviewsPerReviewer;
    int PrimaryReviewerExpertise;
    int SecondaryReviewerExpertise;
    int PrimarySubmissionDomain;
    int SecondarySubmissionDomain;

    int GenerateAssignments;
    int RiskAnalysis;
    string OutputFileName;
};

params parse(string file);


string get_project_cwd(const string &project_name);


#endif //DA_PROJECT_1_DATASTRUCTS_H