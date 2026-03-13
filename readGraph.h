//
// Created by gustavobastos on 13/03/26.
//

#ifndef DA_PROJECT_1_READGRAPH_H
#define DA_PROJECT_1_READGRAPH_H
#include "DataStructs.h"

void writeFailedSubmissions(const std::string& outputFilepath,const std::vector<failedSubmission>& failedSubmissions);

void writeSubmissions(const std::string& outputFilepath,const std::vector<submission>& submissions);

#endif //DA_PROJECT_1_READGRAPH_H