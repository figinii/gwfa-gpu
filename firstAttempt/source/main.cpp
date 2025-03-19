#include <seqan3/core/debug_stream.hpp>
#include "parsingFunctions.h"
#include "charBasedGeneticStructures.cu"
#include "gwfa.hu"

int main(int argc, char **argv)
{
  if(argc < 3){
    seqan3::debug_stream << "Usage: " << argv[0] << "<sequenceFilePath.fa> " << " " 
                                                 << "<graphFilePath.fa> "   <<"\n";
    return 1;
  }

  

  // integeArray representation usage
  GeneticStrChar* sequence = new GeneticStrChar(parseFA(argv[1]));
  GeneticNode<GeneticStrChar>* first = parseGFA<GeneticStrChar>(argv[2]);
  TrackedGeneticNode<GeneticStrChar>* t = new TrackedGeneticNode(first, 0, 0);

  GeneticStrChar* queryD;
  sequence->GeneticStrDeviceMove(&queryD);

  test(queryD);
  cudaDeviceSynchronize();

  std::cout << t->col << std::endl;
  std::cout << strlen(first->nodeContent->content) << std::endl;
  std::cout << first->nodeContent->lcp(0, sequence, 0) << std::endl;

  // std::cout << sequence->toString() << std::endl;
  // std::cout << first->nodeContent->toString() <<std::endl;
  // std::cout << first->reachableNodes[0]->nodeContent->toString() << std::endl;
  

  return 0;
}