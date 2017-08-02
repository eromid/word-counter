CC=gcc
STD_FLAG=-std=c99
CFLAGS=$(STD_FLAG) -Wall -Werror -Wextra -pedantic -O3
TARGET=wordcounts
SRC_DIR=../src

all: wordcounts

wordcounts: main.o trie.o text.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o trie.o text.o

main.o: $(SRC_DIR)/main.c trie.o text.o
	$(CC) $(CFLAGS) -c -o main.o $(SRC_DIR)/main.c 

trie.o: $(SRC_DIR)/trie.c text.o
	$(CC) $(CFLAGS) -c -o trie.o $(SRC_DIR)/trie.c

text.o: $(SRC_DIR)/text.c
	$(CC) $(CFLAGS) -c -o text.o $(SRC_DIR)/text.c

clean:
	rm -f *.o

veryclean: clean
	rm -f $(TARGET)
