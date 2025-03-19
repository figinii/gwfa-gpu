#ifndef GRAPH_STRUCTURE_H
#define GRAPH_STRUCTURE_H

#include "geneticStructures.h"
#include <vector>

//TODO organize the structure in a vector of nodes with pointers to reaching vectors
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

template <typename T>
struct TrackedGeneticNode{
  GeneticNode<T>* genetic;
  long col;
  long diag;
  
  TrackedGeneticNode(GeneticNode<T>* geneticNode, long column, long diagonal)
  : genetic(geneticNode), col(column), diag(diagonal) {}
};

template <typename T>
struct TrackedNodeArr{
  TrackedGeneticNode<T>* arr;
  long size;
};

#endif