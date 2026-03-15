#include "parser.h"

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

submission readSubmission(string line, map<string, int> order){

    submission res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        fields.push_back(word);
    }


    res.id = stoi(fields[order["Id"]]);
    res.title = fields[order["Title"]];
    res.name = fields[order["Authors"]];
    res.email = fields[order["E-mail"]];
    res.primary = stoi(fields[order["Primary"]]);
    res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -1;

    return res;
}

reviewer readReviewer(string line, map<string, int> order){

    reviewer res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        fields.push_back(word);
    }

    res.id = stoi(fields[order["Id"]]);
    res.name = fields[order["Name"]];
    res.email = fields[order["E-mail"]];
    res.primary = stoi(fields[order["Primary"]]);
    res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -1;

    return res;
}

void readParameter(params &params, string line){

    stringstream ss(line);

    string name;
    getline(ss, name, ',');
    trimer(name);

    string value;
    getline(ss, value, ',');
    trimer(value);
    int valueint = stoi(value);

    if (name == "MinReviewsPerSubmission"){params.MinReviewsPerSubmission = valueint;}
    else if (name == "MaxReviewsPerReviewer"){params.MaxReviewsPerReviewer = valueint;}
    else if (name == "PrimaryReviewerExpertise"){params.PrimaryReviewerExpertise = valueint;}
    else if (name == "SecondaryReviewerExpertise"){params.SecondaryReviewerExpertise = valueint;}
    else if (name == "PrimarySubmissionDomain"){params.PrimarySubmissionDomain = valueint;}
    else if (name == "SecondarySubmissionDomain"){params.SecondarySubmissionDomain = valueint;}


}

void readControl(params &params, string line){
    
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
        params.GenerateAssignments = stoi(value);
    }
    if (name == "RiskAnalysis"){
        params.RiskAnalysis = stoi(value);
    }
    if (name == "OutputFileName"){
        params.OutputFileName = value;
    }
}

params parse(string file){


    string path = "Inputs/";
    path = path + file;

    vector<submission> submissions;
    vector<reviewer> reviewers;

    params params;

    ifstream filestream(path);
    string line;

    int reading = -1; //1: reading submissions; 2: reading reviewers; 3: reading parameters; 4:  reading control
    map<string, int> m;

    while (getline(filestream, line)){
        if (line == "#Submissions"){
            getline(filestream, line);
            m = readLayout(line);
            reading = 1;
        }
        else if (line == "#Reviewers"){
            getline(filestream, line);
            m = readLayout(line);
            reading = 2;
        }
        else if (line == "#Parameters"){
            reading = 3;
        }
        else if (line == "#Control"){
            reading = 4;
        }
        else if (!line.empty() && !(line[0] == '#')){
            switch (reading){
                case 1:
                    submissions.push_back(readSubmission(line, m));
                    break;
                case 2:
                    reviewers.push_back(readReviewer(line, m));
                    break;
                case 3:
                    readParameter(params, line);
                    break;
                case 4:
                    readControl(params, line);
                    break;
                default:
                    break;
            }
        }
    }

    params.submissions = submissions;
    params.reviewers = reviewers;

    return params;
}