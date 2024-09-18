#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Graph.h"

std::vector<std::string> split(const std::string &s, char delimiter);

std::vector<int> parseIntList(const std::string &str);

std::vector<std::string> parseCsvLine(const std::string &line);

Graph readData(const std::string &filename);

#endif