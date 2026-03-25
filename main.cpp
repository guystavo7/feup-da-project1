#include "readGraph.h"
#include "create_graph.h"
#include "max_flow.h"
#include "graph.h"
#include "parser.h"
#include "utils.h"

//
// Created by gustavobastos on 19/03/26.
//

int assignment_command(string input_path, string output_file) {


    params info = parse(input_path);

    Graph<int_node> graph=create(info);

    edmondsKarp(&graph,{-1,false},{-2,false});


    std::map<int_node,submission>submissionData;
    std::map<int_node,reviewer>reviewerData;

    for (auto &s:info.submissions) {
        submissionData.insert({{s.id,true},s});
    }

    for (auto &r:info.reviewers) {
        reviewerData.insert({{r.id,false},r});
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

void test() {
    string proj_path=get_project_cwd("DA_Project_1");
    string output_path=proj_path+"/output/";

    vector<pair<string,string>> command_args;

    for (int i=0;i<14;i++) {
        string input_path =proj_path+"/Project1SampleDatasets/Project1SampleDatasets/input/dataset"+to_string(i+1)+ ".csv";
        string output_file= output_path+"output" +to_string(i+1)+ ".txt";
        command_args.push_back({input_path,output_file});
    }

    int st=0,end=14;
    for (int i=st;i<end;i++) {
        assignment_command(command_args[i].first,command_args[i].second);
    }

    for (int i=st;i<end;i++) {
        string expected_output_path =proj_path+"/Project1SampleDatasets/Project1SampleDatasets/output/dataset"+to_string(i+1)+ ".csv";
        string output_file= output_path+"output" +to_string(i+1)+ ".txt";
        if (file_comparator(output_file,expected_output_path,file_len(output_file))) {
            printf("test %d passed\n",i+1);
        }
        else  {
            printf("test %d failed\n",i+1);
        }
    }


}

int main(int argc, char *argv[]) {


   test();

    return 0;
}