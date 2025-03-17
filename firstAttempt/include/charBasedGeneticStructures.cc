#ifndef CHAR_GENETIC_STRUCTURE_H
#define CHAR_GENETIC_STRUCTURE_H

#include "geneticStructures.h"

class GeneticStrChar : public GeneticStr {
private:
  std::string content;

public:
  GeneticStrChar(){
    content = "";
  }

  GeneticStrChar(seqan3::dna5_vector sequence){
    content = "";
    for(auto nucleotide : sequence){
      content += nucleotide.to_char();
    }
  }

  GeneticStrChar(std::string sequence){
    content = sequence;
  }

  std::string toString() const override{
    return content;
  }

  ~GeneticStrChar() override{
    content.clear();
  }

};

#endif