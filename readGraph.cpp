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



void writeSubmissions(const std::string& outputFilepath,const std::vector<submission>& submissions) {
    FILE* file=fopen(outputFilepath.data(),"w");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }
    printf("%s\n", outputFilepath.data());

    fprintf(file,"#SubmissionId,ReviewerId,Match\n");
    for (auto& s:submissions) {

        fprintf(file,"%d, %d, %d\n",s.a->id,s.rw->id,s.a->primaryDomain);
    }

    fprintf(file,"#ReviewerId,SubmissionId,Match\n");

    for (auto& s:submissions) {

        fprintf(file,"%d, %d, %d\n",s.rw->id,s.a->id,s.a->primaryDomain);
    }


    fprintf(file,"#Total: %lu\n",submissions.size());

    fclose(file);
}

void writeFailedSubmissions(const std::string& outputFilepath,const std::vector<failedSubmission>& failedSubmissions) {
    FILE* file=fopen(outputFilepath.data(),"w");
    if (file==NULL) {
        std::cerr << "Could not open file \"" << outputFilepath << "\"" << std::endl;
    }
    printf("%s\n", outputFilepath.data());

    fprintf(file,"#SubmissionId,Domain,MissingReviews\n");
    for (auto& fs:failedSubmissions) {

        fprintf(file,"%d, %d, %d\n",fs.a->id,fs.a->primaryDomain,fs.missingSubmissions);
    }

    fclose(file);
}



