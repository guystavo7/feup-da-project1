#include "create_graph.h"

Graph<int> create(params info){
    Graph<int> newGraph;

    newGraph.addVertex(-1); //source
    newGraph.addVertex(-2); //target
    //create all submission vertices and connect them with source
    for(submission sub : info.submissions){
        newGraph.addVertex(sub.id);
        newGraph.addEdge(-1,sub.id,info.MinReviewsPerSubmission);
    }
    //create all reviewer vertices and connect them with target
    for(reviewer rev : info.reviewers){
        newGraph.addVertex(rev.id);
        newGraph.addEdge(rev.id,-2,info.MaxReviewsPerReviewer);
    }

    //create the edges connecting submissions and reviewers according to GenerateAssignments
    for(submission sub : info.submissions){
        for(reviewer rev : info.reviewers){
            bool match=false;

            if(info.GenerateAssignments==1 || info.GenerateAssignments==0){
                match=(sub.primary==rev.primary);
            }
            else if(info.GenerateAssignments== 2){
                match=sub.primary == rev.primary || sub.secondary == rev.primary;
            }
            else if(info.GenerateAssignments == 3){
                match= sub.primary== rev.primary || sub.primary== rev.secondary || sub.secondary== rev.primary || sub.secondary== rev.secondary;
            }

            if(match){
                newGraph.addEdge(sub.id, rev.id, 1);
            }
        }
    }
    return newGraph;
}