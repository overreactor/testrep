// Program 24_2
// Game AI example - improved
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class connect4_board;
pair<int, int> get_best_move(int, connect4_board, int);            

class connect4_move {
private:
	int player;
	int column;

public:
	void set_move(int p, int c) {
		player = p;
		column = c;
	}
	void ask_move(int nextplayer) {
		player = nextplayer;
		cout << "Player " << nextplayer 
			<< ", which column do you want to place your piece in? ";
		cin >> column;
		column--; //Adjust to make first column be 0
	}
	int c() {
		return column;
	}
	int p() {
		return player;
	}
};

class connect4_board {
private:
	int rows;
	int columns;
	vector<vector<int> > board;

	bool check_vertical_winner(int player) {
		/* Check the board to see if that player has 4 consecutive vertical pieces */
		int i, j;
		for (i = 0; i < columns; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				if ((board[i][j] == player) && (board[i][j + 1] == player)
					&& (board[i][j + 2] == player) && (board[i][j + 3] == player)) {
					return true;
				}
			}
		}
		//Didn't find a winning combination
		return false;
	}

	int check_vertical_advantage() {
		/* Check the board to see if either player has 2 or 3 of 4 needed */
		int i, j, k;
		int advantage = 0;
		for (i = 0; i < columns; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				int count1 = 0;
				int count2 = 0;
				for (k = 0; k < 4; k++) {
					if (board[i][j + k] == 1) {
						count1++;
					}
					else if (board[i][j + k] == 2) {
						count2++;
					}
				}
				if ((count1 == 3) && (count2 == 0)) {
					advantage -= 100;
				}
				else if ((count1 == 0) && (count2 == 3)) {
					advantage += 100;
				}
				else if ((count1 == 2) && (count2 == 0)) {
					advantage -= 10;
				}
				else if ((count1 == 0) && (count2 == 2)) {
					advantage += 10;
				}
			}
		}
		return advantage;
	}

	bool check_horizontal_winner(int player) {
		/* Check the board to see if that player has 4 consecutive horizontal pieces */
		int i, j;
		//Can loop over all but last 3 rows, comparing 4 at a time
		for (i = 0; i < columns - 3; i++) {
			for (j = 0; j < rows; j++) {
				if ((board[i][j] == player) && (board[i + 1][j] == player) 
					&& (board[i + 2][j] == player) && (board[i + 3][j] == player)) {
					return true;
				}
			}
		}
		//Didn't find a winning combination
		return false;
	}

	int check_horizontal_advantage() {
		/* Check the board to see if either player has 2 or 3 of places needed */
		int i, j, k;
		int advantage = 0;
		//Can loop over all but last 3 rows, comparing 4 at a time
		for (i = 0; i < columns - 3; i++) {
			for (j = 0; j < rows; j++) {
				int count1 = 0;
				int count2 = 0;
				for (k = 0; k < 4; k++) {
					if (board[i + k][j] == 1) {
						count1++;
					}
					else if (board[i + k][j] == 2) {
						count2++;
					}
				}
				if ((count1 == 3) && (count2 == 0)) {
					advantage -= 100;
				}
				else if ((count1 == 0) && (count2 == 3)) {
					advantage += 100;
				}
				else if ((count1 == 2) && (count2 == 0)) {
					advantage -= 10;
				}
				else if ((count1 == 0) && (count2 == 2)) {
					advantage += 10;
				}
			}
		}
		return advantage;
	}

	bool check_increasing_diagonal_winner(int player) {
		/* Check the board to see if that player has 4 consecutive increasing 
		diagonal pieces */
		int i, j;
		//Can loop over all but first 3 rows, comparing 4 at a time
		for (i = 3; i < columns; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				if ((board[i][j] == player) && (board[i - 1][j + 1] == player)
					&& (board[i - 2][j + 2] == player) && (board[i - 3][j + 3] == player)) {
					return true;
				}
			}
		}
		//Didn't find a winning combination
		return false;
	}

	int check_increasing_diagonal_advantage() {
		/* Check the board to see if that player has 4 consecutive increasing 
		diagonal pieces */
		int i, j, k;
		int advantage = 0;
		//Can loop over all but first 3 rows, comparing 4 at a time
		for (i = 3; i < columns; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				int count1 = 0;
				int count2 = 0;
				for (k = 0; k < 4; k++) {
					if (board[i - k][j + k] == 1) {
						count1++;
					}
					else if (board[i - k][j + k] == 2) {
						count2++;
					}
				}
				if ((count1 == 3) && (count2 == 0)) {
					advantage -= 100;
				}
				else if ((count1 == 0) && (count2 == 3)) {
					advantage += 100;
				}
				else if ((count1 == 2) && (count2 == 0)) {
					advantage -= 10;
				}
				else if ((count1 == 0) && (count2 == 2)) {
					advantage += 10;
				}
			}
		}
		return advantage;
	}

	bool check_decreasing_diagonal_winner(int player) {
		/* Check the board to see if that player has 4 consecutive decreasing 
		diagonal pieces */
		int i, j;
		//Can loop over all but last 3 rows, comparing 4 at a time
		for (i = 0; i < columns - 3; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				if ((board[i][j] == player) && (board[i + 1][j + 1] == player) 
					&& (board[i + 2][j + 2] == player) && (board[i + 3][j + 3] == player)) {
					return true;
				}
			}
		}
		//Didn't find a winning combination
		return false;
	}

	int check_decreasing_diagonal_advantage() {
		/* Check the board to see if a player has 2 or 3 of needed places */
		int i, j, k;
		int advantage = 0;
		//Can loop over all but last 3 rows, comparing 4 at a time
		for (i = 0; i < columns - 3; i++) {
			//Can loop over all but last 3 rows, comparing 4 at a time
			for (j = 0; j < rows - 3; j++) {
				int count1 = 0;
				int count2 = 0;
				for (k = 0; k < 4; k++) {
					if (board[i + k][j + k] == 1) {
						count1++;
					}
					else if (board[i + k][j + k] == 2) {
						count2++;
					}
				}
				if ((count1 == 3) && (count2 == 0)) {
					advantage -= 100;
				}
				else if ((count1 == 0) && (count2 == 3)) {
					advantage += 100;
				}
				else if ((count1 == 2) && (count2 == 0)) {
					advantage -= 10;
				}
				else if ((count1 == 0) && (count2 == 2)) {
					advantage += 10;
				}
			}
		}
		return advantage;
	}

	bool check_full_board() {
		/* Check the board to see if the board is full */
		//If all columns are full (first element is not 0), it is a full board.
		int i;
		for (i = 0; i < columns; i++) {
			if (board[i][0] == 0) {
				return false;
			}
		}
		// Never found an empty column, so must be full
		return true;
	}

