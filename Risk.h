//
// Created by gustavobastos on 28/03/26.
//

#ifndef DA_PROJECT_1_RISK_H
#define DA_PROJECT_1_RISK_H
#include <vector>
#include "DataStructs.h"
#include "graph.h"

using namespace std;
struct domain_flow_analisys {
    int residual_capacity;
    vector< Vertex<int_node>*> rv;
    int drainage_capacity;
};

std::vector<int> risk_analisys(Graph<int_node>* g,const std::map<int_node,const reviewer*>& reviewerData);

void risk_analisys(const string & output_filepath,Graph<int_node> *g,const std::map<int_node,const reviewer*>& reviewerData,bool allAssigned) ;


#endif //DA_PROJECT_1_RISK_H
