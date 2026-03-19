//
// Created by gustavobastos on 13/03/26.
//

#ifndef DA_PROJECT_1_READGRAPH_H
#define DA_PROJECT_1_READGRAPH_H
#include "DataStructs.h"




void writeAssignments(const std::string& outputFilepath,const std::vector<assignment>& assignments);

void writeFailedAssignments(const std::string& outputFilepath,const std::vector<failedAssignment>& failedAssignments);

#endif //DA_PROJECT_1_READGRAPH_H