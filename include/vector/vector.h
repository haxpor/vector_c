/*
 * Equivalent general-purpose vector in C.
 * Note that caller needs to know exactly the struct definition to get/set via this vector.
 */

#ifndef vector_h_
#define vector_h_

// our vector type
struct vector
{
  /// number of element 
  int len;

  // (internal use only) managed length of estimated legnth
  int mlen;

  // (internal use only) size of element in bytes
  // it'll be set only via vector_createNew()
  int stride;

  /// buffer pointer to hold all data
  void* buffer;

  /// free element function
  /// if you have custom element that need to have a proper memory freeing
  /// you can set it here, otherwise it won't have any effect and its buffer's memory chunk
  /// will be normally freed
  ///
  /// input is `void* element`, you can cast it to your type then do things properly.
  void (*free_element)(void* element);
};
typedef struct vector vector;

///
/// create a new vector
///
/// \param estimatedLen estimated length that vector will probably has at any given time.
///                     This value will be used when `vector_shrink()` function is called to
///                     shrink down the memory.
/// \param stride size in bytes of a single element
///
extern vector* vector_new(int estimatedLen, int stride);

///
/// append a new element to vector
///
/// \param v pointer to vector
/// \param d opaque pointer to new element to be added
///
extern void vector_add(vector* v, void* d);

///
/// remove element at index `i`
///
/// \param v pointer to vector
/// \param i index to remove element from vector
///
extern void vector_remove(vector* v, int i);

///
/// get element from vector at specified index
///
/// \param v pointer to vector
/// \param i index to get element from
///
extern void* vector_get(vector* v, int i);

///
/// Clear all elements inside this vector
///
/// \param vector Pointer to vector
///
extern void vector_clear(vector* v);

/// free vector from memory
/// after calling this function, vector will be freed and set to NULL.
///
/// \param v pointer to vector
///
extern void vector_free(vector* v);

/// shrink allocated memory down to current number of elements that vector has
///
/// \param v pointer to vector
///
extern void vector_shrink_to_fit(vector* v);

#endif /* vector_h_ */
