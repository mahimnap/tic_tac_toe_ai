CC = gcc 
CFLAGS = -std=c99 -Wall -pedantic

all: ttt1.o ttt2.o show_node count_nodes alphatoe

clean: 
	rm *.o show_node count_nodes alphatoe

alphatoe: alphatoe.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) ttt1.o ttt2.o alphatoe.o -o alphatoe 
	
show_node: show_node.o ttt1.o ttt2.o 
	$(CC) $(CFLAGS) ttt1.o ttt2.o show_node.o -o show_node

count_nodes: count_nodes.o ttt1.o ttt2.o 
	$(CC) $(CFLAGS) ttt1.o ttt2.o count_nodes.o -o count_nodes

ttt1.o: ttt.h ttt1.c
	$(CC) $(CFLAGS) -c ttt1.c -o ttt1.o
	
ttt2.o: ttt.h ttt2.c 
	$(CC) $(CFLAGS) -c ttt2.c -o ttt2.o 
	
alphatoe.o: ttt.h alphatoe.c
	$(CC) $(CFLAGS) -c alphatoe.c -o alphatoe.o

show_node.o: ttt.h show_node.c 
	$(CC) $(CFLAGS) -c show_node.c -o show_node.o

count_nodes.o: ttt.h count_nodes.c 
	$(CC) $(CFLAGS) -c count_nodes.c -o count_nodes.o
