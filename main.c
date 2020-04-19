#include "list.h"
#include <stdio.h>
#include <stdlib.h>

static void AssertEq(int expected, int actual, const char* msg) {
  if (expected != actual) {
    printf("Test failed: %s\n expected %d but got %d\n", msg, expected, actual);
    exit(-1);
  }
}

int main(void) {
  List* list = NewList();
  List* list2 = NewList();
  AssertEq(0, Length(list), "Length([]) should be 0");
  Append(list, 1);
  Append(list, 25);
  Append(list2, 10);
  AssertEq(1, Length(list2), "Length([10]) should be 1");
  Prepend(list, 100);
  AssertEq(100, GetAt(list, 0), "GetAt([100]) should be 100");
  Append(list2, 1000);
  InsertAt(list2, 0, 0);
  AssertEq(0, GetAt(list2, 1), "GetAt([0]) should be 0");
  AssertEq(1000, Pop(list2), "Pop(list2) should be 1000");
  AssertEq(100, Dequeue(list), "Dequeue(list) should be 100");
  RemoveAt(list, 0);
  AssertEq(25, GetAt(list, 0), "GetAt([25]) should be 25");
  RemoveAll(list2);
  AssertEq(0, Length(list2), "Length([]) should be 0");
  Append(list2, 30);
  Append(list2, 90);
  AppendAll(list, list2);
  AssertEq(3, Length(list), "Length(list) should be 3");
  AssertEq(30, GetAt(list, 1), "GetAt(list, 1) should be 30");
  DestroyList(list);
  DestroyList(list2);
}
