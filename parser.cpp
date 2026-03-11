#include "parser.h"

using namespace std;



void trimer(string &word){
    if (!word.empty() && word[0] == ' '){
            word.erase(0,1);
        }
}

submission readSubmission(string line){

    submission res;

    stringstream ifs(line);
    string word;

    getline(ifs, word, ',');
    trimer(word);
    res.id = stoi(word);

    getline(ifs, word, ',');
    trimer(word);
    res.title = word;
    
    getline(ifs, word, ',');
    trimer(word);
    res.name = word;

    getline(ifs, word, ',');
    trimer(word);
    res.email = word;

    getline(ifs, word, ',');
    trimer(word);
    res.primary = stoi(word);

    getline(ifs, word, ',');
    trimer(word);
    if (!word.empty()){
        res.secondary = stoi(word);
    }

    return res;
}

vector<submission> parse(string file){


    string path = "Inputs/";
    path = path + file;

    vector<submission> submissions;

    ifstream filestream(path);
    string line;
    int reading = 0;
    bool ignoring = false;

    while (getline(filestream, line)){
        //cout << line << "\n";
        if (!line.empty() && line[0] == '#'){
            if (!ignoring){
                reading++;
            }
            ignoring = true;
        } else{

            ignoring = false;
            
            if (reading == 1){
                submissions.push_back(readSubmission(line));
            }
            
        }
    }


    return submissions;
}