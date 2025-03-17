#ifndef PARSING_FUN_H
#define PARSING_FUN_H

#include <seqan3/io/sequence_file/all.hpp>
#include "geneticStructures.h"
#include "graphStructure.h" 
#include <string>
#include <map>
#include <filesystem>



//TODO extract dna4 sequences
seqan3::dna5_vector parseFA(std::string filePath){
  auto seqFilepath = std::filesystem::current_path() / filePath;
  seqan3::sequence_file_input fin{seqFilepath};
  return (*fin.begin()).sequence();
}

template <typename geneticStrImplementation>
GeneticNode<geneticStrImplementation>* parseGFA(std::string filePath){
  
  auto graphFilepath = std::filesystem::current_path() / filePath;
  
  std::ifstream file(graphFilepath);
  std::map<std::string, GeneticNode<geneticStrImplementation>*> allGeneticStrings;
  std::string line;
  
  GeneticNode<geneticStrImplementation>* firstNode = nullptr;  
  while (std::getline(file, line)){
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "S") {
      std::string name;
      std::string sequence;
      iss >> name >> sequence;
      
      GeneticNode<geneticStrImplementation>* node = new GeneticNode<geneticStrImplementation>(new geneticStrImplementation(sequence));
      allGeneticStrings[name] = node;
      
      if(firstNode == nullptr)
        firstNode = node;
    }

    if (type == "L") {
      std::string nodeName1;
      std::string orientation1;
      std::string nodeName2;
      std::string orientation2;
      std::string overlapping;
      iss >> nodeName1 >> orientation1 >> nodeName2 >> orientation2 >> overlapping;

      GeneticNode<geneticStrImplementation>* node1 = allGeneticStrings[nodeName1];
      GeneticNode<geneticStrImplementation>* node2 = allGeneticStrings[nodeName2];

      node1->addReachableNode(node2);
    }
  }

  return firstNode;
}


#endif