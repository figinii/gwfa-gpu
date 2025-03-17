#ifndef GRAPH_STRUCTURE_H
#define GRAPH_STRUCTURE_H

#include "geneticStructures.h"
#include <vector>

template <typename T>
class GeneticNode{
private:

public:
  T* nodeContent;
  std::vector<GeneticNode*> reachableNodes;
  int reachabilitySize;
  
  GeneticNode(T* content){
    this->nodeContent = content;
    reachabilitySize = 0;
  }

  void addReachableNode(GeneticNode* newReachable){
    reachabilitySize += 1;
    reachableNodes.resize(reachabilitySize);
    reachableNodes[reachabilitySize-1] = newReachable;
  }

  ~GeneticNode(){
    free(nodeContent);
    reachableNodes.clear();
  }
};

#endif