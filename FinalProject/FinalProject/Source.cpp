#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <Windows.h>

using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main();

//winning and losing screens for when games end
//they take you back to the main menu
void winScreen() {
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << endl << "You win! ";
	main();
}

void loseScreen() {
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << endl << "You lose!";
	main();
}


//HANGMAN
//function that checks if entered char is in the word
vector<char> guessWord(char guess, vector<char>guessList, string correct, int& strikes, bool& win) {
	bool right = false;
	for (int i = 0; i < correct.length(); i++) {
		if (correct[i] == guess) {
			guessList[i] = guess; //add correctly guessed letters to vector
			right = true; //don't increase strikes if guess is correct
		}
	}
	if (!right) {
		strikes++; //increase strikes for wrong letters
	}
	if (!(find(guessList.begin(), guessList.end(), '_') != guessList.end())) win = true; //return win=true if all correct letters are guessed
	return guessList; //return list with correctly guessed letters

}

bool alpha(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (!(isalpha(word[i]))) return false;
	} return true;
}

void playHangman() { //NEED TO MAKE ALPHABETICAL ONLY
	cout << "  o         o                                                                               \n";
	cout << " <|>       <|>                                                                              \n";
	cout << " < >       < >                                                                              \n";
	cout << "  |         |      o__ __o/  \\o__ __o     o__ __o/  \\o__ __o__ __o      o__ __o/  \\o__ __o  \n";
	cout << "  o__/_ _\\__o     /v     |    |     |>   /v     |    |     |     |>    /v     |    |     |> \n";
	cout << "  |         |    />     / \\  / \\   / \\  />     / \\  / \\   / \\   / \\   />     / \\  / \\   / \\ \n";
	cout << " <o>       <o>   \\      \\o/  \\o/   \\o/  \\      \\o/  \\o/   \\o/   \\o/   \\      \\o/  \\o/   \\o/ \n";
	cout << "  |         |     o      |    |     |    o      |    |     |     |     o      |    |     |  \n";
	cout << " / \\       / \\    <\\__  / \\  / \\   / \\   <\\__  < >  / \\   / \\   / \\    <\\__  / \\  / \\   / \\ \n";
	cout << "                                                |                                           \n";
	cout << "                                        o__     o                                           \n";
	cout << "                                        <\\__ __/>                                           \n";

	while (true) {
		string word; //word to be guessed
		string guess; //letter being guessed
		bool win = false; //win status
		int strikes = 0; //5 strikes to lose
		vector<char> guessList; //blank list to be filled with letters


		cout << "\nWelcome to Hangman! Enter a word for your friend to guess: ";
		//cin >> word; //user chooses word
		cin.clear();
		cin.ignore();
		//getline(cin, word);
		cin >> word; //user chooses word
		if (!alpha(word)) {
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nWord must contain letters only\n";
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			continue;
		}
		for (int k = 0; k < 60; k++) {
			cout << endl; //empty lines to hide word from P2
		}
		for (int i = 0; i < word.length(); i++) { //make list of underscores for blank word
			guessList.push_back('_');
			cout << guessList[i] << " ";
		}
		cout << endl;
		while (true) {
			cout << "Strikes: " << strikes << endl;
			cout << "Guess a letter: ";

			//cin >> guess; //P2 guesses a letter
			cin >> guess;
			//if (guess.length() > 1) cout << "\nOnly one letter at a time\n";
			cout << endl;
			guessList = guessWord(guess[0], guessList, word, strikes, win); //return blank word with filled letters
			for (int j = 0; j < word.length(); j++) {
				cout << guessList[j] << " "; //display current word status
			} cout << endl;

			//if game ends
			if (win) {
				winScreen();
			}
			else if (strikes >= 5) {
				cout << "The word was: " << word;
				loseScreen();
			}

		}
	}
}

//BLACKJACK

void showHand(vector<int> playerHand) {
	for (int i = 0; i < playerHand.size(); i++) {
		if (i != playerHand.size() - 1) cout << playerHand[i] << ", ";
		else cout << playerHand[i] << endl;
	}
}

