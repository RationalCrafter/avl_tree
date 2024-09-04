CC = gcc 
CFLAGS = -Wall -g -O0
TARGET = test_avl
OBJS = test_avl_tree.o avl_tree.o array_stack.o
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
test_avl_tree.o: test_avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c test_avl_tree.c 
avl_tree.o:avl_tree.h avl_tree.c 
	$(CC) $(CFLAGS) -c avl_tree.c
array_stack.o: array_stack/array_stack.c array_stack/array_stack.h
	$(CC) $(CFLAGS) -c array_stack/array_stack.c
.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)
