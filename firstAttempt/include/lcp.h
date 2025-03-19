#ifndef LCP_H 
#define LCP_H

template <typename T>
class LCP{
public:
  virtual long lcp(long myIndex, T* other, long otherIndex) const = 0;
};

#endif