#ifndef GRAPH_STRUCTURE_H
#define GRAPH_STRUCTURE_H

#include "./geneticStructures.h"
#include <vector>

class GeneticNode{
private:

public:
  GeneticStr* nodeContent;
  std::vector<GeneticNode*> reachableNodes;
  int reachabilitySize;
  
  GeneticNode(GeneticStr* content){
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

typedef struct {
  GeneticNode node;
  long diagonal;
  long column;
} TrackingNode;

#endif