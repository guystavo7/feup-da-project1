#include "parser.h"

#include <cstring>
#include <unistd.h>

using namespace std;



void trimer(string &word){
    while (!word.empty() && word[0] == ' '){
        word.erase(0,1);
    }
}



map<string, int> readLayout(string line) {
    map<string, int> m;
    while (!line.empty() && line[0] == '#'){
        line.erase(0,1);
    }

    int curr = 0;

    string word;
    stringstream ss(line);

    while (getline(ss, word, ',')){
        trimer(word);

        m[word] = curr;
        

        curr++;
    }

    return m;
}

submission readSubmission(params &params, string line, map<string, int> order){

    submission res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        if (!word.empty()) fields.push_back(word);
    }

    if (order.find("Id") != order.end()){
        try{
            res.id = stoi(fields[order["Id"]]);
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }
    if (order.find("Title") != order.end()) {
        res.title = fields[order["Title"]];
    } else{
        params.valid = false;
    }
    if (order.find("Authors") != order.end()) {
        res.name = fields[order["Authors"]];
    } else{
        params.valid = false;
    }
    if (order.find("E-mail") != order.end()) {
        res.email = fields[order["E-mail"]];
    } else{
        params.valid = false;
    }
    if (order.find("Primary") != order.end()) {
        try{
            res.primary = stoi(fields[order["Primary"]]);
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }
    if (order.find("Secondary") != order.end()) {
        try{
            res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -1;
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }

    return res;
}

reviewer readReviewer(params &params, string line, map<string, int> order){

    reviewer res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        if (!word.empty()) fields.push_back(word);
    }

    if (order.find("Id") != order.end()){
        try{
            res.id = stoi(fields[order["Id"]]);
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }
    if (order.find("Name") != order.end()) {
        res.name = fields[order["Name"]];
    } else{
        params.valid = false;
    }
    if (order.find("E-mail") != order.end()) {
        res.email = fields[order["E-mail"]];
    } else{
        params.valid = false;
    }
    if (order.find("Primary") != order.end()) {
        try{
            res.primary = stoi(fields[order["Primary"]]);
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }
    if (order.find("Secondary") != order.end()) {
        try{
            res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -2;
        } catch (...){
            params.valid = false;
        }
    } else{
        params.valid = false;
    }
    
    

    return res;
}

void readParameter(params &params, vector<int> &steps, string line){

    stringstream ss(line);

    string name;
    getline(ss, name, ',');
    trimer(name);

    string value;
    getline(ss, value, ',');
    trimer(value);
    int valueint;
    try{
        valueint = stoi(value);
    } catch (...){
        params.valid = false;
    }

    if (name == "MinReviewsPerSubmission"){params.MinReviewsPerSubmission = valueint; steps[0] += 1;}
    else if (name == "MaxReviewsPerReviewer"){params.MaxReviewsPerReviewer = valueint; steps[1] += 1;}
    else if (name == "PrimaryReviewerExpertise"){params.PrimaryReviewerExpertise = valueint; steps[2] += 1;}
    else if (name == "SecondaryReviewerExpertise"){params.SecondaryReviewerExpertise = valueint; steps[3] += 1;}
    else if (name == "PrimarySubmissionDomain"){params.PrimarySubmissionDomain = valueint; steps[4] += 1;}
    else if (name == "SecondarySubmissionDomain"){params.SecondarySubmissionDomain = valueint; steps[5] += 1;}

}

void readControl(params &params, vector<int> &steps, string line){
    
    
    stringstream ss(line);

    string name;
    getline(ss, name, ',');
    trimer(name);

    string value;
    getline(ss, value, ',');
    trimer(value);

    while (!value.empty() && !isalnum(value.front())){value.erase(0,1);}
    while (!value.empty() && !isalnum(value.back())){value.pop_back();}

    if (name == "GenerateAssignments"){
        try{
            params.GenerateAssignments = stoi(value);
        } catch (...){
            params.valid = false;
        }
        steps[0] += 1;
    }
    if (name == "RiskAnalysis"){
        try{
            params.RiskAnalysis = stoi(value);
        } catch (...){
            params.valid = false;
        }
        steps[1] += 1;
    }
    if (name == "OutputFileName"){
        params.OutputFileName = value;
        steps[2] += 1;
    }

    
}

params parse(string path){


    vector<submission> submissions;
    vector<reviewer> reviewers;

    params params;
    params.valid = true;

    ifstream filestream(path);
    string line;

    vector<int> steps = {0, 0, 0, 0};
    vector<int> parameterSteps = {0, 0, 0, 0, 0, 0};
    vector<int> controlSteps = {0, 0, 0};

    int reading = -1; //1: reading submissions; 2: reading reviewers; 3: reading parameters; 4:  reading control
    map<string, int> m;
    if (!filestream.is_open()) {
        std::perror("Erro ao abrir o ficheiro");
    }

    while (getline(filestream, line)){
        if (line == "#Submissions"){
            getline(filestream, line);
            m = readLayout(line);
            reading = 1;
            steps[0] += 1;
        }
        else if (line == "#Reviewers"){
            getline(filestream, line);
            m = readLayout(line);
            reading = 2;
            steps[1] += 1;
        }
        else if (line == "#Parameters"){
            reading = 3;
            steps[2] += 1;
        }
        else if (line == "#Control"){
            reading = 4;
            steps[3] += 1;
        }
        else if (!line.empty() && !(line[0] == '#')){
            switch (reading){
                case 1:
                    submissions.push_back(readSubmission(params, line, m));
                    break;
                case 2:
                    reviewers.push_back(readReviewer(params, line, m));
                    break;
                case 3:
                    readParameter(params, parameterSteps, line);
                    break;
                case 4:
                    readControl(params, controlSteps, line);
                    break;
                default:
                    break;
            }
        }
    }

    params.submissions = submissions;
    params.reviewers = reviewers;

    
    for (int i = 0; i<steps.size(); i++){
        if (steps[i] != 1){
            params.valid = false;
        }
    }
    for (int i = 0; i<parameterSteps.size(); i++){
        if (parameterSteps[i] != 1){
            params.valid = false;
        }
    }
    for (int i = 0; i<controlSteps.size(); i++){
        if (controlSteps[i] != 1){
            params.valid = false;
        }
    }

    return params;
}

string get_project_cwd(const string &project_name) {

    string res;

    char buffer[1024];

    getcwd(buffer,1024);

    res=string(buffer);


    int index=res.rfind(project_name); //found project_name in res (cwd);

    if (index != string::npos) {
        res=res.substr(0,index+project_name.size());
    }

    return res;

}