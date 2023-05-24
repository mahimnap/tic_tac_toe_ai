#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

int main (int argc, char **argv){
	int vals[argc - 1];
	for (int i = 0; i < (argc - 1); i++){
		vals[i] = atoi (argv[i + 1]);
	} 
	/* int vals is the size of the number of use inputs (besides 
	 * the executable input) 
	 * for loop converts each number represented by a string into 
	 * an integer value
	 */
	init_boards(); 
	init_board(START_BOARD);
	join_graph(START_BOARD);
	compute_score();  
	/* setup entire hash table with all possible board combinations 
	 * and link the directed acylic graph through the move attribute 
	 * in every node
	 * This is essentially the main setup for the data structures 
	 * being worked with 
	 */
	for (int i = 0; i < (argc-1);i++){
		print_node(htable[vals[i]]);
	}
	//print out nodes for user entered hash value indexes in hash table
	return 0;
}
