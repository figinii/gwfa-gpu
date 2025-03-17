#ifndef PARSING_FUN_H
#define PARSING_FUN_H

#include <seqan3/io/sequence_file/all.hpp>
#include "geneticStructures.h"
#include "graphStructure.h" 
#include <string>
#include <map>
#include <filesystem>



//TODO extract dna4 sequences


GeneticStr* parseFA(std::string filePath){
  auto seqFilepath = std::filesystem::current_path() / filePath;
  seqan3::sequence_file_input fin{seqFilepath};
  auto seq = (*fin.begin()).sequence();
  return new GeneticStr(seq);
}

GeneticNode* parseGFA(std::string filePath){
  
  auto graphFilepath = std::filesystem::current_path() / filePath;
  
  std::ifstream file(graphFilepath);
  std::map<std::string, GeneticNode*> allGeneticStrings;
  std::string line;
  
  GeneticNode* firstNode = nullptr;  
  while (std::getline(file, line)){
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "S") {
      std::string name;
      std::string sequence;
      iss >> name >> sequence;
      
      GeneticNode* node = new GeneticNode(new GeneticStr(sequence));
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

      GeneticNode* node1 = allGeneticStrings[nodeName1];
      GeneticNode* node2 = allGeneticStrings[nodeName2];

      node1->addReachableNode(node2);
    }
  }

  return firstNode;
}


#endif