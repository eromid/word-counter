#include "trie.h"
#include "text.h"
#include <stdlib.h>  /* calloc */

/*
  Add a word to the tree
*/
void addWord(const char *word, trienode *root)
{
  int character;
  trienode *node = root;
  
  /* if we have an actual word... */
  if (word != NULL)
  {
    /* for each character... */
    for (character = 0; word[character] != '\0'; ++character)
    {
      /* Move to existing node */
    	if (node->children[indexOf(word[character])] != NULL)
        node = node->children[indexOf(word[character])]; 
      /* Make new node to move to */
      else
        node = node->children[indexOf(word[character])] = calloc(1, sizeof(trienode));  
    }
    /* increment the counter for this word */
    ++(node->count);
  }
}


/*
  Get the index corresponding to a character.
*/
int indexOf(char c)
{
  return c == '\'' ? 26 : c - 'a';
}


/*
  Get the count of a certain word in an trie rooted at root.
*/
unsigned int getCount(const char *word, const trienode *root)
{
  int character;
  const trienode *node = root;
  for (character = 0; word[character] != '\0'; ++character)
  {
    if (node->children[indexOf(word[character])] != NULL)
      return 0;  
    else
      node = node->children[indexOf(word[character])]; 
  }
  return node->count;
}


/*
  Add the contents of a text file to the word count.  
*/
trienode * countTextFile(const char *path)
{
  const char *word = NULL;   /* The current word */
  Text text = getText(path);
  
  preprocess(&text);
  trienode *count_tree = calloc(1, sizeof(trienode));
  
  while ((word = getNextWord(&text)) != NULL) addWord(word, count_tree);
 
  freeText(&text);

  return count_tree;
}


/* The number of characters we support. */
const int n_chars = N_CHARS;
/* The mapping of characters to indices. */
const char characters[N_CHARS] = "abcdefghijklmnopqrstuvwxyz\'";


/*
  Print word counts to stream, defaulting to stdout.
*/
void printCounts(FILE *stream, trienode *root)
{
  int i;
  for (i = 0; i < n_chars; ++i)
  {
    if (root->children[i] != NULL)
    {
      printNode(stream, root->children[i], characters[i], 0);
    } 
  }
}


/*
  Recursively called to print words with > 0 instances.
*/
void printNode(FILE *stream, const trienode *node, char c, int depth)
{
  /* Storage for the string we build in our DFS */
  static char stack[64];

  /* push this character to the stack. */
  stack[depth] = c;

  /* If there are instances recorded, print the word and number */
  if (node->count)
    printf("%25s | %d\n", stack, node->count);

  /* Iterate over the other characters and call recursively as needed. */
  int i;
  for (i = 0; i < n_chars; ++i)
  {
    if (node->children[i] != NULL)
      printNode(stream, node->children[i], characters[i], depth+1);
  }
  stack[depth] = '\0';
}


/*
  De-allocate a tree or subtree.
*/
void freeTree(trienode *root)
{
  int i;
  for (i = 0; i < n_chars; ++i)
  {
    if (root->children[i] != NULL)
    {
      freeTree(root->children[i]);
    }
  }
  free(root);
}