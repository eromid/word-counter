#include <stdio.h>

#define N_CHARS 27

/*
 *  A 27-ary tree to hold word counds
 */

/*
  Struct representing each vertex in the count tree.
*/
typedef struct AlphNode AlphNode;
struct AlphNode
{
  AlphNode *children[27];
  unsigned int count;
};

/*
  Add a word to the tree
*/
void addWord(const char *word, AlphNode *root);

/*
  Get the index corresponding to a character.
*/
int indexOf(char c);

/*
  Add the contents of a text file to the word count.  
*/
AlphNode * countTextFile(const char *path);

/*
  Get the count of a certain word in an alphtree rooted at root.
*/
unsigned int getCount(const char *word, const AlphNode *root);

/*
  Print word counts to stream, defaulting to stdout.
*/
void printCounts(FILE *stream, AlphNode *root);

/*
  Recursively called to print words with > instance.
*/
void printNode(FILE *stream, const AlphNode *node, char c, int depth);

/*
  De-allocate a tree or subtree.
*/
void freeTree(AlphNode *root);