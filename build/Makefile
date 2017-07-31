CC=gcc
STD_FLAG=-std=c99
CFLAGS=$(STD_FLAG) -Wall -Werror -Wextra -pedantic -O3
TARGET=wordcounts
SRC_DIR=../src

all: wordcounts

wordcounts: main.o alphtree.o text.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o alphtree.o text.o

main.o: $(SRC_DIR)/main.c alphtree.o text.o
	$(CC) $(CFLAGS) -c -o main.o $(SRC_DIR)/main.c 

alphtree.o: $(SRC_DIR)/alphtree.c text.o
	$(CC) $(CFLAGS) -c -o alphtree.o $(SRC_DIR)/alphtree.c

text.o: $(SRC_DIR)/text.c
	$(CC) $(CFLAGS) -c -o text.o $(SRC_DIR)/text.c

clean:
	rm -f *.o

veryclean: clean
	rm -f $(TARGET)