void drawCard(vector<int> &playerHand, vector<int> &cpuHand, int repeat, int &total, int &cpuTotal) {
	random_device rd;
	for (int i = 0; i < repeat; i++) {
		playerHand.push_back(rd() % 10 + 1);
		total += playerHand[playerHand.size()-1];
		cpuHand.push_back(rd() % 10 + 1);
		cpuTotal += cpuHand[cpuHand.size()-1];
	}
}

void playBlackjack() {
	//declare variables
	int cardChoice = -1;
	int total = 0;
	int cpuTotal = 0;
	random_device rd;
	vector<int> userCards;
	vector<int> cpuCards;
	//fill user and cpu hands with 2 cards each
	drawCard(userCards, cpuCards, 2, total, cpuTotal);
	cout << ".------..------..------..------..------..------..------..------..------. \n";
	cout << "|B.--. ||L.--. ||A.--. ||C.--. ||K.--. ||J.--. ||A.--. ||C.--. ||K.--. |\n";
	cout << "| :(): || ://\: || (\//) || ://\: || ://\: || :(): || (\//) || ://\: || ://\: |\n";
	cout << "| ()() || (__) || :\//: || :\//: || :\//: || ()() || :\//: || :\//: || :\//: |\n";
	cout << "| '--'B|| '--'L|| '--'A|| '--'C|| '--'K|| '--'J|| '--'A|| '--'C|| '--'K|\n";
	cout << "`------'`------'`------'`------'`------'`------'`------'`------'`------'\n";
	cout << "\nWelcome to Blackjack! \n" << endl;
	while (true) {

		cout << "\nThis is your hand:" << endl;
		showHand(userCards);
		cout << "Your Total: " << total << endl;
		//end game if someone's total > 21
		if (total > 21) {
			loseScreen();
		}

		else if (cpuTotal > 21) {
			cout << "This is the CPU's hand: " << endl;
			showHand(cpuCards);
			cout << "CPU's total: " << cpuTotal << endl << endl;
			winScreen();
		}

		//let user decide what they want to do
		cout << "What do you want to do?" << endl;
		cout << endl << "1. Draw a card (random value between 1 and 10)" << endl;
		cout << "2. Stand and see if you beat the CPU" << endl;
		cin >> cardChoice;
		if (cin.fail() || (cardChoice != 1 && cardChoice != 2)){
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nINVALID INPUT \n";
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.clear();
			cin.ignore();
			continue;
		}
		//user and cpu draw a card each
		if (cardChoice == 1) drawCard(userCards, cpuCards, 1, total, cpuTotal);
		//end game and show hands
		if (cardChoice == 2) {
			cout << endl << "This is your hand:" << endl;
			showHand(userCards);
			cout << "Your total: " << total << endl << endl;
			cout << "This is the CPU's hand: " << endl;
			showHand(cpuCards);
			cout << "CPU's total: " << cpuTotal << endl << endl;
			if (total > cpuTotal) winScreen();
			else loseScreen();
		}
	}

	

}

//NUMBER GUESSER
void playNumberGuesser() {
	//declare variables
	random_device rd;
	int range;
	int strikes = 0;
	int number;
	int guess;
	cout << " _   _                 _                 _____                               \n";
	cout << "| \\ | |               | |               |  __ \\                              \n";
	cout << "|  \\| |_   _ _ __ ___ | |__   ___ _ __  | |  \\/_   _  ___  ___ ___  ___ _ __ \n";
	cout << "| . ` | | | | '_ ` _ \\| '_ \\ / _ \\ '__| | | __| | | |/ _ \\/ __/ __|/ _ \\ '__|\n";
	cout << "| |\\  | |_| | | | | | | |_) |  __/ |    | |_\\ \\ |_| |  __/\\__ \\__ \\  __/ |   \n";
	cout << "\\_| \\_/\\__,_|_| |_| |_|_.__/ \\___|_|     \\____/\\__,_|\\___||___/___/\\___|_|   \n";
	cout << "                                                                             \n";
	cout << "                                                                             \n";
	cout << "Welcome to Number Guesser!" << endl;
	while (true) {
		//max number value chosen by player
		cout << "Enter maximum number value: ";
		cin >> range;
		//make sure input is a positive integer
		if (cin.fail() || (range <= 0)) {
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nINVALID INPUT\n";
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.clear();
			cin.ignore();
			continue;
		}
		number = rd() % range + 1;
		while (true) {
			cout << "Guess the CPU's number: ";
			cin >> guess;
			//make sure guess is a postitive integer
			if (cin.fail() || (guess <= 0)) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "\nINVALID INPUT\n";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cin.clear();
				cin.ignore();
				continue;
			}
			
			//end game if user guesses correctly
			if (guess == number) winScreen();
			//tell user if they are too high or too low
			if (guess > number) {
				cout << "Too high!\n"; 
				strikes++;
			}
			if (guess < number) {
				cout << "Too low!\n"; 
				strikes++;
			}
			cout << "Strikes:" << strikes << "/5" << endl;
			if (strikes >= 5) loseScreen();
		}
	}
}

