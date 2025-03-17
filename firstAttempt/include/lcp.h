#ifndef LCP_H 
#define LCP_H

template <typename T>
class LCP{
public:
  virtual long lcp(T* other) const = 0;
};

#endif