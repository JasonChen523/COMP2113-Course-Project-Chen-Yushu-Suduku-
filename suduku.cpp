#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <list>
#include <cmath>
#include <string>
#include <cctype>
#include <utility>
using namespace std;


const int size = 4;  //size of gameboard
int gameboard[size][size];
list<int> temp_set[size][size];  //to store temporary data used for backtracking
int r = sqrt(size);  //size of each smaller block
list<int> number_set;  //template list to contain numbers 1-4
vector<pair<int, int> > fixed_indices;  //fixed numbers at start of Sudoku game

void draw_gameboard(int [][size]);
void initialize_gameboard(int [][size]);
void complete_gameboard(int [][size], list<int> &);
void forward(int [][size], int, int);
void backward(int [][size], int, int);
void leave_blank(int [][size], vector<pair<int, int> > &);
void scan_gameboard(int [][size]);
void interacting(int, int);
void locating(int, int, int);
void value_check(int &, int &);

int main()
{
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j)
			gameboard[i][j] = 0;
	}
	initialize_gameboard(gameboard);
	complete_gameboard(gameboard, number_set);  //initialize an empty gameboard
	leave_blank(gameboard, fixed_indices);
	cout << "Start Sudoku Game right now? (yes / no)" << endl;
	string x;
	cin >> x;
	while (x != "yes" && x != "no"){
		cout << "Enter 'yes' to start or 'no' to leave." << endl;
		cin >> x;
	}
	if (x == "yes"){
		cout << "Welcome to Sudoku game. Fill in the 4*4 gameboard with numbers between 1-4." << endl;
		cout << "Make sure that each row, each column and each 2*2 block at the corner are exactly filled with 1, 2, 3, 4." << endl;
		cout << "Enter a number to fill in the blank. Enter i to access index, " << 
			"then enter two numbers to jump to any row and column!" << endl;   //introduction of rules
		int flag = 0;  //to exit the loop if a blank is found
		int y, z = 0;
		for (int i = 0; i < size; ++i){
			for (int j = 0; j < size; ++j){
				if (gameboard[i][j] == 0){
					gameboard[i][j] = -1;
					flag = 1;
					y = i, z = j;		//point to first blank on gameboard
					break;
				}
			}
			if (flag == 1)
				break;
		}
		draw_gameboard(gameboard);
		interacting(y, z);  //major interactive function
	}		
	if (x == "no")
		cout << "Bye bye!" << endl;
	return 0;
}

void draw_gameboard(int g[size][size]){
	cout << endl;
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j){
			if (g[i][j] == 0)   //blanks on gameboard
				cout << "□";
			else if (g[i][j] == -1)
					cout << "__";  //pointing out the current position to fill-in
			else
				cout << g[i][j] << " ";
		}
		cout << endl;
	}
}

void initialize_gameboard(int h[size][size]){  //random generation of 1st row and 1st column
	vector<int> number_set;
	for (int k = 0; k < size; ++k)
		number_set.push_back(k+1); 
	vector<int> temp1 = number_set;  //numbers of 1st row
	vector<int> temp2 = temp1;  //numbers of 1st column
	srand(time(NULL));
	for (int j = 0; j < size; ++j){
		int x = rand() % (size - j);
		h[0][j] = temp1[x];
		temp1.erase(temp1.begin() + x);  //avoid repetition
		if (j == 0)
			temp2.erase(temp2.begin() + x);
			else if(j == 1){
				int y1 = rand() % (size - j - 1);
				h[j][0] = temp1[y1];
				vector<int>::iterator itr = find(temp2.begin(), temp2.end(), temp1[y1]);  //remove numbers of top-left block
				temp2.erase(itr);  
			}
		else{
			int y = rand() % (size - j);
			h[j][0] = temp2[y];
			temp2.erase(temp2.begin() + y);
		}
		}
}

void complete_gameboard(int h[size][size], list<int> &number_set){  //solve the rest of gameboard
	for (int k = 0; k < size; ++k)
		number_set.push_back(k+1);
	forward(h, 1, 1);
}

