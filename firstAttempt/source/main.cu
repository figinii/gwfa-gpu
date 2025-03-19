#include "parsingFunctions.h"
#include "charBasedGeneticStructures.cu"
#include "gwfa.hu"
#include <cuda_runtime.h>

#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
  cudaSetDevice(1);
  if(argc < 3){
    std::cout << "Usage: " << argv[0] << "<sequenceFilePath.fa> " << " " 
                                                 << "<graphFilePath.fa> "   << std::endl;
    return 1;
  }

  // integeArray representation usage
  GeneticStrChar* sequence = new GeneticStrChar(parseFA(argv[1])[">read1"]);
  GeneticNode* first = parseGFA(argv[2]);
  TrackedGeneticNode* tracked = new TrackedGeneticNode(first, 0, 0);

  GeneticStrChar* queryD;
  TrackedGeneticNode* trackedD;
  GeneticNode* pttr;
  sequence->sendToCuda(&queryD);
  first->sendToCuda(&pttr);
  tracked->sendToCuda(&trackedD, &pttr);
  test<<<1, 1>>>(queryD);
  test<<<1, 1>>>(tracked, pttr);
  cudaDeviceSynchronize();

  std::cout << tracked->col << std::endl;
  std::cout << first->nodeContent->lcp(0, sequence, 0) << std::endl;

  // std::cout << sequence->toString() << std::endl;
  // std::cout << first->nodeContent->toString() <<std::endl;
  // std::cout << first->reachableNodes[0]->nodeContent->toString() << std::endl;
  
  return 0;
}