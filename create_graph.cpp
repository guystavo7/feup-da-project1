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

            if(info.GenerateAssignments==1){
                match=(sub.primary==rev.primary && (info.PrimaryReviewerExpertise==1 && info.PrimarySubmissionDomain==1));
            }
            else if(info.GenerateAssignments== 2){
                match=(sub.primary == rev.primary && (info.PrimaryReviewerExpertise==1 && info.PrimarySubmissionDomain==1))
                || (sub.secondary == rev.primary && (info.PrimaryReviewerExpertise==1 && info.SecondarySubmissionDomain==1));
            }
            else if(info.GenerateAssignments == 3){
                match= (sub.primary== rev.primary && (info.PrimaryReviewerExpertise==1 && info.PrimarySubmissionDomain==1)) 
                || (sub.primary== rev.secondary && (info.SecondaryReviewerExpertise==1 && info.PrimaryReviewerExpertise==1)) 
                || (sub.secondary== rev.primary && (info.PrimaryReviewerExpertise==1 && info.SecondarySubmissionDomain==1)) 
                || (sub.secondary== rev.secondary && (info.SecondaryReviewerExpertise==1 && info.SecondarySubmissionDomain==1));
            }

            if(match){
                newGraph.addEdge(sub.id, rev.id, 1);
            }
        }
    }
    return newGraph;
}