void forward(int h[size][size], int x, int y){  //start at point(x,y)
	for (int i = x; i < size; ++i){  //solve from top left to bottom right
		list<int> line = number_set;
		line.remove(h[i][0]);
		if (i == x){  //used to continue from where backtracking stops
			for (int n = 1; n < y; ++n)
				line.remove(h[i][n]);  //remove numbers in same row
			for (int j = y; j < size; ++j) {  
				list<int> temp = line;
				for (int m = 0; m < i; ++m)
					temp.remove(h[m][j]);  //remove numbers in same column
				int n = r * (i % r) + (j % r);  //find relative position in corresponding 2*2 block
				switch (n){  //remove numbers in same block
					case 1:
						if (j == 1)
							temp.remove(h[i + 1][j - 1]);
						break;
					case 2:
						temp.remove(h[i - 1][j + 1]);
						break;
					case 3:
						temp.remove(h[i - 1][j - 1]);
						break;
				}
				if (temp.empty())  //backwards if no number to fill in
					backward(h, i, j);
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();  //delete the current path
					temp_set[i][j] = temp;
					line.remove(h[i][j]);
				}
			}
		}
		else{
			for (int j = 1; j < size; ++j) {  //used for numbers in a new line
				list<int> temp = line;
				for (int m = 0; m < i; ++m)
					temp.remove(h[m][j]);	
				int n = r * (i % r) + (j % r);
				switch (n){
					case 1:
						if (j == 1)
							temp.remove(h[i + 1][j - 1]);
						break;
					case 2:
						temp.remove(h[i - 1][j + 1]);
						break;
					case 3:
						temp.remove(h[i - 1][j - 1]);
						break;
				}
				if (temp.empty()){  //solving algorithms are similar to above
					backward(h, i, j);
				}
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();
					temp_set[i][j] = temp;  //renewing each time
					line.remove(h[i][j]);
				}
			}
		}
	}
}

void backward(int h[size][size], int i, int j){  //backtrack to last position
	if (j == 1){   //last position on previous row
		if (temp_set[i - 1][size - 1].empty())
			backward(h, (i - 1), (size - 1));  //recursion if no reserving path for last one
		else{
			h[i - 1][size - 1] = temp_set[i - 1][size - 1].front();  //choose the first available path
			temp_set[i - 1][size - 1].pop_front();  //remove it for the next backtracking
			forward(h, i, j);  //start forward progress
		}
	}
	else{  //last position on the left
		if (temp_set[i][j - 1].empty())
			backward(h, (i), (j - 1));
		else{
			h[i][j - 1] = temp_set[i][j - 1].front();
			temp_set[i][j - 1].pop_front();
			forward(h, i, j);
		}
	}
}

void leave_blank(int f[size][size], vector<pair<int, int> > &n){
	srand(time(NULL));
	for (int i = 0; i < 12; ++i){  //hit the gameboard for 12 random times
		int x = rand() % size;
		int y = rand() % size;
		f[x][y] = 0;  //remove the hitted number on gameboard and leave a blank
	}		//normally 6-8 numbers left
	n.clear();
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (gameboard[i][j] != 0){
				pair<int, int> z(i, j);
				n.push_back(z);	  //fix the remaining numbers to avoid modifying
			}
		}
	}
}

