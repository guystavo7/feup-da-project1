//
// Created by gustavobastos on 13/03/26.
//

#ifndef DA_PROJECT_1_READGRAPH_H
#define DA_PROJECT_1_READGRAPH_H
#include "DataStructs.h"
#include "algorithm"
#include "graph.h"
#include "map"



void writeAssignments(const std::string& outputFilepath, std::vector<assignment>& assignments);

void writeFailedAssignments(const std::string& outputFilepath, std::vector<failedAssignment>& failedAssignments);


template<class T>
void readGraphAssignments(Graph<T> *g, Vertex<T> *s, Vertex<T> *t,const std::map<int_node, const submission*>& submissionData,const std::map<int_node,const reviewer*>& reviewerData, std::vector<assignment>& assignments,std::vector<failedAssignment>& failedAssignments, bool & allAssigned) {

    allAssigned = true;

    for (auto& articleEdge:s->getAdj()) {
        if (articleEdge->getWeight()!=articleEdge->getFlow()) {
            allAssigned = false;
        }
    }
    if (allAssigned || true) {
        for (auto& articleEdge:s->getAdj()) {
            Vertex<T>* articleNode=articleEdge->getDest();
            for (auto& reviewerEdge:articleNode->getAdj()) {
                Vertex<T>* reviewerNode=reviewerEdge->getDest();
                if (reviewerEdge->getFlow()==1) {
                    assignments.push_back({submissionData.at(articleNode->getInfo()),reviewerData.at(reviewerNode->getInfo())});
                }
            }
        }
    }
    if (true){
        for (auto& articleEdge:s->getAdj()) {
            Vertex<T>* articleNode=articleEdge->getDest();

            if (articleEdge->getWeight()!=articleEdge->getFlow()) {
                failedAssignments.push_back({submissionData.at(articleNode->getInfo()),(unsigned int)(articleEdge->getWeight()-articleEdge->getFlow())});
            }

        }
    }

}

#endif //DA_PROJECT_1_READGRAPH_H