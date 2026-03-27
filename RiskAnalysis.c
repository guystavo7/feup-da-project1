/*
Check which risk analysis to do
Get the main graph
Iterate through every reviewer
Run EdmondsKarp for every reviewer missing
Check if it's possible and mark the names
*/

#include "RiskAnalysis.h"

template <class T>
bool check(Graph<T>* g, int source, int target){
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    double sourceWeight = 0;
    for (Edge<T>* edge : s->getAdj()){
        sourceFlow += edge->getWeight();
    }

    double sinkFlow = 0;
    for (Edge<T>* edge : t->getAdj()){
        sinkFlow += edge->getFlow();
    }

    return sourceWeight == sinkFlow;
}

template <class T>
vector<reviewer> analyze(Graph<T>* g, int type, vector<Vertex<T>*> reviewers, int source, int target){
    vector<reviewer> v;

    if (type == 0){
        edmondsKarp(g, sourse, target);
        return v;
    } else if (type == 1){
        for (Vertex<T>* reviewerNode : reviewers){
            reviewerNode->setProcessing(false);
        }

        for (Vertex<T>* reviewerNode : reviewers){
            reviewerNode->setProcessing(true);
            edmondsKarp(g, source, target);
            if (!check(g, source, target)){
                v.push_back(reviewerNode);
            }
            reviewerNode->setProcessing(false);
        }

        return v;
    }

    
}
