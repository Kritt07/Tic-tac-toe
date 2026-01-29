#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';
const char EMPTY = ' ';

// показ инструкций
void instructions();
// задает вопрос да\нет, возвращает символ y или n
char askYesNo(string question);
// запрашивает число из диапазона чисел поля
int askNumber(string question, int high, int low = 0);
// определяет какими фигурами будет играть игрок, возвращает Y / N
char humanPiece();
// дает компьютеру оставшуюся фигуру
char opponent(char piece);
// отображает поле
void displayBoard(const vector<char>& board);
// определяет победителя, возвращает одну из констант
char winner(const vector<char>& board);
// определяет, правильно ли сделан ход
char islegal(const vector<char>& board, int move);
// ход пользователя
int humanMove(const vector<char>& board, char human);
// ход компьтера
int computerMove(const vector<char>& board, char computer);
// оглашает результаты
void announceWinner(char winner, char computer, char human);

int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);
	while (winner(board) == NO_ONE) {
		if (turn == human) {
			move = humanMove(board, human);
			board[move] = human;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	return 0;
}

void instructions() {
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe." << endl;
	cout << "--where human brain is pit against silicon processor\n" << endl;
	cout << "Make your move known by entering a number, 0 - 8. The number" << endl;
	cout << "correspondent to the desired board position as illustrated:\n" << endl;
	cout << " 0 | 1 | 2" << endl;
	cout << " ---------" << endl;
	cout << " 3 | 4 | 5" << endl;
	cout << " ---------" << endl;
	cout << " 6 | 7 | 8\n" << endl;
	cout << "Prepare yourself, human. The battle is about to begin.\n" << endl;
}

char askYesNo(string question) {
	char responce;
	while (responce != 'y' || responce != 'n') {
		cout << question << " (y/n): ";
		cin >> responce;
	}
	return responce;
}

int askNumber(string question, int high, int low) {
	int number;
	while (number > high || number < low) {
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	}
	return number;
}

char humanPiece() {
	char go_first = askYesNo("Do you want to do first move?");
	if (go_first == 'y') {
		cout << "\nThen take the first move. You will need it." << endl;
		return X;
	}
	else {
		cout << "\nYour bravery will be your undoing... I will go first." << endl;
		return O;
	}
}

char opponent(char piece) {
	return piece == X ? O : X;
}