public:
	connect4_board() {
		rows = 6;
		columns = 7;
		vector<int> col(rows, 0);
		board = vector<vector<int> >(columns, col);
	}
	connect4_board(int r, int c) {
		rows = r;
		columns = c;
		vector<int> col(rows, 0);
		board = vector<vector<int> >(columns, col);
	}

	void print_board() {
		int i, j;
		//Loop through rows first
		for (j = 0; j < rows; j++) {
			//Loop through columns next
			for (i = 0; i < columns; i++) {
				//Display that location
				if (board[i][j] == 0) {
					cout << ". "; //Empty Cell
				}
				else if (board[i][j] == 1) {
					cout << "1 "; //Player 1 has it
				}
				else {
					cout << "2 "; //Player 2 has it
				}
			}
			cout << endl;  // End of a row
		}
	}
	int check_winner() {
		/* Check the board to see if someone has won or if the board is full */
		if (check_vertical_winner(1) ||
			check_horizontal_winner(1) ||
			check_increasing_diagonal_winner(1) ||
			check_decreasing_diagonal_winner(1)) {
			return 1;
		}
		if (check_vertical_winner(2) ||
			check_horizontal_winner(2) ||
			check_increasing_diagonal_winner(2) ||
			check_decreasing_diagonal_winner(2)) {
			return 2;
		}
		//No winner, but if full board, it's a tie
		if (check_full_board()) {
			return 3;
		}
		//No winner, board not full, so game is not over
		return 0;
	}

	// Returns whether a column is full or not
	int isfullcol(int c) {
		return (board[c][0] != 0);
	}

	// Returns negative value for player 1 advantage, positive for player 2 advantage
	int get_board_score() {
		int winner = check_winner();
		if (winner == 1) return -1000;
		if (winner == 2) return 1000;
		if (winner == 3) return 0;
		// No one has won yet, so see who is "closer"
		int advantage = 0;
		advantage += check_vertical_advantage();
		advantage += check_horizontal_advantage();
		advantage += check_increasing_diagonal_advantage();
		advantage += check_decreasing_diagonal_advantage();
		advantage += rand() % 11 - 5;
		return advantage;
	}

	void take_turn(connect4_move m) {
		int last_empty = 0;
		int column = m.c();
		int player = m.p();
		while ((last_empty < rows) && (board[column][last_empty] == 0)) {
			last_empty++;
		}
		last_empty--;
		board[column][last_empty] = player;
	}
};