void scan_gameboard(int f[size][size]){  //test whether players complete the gameboard correctly
	for (int k = 0; k < size; ++k)
		number_set.push_back(k+1);
	for (int i = 0; i < size; ++ i){
		list<int> row, column = number_set;
		for (int j = 0; j < size; ++j){  //test each row and column
			row.remove(f[i][j]);
			column.remove(f[j][i]);
			if ((i % 2 == 0) && (j % 2 == 0)){
				list<int> block = number_set;  //test each block
				block.remove(f[i][j]);
				block.remove(f[i][j + 1]);
				block.remove(f[i + 1][j]);
				block.remove(f[i + 1][j + 1]);
				if (!block.empty())
					row.push_back(size + 1);  //fail the block test will add number 5 to the row set, makes it unable to be emptied
			}
		}
		if(!(row.empty() && column.empty())){  //players lose the game once a unit not reached
			cout << "You lose the game. Try again? (yes / no)" << endl;
			string x;
			cin >> x;
			if (x == "yes"){  //restart and initialize the gameboard
							for (int i = 0; i < size; ++i){
					for (int j=0; j < size; ++j)
						gameboard[i][j] = 0;
				}								
				initialize_gameboard(gameboard);  //similar to main function
				complete_gameboard(gameboard, number_set);
				leave_blank(gameboard, fixed_indices);
				int flag = 0; 
				int y, z = 0;
				for (int i = 0; i < size; ++i){
					for (int j = 0; j < size; ++j){
						if (gameboard[i][j] == 0){
							gameboard[i][j] = -1;
							flag = 1;
							y = i, z = j;
							break;
						}
					}
					if (flag == 1)
						break;
				}
				draw_gameboard(gameboard);
				interacting(y, z);
			}
			else{
				cout << "Bye bye!" <<endl;
				break;
			}
		}
		if (i == (size - 1)){  //mistakes not found after all of the testings
			cout << "Congratulations! You are a master of Sudoku! Play again? (yes / no)" << endl;
			string x;
			cin >> x;
			if (x == "yes"){  //regenerate a random gameboard
				for (int i = 0; i < size; ++i){
					for (int j=0; j < size; ++j)
						gameboard[i][j] = 0;
				}
				initialize_gameboard(gameboard);
				complete_gameboard(gameboard, number_set);
				leave_blank(gameboard, fixed_indices);
				int flag = 0;  
				int y, z = 0;
				for (int i = 0; i < size; ++i){
					for (int j = 0; j < size; ++j){
						if (gameboard[i][j] == 0){
							gameboard[i][j] = -1;
							flag = 1;
							y = i, z = j;
							break;
						}
					}
					if (flag == 1)
						break;
				}
				draw_gameboard(gameboard);
				interacting(y, z);
			}
			else{
				cout << "Bye bye!" << endl;
				break;
			}
		}
	}
}

void interacting(int i, int j){
	cout << "Please fill in a number or enter an index: " << endl;
	char input;
	cin >> input;
	if (isdigit(input)){
		int x = input - '0';
		locating(x, i, j);  //input a number directs to the number-filling function
	}
	else if (input == 'i'){  //input 'i' to enter an index
		char input1, input2, num = 'a';
		while(!(isdigit(input1) && isdigit(input2))){
			cout << "Please enter an index with two numbers: " << endl;
			cin >> input1 >> input2;
		}
		int y = (input1 - '0' - 1), z = (input2 - '0' - 1);  //convert the input character to correspoding row and column
		value_check(y, z);  //check whether the number at (y, z) is fixed
		gameboard[y][z] = -1;  //pass the cursor to that position
		if (gameboard[i][j] == -1)
			gameboard[i][j] = 0;
		draw_gameboard(gameboard);
		while(!isdigit(num)){
			cout << "Please fill in a number: " << endl;
			cin >> num;
		}
		int x = num - '0';
		locating(x, y, z);  //enable number-filling
	}
	else
		interacting(i, j);  //repeat if input is not a number or 'i'
}

void locating(int x, int y, int z){
	gameboard[y][z] = x;
	int flag1, flag2 = 0;  //To indecate whether the user completed the gameboard.
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){  //search for remaining blanks
			if (gameboard[i][j] == 0){
				gameboard[i][j] = -1;
				flag1 = 1;
				flag2 = 1;
				y = i, z = j;
				break;
			}
		}
		if (flag1 == 1)
			break;
	}
	if (flag2 == 1){
		gameboard[y][z] = -1; //pass the cursor to next blank
		draw_gameboard(gameboard);
		interacting(y, z);
	}
	else{  //no blanks remained
		draw_gameboard(gameboard);
		cout << "Finish the game? (yes / no)" << endl;
		string w;
		cin >> w;
		if (w == "yes")
			scan_gameboard(gameboard);   //check win condition
		else 
			interacting(y, z);
	}
}

void value_check(int &y, int &z){
	pair<int, int> w(y, z);  
	int x = count(fixed_indices.begin(), fixed_indices.end(), w);  //check fixed or not, skip if not fixed
	if (x!=0){
		cout << "You cannot modify a fixed number. Please enter another index." << endl;
		char input1, input2 = 'a';
		cin >> input1 >> input2;
		while(!(isdigit(input1) && isdigit(input2))){
			cout << "Please enter an index with two numbers: ";
			cin >> input1 >> input2;
		}
		int y1 = (input1 - '0' - 1), z1 = (input2 - '0' - 1);
		y = y1, z = z1;  //pass-by-reference for index coordinate
		value_check(y, z);  //check again until it is valid
	}
}
