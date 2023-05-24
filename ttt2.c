/*
 * Name: Mahimna Pyakuryal 
 * Class: 2520 
 * Assignment 7
 * mpyakury
 * 1014826
 */

#include "ttt.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void init_boards (){
	for (int i = 0; i < HSIZE; i++){ 
		htable[i].init = 0; 
	}
}
/* loop through all nodes in the hash table (HSIZE)
 * set each init attribute to 0 indicating currently that
 * it's not a valid playable board
 */

int depth (Board board){
	int cnt = 0; 
	for (int i = 0; i < 9; i++){
		if ((board[pos2idx[i]] == 'X') || (board[pos2idx[i]] == 'O')){
			cnt++; 
		}
	}
	return cnt; 
}
/* loop through every playable index (pos2idx) in the string board 
 * and count all the Xs and Os 
 */

char winner (Board board){
	for (int i = 0; i < 8; i++){
		if ((board[pos2idx[WINS[i][0]]] == 'X') 
		&& (board[pos2idx[WINS[i][1]]] == 'X')
		&& (board[pos2idx[WINS[i][2]]] == 'X')){
			return 'X';
		}
		if ((board[pos2idx[WINS[i][0]]] == 'O') 
		&& (board[pos2idx[WINS[i][1]]] == 'O')
		&& (board[pos2idx[WINS[i][2]]] == 'O')){
			return 'O';
		}
	}
	if (depth (board) == 9){ 
		return '-'; 
	} 
	else {
		return '?'; 
	}
}
/* loop through the array WINS (8 possible wins) 
 * check if either X or O at a given element in WINS matches 
 * all the indexes stored
 * if this is true then someone has won (X or O) else 
 * check if the board depth is at 9
 * here you know that no one has one and the board is full 
 * so this is a tie 
 * finally if the board is not full and no one has one, return ?
 * which indicates the game is still in progress
 */

char turn (Board board){
	if ((depth(board) == 9) ||
		(winner(board) == 'X') ||
		(winner(board) == 'O')){
		return '-'; 
	}
	else if (depth(board) % 2 == 0){
		return 'X';
	}
	else if (depth(board) %2 == 1){
		return 'O'; 
	}
	else {
		printf ("Error in turn function!\n"); 
		return '\0'; 
	}
}
/* if the board is full or there is a winner then no more turns 
 * can be played so return '-' indicating no more turns available
 * if the board is not full and no one has one then determine if it's
 * an even or odd turn. X always starts so X is even and O is odd
 * adding a return of NULL as default to indicate error has occurred
 * as function with a return requires a default return val to avoid 
 * warnings 
 */

void init_board( Board board ){
	int hashVal = board_hash(board); 
	htable[hashVal].init = 1; 
	htable[hashVal].turn = turn(board); 
	htable[hashVal].depth = depth(board); 
	strcpy(htable[hashVal].board, board); 
	htable[hashVal].winner = winner(board); 
}
/* compute the board hash value to setup the node in the hash table 
 * for the given board 
 * then set the init of this board to 1 indicating it's a valid
 * playable state of the board 
 * set the turn for the node using turn, set depth using depth, 
 * and set winner using winner
 * strcpy the board passed in to the board attribute (string) in the 
 * node
 */

void join_graph( Board board ){
	int hashVal = board_hash (board);
	int hashVal2; 
	Board temp; 
	for (int i = 0; i < 9; i++){
		if ((board[pos2idx[i]] == 'X') || (board[pos2idx[i]] == 'O')
			|| (turn(board) == '-')){
			htable[hashVal].move[i] = -1; 
		}
		else { 
			strcpy (temp, board); 
			temp[pos2idx[i]] = turn(board); 
			hashVal2 = board_hash (temp); 
			htable[hashVal].move[i] = hashVal2; 
			if (htable[hashVal2].init == 0){
				init_board(temp); 
				join_graph(temp);
			}
		}
	}
}
/* loop through all move positions in current board node 
 * if a given index on the board (board idx (pos2idx) = move idx) 
 * is already filled with an X, O, or there are no more turns
 * remaining (tie/win) then set the move value for that playable 
 * spot to -1 indicating nothing can be added here 
 * otherwise, copy the unchanged board into a temp variable 
 * then add X or O to the position depending on whose turn it is
 * then hash the value of the updated temp string 
 * if the hash value index node on the hash table is already init 
 * continue, if not init the board and call join_graph recursively 
 * this will set the move values for the new node (temp board) 
 * and thus continue up the graph until it sets all possible move 
 * values for every possible board node
 */

