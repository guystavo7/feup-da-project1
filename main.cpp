#include "readGraph.h"
#include "create_graph.h"
#include "max_flow.h"
#include "graph.h"
#include "parser.h"
#include "utils.h"
#include "assignment_command.h"
#include "Menu.h"

//
// Created by gustavobastos on 19/03/26.
//


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
    if (argc>1) {

        if ((string(argv[1])!="-b") or argc!=4) {
            printf("Usage: ATR -b input.cvs output.cvs\n");
        }
        else {
            try {
                assignment_command(argv[2],argv[3]);
            }
            catch (...) {
                printf("Error: input %s did not exist or parsing failed\n",argv[2]);
            }
        }
        return 0;
    }
    Menu menu;
    menu.run();
    ///home/gustavobastos/Pessoal/Faculdade/LEIC-FEUP/2 ano/2 semestre/DA/Projeto1/DA_Project_1/Project1SampleDatasets/Project1SampleDatasets/input/dataset9.csv

    return 0;
}