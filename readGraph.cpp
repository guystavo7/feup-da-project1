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



void writeAssignments(const std::string& outputFilepath,const std::vector<assignment>& assignments) {
    FILE* file=fopen(outputFilepath.data(),"w");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }
    printf("%s\n", outputFilepath.data());

    fprintf(file,"#SubmissionId,ReviewerId,Match\n");
    for (auto& s:assignments) {

        fprintf(file,"%d, %d, %d\n",s.a->id,s.rw->id,s.a->primary);
    }

    fprintf(file,"#ReviewerId,SubmissionId,Match\n");

    for (auto& s:assignments) {

        fprintf(file,"%d, %d, %d\n",s.rw->id,s.a->id,s.rw->primary);
    }


    fprintf(file,"#Total: %lu\n",assignments.size());

    fclose(file);
}

void writeFailedAssignments(const std::string& outputFilepath,const std::vector<failedAssignment>& failedAssignments) {
    FILE* file=fopen(outputFilepath.data(),"w");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }
    printf("%s\n", outputFilepath.data());

    fprintf(file,"#SubmissionId,Domain,MissingReviews\n");
    for (auto& fs:failedAssignments) {

        fprintf(file,"%d, %d, %d\n",fs.a->id,fs.a->primary,fs.missingSubmissions);
    }

    fclose(file);
}



