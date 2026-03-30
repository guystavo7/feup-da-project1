//
// Created by gustavobastos on 22/03/26.
//
/**
 * @file utils.h
 * @brief Utility functions for file handling and comparison.
 *
 * This module provides helper functions for:
 * - Comparing the contents of two files
 * - Counting the number of lines in a file
 */
#ifndef DA_PROJECT_1_UTILS_H
#define DA_PROJECT_1_UTILS_H
#include <string>

/**
 * @brief Compares two files line by line up to a given limit.
 *
 * Reads both files simultaneously and compares their contents line by line.
 * The comparison stops when:
 * - A difference is found
 * - The specified number of lines is reached
 * - Both files reach EOF
 *
 * @param caminho1 Path to the first file
 * @param caminho2 Path to the second file
 * @param limiteLinhas Maximum number of lines to compare
 * @return true if the compared lines are identical, false otherwise
 *
 * @complexity O(n), where n is the number of lines compared
 */
bool file_comparator(const std::string& caminho1, const std::string& caminho2, int limiteLinhas) ;

/**
 * @brief Counts the number of lines in a file.
 *
 * Reads the file line by line and counts how many lines it contains.
 *
 * @param filePath Path to the file
 * @return Number of lines in the file, or -1 if the file cannot be opened
 *
 * @complexity O(n), where n is the number of lines in the file
 */
int file_len(const std::string& filePath) ;

#endif //DA_PROJECT_1_UTILS_H