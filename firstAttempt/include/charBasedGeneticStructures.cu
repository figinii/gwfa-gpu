#ifndef CHAR_GENETIC_STRUCTURE_H
#define CHAR_GENETIC_STRUCTURE_H

#include "geneticStructures.h"
#include "lcp.h"
#include <cuda_runtime.h>
#include <iostream>

class GeneticStrChar : public GeneticStr<GeneticStrChar> {
private:
public:
  char* content;
  u_long len;


  GeneticStrChar(){
    content = (char*) malloc(sizeof(char));
    *content = '\0';
    len = 0;
  }

  GeneticStrChar(std::string sequence){
    content = (char*) malloc(sizeof(char) * (sequence.size()+1));
    int i = 0;
    for(auto nucleotide : sequence){
      content[i] = nucleotide;
      i++;
    }
    len = sequence.size();
    this->content[len] = '\0';
  }

  void sendToCuda(GeneticStrChar** ptr) const override{
    char* contentD;
    cudaMalloc((void**)&contentD, (sizeof(char) * (len+1)));
    cudaMemcpy(contentD, this->content, (sizeof(char) * (len+1)), cudaMemcpyHostToDevice);

    cudaMalloc((void**)ptr, sizeof(GeneticStrChar));
    GeneticStrChar* tmp = new GeneticStrChar();
    tmp->content = contentD;
    tmp->len = len;
    cudaMemcpy(*ptr, tmp, sizeof(GeneticStrChar), cudaMemcpyHostToDevice);
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