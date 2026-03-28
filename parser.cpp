/**
 * @file parser.cpp
 * @brief Implementation of CSV parsing utilities.
 *
 * Contains helper functions to parse submissions, reviewers,
 * parameters, and control sections from input files.
 */
#include "parser.h"

#include <cstring>
#include <unistd.h>

using namespace std;


/**
 * @brief Removes leading spaces from a string.
 *
 * @param word String to trim
 *
 * complexity O(n), where n is the length of the string
 */
void trimer(string &word){
    while (!word.empty() && word[0] == ' '){
        word.erase(0,1);
    }
}


/**
 * @brief Reads a header line and maps column names to indices.
 *
 * Removes the leading '#' and splits the line by ',' to create
 * a mapping between column names and their positions.
 *
 * @param line Header line
 * @return map<string,int> Mapping of field names to column indices
 *
 * complexity O(k), where k is the number of columns
 */
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

/**
 * @brief Parses a submission from a CSV line.
 *
 * Extracts submission fields based on the column mapping.
 *
 * @param line CSV line representing a submission
 * @param order Mapping of column names to indices
 * @return submission Parsed submission structure
 *
 * complexity O(k), where k is the number of fields
 */
submission readSubmission(string line, map<string, int> order){

    submission res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        if (!word.empty()) fields.push_back(word);
    }


    res.id = stoi(fields[order["Id"]]);
    res.title = fields[order["Title"]];
    res.name = fields[order["Authors"]];
    res.email = fields[order["E-mail"]];
    res.primary = stoi(fields[order["Primary"]]);
    res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -1;

    return res;
}

/**
 * @brief Parses a reviewer from a CSV line.
 *
 * Extracts reviewer fields based on the column mapping.
 *
 * @param line CSV line representing a reviewer
 * @param order Mapping of column names to indices
 * @return reviewer Parsed reviewer structure
 *
 * complexity O(k)
 */
reviewer readReviewer(string line, map<string, int> order){

    reviewer res;

    stringstream ifs(line);
    string word;

    vector<string> fields;

    while (getline(ifs, word, ',')){
        trimer(word);
        if (!word.empty()) fields.push_back(word);
    }

    res.id = stoi(fields[order["Id"]]);
    res.name = fields[order["Name"]];
    res.email = fields[order["E-mail"]];
    res.primary = stoi(fields[order["Primary"]]);
    res.secondary = order["Secondary"] < fields.size() ? stoi(fields[order["Secondary"]]) : -2;

    return res;
}

/**
 * @brief Parses a parameter line and updates the params struct.
 *
 * @param params Reference to params structure
 * @param line CSV line containing parameter name and value
 *
 * complexity O(1)
 */
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

/**
 * @brief Parses control parameters from a CSV line.
 *
 * Handles assignment generation, risk analysis, and output file name.
 *
 * @param params Reference to params structure
 * @param line CSV line containing control data
 *
 * complexity O(1)
 */
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

/**
 * @brief Parses the input CSV file and builds the params structure.
 *
 * The file is processed line by line and divided into sections:
 * - #Submissions
 * - #Reviewers
 * - #Parameters
 * - #Control
 *
 * Depending on the current section, the appropriate parsing function is used.
 *
 * @param path Path to the input file
 * @return params Struct containing all parsed data
 *
 * complexity O(n), where n is the number of lines in the file
 *
 * @note Assumes the input file follows the expected format.
 */
params parse(string path){

   // printf("%s\n",buffer);



    vector<submission> submissions;
    vector<reviewer> reviewers;

    params params;

    ifstream filestream(path);
    string line;

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

/**
 * @brief Retrieves the project root directory from the current working directory.
 *
 * Searches for the project name in the current path and trims the path accordingly.
 *
 * @param project_name Name of the project folder
 * @return string Path to project root
 *
 * complexity O(n), where n is the length of the path
 */
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