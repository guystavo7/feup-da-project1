//
// Created by gustavobastos on 28/03/26.
//
/**
 * @file Menu.h
 * @brief Console-based user interface for the assignment tool.
 *
 * Provides an interactive menu system that allows the user to:
 * - Load input data
 * - View submissions and reviewers
 * - Inspect parameters
 * - Execute assignment generation
 */
#ifndef DA_PROJECT_1_MENU_H
#define DA_PROJECT_1_MENU_H

#include "parser.h"
#include "assignment_command.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
/**
 * @brief Prints a newline.
 */
void nl();
/**
 * @brief Clears the terminal screen.
 */
void clear_terminal() ;
/**
 * @brief Prints a centered string.
 *
 * @param s String to print
 * @param width Width of the screen
 * @param after String printed after (default newline)
 */
void printf_center(const std::string & s, int width,const string& after);
/**
 * @brief Repeats a string multiple times.
 *
 * @param str String to repeat
 * @param n Number of repetitions
 * @return Resulting concatenated string
 */
string repeat(const string &str, int n) ;

/**
 * @class Menu
 * @brief Handles the interactive console menu.
 *
 * Manages user interaction and navigation between different views,
 * including data loading, visualization, and assignment execution.
 */
class  Menu {
    int screen_width=100;
    string bar= repeat("-",screen_width-1)+"\n";

    bool no_data=true;
    params cur_params;
public:
    /**
     * @brief Starts the main menu loop.
     */
    void run();
    /**
     * @brief Loads input data from file.
     */
    void load_data();
    /**
     * @brief Displays the list of submissions.
     */
    void list_of_submissions();
    /**
     * @brief Displays the list of reviewers.
     */
    void list_of_reviewers();
    /**
     * @brief Displays current parameters.
     */
    void current_parameters();
    /**
     * @brief Displays assignment results.
     */
    void list_of_assignments();
    /**
     * @brief Generic page with custom content.
     *
     * @param title Page title
     * @param print_data Function that prints the content
     */
    template<typename Func>
    void basic_view_page(const string& title,Func print_data) ;

    /**
     * @brief Displays a list-based page.
     *
     * @param title Page title
     * @param data Vector of elements
     * @param print_data Function that converts elements to string
     */
    template<typename T>
    void list_view_page(const string& title,const vector< T>&data,string(*print_data)(const T&));

private:
    /**
     * @brief Prints centered text with newline.
     */
    void printn_c(const string &str) ;
    /**
     * @brief Prints centered text without newline.
     */
    void print_c(const string &str) ;
};




template<typename Func>
void Menu::basic_view_page(const string& title,Func print_data) {



    string line;
    int input;
    string error="\n";
    if (no_data) {
        error="No data available. Go to menu and Load Data (option: 1)";
    }
    bool exit=false;
    while (!exit) {
        clear_terminal();
        printn_c(bar);
        printn_c(title);
        printn_c(bar);
        printf((error).c_str());
        nl();

        print_data();

        printf("\n");

        print_c("Press 0 to go back to menu: ");


        try {
            getline(std::cin,line);
            if (line.size()<=1) {
                input=atoi(line.c_str());
                if (line!="0" and input==0) {

                    error="Error: Please enter a valid input\n";
                    input=7;
                }
            }
            else {
                error="Error: Please enter a valid input\n";
                input=7;
            }
        }
        catch (...) {
            error="Error: Please enter a valid input\n";

        }

        if (input == 0) {
            exit=true;
        }


    }

}

template<typename T>
void Menu::list_view_page(const string& title,const vector< T>&data,string(*print_data)(const T&)) {
    basic_view_page<>(title,[&]() {
        int i=0;
        for (const T& d :data) {
            printf(("\t\t"+to_string(i)+" - "+ print_data(d)+"\n\n").c_str());
            i++;
        }
    }
    );


}

#endif //DA_PROJECT_1_MENU_H