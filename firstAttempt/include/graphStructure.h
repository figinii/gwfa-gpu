#ifndef GRAPH_STRUCTURE_H
#define GRAPH_STRUCTURE_H

// TODO unaccettable to be type dependent
#include "charBasedGeneticStructures.cu"
#include "geneticStructures.h"
#include <vector>

//TODO organize the structure in a vector of nodes with pointers to reaching vectors
class GeneticNode{
private:

public:
  GeneticStrChar* nodeContent;
  GeneticNode** reachableNodes;
  u_long reachabilitySize;
  
  GeneticNode(){
    this->nodeContent = new GeneticStrChar();;
    reachableNodes = nullptr;
    reachabilitySize = 0;
  }

  GeneticNode(GeneticStrChar* content){
    this->nodeContent = content;
    reachableNodes = nullptr;
    reachabilitySize = 0;
  }

  void addReachableNode(GeneticNode* newReachable){
    reachabilitySize += 1;
    reachableNodes = (GeneticNode**) realloc(reachableNodes, reachabilitySize * sizeof(GeneticNode*));
    reachableNodes[reachabilitySize-1] = newReachable;
  }

  void sendToCuda(GeneticNode** d_ptr){
    cudaMalloc((void**)d_ptr, sizeof(GeneticNode));
    GeneticNode* tmp = new GeneticNode();
    tmp->reachabilitySize = this->reachabilitySize;

    GeneticStrChar* d_nodeContent;
    nodeContent->sendToCuda(&d_nodeContent);
    tmp->nodeContent = d_nodeContent;
    
    GeneticNode* d_pointers[reachabilitySize];
    for(u_long i = 0; i < this->reachabilitySize; i++){
      GeneticNode* d_reachability;
      reachableNodes[i]->sendToCuda(&d_reachability);
      d_pointers[i] = d_reachability;
    }
    GeneticNode* d_reachabilityList;
    cudaMalloc(&d_reachabilityList, reachabilitySize * sizeof(GeneticNode*));
    cudaMemcpy(d_reachabilityList, d_pointers, reachabilitySize * sizeof(GeneticNode*), cudaMemcpyHostToDevice);

    GeneticNode** d_listPointer;
    cudaMalloc(&d_listPointer, sizeof(GeneticNode**));
    cudaMemcpy(d_listPointer, d_reachabilityList, sizeof(GeneticNode**), cudaMemcpyHostToDevice);
    tmp->reachableNodes = d_listPointer;

    cudaMemcpy(*d_ptr, tmp, sizeof(GeneticNode), cudaMemcpyHostToDevice);
  }

  ~GeneticNode(){
    free(nodeContent);
    free(reachableNodes);
  }
};

struct TrackedGeneticNode{
  GeneticNode* genetic;
  long col;
  long diag;
  
  TrackedGeneticNode(GeneticNode* geneticNode, long column, long diagonal)
  : genetic(geneticNode), col(column), diag(diagonal) {}

  void sendToCuda(TrackedGeneticNode** ptr, GeneticNode** pttr){
    
  }
};

#endif