//ROCK PAPER SCISSORS
void playRPS() {
	cout << " ____ _____ ___ _  _    ____  __   ____ ____ ____    ___  ___ ____ ___ ___ _____ ____ ___  \n";
	cout << "(  _ (  _  / __( )/ )  (  _ \\/__\\ (  _ ( ___(  _ \\  / __)/ __(_  _/ __/ __(  _  (  _ / __) \n";
	cout << " )   /)(_)( (__ )  (    )___/(__)\\ )___/)__) )   /  \\__ ( (__ _)(_\\__ \\__ \\)(_)( )   \\__ \\ \n";
	cout << "(_)\\_(_____\\___(_)\\_)  (__)(__)(__(__) (____(_)\\_)  (___/\\___(____(___(___(_____(_)\\_(___/ \n";
	cout << "\nWelcome to Rock, Paper, Scissors. Enter 'rock', 'paper', or 'scissors' and see if you can win against the computer" << endl;
	cout << "End the game at any time by typing 'quit'" << endl;
	//declare variables
	string userInput = "";
	int userNumber = -1;
	random_device rd;
	string compChoice = "";
	cin.clear();
	cin.ignore();

	while (true) {
		//user chooses rock, paper or scissors
		cout << "\n" << "Enter rock, paper or scissors" << endl;
		//getline(cin, userInput);
		cin >> userInput;
		//make sure input is valid
		if (!(userInput == "rock" || userInput == "paper" || userInput == "scissors" || userInput == "quit")) {
			userInput = "";
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Invalid input" << endl;
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.clear();
			cin.ignore();
			continue;
		}
		//go to main if user quits
		if (userInput == "quit") {
			system("CLS");
			main();
		}

		int compInt = rd() % 3;
		// rock = 0
		// paper = 1
		// scissors = 2
		if (compInt == 0) compChoice = "rock";
		if (compInt == 1) compChoice = "paper";
		if (compInt == 2) compChoice = "scissors";

		cout << "You chose: " << userInput << endl;
		cout << "The computer chose: " << compChoice << endl;
		//check if user wins, loses or ties
		if (userInput == compChoice) cout << "You tied!\n" << endl;
		else {
			if (userInput == "rock") {
				if (compChoice == "paper") cout << "You lose!\n" << endl;
				else cout << "You win!\n" << endl;
			}
			else if (userInput == "paper") {
				if (compChoice == "scissors") cout << "You lose!\n" << endl;
				else cout << "You win!\n" << endl;
			}
			else {
				if (compChoice == "rock") cout << "You lose!\n" << endl;
				else cout << "You win!\n" << endl;
			}
		}
	}
}


//TIC TAC TOE
bool canSquareReplace(vector<vector<char>> &board, int square) {
	if ((square > 0 && square <= 3) && (board[0][square - 1] != 'X' && board[0][square - 1] != 'O')) return true;
	else if ((square > 3 && square <= 6) && (board[1][square - 4] != 'X' && board[1][square - 4] != 'O')) return true;
	else if ((square > 6 && square <= 9) && (board[2][square - 7] != 'X' && board[2][square - 7] != 'O')) return true;
	return false;
}


