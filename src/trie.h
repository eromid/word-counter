#include <stdio.h>

#define N_CHARS 27

/*
 *  A 27-ary tree to hold word counds
 */

/*
  Struct representing each vertex in the count tree.
*/
typedef struct trienode trienode;
struct trienode
{
  trienode *children[27];
  unsigned int count;
};

/*
  Add a word to the tree
*/
void addWord(const char *word, trienode *root);

/*
  Get the index corresponding to a character.
*/
int indexOf(char c);

/*
  Add the contents of a text file to the word count.  
*/
trienode * countTextFile(const char *path);

/*
  Get the count of a certain word in an trie rooted at root.
*/
unsigned int getCount(const char *word, const   trienode *root);

/*
  Print word counts to stream, defaulting to stdout.
*/
void printCounts(FILE *stream, trienode *root);

/*
  Recursively called to print words with > instance.
*/
void printNode(FILE *stream, const trienode *node, char c, int depth);

/*
  De-allocate a tree or subtree.
*/
void freeTree(trienode *root);