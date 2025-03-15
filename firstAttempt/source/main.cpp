#include <seqan3/core/debug_stream.hpp>
#include "./parsingFunctions.h"

int main(int argc, char **argv)
{
  if(argc < 3){
    seqan3::debug_stream << "Usage: " << argv[0] << "<sequenceFilePath.fa> " << " " 
                                                 << "<graphFilePath.fa> "   <<"\n";
    return 1;
  }

  seqan3::debug_stream << "Hello World!\n";
  
  
  GeneticStr* sequence = parseFA(argv[1]);
  GeneticNode* first = parseGFA(argv[2]);


  std::cout << sequence->toString() << std::endl;
  std::cout << first->nodeContent->toString() <<std::endl;
  std::cout << first->reachableNodes[0]->nodeContent->toString() << std::endl;
  

  return 0;
}