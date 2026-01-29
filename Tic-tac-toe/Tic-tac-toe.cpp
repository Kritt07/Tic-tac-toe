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

