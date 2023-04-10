#pragma once

#include <string>

#include <vector>

std::string encodeLZW(const std::string &text);

std::string decodeLZW(const std::vector<int> &arr);
