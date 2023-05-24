#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

int main (int argc, char **argv){
	int cnt = 0; 
	init_boards(); 
	init_board(START_BOARD); 
	join_graph(START_BOARD); 
	/*setup data structure for direct acylic graph connecting all nodes
	 * and setup all the nodes in the hash table showing all possible
	 * board positions
	 */
	for (int i = 0; i < HSIZE; i++){
		if (htable[i].init == 1){
			cnt++; 
		}
	}
	//count every possible board (init == 1) in the hash table
	printf ("Number of Possible Boards: %d\n", cnt); 
}
