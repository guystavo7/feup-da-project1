//
#include <fcntl.h>

#include "graph.h"
#include <limits>
#include <map>
#include <unistd.h>
#include "DataStructs.h"
#include "readGraph.h"
//
// Created by gustavobastos on 13/03/26.
//

void assignmentFailureTest1() {
    Graph<int>graph;
    unsigned int minReviewsPerArticle=3;
    unsigned int maxReviewsPerReviewer=3;


    std::map<int, article>articleData={{1,{1,1}},{2,{2}},{3,{3,3,1}}};
    std::map<int,reviewer> reviewerData={{4,{4,1}},{5,{5,1,2}},{6,{6,2}},{7,{7,2}},{8,{8,3}}};

    std::map<int,std::vector<int>>ligações{{1,{4,5}},{2,{5,6,7}},{3,{8,5,4}}};//ligações entre articles com vários reviewers (só com ids)

    graph.addVertex(-1);//source
    graph.addVertex(-2);//sink
    for (int i=1;i<=8;i++) {
        graph.addVertex(i);
    }

    for (int i=1;i<=3;i++) {
        graph.addEdge(-1,i,minReviewsPerArticle);// add edges from source to articles
    }

    for (int i=4;i<=8;i++) {
        graph.addEdge(i,-2,maxReviewsPerReviewer); // add edges from reviewers to sink

    }


    //conectar articles com reviewers
    for (int articleId=1;articleId<=3;articleId++) {
        for (auto& reviwerId:ligações[articleId]) {
            graph.addEdge(articleId,reviwerId,1);
        }
    }


    //configurar flow entre articles e reviewers
    for (int i=1;i<=3;i++) {
        Vertex<int>* w=graph.findVertex(i);
        for (auto& e:w->getAdj()) {
            if (i==1 && e->getDest()->getInfo()==5) {
                e->setFlow(0);
            }
            else {
                e->setFlow(1);
            }
        }
    }


    //configurar flow entre source e articles
    Vertex<int>* source=graph.findVertex(-1);
    for (auto& e:source->getAdj()) {
        if (e->getDest()->getInfo()==1) {
            e->setFlow(1);
        }
        else {
            e->setFlow(3);
        }
    }


    //configurar flow entre reviewers e sink

    Vertex<int>* sink=graph.findVertex(-2);
    for (auto& e:sink->getIncoming()) {
        if (e->getOrig()->getInfo()==4 || e->getOrig()->getInfo()==5) {
            e->setFlow(2);
        }
        else {
            e->setFlow(1);
        }
    }

    bool assignmentSuccess=false;


    std::vector<submission> submissions;
    std::vector<failedSubmission> failedSubmissions;
    bool allAssigned=false;
    readGraphSubmissions(&graph,source,sink,articleData,reviewerData,submissions,failedSubmissions,allAssigned);

    if (failedSubmissions.empty())
    printf("allAssigned=%d\n",allAssigned);

    for (auto& fs:failedSubmissions) {

        printf("article=%d with domain=%d failed missing %d submissions \n",fs.a->id,fs.a->primaryDomain,fs.missingSubmissions);
    }

    char buffer[1024];
    getcwd(buffer,1024);
    std::string path=std::string(buffer);
    writeFailedSubmissions(path+"/output.txt",failedSubmissions);



}


void assigmentSuccessTest1() {
    Graph<int>graph;
    unsigned int minReviewsPerArticle=2;
    unsigned int maxReviewsPerReviewer=3;


    std::map<int, article>articleData={{1,{1,1}},{2,{2}},{3,{3,3,1}}};
    std::map<int,reviewer> reviewerData={{4,{4,1}},{5,{5,1,2}},{6,{6,2}},{7,{7,2}},{8,{8,3}}};

    std::map<int,std::vector<int>>ligações{{1,{4,5}},{2,{5,6,7}},{3,{8,5,4}}};//ligações entre articles com vários reviewers (só com ids)

    graph.addVertex(-1);//source
    graph.addVertex(-2);//sink
    for (int i=1;i<=8;i++) {
        graph.addVertex(i);
    }

    for (int i=1;i<=3;i++) {
        graph.addEdge(-1,i,minReviewsPerArticle);// add edges from source to articles
    }

    for (int i=4;i<=8;i++) {
        graph.addEdge(i,-2,maxReviewsPerReviewer); // add edges from reviewers to sink

    }


    //conectar articles com reviewers
    for (int articleId=1;articleId<=3;articleId++) {
        for (auto& reviwerId:ligações[articleId]) {
            graph.addEdge(articleId,reviwerId,1);
        }
    }


    //configurar flow entre articles e reviewers
    for (int i=1;i<=3;i++) {
        Vertex<int>* w=graph.findVertex(i);
        for (auto& e:w->getAdj()) {
            if ((i==2 && e->getDest()->getInfo()==5) || (i==3 && e->getDest()->getInfo()==4) ) {
                e->setFlow(0);
            }
            else {
                e->setFlow(1);
            }
        }
    }


    //configurar flow entre source e articles
    Vertex<int>* source=graph.findVertex(-1);
    for (auto& e:source->getAdj()) {
        e->setFlow(2);
    }


    //configurar flow entre reviewers e sink

    Vertex<int>* sink=graph.findVertex(-2);
    for (auto& e:sink->getIncoming()) {
        if ( e->getOrig()->getInfo()==5) {
            e->setFlow(2);
        }
        else {
            e->setFlow(1);
        }
    }

    bool assignmentSuccess=false;


    std::vector<submission> submissions;
    std::vector<failedSubmission> failedSubmissions;
    bool allAssigned=false;
    readGraphSubmissions(&graph,source,sink,articleData,reviewerData,submissions,failedSubmissions,allAssigned);

    if (failedSubmissions.empty())
    printf("allAssigned=%d\n",allAssigned);



    for (auto& s:submissions) {

        printf("article=%d with reviewer=%d  |  on the matching domain: %d  \n",s.a->id,s.rw->id,s.a->primaryDomain);
    }


    char buffer[1024];
    getcwd(buffer,1024);
     std::string path=std::string(buffer);
    writeSubmissions(path+"/output.txt",submissions);

}
#define RUNTEST 1

#if RUNTEST
int main(){


    assignmentFailureTest1();
    return 0;
}
#endif