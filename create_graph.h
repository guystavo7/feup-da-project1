/**
 * @file create_graph.h
 * @brief Builds the graph for the reviewer assignment problem.
 *
 * This module is responsible for transforming the parsed input data into a
 * graph representation suitable for max-flow algorithms.
 */
#ifndef CREATE_GRAPH_H
#define CREATE_GRAPH_H

#include "graph.h"
#include "parser.h"

/**
 * @brief Constructs a graph for the assignment problem.
 *
 * The resulting graph follows this structure:
 * - Source node (id = -1)
 * - Sink node (id = -2)
 * - Submission nodes (is_sub = true)
 * - Reviewer nodes (is_sub = false)
 *
 * Edges:
 * - Source -> Submission (capacity = MinReviewsPerSubmission)
 * - Reviewer -> Sink (capacity = MaxReviewsPerReviewer)
 * - Submission -> Reviewer (capacity = 1 if domains match)
 *
 * Matching rules depend on the GenerateAssignments parameter:
 * - 1: Only primary domain/expertise
 * - 2: Primary + secondary submissions vs primary reviewers
 * - 3: Full matching (primary + secondary both sides)
 *
 * @param info Struct containing submissions, reviewers, and parameters.
 * @return Graph<int_node> Graph ready for max-flow utilization.
 *
 * @complexity O(S*R), where S=number of submissions and R=number of reviewers.
 */

Graph<int_node> create(params info);

#endif