void squareReplace(char letter, vector<vector<char>> &board, int square) {
	if (letter == 'X') {
		if (square <= 3) board[0][square - 1] = 'X';
		else if (square <= 6) board[1][square - 4] = 'X';
		else board[2][square - 7] = 'X';
	}
	else {
		if (square <= 3) board[0][square - 1] = 'O';
		else if (square <= 6) board[1][square - 4] = 'O';
		else board[2][square - 7] = 'O';
	}
}

bool inARow(char letter, vector<vector<char>> board) {
	//check horizontally 
	if ((board[0][0] == board[0][1]) && (board[0][0] == board[0][2]) && (board[0][0] == letter)) return true;
	if ((board[1][0] == board[1][1]) && (board[1][0] == board[1][2]) && (board[1][0] == letter)) return true;
	if ((board[2][0] == board[2][1]) && (board[2][0] == board[2][2]) && (board[2][0] == letter)) return true;
	//check vertically
	if((board[0][0] == board[1][0]) && (board[0][0] == board[2][0]) && (board[0][0] == letter)) return true;
	if((board[0][1] == board[1][1]) && (board[0][1] == board[2][1]) && (board[0][1] == letter)) return true;
	if((board[0][2] == board[1][2]) && (board[0][2] == board[2][2]) && (board[0][2] == letter)) return true;
	//check diagonally
	if ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] == letter)) return true;
	if ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] == letter)) return true;
	//return false if no win
	return false;


}

bool boardFull(vector<vector<char>> board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(board[i][j] == 'X' || board[i][j] == 'O')) return false;
		}
	} return true;
}

void drawBoard(vector<vector<char>> board) {
	cout << "  ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[0][0];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[0][1];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[0][2];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "  \n";
	cout << "=============\n";
	cout << "  ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[1][0];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[1][1];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[1][2];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "  \n";
	cout << "=============\n";
	cout << "  ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[2][0];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[2][1];
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << " | ";
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << board[2][2];
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "  \n";

}

void playTicTacToe() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl;
	cout << "  _______ _        _______           _______          \n";
	cout << " |__   __(_)      |__   __|         |__   __|         \n";
	cout << "    | |   _  ___     | | __ _  ___     | | ___   ___  \n";
	cout << "    | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n";
	cout << "    | |  | | (__     | | (_| | (__     | | (_) |  __/ \n";
	cout << "    |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___|  \n";
	cout << "                                                      \n";
	bool p1 = true;
	bool p2 = false;
	int p1choice;
	int p2choice;
	vector<vector<char>> board = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
	cout << "Welcome to Tic Tac Toe!\n";
	while (true) {
		drawBoard(board);
		if(inARow('X', board)) {
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\nPlayer 1 wins!";
			main();
		}
		if (inARow('O', board)) {
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\nPlayer 2 wins!";
			main();
		}
		if (boardFull(board)) {
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\nIt's a tie!";
			main();
		}
		if (p1) {
			p1 = false;
			p2 = true;
			cout << "\nPlayer 1 (X), choose your square: ";
			cin >> p1choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
			}
			if(canSquareReplace(board, p1choice)) squareReplace('X', board, p1choice);
			else {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "Invalid square";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				p1 = true;
				p2 = false;
			}
		}

		else if (p2) {
			p1 = true;
			p2 = false;
			cout << "\nPlayer 2 (O), choose your square: ";
			cin >> p2choice;
			cin.clear();
			cin.ignore();
			if(canSquareReplace(board, p2choice)) squareReplace('O', board, p2choice);
			else {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "Invalid square";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				p1 = false;
				p2 = true;
			}
		}
	}
}

//WORD SHUFFLE

vector<char> shuffleArray(string correct) {
	//add chars to vector and shuffle them
	vector<char> shuffled;
	random_device rd;
	for (int i = 0; i < correct.length(); i++) {
		shuffled.push_back(correct[i]);
	}
	for (int j = 0; j < correct.length(); j++) {
		int r = rd() % correct.length();
		char temp = shuffled[j];
		shuffled[j] = shuffled[r];
		shuffled[r] = temp;
	}

	return shuffled;
}

