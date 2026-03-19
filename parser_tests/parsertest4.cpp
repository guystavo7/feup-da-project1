#include "../parser.h"

using namespace std;

int main(){
    string path =get_project_cwd("DA_Project_1")+ "/parser_tests/Inputs/dataset2.csv";


    params params = parse(path);


    bool passedalltests = true;

    vector<string> exp = {

    "1", "\"AI Planning Systems\"", "Alice Brown", "alice@gmail.com", "1", "2",
    "2", "\"Secure Databases\"", "Bob Smith", "bob@gmail.com", "2", "3",
    "3", "\"GPU Scheduling\"", "Carla Costa", "carla@gmail.com", "3", "4",

    "1", "John Miller", "jm@gmail.com", "1", "2",
    "2", "Sarah White", "sw@gmail.com", "2", "3",
    "3", "Pedro Lopes", "pl@gmail.com", "3", "4",
    "4", "Rui Gomes", "rg@gmail.com", "3", "1",
    "5", "Ana Torres", "at@gmail.com", "1", "3",
    "6", "Luis Costa", "lc@gmail.com", "2", "4",
    "7", "John Miller", "jm@gmail.com", "1", "2",
    "8", "Sarah White", "sw@gmail.com", "2", "3",
    "9", "Pedro Lopes", "pl@gmail.com", "3", "1",

    "2", "3", "1", "0", "1", "0",

    "1", "0", "output_dataset2.csv"

    };

    int counter = 0;   
    int exp_i = 0;    


    for (submission sub : params.submissions){
        counter++;
        if (to_string(sub.id) != exp[exp_i]) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        exp_i++;
        if (sub.title != exp[exp_i]) {cout << counter << ": Wrong sub title: " << sub.title << endl; passedalltests = false;}
        exp_i++;
        if (sub.name != exp[exp_i]) {cout << counter << ": Wrong sub authors: " << sub.name << endl; passedalltests = false;}
        exp_i++;
        if (sub.email != exp[exp_i]) {cout << counter << ": Wrong sub email: " << sub.email << endl; passedalltests = false;}
        exp_i++;
        if (to_string(sub.primary) != exp[exp_i]) {cout << counter << ": Wrong sub primary: " << sub.primary << endl; passedalltests = false;}
        exp_i++;
        if (to_string(sub.secondary) != exp[exp_i]) {cout << counter << ": Wrong sub secondary: " << sub.secondary << endl; passedalltests = false;}
        exp_i++;
    }


    counter = 0;


    for (reviewer rev : params.reviewers){
        counter++;
        if (to_string(rev.id) != exp[exp_i]) {cout << counter << ": Wrong rev id: " << rev.id << endl; passedalltests = false;}
        exp_i++;
        if (rev.name != exp[exp_i]) {cout << counter << ": Wrong rev name: " << rev.name << endl; passedalltests = false;}
        exp_i++;
        if (rev.email != exp[exp_i]) {cout << counter << ": Wrong rev email: " << rev.email << endl; passedalltests = false;}
        exp_i++;
        if (to_string(rev.primary) != exp[exp_i]) {cout << counter << ": Wrong rev primary: " << rev.primary << endl; passedalltests = false;}
        exp_i++;
        if (to_string(rev.secondary) != exp[exp_i]) {cout << counter << ": Wrong rev primary: " << rev.secondary << endl; passedalltests = false;}
        exp_i++;
    }


    if (params.MinReviewsPerSubmission != stoi(exp[exp_i])) {cout << "Wrong MinReviewsPerSubmission parameter: " << params.MinReviewsPerSubmission << endl; passedalltests = false;}
    exp_i++;

    if (params.MaxReviewsPerReviewer != stoi(exp[exp_i])) {cout << "Wrong MaxReviewsPerReviewer parameter: " << params.MaxReviewsPerReviewer << endl; passedalltests = false;}
    exp_i++;

    if (params.PrimaryReviewerExpertise != stoi(exp[exp_i])) {cout << "Wrong PrimaryReviewerExpertise parameter: " << params.PrimaryReviewerExpertise << endl; passedalltests = false;}
    exp_i++;

    if (params.SecondaryReviewerExpertise != stoi(exp[exp_i])) {cout << "Wrong SecondaryReviewerExpertise parameter: " << params.SecondaryReviewerExpertise << endl; passedalltests = false;}
    exp_i++;  

    if (params.PrimarySubmissionDomain != stoi(exp[exp_i])) {cout << "Wrong PrimarySubmissionDomain parameter: " << params.PrimarySubmissionDomain << endl; passedalltests = false;}
    exp_i++;

    if (params.SecondarySubmissionDomain != stoi(exp[exp_i])) {cout << "Wrong SecondarySubmissionDomain parameter: " << params.SecondarySubmissionDomain << endl; passedalltests = false;} 
    exp_i++;

    if (params.GenerateAssignments != stoi(exp[exp_i])) {cout << "Wrong GenerateAssignments: " << params.GenerateAssignments << endl; passedalltests = false;}
    exp_i++;

    if (params.RiskAnalysis != stoi(exp[exp_i])) {cout << "Wrong RiskAnalysis: " << params.RiskAnalysis << endl; passedalltests = false;}
    exp_i++;

    if (params.OutputFileName != exp[exp_i]) {cout << "Wrong OutputFileName: " << params.OutputFileName << endl; passedalltests = false;}
    exp_i++;

    if (passedalltests){
        cout << "Test nº4 passed" << endl;
    }
    
    return 0;
}