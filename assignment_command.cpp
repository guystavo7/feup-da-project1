//
// Created by gustavobastos on 28/03/26.
//

#include "assignment_command.h"

#include "readGraph.h"
#include "create_graph.h"
#include "max_flow.h"
#include "graph.h"
#include "parser.h"
#include "utils.h"


//
// Created by gustavobastos on 19/03/26.
//


int assignment_command(const params & info, string output_file) {

    Graph<int_node> graph=create(info);

    edmondsKarp(&graph,{-1,false},{-2,false});


    std::map<int_node,const submission*>submissionData;
    std::map<int_node,const reviewer*>reviewerData;

    for (auto &s:info.submissions) {
        submissionData.insert({{s.id,true},&s});
    }

    for (auto &r:info.reviewers) {
        reviewerData.insert({{r.id,false},&r});
    }

    Vertex<int_node>*source=graph.findVertex({-1,false});
    Vertex<int_node>*sink=graph.findVertex({-2,false});

    std::vector<assignment> assignments;
    std::vector<failedAssignment> failedAssignments;
    bool allAssigned=false;
    readGraphAssignments(&graph,source,sink,submissionData,reviewerData,assignments,failedAssignments,allAssigned);

    if (allAssigned||true) {

        writeAssignments(output_file,assignments);
    }
    if (!allAssigned) {
        writeFailedAssignments(output_file,failedAssignments);
    }


    return  0;
}

int assignment_command(string input_path, string output_file) {
    params info = parse(input_path);
    return assignment_command(info,output_file);
}