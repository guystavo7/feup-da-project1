/**
 * @file parser.h
 * @brief Handles parsing of input files into local data structures.
 * 
 * This module reads structured input files describing submissions,
 * reviewers, parameters, and control options, and converts them into
 * our project's data structures.
 */
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

/**
 * @brief Stores all parsed input data.
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

/**
 * @brief Parses a CSV input file.
 *
 * Extracts submissions, reviewers, and parameters.
 *
 * @param file Path to input file
 * @return params Struct containing all parsed data
 *
 * @complexity O(n), where n is number of lines in the file
 */
params parse(string file);

/**
 * @brief Gets the root directory of the project.
 *
 * Uses the current working directory and extracts the path up to the
 * specified project folder name.
 *
 * @param project_name Name of the project folder
 * @return string Absolute path to the project root directory
 *
 * @complexity O(n), where n is the length of the current path string
 */
string get_project_cwd(const string &project_name);


#endif //DA_PROJECT_1_PARSER_H