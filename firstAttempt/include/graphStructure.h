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

  void sendToCuda(GeneticNode** ptr){
    GeneticStrChar* nodeContentCuda;
    nodeContent->sendToCuda(&nodeContentCuda);
    
    // GeneticNode** reachabilityPtrCuda;
    // cudaMalloc((void**)&reachabilityPtrCuda, sizeof(GeneticNode**));

    // GeneticNode* reachableArrayCuda[reachabilitySize];
    // GeneticNode *tmp;
    // for(long i=0; i < reachabilitySize; i++){
    //   this->reachableNodes[i]->sendToCuda(&tmp);
    //   reachableArrayCuda[i] = tmp;
    // }
    // cudaMemcpy(reachabilityPtrCuda, tmp, sizeof(GeneticNode*), cudaMemcpyHostToDevice);

    cudaMalloc((void**)ptr, sizeof(GeneticNode*));
    GeneticNode* tmpNode = new GeneticNode(nodeContentCuda);
    tmpNode->reachabilitySize += 140;
    // tmpNode->reachableNodes = reachabilityPtrCuda;

    cudaMemcpy(*ptr, tmpNode, sizeof(GeneticNode), cudaMemcpyHostToDevice);
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