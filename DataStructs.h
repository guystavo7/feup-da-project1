//
// Created by gustavobastos on 13/03/26.
//

#ifndef DA_PROJECT_1_DATASTRUCTS_H
#define DA_PROJECT_1_DATASTRUCTS_H


struct article {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string title="";
};

struct reviewer {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string name="";

};

struct submission {
    const article* a;
    const reviewer* rw;
};

struct failedSubmission {
    const article* a;
    unsigned int missingSubmissions;
};



template<class T>
void readGraphSubmissions(Graph<T> *g, Vertex<T> *s, Vertex<T> *t,const std::map<int, article>& articleData,const std::map<int,reviewer>& reviewerData, std::vector<submission>& submissions,std::vector<failedSubmission>& failedSubmissions, bool & allAssigned) {

    allAssigned = true;

    for (auto& articleEdge:s->getAdj()) {
        if (articleEdge->getWeight()!=articleEdge->getFlow()) {
            allAssigned = false;
        }
    }
    if (allAssigned) {
        for (auto& articleEdge:s->getAdj()) {
            Vertex<T>* articleNode=articleEdge->getDest();
            for (auto& reviewerEdge:articleNode->getAdj()) {
                Vertex<T>* reviewerNode=reviewerEdge->getDest();
                if (reviewerEdge->getFlow()==1) {
                    submissions.push_back({&articleData.at(articleNode->getInfo()),&reviewerData.at(reviewerNode->getInfo())});
                }
            }
        }
    }
    else {
        for (auto& articleEdge:s->getAdj()) {
            Vertex<T>* articleNode=articleEdge->getDest();

            if (articleEdge->getWeight()!=articleEdge->getFlow()) {
                failedSubmissions.push_back({&articleData.at(articleNode->getInfo()),(unsigned int)(articleEdge->getWeight()-articleEdge->getFlow())});
            }

        }
    }

}
#endif //DA_PROJECT_1_DATASTRUCTS_H