void compute_score(){
	for (int i = 9; i >= 0; i--){
		for (int j = 0; j < HSIZE; j++){
			if (htable[j].depth == i){
				if (htable[j].winner == 'X'){
					htable[j].score = 1; 
				}
				else if (htable[j].winner == 'O'){
					htable[j].score = -1; 
				}
				else if (htable[j].winner == '-'){
					htable[j].score = 0; 
				}
				else if (htable[j].turn == 'X'){
					int a,b; 
					int cnt = 0;
					for (int p = 0; p < 9; p++){
						if (htable[j].move[p] != -1){
							a = htable[htable[j].move[p]].score; 
							if (cnt == 0){
								b = a;
								cnt++;  
							}
							else if (a > b){
								b = a; 
							}
						}
					}
					htable[j].score = b; 
				}
				else if (htable[j].turn == 'O'){
					int a,b; 
					int cnt = 0;
					for (int p = 0; p < 9; p++){
						if (htable[j].move[p] != -1){
							a = htable[htable[j].move[p]].score; 
							if (cnt == 0){
								b = a;
								cnt++;  
							}
							else if (a < b){
								b = a; 
							}
						}
					}
					htable[j].score = b; 
				}
			}
		}
	}
}
/* loop through table all possible depth (max = 9 ie 9 moves played) 
 * then loop through entire hash table only accessing nodes with 
 * current depth being looked at 
 * if someone has won at the board node then score = 1(X) or -1 (O)
 * if someone tied then score is 0
 * if the turn is X and no one has one and tie hasn't occurred then
 * find the max score value in all the move hash indexes to see if 
 * X has the potential to win given they make the correct move (ie
 * select board position where the move index has the highest score 
 * (could also be the winning position) 
 * store the max value (potential) in the current node score value 
 * same logic for O except looking for min (O win = -1) 
 * cnt variable is used to set the first comparing value to the first
 * valid move value (ie not -1) and use that to continue to compare 
 * every element in move's node's score value
 */

int best_move( int board ){
	int cnt = 0; 
	int a,b; 
	int bestMove = -1;  
	for (int i = 0; i < 9; i++){ 
		if (htable[board].turn == 'X'){
			if (htable[board].move[i] != -1){
				a = htable[htable[board].move[i]].score; 
				if (htable[htable[board].move[i]].winner == 'X'){
					return i; 
				}
				else if (cnt == 0){
					b = a; 
					bestMove = i; 
					cnt++; 
				}
				else if (a > b){
					b = a; 
					bestMove = i; 
				}
			}
		}
		else if (htable[board].turn == 'O'){
			if (htable[board].move[i] != -1){
				a = htable[htable[board].move[i]].score; 
				if (htable[htable[board].move[i]].winner == 'O'){
					return i; 
				}
				else if (cnt == 0){
					b = a; 
					bestMove = i; 
					cnt++; 
				}
				else if (a < b){
					b = a; 
					bestMove = i; 
				}
			}			
		}
	}
	return bestMove;
}
/* loop through all move indexes 
 * if turn is X's then check if the current move being looped through
 * is valid (not -1)
 * if it's valid and the move being looped through would result in a 
 * win, return index of move for bestMove because if they make this move they win
 * otherwise, set that score value as the default 
 * then the loop will continue and check every score value (same 
 * logic as compute_score) to find the max score value
 * Same logic for O except checking for min rather than max  
 */

/* Note to self
 * the reason this isn't a tree structure but an directed acylic 
 * graph is because there are multiple ways to arive at a given 
 * child node (e.g. x 1 2, x o 2, x o x or 0 1 x, 0 o x, x o x result 
 * in the same end node ie x o x hash value index in the table)
 */
