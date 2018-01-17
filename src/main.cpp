//
// Created by Dzaposlav on 16/01/2018.
//
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "algorithms.h"

int main(int argc, const char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " " << "input.fasta" << std::endl;
    return -1;
  }

  std::ifstream data_in(argv[1]);
  if (!data_in.good()) {
    std::cerr << "Given input file doesn't exist." << std::endl;
    return -1;
  }

  std::string line;
  std::string sequence;
  std::getline(data_in, line);  // ignore header of fastA file
  while (!data_in.eof()) {
    std::getline(data_in, line);
    sequence += line;
  }
  sequence += '$'; // append terminator character

  auto lcp_array = compute_lcp(sequence);

  std::string output;

  output += "[";

  auto size = lcp_array.size();

  for (auto i = 0u; i < size; ++i) {
    output += std::to_string(lcp_array.at(i));
    if (i + 1 != size) {
      output += ",";
    } else {
      output += "]";
    }
  }

  std::cout << output << std::endl;

  return 0;
}