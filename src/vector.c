#include "vector/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// increasing factor when vector needs to expand memory space
#define INC_ELEM_FACTOR 1.5

vector* vector_new(int estimatedLen, int stride)
{
  // it should satisfy
  // 1. estimatedLen > 0
  // 2. stride > 0

  // create vector
  vector* out = malloc(sizeof(vector));
  out->len = 0;
  out->mlen = estimatedLen;
  out->stride = stride;
  out->free_element = NULL; // default with no custom freeing function for its element
  
  // create buffer held by vector
  void* buf = malloc(stride * estimatedLen);
  // set to vector
  out->buffer = buf;

  return out;
}

void vector_add(vector* v, void* d)
{
  // it should satisfy
  // 1. v != NULL
  // 2. d != NULL

  // if there is still space left to fill
  if (v->len < v->mlen) {
    // do memory copy from source to our buffer
    memcpy(v->buffer + v->len*v->stride, d, v->stride);
    v->len++;
  }
  // otherwise it need to allocate more space
  // increase memory space by INC_ELEM_FACTOR of current element count
  else {
    // mlen or len, no matter now, they are equal
    v->mlen = lroundf(v->mlen * INC_ELEM_FACTOR);
    v->buffer = realloc(v->buffer, v->mlen*v->stride); 
    // add a new element
    memcpy(v->buffer + v->len*v->stride, d, v->stride);
    v->len++;
  }
}

void vector_remove(vector* v, int i)
{
  // it should satisfy
  // 1. v != NULL
  // 2. i < v->len

  // do custom memory freeing if user supply such function
  if (v->free_element != NULL)
  {
    v->free_element(v->buffer + i*v->stride);
  }

  // we can do the whole memory shift
  if (i+1 < v->len)
  {
    // move the whole memory chunk to the left
    // source and destination does not overlap, no need to use memmove here
    memcpy(v->buffer + i*v->stride, v->buffer + (i+1)*v->stride, (v->len - i - 1) * v->stride);
    // set zero to the last element
    memset(v->buffer + (v->len - 1)*v->stride, 0, v->stride);
  }
  // otherwise we just need to zero last element's memory
  else
  {
    memset(v->buffer + i*v->stride, 0, v->stride);
  }

  // update len
  // note: don't decrement mlen, we will only grow not shrink.
  // only shrink when free via vector_free()
  v->len--;
}

void* vector_get(vector* v, int i)
{
  // it should satisfy
  // 1. v != NULL
  // 2. i < v->len

  return v->buffer + i*v->stride;
}

void vector_clear(vector* v)
{
  // only make sense if we do this operation when there's at least 1 element inside
  if (v->len > 0)
  {
    // if need to do custom memory freeing for element, then do it
    if (v->free_element != NULL)
    {
      // do it for all element
      for (int i=0; i<v->len; i++)
      {
        v->free_element(v->buffer + i*v->stride);
      }
    }

    // write 0 for all allocated memory (for safety)
    memset(v->buffer, 0, v->len*v->stride);

    // now all elements are not making sense if we still access it
    v->len = 0;
    // shirnk data down, set back to estimated number of element of 1
    v->mlen = 1;
    v->buffer = realloc(v->buffer, v->mlen*v->stride);
  }
}

void vector_free(vector* v)
{
  // it should satisfy
  // 1. v != NULL

  // do custom memory freeing for all elements
  // if user supplies with such function
  if (v->free_element != NULL)
  {
    for (int i=0; i<v->len; i++)
    {
      v->free_element(v->buffer + i*v->stride);
    }
  }

  // free its buffer first
  if (v->buffer != NULL) {
    free(v->buffer);
    v->buffer = NULL;
  }

  // free the source
  free(v);
  v = NULL;
}

void vector_shrink_to_fit(vector* v)
{
  // if current managed length is more than the current element length
  // then we need to shrink
  if (v->mlen > v->len && v->len > 0)
  {
    // shrink down
    v->buffer = realloc(v->buffer, v->len * v->stride);   
    // update the number of elements
    v->mlen = v->len;
  }
}
