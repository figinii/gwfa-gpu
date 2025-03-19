#ifndef GENETIC_STRUCTURE_H
#define GENETIC_STRUCTURE_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "lcp.h"

template <typename T>
class GeneticStr : public LCP<T>{
public:
  //TODO virtualize also constructor with factory method
  // virtual GeneticStr* getGeneticStr() const = 0;
  // virtual GeneticStr* getGeneticStr(seqan3::dna5_vector sequence) const = 0;
  // virtual GeneticStr* getGeneticStr(std::string sequence) const = 0;
  virtual ~GeneticStr() = default;
  virtual void sendToCuda(T** ptr) const = 0;
  virtual std::string toString() const = 0;
};

#endif