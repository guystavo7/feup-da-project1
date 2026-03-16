#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct submission{
    int id;
    string title="";
    string name="";
    string email="";
    int primary;
    int secondary = -1;
};

struct reviewer{
    int id;
    string name="";
    string email="";
    int primary="";
    int secondary = -1;
};

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