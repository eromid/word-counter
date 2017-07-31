#include <stdbool.h>

/*
  Structure to represent a loaded text.
*/
typedef struct Text
{
  unsigned long length;
  char *data;
  char *current_word;
} Text;

/*
  Load the text from file at path.
*/
Text getText(const char *path);

/*
  Dealloc the memory used by the text.
*/
void freeText(Text *text);

/*
  Lower text and replace illegal characters with \0s
*/
void preprocess(Text *text);

/*
  Get pointer to the next word.
*/
const char * getNextWord(Text *text);

/*
  Covert alpha character to lowercase
*/
char lower(char c);

/*
  Return true if the character is alphabetical
*/
bool isAlpha(char c);

/*
  Is c and apostrophe?
*/
bool isApostrophe(char c);