void playWordShuffle() {
	//declare variables
	string correct;
	vector<char> shuffled;
	string guess;
	string check;
	int strikes = 0;
	cout << "                U  ___ u   ____     ____         ____     _   _    _   _   _____   _____    _     U _____ u  \n";
	cout << " __        __    \\/ _ \\/U |  _ \\ u |  _ \\       / __ | u |'| |'|U | |u| | |  ___| |  ___|  | |    \\| ___ |/  \n";
	cout << " \\ \\      / /    | | | | \\| |_) |//| | | |     <\\___ \\/ /| |_| |\\\\| |\\| |U| |_  uU| |_  uU | | u   |  _|     \n";
	cout << " /\\ \\ /\\ / /\\.-,_| |_| |  |  _ <  U| |_| |\\     u___) | U|  _  |u | |_| |\\|  _|/ \\|  _|/  \\| |/__  | |___    \n";
	cout << "U  \\ V  V /  U\\_)-\\___/   |_| \\_\\  |____/ u     |____/>> |_| |_| <<\\___/  |_|     |_|      |_____| |_____|   \n";
	cout << ".-,_\\ /\\ /_,-.     \\\\     //   \\\\_  |||_         )(  (__)//   \\\\(__) )(   )(\\\\,-  )(\\\\,-   //  \\\\  <<   >>   \n";
	cout << " \\_)-'  '-(_/     (__)   (__)  (__)(__)_)       (__)    (_ ) ( _)   (__) (__)(_/ (__)(_/  (_ )( _)(__) (__)  \n";
	cout << "\nWelcome to Word Shuffle!" << endl;
	//player 1 chooses word
	cout << "Enter a word for player 2 to unscramble: ";
	cin.clear();
	cin.ignore();
	getline(cin, correct);
	//shuffle vector
	cout << "Shuffling..." << endl;
	shuffled = shuffleArray(correct);
	//make sure shuffled word != original word
	for (int h = 0; h < correct.length(); h++) {
		check += shuffled[h];
	}
	if (check == correct) {
		check = "";
		shuffled = shuffleArray(correct);
	}

	//skip lines so player 2 can't see original word
	for (int q = 0; q < 60; q++) {
		cout << endl;
	}
	//player 2 guesses word
	while (true) {
		cout << "Shuffled word is: ";
		for (int i = 0; i < correct.length(); i++) {
			cout << shuffled[i];
		}
		cout << endl << "Strikes: " << strikes << "/5" << endl;
		cout << "\nWhat is your guess?" << endl;
		getline(cin, guess);
		//win game if player 2 guesses correctly
		if (guess == correct) {
			winScreen();
		}
		//add strike if incorrect guess
		else {
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Incorrect guess\n" << endl;
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			strikes++;
		}
		//lose game at 5 strikes
		if (strikes >= 5) {
			cout << "The word was: " << correct << endl;
			loseScreen();
		}
	}

}

//MASTERMIND

int correctPlace(vector<int> correct, vector<int> guess) {
	int c_p = 0;
	for (int i = 0; i < 4; i++) {
		if (correct[i] == guess[i]) {
			c_p++;
		}
	} return c_p;
}

int correctNumber(vector<int> correct, vector<int> guess) {
	int c_n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (guess[j] == correct[i]) c_n++;
		}
	} return c_n;
}

