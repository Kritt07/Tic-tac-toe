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
void displayBoard(const vector<char>* board);
// определяет победителя
char winner(const vector<char>* board);
// проверяет, является ли ход допустимым
bool isLegal(int move, const vector<char>* board);
// ход пользователя
int humanMove(const vector<char>* board, char human);
// ход компьютера
int computerMove(const vector<char>* board, char computer);
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
    displayBoard(&board);  // Передаём указатель

    while (winner(&board) == NO_ONE) {
        if (turn == human) {
            move = humanMove(&board, human);
            board[move] = human;
        }
        else {
            move = computerMove(&board, computer);
            board[move] = computer;
        }
        displayBoard(&board);
        turn = opponent(turn);
    }

    announceWinner(winner(&board), computer, human);
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
	cout << question << " (y/n): ";
	cin >> responce;
	while (responce != 'y' && responce != 'n') {
		cout << question << " (y/n): ";
		cin >> responce;
	}
	return responce;
}

int askNumber(string question, int high, int low) {
	int number;
	cout << question << " (" << low << " - " << high << "): ";
	cin >> number;
	while (number < low || number > high) {
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

void displayBoard(const vector<char>* board) {
    cout << "\n\t" << (*board)[0] << " | " << (*board)[1] << " | " << (*board)[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[3] << " | " << (*board)[4] << " | " << (*board)[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[6] << " | " << (*board)[7] << " | " << (*board)[8];
    cout << "\n\n";
}

char winner(const vector<char>* board) {
    const int WINNING_ROWS[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& row : WINNING_ROWS) {
        if ((*board)[row[0]] != EMPTY &&
            (*board)[row[0]] == (*board)[row[1]] &&
            (*board)[row[1]] == (*board)[row[2]]) {
            return (*board)[row[0]];
        }
    }

    if (count(board->begin(), board->end(), EMPTY) == 0)
        return TIE;

    return NO_ONE;
}

bool isLegal(int move, const vector<char>* board) {
    return ((*board)[move] == EMPTY);
}

int humanMove(const vector<char>* board, char human) {
    int move = askNumber("Where will you move?", (board->size() - 1));
    while (!isLegal(move, board)) {
        cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber("Where will you move?", (board->size() - 1));
    }
    cout << "Fine...\n";
    return move;
}

int computerMove(const vector<char>* originalBoard, char computer) {
    // Создаём локальную копию для симуляций
    vector<char> board = *originalBoard;

    // Теперь работаем с board — это копия, оригинал не тронут
    unsigned int move = 0;
    bool found = false;

    // 1. Попытка победить
    while (!found && move < board.size()) {
        if (board[move] == EMPTY) {
            board[move] = computer;
            found = (winner(&board) == computer); // ← передаём указатель на КОПИЮ
            board[move] = EMPTY; // откат
        }
        if (!found) ++move;
    }

    // 2. Блокировка
    if (!found) {
        move = 0;
        char human = opponent(computer);
        while (!found && move < board.size()) {
            if (board[move] == EMPTY) {
                board[move] = human;
                found = (winner(&board) == human);
                board[move] = EMPTY;
            }
            if (!found) ++move;
        }
    }

    // 3. Лучший ход
    if (!found) {
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
        for (int i = 0; i < 9 && !found; ++i) {
            move = BEST_MOVES[i];
            if (board[move] == EMPTY) {
                found = true;
            }
        }
    }

    cout << "I shall take square number " << move << endl;
    return move; // возвращаем номер хода, НЕ изменяя оригинал
}

void announceWinner(char winner, char computer, char human) {
	if (winner == human)
		cout << "You win! Congratulations!" << endl;
	else if (winner == computer)
		cout << "Computer wins! Better luck next time." << endl;
	else
		cout << "It's a tie!" << endl;
}