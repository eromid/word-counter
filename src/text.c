#include "text.h"

#include <stdio.h>
#include <stdlib.h>

/*
  Load the text from file at path.
*/
Text getText(const char *path)
{
  Text text;
  FILE *in_file = NULL;
  size_t bytes_read = 0;

  /* Zero the members of the struct. */
  text.length       = 0ul;
  text.data         = NULL;
  text.current_word = NULL;

  /* Open file. */
  if (!(in_file = fopen(path, "rb")))
  {
    fprintf(stderr, "Couldn't open %s!", path);
    exit(2);
  }

  /* Get the length of the file and allocate buffer, with space for a null. */
  fseek(in_file, 0, SEEK_END);
  text.length = ftell(in_file);
  if ( !(text.data = calloc(text.length + 1, sizeof(*text.data))) )
  {
    fclose(in_file);
    fprintf(stderr, "Couldn't allocate memory (%zd bytes)!",
            sizeof(*text.data) * text.length + 1);
    exit(3);
  }

  /* Read the data */
  fseek(in_file, 0, SEEK_SET);
  bytes_read = fread(text.data, 1, text.length, in_file);
  fclose(in_file);

  /* Check we read all the data. */
  if (bytes_read != text.length)
  {
    if (text.data)
      free(text.data);
    fprintf(stderr, "Failed to read expected number of chars!\n");
    exit(4);
  }

  /* Set the "current word" pointer to the start. */
  text.current_word = text.data;
  return text;
}


/*
  Dealloc the memory used by the text and zero the members.
*/
void freeText(Text *text)
{
  if (text->data)
  {
    free(text->data);
    text->data = NULL;
    text->current_word = NULL;
    text->length = 0;
  }
}


/*
  Lower text and replace illegal characters with \0s, creating an array of
  words which are null terminated by one or more null bytes.
*/
void preprocess(Text *text)
{
  unsigned long char_index;
  char previous = '\0';
  char current  = '\0';
  char next = text->data[0];  /* Next is the first charcter as we go into the loop */
  for (char_index = 0ul; char_index < text->length; ++char_index)
  {
    previous = current;
    current = next;
    next = text->data[char_index+1];
    if (isAlpha(current))
    {
      text->data[char_index] = lower(current);
    }
    else if (isAlpha(previous) && isAlpha(next) && current == '\'')
    {
      continue;
    }
    else
    {
      text->data[char_index] = '\0';
    }
  }
}


/*
  Get pointer to the next word.
*/
const char * getNextWord(Text *text)
{
  const char *word = NULL;

  /* Skip any null characters between words */
  while ((unsigned long)(text->current_word - text->data) < text->length &&
         *text->current_word == '\0')
  {
    ++text->current_word;
  }

  word = text->current_word;  /* we are at a word */

  /* Skip to the end of the current word ready for the next call. */
  while ((unsigned long)(text->current_word - text->data) < text->length &&
         *text->current_word != '\0')
  {
    ++text->current_word;
  }

  /* Make sure we aren't at the end of the data. */
  if (word < (text->data + text->length))
    return word;
  else
    return NULL;
}
 

/*
  Return true if the character is alphabetical
*/
bool isAlpha(char c)
{
  return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}


/*
  Convert char c to lowercase.
  CAUTION: Expects alpha
*/
char lower(char c)
{
  return c | 32;
}