void playMastermind() {
	cout << " __   __  _______  _______  _______  _______  ______    __   __  ___   __    _  ______   \n";
	cout << "|  |_|  ||   _   ||       ||       ||       ||    _ |  |  |_|  ||   | |  |  | ||      |  \n";
	cout << "|       ||  |_|  ||  _____||_     _||    ___||   | ||  |       ||   | |   |_| ||  _    | \n";
	cout << "|       ||       || |_____   |   |  |   |___ |   |_||_ |       ||   | |       || | |   | \n";
	cout << "|       ||       ||_____  |  |   |  |    ___||    __  ||       ||   | |  _    || |_|   | \n";
	cout << "| ||_|| ||   _   | _____| |  |   |  |   |___ |   |  | || ||_|| ||   | | | |   ||       | \n";
	cout << "|_|   |_||__| |__||_______|  |___|  |_______||___|  |_||_|   |_||___| |_|  |__||______|  \n";
	cout << endl << "Welcome to Mastermind" << endl;
	vector<int> sequence;
	vector<int> possible = { 1,2,3,4,5,6 };
	random_device rd;
	int c_n = 0;
	int c_p = 0;
	int temp = -1;
	int turns = 1;
	for (int i = 0; i < 4; i++) {
		temp = possible[rd() % possible.size()];
		sequence.push_back(temp);
		possible.erase(remove(possible.begin(), possible.end(), temp), possible.end());
		temp = -1;

		//cout << sequence[i];
	}
	cout << "A 4-digit sequence has been created using unique integers from 1-6" << endl;
	while (true) {
vector<int> guess;
int temp;
cout << "Turn " << turns << "/10" << endl;
for (int j = 0; j < 4; j++) {
	cout << "Enter guess for index " << j << ": ";
	cin >> temp;
	if (cin.fail() || (temp < 1 || temp > 6)) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\nInvalid input\n";
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cin.clear();
		cin.ignore();
		j--;
		continue;
	}
	guess.push_back(temp);
}
c_p = correctPlace(sequence, guess);
c_n = correctNumber(sequence, guess);
cout << "Correct placements: " << c_p << endl;
cout << "Correct numbers: " << c_n << endl;
turns++;
if (c_p == 4) {
	cout << "Sequence was: ";
	for (int q = 0; q < 4; q++) {
		cout << sequence[q];
	}
	cout << endl;
	winScreen();
}

if (turns > 10) {
	cout << "Sequence was: ";
	for (int q = 0; q < 4; q++) {
		cout << sequence[q];
	}
	cout << endl;
	loseScreen();
}


	}
}

//MATH PUZZLES

bool doMath(string difficulty, char oper) {
	random_device rd;
	int max = 0;
	double temp1;
	double temp2;
	double answer;
	double guess;
	cout << "Guess should be correct to one decimal place" << endl;
	if (difficulty == "easy") max = 12;
	else if (difficulty == "medium") max = 60;
	else max = 120;

	if (oper == '+') {
		temp1 = rd() % (max*5);
		temp2 = rd() % (max*5);
		cout << temp1 << " + " << temp2 << " = ";
		answer = temp1 + temp2;
	}

	else if (oper == '-') {
		temp1 = rd() % (max*5);
		temp2 = rd() % max;
		cout << temp1 << " - " << temp2 << " = ";
		answer = temp1 - temp2;
	}

	else if (oper == '*') {
		temp1 = rd() % (max);
		temp2 = rd() % (max);
		cout << temp1 << " * " << temp2 << " = ";
		answer = temp1 * temp2;
	}

	else if (oper == '/') {
		temp1 = rd() % max;
		temp2 = rd() % (max/4) + 1;
		cout << temp1 << " / " << temp2 << " = ";
		answer = temp1 / temp2;
	}

	cin >> guess;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		return false;
	}
	if (guess == answer) return true;

	return false;
}

