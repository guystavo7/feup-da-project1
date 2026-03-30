//
// Created by gustavobastos on 13/03/26.
//
/**
 * @file readGraph.h
 * @brief Extracts assignments from the flow graph and writes results to files.
 *
 * This module is responsible for:
 * - Interpreting the flow graph after running the max-flow algorithm
 * - Extracting valid assignments between submissions and reviewers
 * - Identifying failed assignments (insufficient reviewers)
 * - Writing results to output files
 */
#ifndef DA_PROJECT_1_READGRAPH_H
#define DA_PROJECT_1_READGRAPH_H
#include "DataStructs.h"
#include "algorithm"
#include "graph.h"
#include "map"


/**
 * @brief Writes successful assignments to an output file.
 *
 * The outputs are of types:
 * - Submission, Reviewer , Matching Domain
 * - Reviewer, Submission, Matching Domain
 * - Total number of assignments
 *
 * @param outputFilepath Path to output file
 * @param assignments Vector of successful assignments
 *
 * complexity O(n*log(n)), due to sorting
 */
void writeAssignments(const std::string& outputFilepath, std::vector<assignment>& assignments);

/**
 * @brief Writes failed assignments to an output file.
 *
 * Lists submissions that did not receive enough reviewers and the number
 * of missing assignments.
 *
 * @param outputFilepath Path to output file
 * @param failedAssignments Vector of failed assignments
 *
 * complexity O(n)
 */
void writeFailedAssignments(const std::string& outputFilepath, std::vector<failedAssignment>& failedAssignments);

/**
 * @brief Extracts assignments from the flow graph.
 *
 * Interprets the result of the max-flow algorithm by:
 * - Identifying edges with flow = 1 between submissions and reviewers
 * - Creating assignment objects
 * - Detecting submissions that did not receive enough reviewers
 *
 * @param g Pointer to the graph
 * @param s Source vertex
 * @param t Target vertex
 * @param submissionData Map from graph nodes to submission data
 * @param reviewerData Map from graph nodes to reviewer data
 * @param assignments Output vector of successful assignments
 * @param failedAssignments Output vector of failed assignments
 * @param allAssigned Boolean flag indicating if all submissions were fully assigned
 *
 * complexity O(V+E)
 */
template<class T>
void readGraphAssignments(Graph<T> *g, Vertex<T> *s, Vertex<T> *t,const std::unordered_map<int_node, const submission*,int_node_hash>& submissionData,const std::unordered_map<int_node,const reviewer*,int_node_hash>& reviewerData, std::vector<assignment>& assignments,std::vector<failedAssignment>& failedAssignments, bool & allAssigned) {

    allAssigned = true;

    for (auto& articleEdge:s->getAdj()) {
        if (articleEdge->getWeight()!=articleEdge->getFlow()) {
            allAssigned = false;
        }
    }
    for (auto& articleEdge:s->getAdj()) {
        Vertex<T>* articleNode=articleEdge->getDest();
        for (auto& reviewerEdge:articleNode->getAdj()) {
            Vertex<T>* reviewerNode=reviewerEdge->getDest();
            if (reviewerEdge->getFlow()==1) {
                assignments.push_back({submissionData.at(articleNode->getInfo()),reviewerData.at(reviewerNode->getInfo())});
            }
        }
    }
    for (auto& articleEdge:s->getAdj()) {
        Vertex<T>* articleNode=articleEdge->getDest();

        if (articleEdge->getWeight()!=articleEdge->getFlow()) {
            failedAssignments.push_back({submissionData.at(articleNode->getInfo()),
                (unsigned int)(articleEdge->getWeight()-articleEdge->getFlow())});
        }

    }

}

#endif //DA_PROJECT_1_READGRAPH_H