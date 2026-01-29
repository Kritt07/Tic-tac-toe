#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';

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
void displayBoard(const vector<string>& board);
// определяет победителя, возвращает одну из констант
char winner(const vector<string>& board);
// определяет, правильно ли сделан ход
char islegal(const vector<string>& board, int move);
// ход пользователя
int humanMove(const vector<string>& board, char human);
// ход компьтера
int computerMove(const vector<string>& board, char computer);
// оглашает результаты
void announceWinner(char winner, char computer, char human);
