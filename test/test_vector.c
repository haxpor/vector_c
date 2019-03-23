// test code for vector
#include <stdio.h>
#include "vector/vector.h"
#include <string.h>

#define STRING_BUFFER 255+1

struct myStruct {
  int integerValue;
  float floatValue;
  char nameValue[STRING_BUFFER];
  int* refIntegerValue;
};
typedef struct myStruct myStruct;

vector* vGeneral = NULL;
// integer that is referenced by myStruct
// this is to prove that deep copy for pointer type works
int outside_referenced = 999;

void printElements(vector* v) {
  printf("struct info: len=%d, mlen=%d\n", v->len, v->mlen);

  myStruct* tempStruct = NULL;
  for (int i=0; i<v->len; i++) {
    // convert to myStruct
    tempStruct = (myStruct*)(v->buffer + i*v->stride);
    printf("element %d: %d, %f, %s, %d\n", i, tempStruct->integerValue, tempStruct->floatValue, tempStruct->nameValue, *tempStruct->refIntegerValue);
  }
}

void custom_free_element(void* element)
{
  // cast to myStruct
  myStruct* casted_element = (myStruct*)element;

  printf("before free_element on struct {integerValue: %d, floatValue: %f, nameValue: %s, refIntegerValue address: %p}\n", casted_element->integerValue, casted_element->floatValue, casted_element->nameValue, casted_element->refIntegerValue);

  // do memory clearing task
  casted_element->integerValue = 0;
  casted_element->floatValue = 0.f;
  memset(casted_element->nameValue, 0, STRING_BUFFER);
  casted_element->refIntegerValue = NULL;

  printf("after free_element on struct {integerValue: %d, floatValue: %f, nameValue: %s, refIntegerValue address: %p}\n", casted_element->integerValue, casted_element->floatValue, casted_element->nameValue, casted_element->refIntegerValue);
}

int main(int argc, char* argv[])
{
  vGeneral = vector_new(5, sizeof(myStruct));
  // set freeing memory for each element
  vGeneral->free_element = custom_free_element;

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 1;
  newStruct.floatValue = 2.0;
  const char* str_value = "I'm struct 1";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 3;
  newStruct.floatValue = 4.0;
  const char* str_value = "I'm struct 2";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 5;
  newStruct.floatValue = 6.0;
  const char* str_value = "I'm struct 3";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 7;
  newStruct.floatValue = 8.0;
  const char* str_value = "I'm struct 4";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }
  
  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 9;
  newStruct.floatValue = 10.0;
  const char* str_value = "I'm struct 5";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // modify outside value
  outside_referenced = -999;

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 11;
  newStruct.floatValue = 12.0;
  const char* str_value = "I'm struct 6";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // remove 2nd element
  printf("Remove 2nd element\n");
  vector_remove(vGeneral, 1);
  printElements(vGeneral);

  // remove last element
  printf("Remove last element\n");
  vector_remove(vGeneral, vGeneral->len-1);
  printElements(vGeneral);

  // get before last element
  myStruct elem = *(myStruct*)vector_get(vGeneral, vGeneral->len-2);
  printf("pre-last element: %d,%f,%s\n", elem.integerValue, elem.floatValue, elem.nameValue);

	// shrink to fit
	printf("Shrink to fit\n");
	vector_shrink_to_fit(vGeneral);
	printElements(vGeneral);

  // clear all elements
  printf("gonna clear all elements now\n");
  vector_clear(vGeneral);
  printElements(vGeneral);

	// shrink to fit (should not take into effect)
	printf("Shrink to fit (should not take into effect)\n");
	vector_shrink_to_fit(vGeneral);
	printElements(vGeneral);

  // add a new element
  {
  myStruct newStruct;
  newStruct.integerValue = 12;
  newStruct.floatValue = 13.0;
  const char* str_value = "I'm struct 7";
  strncpy(newStruct.nameValue, str_value, strlen(str_value));
  newStruct.refIntegerValue = &outside_referenced;
  vector_add(vGeneral, (void*)(&newStruct));
  printElements(vGeneral);
  }

  // free vGeneral
  vector_free(vGeneral);

  return 0;
}
