#ifndef CUCGPRECONDITIONER_H
#define CUCGPRECONDITIONER_H

#include "cuNDArray.h"

template <class T> class cuCGPreconditioner
{
 public:
  cuCGPreconditioner() {}
  virtual ~cuCGPreconditioner() {}
  virtual int apply(cuNDArray<T>* in, cuNDArray<T>* out) = 0;
};

template <class T> class cuCGPrecondWeight : public cuCGPreconditioner<T>
{
 public:
  virtual int set_weights(cuNDArray<T>* w) {
    weights_ = *w;
    return 0;
  }

  virtual int apply(cuNDArray<T>* in, cuNDArray<T>* out);

 protected:
  cuNDArray<T> weights_;
};

#endif //CUCGPRECONDITIONER_H