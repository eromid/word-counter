#include <stdio.h>
#include "alphtree.h"

/*
  Read a file and print out the number of occurrences of each word.
*/
int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s <text file>\n", argv[0]);
    return 1;
  }	

  AlphNode *counts_root = countTextFile(argv[1]);
  printCounts(stdout, counts_root);
  freeTree(counts_root);
  return 0;
}