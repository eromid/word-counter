# Word-Counts #

This small project was inspired by a programming assignment on course I was demonstrating/marking on. The students had to create a program to count the frequency with which each unique word occurs in a file. They were to use a couple of data structures to store the words and associated counts, including IIRC linked lists, arrays and trees. "Trees" here was meant to mean "binary search trees", however as I was currently working with [octrees](https://en.wikipedia.org/wiki/Octree) (think a quadtree but in three dimensions, or a binary tree but with eight children per node vs two), a different interpretation came to mind.

## A 27-ary Tree ##

This solution is built around a 27-ary tree, one child node for each letter of the alphabet, plus one for the apostrophe. This concept, it turns out, is known as a [Trie](https://en.wikipedia.org/wiki/Trie).

![A trie](./trie.png)

_Adapted from public domain work found on Wikipedia._

## How it works ##

Being a tree, there exists exactly one path from the root to every other node. The sequence of nodes in this path represents a word and the frequency (number of occurrences) of the word can be stored at the node where it terminates. So to add a word to the tree, we follow the path determined by the letters and increment a counter at the node where the path terminates. To retrieve all the counts (e.g. when we pretty-print them at the end of our counting) we do a depth-first traversal of our tree, and when we hit a node with a non-zero counter, we print it and the associated count (which involves a little back tracking in my implementation).

## Building ##

I've only tested with GCC 4.8 using `-std=c99` (as per the Makefile) on Linux.

`cd build && make`

## Usage ##

`./wordcounts <textfile>`