void playMathPuzzles() {
	cout << " ___ ___   ____  ______  __ __      ____  __ __  _____  _____  _        ___  _____ \n";
	cout << "|   |   | /    ||      ||  |  |    |    \\|  |  ||     ||     || |      /  _]/ ___/ \n";
	cout << "| _   _ ||  o  ||      ||  |  |    |  o  )  |  ||__/  ||__/  || |     /  [_(   \\_  \n";
	cout << "|  \\_/  ||     ||_|  |_||  _  |    |   _/|  |  ||   __||   __|| |___ |    _]\\__  | \n";
	cout << "|   |   ||  _  |  |  |  |  |  |    |  |  |  :  ||  /  ||  /  ||     ||   [_ /  \\ | \n";
	cout << "|   |   ||  |  |  |  |  |  |  |    |  |  |     ||     ||     ||     ||     |\\    | \n";
	cout << "|___|___||__|__|  |__|  |__|__|    |__|   \\__,_||_____||_____||_____||_____| \\___| \n";
	cout << "                                                                                   \n";
	cout << endl << "Welcome to Math Puzzles!" << endl;
	string difficulty;
	char oper;
	int strikes = 0;
	int points = 0;
	bool result;
	while (true) {
		cout << "Choose difficulty (easy, medium hard): ";
		cin >> difficulty;
		if (cin.fail() || (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")) {
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Invalid input" << endl;
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.clear();
			cin.ignore();
			continue;
		}	while (true) {
			cout << "\nChoose addition('+'), subtraction('-'), multiplication('*') or division('/'): ";
			cin >> oper;
			if (cin.fail() || (oper != '+' && oper != '-' && oper != '*' && oper != '/')) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "Invalid input" << endl;
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cin.clear();
				cin.ignore();
				continue;
			}
			while (true) {
				cout << "Current points: " << points << "/10" << endl;
				cout << "Current strikes: " << strikes << "/3" << endl;
				result = doMath(difficulty, oper);
				if (result) {
					cout << "Correct!" << endl;
					points++;
				}

				else {
					cout << "Wrong!" << endl;
					strikes++;
				}

				if (points >= 10) {
					winScreen();
				}

				if (strikes >= 3) {
					loseScreen();
				}
			}
		}
	}
}

int main() {
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << endl;
	cout << " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  \n";
	cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | \n";
	cout << "| |      __      | || |  _______     | || |     ______   | || |      __      | || |  ________    | || |  _________   | | \n";
	cout << "| |     /  \\     | || | |_   __ \\    | || |   .' ___  |  | || |     /  \\     | || | |_   ___ `.  | || | |_   ___  |  | | \n";
	cout << "| |    / /\\ \\    | || |   | |__) |   | || |  / .'   \\_|  | || |    / /\\ \\    | || |   | |   `. \\ | || |   | |_  \\_|  | | \n";
	cout << "| |   / ____ \\   | || |   |  __ /    | || |  | |         | || |   / ____ \\   | || |   | |    | | | || |   |  _|  _   | | \n";
	cout << "| | _/ /    \\ \\_ | || |  _| |  \\ \\_  | || |  \\ `.___.'\\  | || | _/ /    \\ \\_ | || |  _| |___.' / | || |  _| |___/ |  | | \n";
	cout << "| ||____|  |____|| || | |____| |___| | || |   `._____.'  | || ||____|  |____|| || | |________.'  | || | |_________|  | | \n";
	cout << "| |              | || |              | || |              | || |              | || |              | || |              | | \n";
	cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | \n";
	cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  \n";
	while (true) {
		vector<string> gameList = { "Hangman", "Blackjack", "Number Guesser", "Rock, Paper, Scissors", "Tic Tac Toe", "Word Shuffle", "Mastermind", "Math Puzzles" };
		int gameChosen;
		cout << "\nWelcome to the arcade!" << endl;
		cout << "Here is a list of games, type its number to play:" << endl << "(enter '0' to quit)\n" << endl;
		for (int i = 0; i < gameList.size(); i++) {
			cout << i + 1 << ". " << gameList[i] << endl;
		}
		cin >> gameChosen;
		if (cin.fail() || (gameChosen < 0 || gameChosen>gameList.size())) {
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nINVALID INPUT\n" << endl;
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cin.clear();
			cin.ignore();
			gameChosen = -1;
			continue;
		}
		switch (gameChosen) {
		case 0: exit(0);
		case 1: system("CLS"); playHangman(); break;
		case 2: system("CLS"); playBlackjack(); break;
		case 3: system("CLS"); playNumberGuesser(); break;
		case 4: system("CLS"); playRPS(); break;
		case 5: system("CLS"); playTicTacToe(); break;
		case 6: system("CLS"); playWordShuffle(); break;
		case 7: system("CLS"); playMastermind(); break;
		case 8: system("CLS"); playMathPuzzles(); break;
		default: SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); cout << "Invalid input" << endl; break;
		}
	}
}