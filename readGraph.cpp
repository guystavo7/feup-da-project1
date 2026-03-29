#include <fcntl.h>

#include "graph.h"
#include <limits>
#include <map>
#include <unistd.h>
#include "DataStructs.h"
#include "readGraph.h"
//
// Created by gustavobastos on 10/03/26.
//



void writeAssignments(const std::string& outputFilepath, std::vector<assignment>& assignments) {
    FILE* file=fopen(outputFilepath.data(),"w");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }


    fprintf(file,"#SubmissionId,ReviewerId,Match\n");

    std::sort(assignments.begin(),assignments.end(),[](const assignment& i1, const assignment& i2) {
        return (i1.a->id)<(i2.a->id);
    });
    for (auto& s:assignments) {
        //int match=(s.a->primary==s.rw->primary)?s.a->primary:s.a->secondary;
        fprintf(file,"%d, %d, %d\n",s.a->id,s.rw->id,s.rw->primary);
    }

    std::sort(assignments.begin(),assignments.end(),[](const assignment& i1, const assignment& i2) {
        return (i1.rw->id)<(i2.rw->id);
    });
    fprintf(file,"#ReviewerId,SubmissionId,Match\n");

    for (auto& s:assignments) {

        fprintf(file,"%d, %d, %d\n",s.rw->id,s.a->id,s.rw->primary);
    }


    fprintf(file,"#Total: %lu\n",assignments.size());

    fflush(file);
    fclose(file);



}

void writeFailedAssignments(const std::string& outputFilepath, std::vector<failedAssignment>& failedAssignments) {
    FILE* file=fopen(outputFilepath.data(),"a");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }


    fprintf(file,"#SubmissionId,Domain,MissingReviews\n");
    for (auto& fs:failedAssignments) {

        fprintf(file,"%d, %d, %d\n",fs.a->id,fs.a->primary,fs.missingSubmissions);
    }


    fflush(file);
    fclose(file);



}



