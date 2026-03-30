//
// Created by gustavobastos on 28/03/26.
//

#ifndef DA_PROJECT_1_RISK_H
#define DA_PROJECT_1_RISK_H
#include <vector>
#include "DataStructs.h"
#include "graph.h"
#include "map"
#include "unordered_map"

using namespace std;
struct domain_flow_analysis {
    int residual_capacity;
    vector< Vertex<int_node>*> rv;
    int drainage_capacity;
};

std::vector<int> risk_analysis(Graph<int_node>* g,const std::unordered_map<int_node,const reviewer*,int_node_hash>& reviewerData);

void risk_analysis(const string & output_filepath,Graph<int_node> *g,const std::unordered_map<int_node,const reviewer*,int_node_hash>& reviewerData,bool allAssigned) ;


#endif //DA_PROJECT_1_RISK_H
