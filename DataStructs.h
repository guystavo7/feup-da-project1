//
// Created by gustavobastos on 13/03/26.
//

/**
 * @file DataStructs.h
 * @brief Defines core data structures used in the project.
 */

#ifndef DA_PROJECT_1_DATASTRUCTS_H
#define DA_PROJECT_1_DATASTRUCTS_H

#include <string>

#include <vector>

/**
 * @brief Represents a submission (paper).
 */
struct submission{
    int id;                     ///< Identifier
    int primary;                ///< Primary domain
    int secondary = -1;         ///< Secondary domain (optional)
    std::string title="";
    std::string name="";
    std::string email="";

};

/**
 * @brief Represents a reviewer.
 */
struct reviewer{
    int id;                     ///< Unique identifier
    int primary;                ///< Primary domain
    int secondary = -2;         ///< Secondary domain (optional)
    std::string name="";
    std::string email="";

};

/**
 * @brief Node type used in the graph.
 *
 * This structure extends the graph node to distinguish between:
 * - Submissions (is_sub = true)
 * - Reviewers (is_sub = false)
 */
struct int_node {
    int integer;            ///< Identifier (submission or reviewer)
    bool is_sub=false;      ///< True if submission, false if reviewer
};

/**
 * @brief Comparison operator for int_node.
 */
bool operator< (const int_node& i1,const int_node& i2) ;

/**
 * @brief Equality operator for int_node.
 */
bool operator== (const int_node& i1,const int_node& i2);
/*
struct article {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string title="";
};

struct reviewer {
    int id;
    int primaryDomain;
    int secondaryDomain=-1;
    //  std::string name="";

};*/

/**
 * @brief Represents a successful assignment.
 */
struct assignment {
    const submission* a;
    const reviewer* rw;
};

/**
 * @brief Represents a failed assignment (missing reviews).
 */
struct failedAssignment {
    const submission* a;
    unsigned int missingSubmissions;
};



#endif //DA_PROJECT_1_DATASTRUCTS_H