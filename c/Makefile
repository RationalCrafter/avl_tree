CC = gcc 
CFLAGS = -Wall -O3
LDLIBS = -lc
TARGET = test_avl
TARGET_NODE = test_node
OBJS_NODE= avl_tree.o array_stack.o test_node.o
OBJS = test_avl_tree.o avl_tree.o array_stack.o
all:$(TARGET) $(TARGET_NODE)
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
$(TARGET_NODE):$(OBJS_NODE)
	$(CC) $(CFLAGS) $(LDLIBS) -o $(TARGET_NODE) $(OBJS_NODE) 
test_node.o: avl_tree.c avl_tree.h test_node.c
	$(CC) $(CFLAGS) -c test_node.c
test_avl_tree.o: test_avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c test_avl_tree.c 
avl_tree.o:avl_tree.h avl_tree.c 
	$(CC) $(CFLAGS) -c avl_tree.c
array_stack.o: array_stack/array_stack.c array_stack/array_stack.h
	$(CC) $(CFLAGS) -c array_stack/array_stack.c
.PHONY: clean
clean:
	rm $(TARGET) $(TARGET_NODE) $(OBJS) test_node.o 
