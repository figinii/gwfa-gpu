#ifndef CHAR_GENETIC_STRUCTURE_H
#define CHAR_GENETIC_STRUCTURE_H

#include "geneticStructures.h"
#include "lcp.h"

class GeneticStrChar : public GeneticStr<GeneticStrChar> {
private:
public:
  char* content;
  u_long len;


  GeneticStrChar(){
    content = (char*) malloc(sizeof(char));
    *content = (char) "\0";
    len = 0;
  }

  GeneticStrChar(seqan3::dna5_vector sequence){
    content = (char*) malloc(sizeof(char) * (sequence.size()+1));
    int i = 0;
    for(auto nucleotide : sequence){
      char tmp = nucleotide.to_char();
      content[i] = tmp;
      i++;
    }
    len = sequence.size();
  }

  GeneticStrChar(std::string sequence){
    content = (char*) malloc(sizeof(char) * (sequence.size()+1));
    int i = 0;
    for(auto nucleotide : sequence){
      content[i] = nucleotide;
      i++;
    }
    len = sequence.size();
  }

  void GeneticStrDeviceMove(GeneticStrChar** ptr){
    char* contentD;
    cudaMalloc((void**)&contentD, (sizeof(char) * (len+1)));
    cudaMemcpy(contentD, this->content, (this->len+1), cudaMemcpyHostToDevice);

    cudaMalloc((void**)ptr, sizeof(GeneticStrChar));
    cudaMemcpy(*ptr, this, sizeof(GeneticStrChar), cudaMemcpyHostToDevice);
  }

  long lcp(long myIndex, GeneticStrChar* other, long otherIndex) const override {
    long len = 0;
    while(content[myIndex+len] != '\0' && 
          other->content[len+otherIndex] != '\0' &&
          content[myIndex+len] == other->content[len+otherIndex])
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