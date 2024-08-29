CC = gcc
CFLAGS = -Wall -g
TARGET = test_avl
OBJS = test_avl_tree.o avl_tree.o
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
test_avl_tree.o: test_avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c test_avl_tree.c 
avl_tree.o:avl_tree.h avl_tree.c 
	$(CC) $(CFLAGS) -c avl_tree.c
.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)
