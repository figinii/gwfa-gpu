#ifndef INT_GENETIC_STRUCTURE_H
#define INT_GENETIC_STRUCTURE_H

#include "geneticStructures.h"

#define MAX_NUCLEOTIDE_SIZE 32

typedef struct GeneticContent{
  uint64_t content;
  int8_t nucleotideNum;
  GeneticContent* next;
}GeneticContent;

class GeneticStrInt : public GeneticStr{
private:
  GeneticContent* contentListHead;
  GeneticContent* contentListTail;
  uint8_t actualSize;  

  //TODO move this in a genetic content class 
  GeneticContent* getNewNode(){
    GeneticContent* newNode = (GeneticContent*) malloc(sizeof(GeneticContent));
    newNode->content = 0;
    newNode->next = nullptr;
    newNode->nucleotideNum = 0;
    return newNode;
  }
  //TODO make it so the bits are always alligned on left
  void addNucleotide(uint8_t nucleotide){
    if(contentListTail->nucleotideNum == MAX_NUCLEOTIDE_SIZE){
      GeneticContent* substitute = getNewNode();
      this->actualSize +=1;
      this->contentListTail->next = substitute;
      this->contentListTail = substitute;
    }
    this->contentListTail->content <<= 2;
    this->contentListTail->content += nucleotide;

    this->contentListTail->nucleotideNum++;
  }
public:
  GeneticStrInt(){
    this->actualSize = 1;
    GeneticContent* firstNode = getNewNode();
    contentListHead = firstNode;
    contentListTail = firstNode;
  }

  GeneticStrInt(seqan3::dna5_vector sequence){
    this->actualSize = 1;
    GeneticContent* firstNode = getNewNode();
    contentListHead = firstNode;
    contentListTail = firstNode;

    for(auto nucelotide : sequence){
      int val = nucelotide.to_rank();
      if(val == 4)
        val = 3;
      this->addNucleotide(val);
    }
  }

  GeneticStrInt(std::string sequence){
    this->actualSize = 1;
    GeneticContent* firstNode = getNewNode();
    contentListHead = firstNode;
    contentListTail = firstNode;

    for(auto c : sequence){
      int val;
      switch (c)
      {
      case 'A':
        val = 0;
        break;
      case 'C':
        val = 1;
        break;
      case 'G':
        val = 2;
        break;
      case 'T':
        val = 3;
        break;
      default:
        break;
      }

      this->addNucleotide(val);
    }
  }
  

  std::string toString() const override{
    std::string result;
    GeneticContent* current = this->contentListHead;
    while(current != nullptr){
      result.append(std::to_string(current->content));
      current = current->next;
    }
    return result;
  }

  ~GeneticStrInt() override{
    GeneticContent* current = this->contentListHead;
    while(current!=nullptr){
      GeneticContent* next = current->next;
      free(next);
      current = next;
    }
  }

};

#endif