class game {
private:
	connect4_board board;
	connect4_move turn;
	int playerturn;
	int numturns;
	int computerplayer;

protected:
	//Return 1 if player 1 wins, 2 if player 2 wins, 3 if tie, 0 if game not over
	int check_winner() {
		return board.check_winner();
	}

	void take_turn() {
		board.print_board();
		if (playerturn == computerplayer) {
			pair<int, int> mv = get_best_move(playerturn, board, 6);
			turn.set_move(playerturn, mv.second);
			cout << "Computer Moves in Column " << mv.second + 1 << endl;
		}
		else {
			turn.ask_move(playerturn);
		}
		board.take_turn(turn);
	}

	void declare_winner() {
		int result = check_winner();
		board.print_board();
		cout << "The game ended after " << numturns << " turns." << endl;
		if (result == 1) {
			cout << "Player 1 wins!  Congratulations!" << endl;
		}
		else if (result == 2) {
			cout << "Player 2 wins!  Congratulations!" << endl;
		}
		else if (result == 3) {
			cout << "The game has ended in a tie." << endl;
		}
		else if (result == 0) {
			cout << "The game ended before it was completed." << endl;
		}
	}

public:
	game(connect4_board& b, connect4_move& m) {
		board = b;
		turn = m;
	}

	void start_game() {
		numturns = 0;
		playerturn = 1;
		cout << "Should the computer be player 1 or 2? ";
		cin >> computerplayer;
		while (check_winner() == 0) {
			take_turn();
			if (playerturn == 1) {
				playerturn = 2;
			}
			else {
				playerturn = 1;
			}
			numturns++;
		}
		declare_winner();
	}
};

pair<int, int> get_best_move(int player_to_move, connect4_board b, int depthtogo) {
	int i;
	// Make list of moves
	vector<pair<int, int> > possible_moves;
	for (i = 0; i < 7; i++) {
		if (!b.isfullcol(i)) {
			// This is a possible move
			possible_moves.push_back(make_pair(0, i));
		}
	}
	// Evaluate each move
	for (auto& m : possible_moves) {
		connect4_board newboard = b;
		connect4_move nextmove;
		pair<int, int> mv;
		nextmove.set_move(player_to_move, m.second);
		newboard.take_turn(nextmove);
		if ((depthtogo == 0) || (newboard.check_winner())) {
			// Don't look ahead any more - just see how good this board is by itself
			m.first = newboard.get_board_score();
		}
		else {
			// Look ahead another level
			mv = get_best_move(3 - player_to_move, newboard, depthtogo - 1);
			m.first = mv.first;
		}
	}
	// Select best move
	sort(possible_moves.begin(), possible_moves.end());
	if (player_to_move == 1) {
		// Player 1's move, so want smallest value
		return possible_moves[0];
	}
	else {
		// Player 2's move, so largest score is best
		return possible_moves[possible_moves.size() - 1];
	}
}

int main() {
	connect4_move m;
	connect4_board b;
	game g(b, m);                           
	g.start_game();    
}