#ifndef CHAR_GENETIC_STRUCTURE_H
#define CHAR_GENETIC_STRUCTURE_H

#include "geneticStructures.h"
#include "lcp.h"

class GeneticStrChar : public GeneticStr<GeneticStrChar> {
private:
public:
  char* content;
  GeneticStrChar(){
    content = (char*) malloc(sizeof(char));
  }

  GeneticStrChar(seqan3::dna5_vector sequence){
    content = (char*) malloc(sizeof(char) * (sequence.size()+1));
    int i = 0;
    for(auto nucleotide : sequence){
      char tmp = nucleotide.to_char();
      content[i] = tmp;
      i++;
    }
  }

  GeneticStrChar(std::string sequence){
    content = (char*) malloc(sizeof(char) * (sequence.size()+1));
    int i = 0;
    for(auto nucleotide : sequence){
      content[i] = nucleotide;
      i++;
    }
  }

  long lcp(GeneticStrChar* query) const override {
    long len = 0;    
    while(content[len] != '\0' && 
          query->content[len] != '\0' &&
          content[len] == query->content[len])
      len++;
    return len;
  }

  std::string toString() const override{
    return content;
  }

  ~GeneticStrChar() override{
    free(content);
  }

};

#endif