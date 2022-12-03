#include <iostream>
#include <string>

using namespace std;

bool CheckWinner(string field[3][3], string playersign) {
	//horizontal winning
	if (field[0][0] == playersign && field[0][1] == playersign && field[0][2] == playersign) {
		return false;
	}
	else if (field[1][0] == playersign && field[1][1] == playersign && field[1][2] == playersign) {
		return false;
	}
	else if (field[2][0] == playersign && field[2][1] == playersign && field[2][2] == playersign) {
		return false;

	}

	//vertical winning
	else if (field[0][0] == playersign && field[1][0] == playersign && field[2][0] == playersign) {
		return false;
	}
	else if (field[0][1] == playersign && field[1][1] == playersign && field[2][1] == playersign) {
		return false;
	}
	else if (field[0][2] == playersign && field[1][2] == playersign && field[2][2] == playersign) {
		return false;
	}

	//diagonal winning
	else if (field[0][0] == playersign && field[1][1] == playersign && field[2][2] == playersign) {
		return false;
	}
	else if (field[0][2] == playersign && field[1][1] == playersign && field[2][0] == playersign) {
		return false;
	}

	//draw
	else {
		return true;
	}
}

bool CheckFormat(string move) {
	if (move.find("-") != string::npos) {
		int minus = move.find("-");
		if (move.find("-", minus + 1) == string::npos) {
			if (minus != 0 && minus != move.length() - 1) {
				int first = stoi(move.substr(0, minus));
				int sec = stoi(move.substr(minus + 1));
				if (first && sec) {
					if (first > 0 && sec > 0) {
						if (first <= 3 && sec <= 3) {
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void print(string field[3][3]) {
	cout << "Board: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (field[i][j] == "") {
				field[i][j] = " ";
			}
			if (j != 2) {
				cout << " " << field[i][j] << " |";
			}
			else {
				cout << " " << field[i][j] << endl;
			}
		}
		if (i != 2) {
			cout << "-----------" << endl;
		}
	}
}

void PlayerMove(string playername, string playersign, string field[3][3]) {
	string move;
	string nonprint = "";
	cout << playername << ", make your move: ";
	cin >> move;
	bool loop = true;
	while (loop) {
		//giving correct move format
		if (CheckFormat(move)) {
			//finding location of minus and the values of row and col
			int minus = move.find("-");
			int row = stoi(move.substr(0, minus));
			int col = stoi(move.substr(minus + 1));
			//implying move 
			//if location is empty
			if (field[row - 1][col - 1] == " ") {
				field[row - 1][col - 1] =  playersign ;
				loop = false;
				nonprint = "yes";
			}

			//if cell is full
			else if (field[row - 1][col - 1] == "X" || field[row - 1][col - 1] == "O") {
				cout << "That cell is  full!" << endl;
				cout << playername << ", make your move: ";
				cin >> move;
				nonprint = "no";
			}
			//no winners
			if (CheckWinner(field, playersign)) {
				//no draw
				int count = 0;
				int onetime = 0;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (field[i][j] == "X" || field[i][j] == "O") {
							count++;
						}
					}
				}
				//if not all cells are full, so count != 9
				if (count != 9) {
					if (nonprint == "yes") {
						print(field);
					}

				}
			}
		}
		//proper message
		else {
			cout << "Incorrect move format!" << endl;
			cout << playername << ", make your move: ";
			cin >> move;
		}
	}
}

void PlayGame(string p1name, string p1sign, string p2name, string p2sign, int& p1scr, int& p2scr) {
	string field[3][3];
	cout << "Game is initializing..." << endl;
	print(field);
	bool game = true;
	int count = 2;
	while (game) {
		if (count % 2 == 0) {
			PlayerMove(p1name, p1sign, field);
			count++;
		}
		else {
			PlayerMove(p2name, p2sign, field);
			count++;
		}
		//player1 wins
		if (!CheckWinner(field, p1sign)) {
			cout << p1name << " won!";
			game = false;
			p1scr++;
		}

		//player 2 wins
		else if (!CheckWinner(field, p2sign)) {
			cout << p2name << " won!";
			game = false;
			p2scr++;
		}

		//draw
		else if (CheckWinner(field, p1sign) || CheckWinner(field, p2sign)) {
			int count = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (field[i][j] == "X" || field[i][j] == "O") {
						count++;
					}
					if (count == 9) {
						if (p1sign == "X") {
							cout << "Draw!";
							game = false;
						}
						else if (p1sign == "O") {
							cout << "Draw!";
							game = false;
						}
					}
				}
			}
		}
	}
}

int main() {
	string p1name, p2name;
	int p1scr = 0, p2scr = 0;
	cout << "Welcome to X O X!" << endl;
	cout << "Player 1, enter your name: ";
	cin >> p1name;
	cout << "Welcome to game " << p1name << ". Your sign is X" << endl;
	cout << "Player 2, enter your name: ";
	cin >> p2name;
	cout << "Welcome to game" << p2name << ". Your sign is O" << endl << endl;
	PlayGame(p1name, "X", p2name, "O", p1scr, p2scr);
	cout << endl << "Scores: " << endl << p1name << ": " << p1scr << "   " << p2name << ": " << p2scr << endl << endl;
	int p1scr_2, p2scr_2;
	p2scr_2 = p1scr;
	p1scr_2 = p2scr;
	cout << "Signs are switched." << endl;
	PlayGame(p2name, "O", p1name, "X", p1scr_2, p2scr_2);
	cout << endl << "Scores: " << endl << p1name << ": " << p2scr_2 << "   " << p2name << ": " << p1scr_2;
	cout << endl << endl << "Final Scores: " << endl << p1name << ": " << p2scr_2 << "   " << p2name << ": " << p1scr_2 << endl;
	if (p2scr_2 > p1scr_2) {
		cout << "overall winner is "<< p1name << endl;
	}
	else if (p2scr_2 < p1scr_2) {
		cout << "overall winner is " << p2name << endl;
	}
	else {
		cout << "Game Draw!";
	}
	return 0;
}
