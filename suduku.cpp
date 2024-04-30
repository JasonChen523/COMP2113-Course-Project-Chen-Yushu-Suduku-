#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <list>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

const int size = 4;
int gameboard[size][size];
list<int> temp_set[size][size]; 
int r = sqrt(size);
list<int> number_set;

void draw_gameboard(int [][size]);
void initialize_gameboard(int [][size]);
void complete_gameboard(int [][size], list<int> &);
void forward(int [][size], int, int);
void backward(int [][size], int, int);
void leave_blank(int [][size]);
int main()
{
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j)
			gameboard[i][j] = 0;
	}
	initialize_gameboard(gameboard);
	complete_gameboard(gameboard, number_set);
	leave_blank(gameboard);
	cout << "Start Suduku Game right now? (yes / no)" << endl;
	string x;
	cin >> x;
	while (x != "yes" && x != "no"){
		cout << "Enter 'yes' to start or 'no' to leave." << endl;
		cin >> x;
	}
	if (x == "yes"){
		draw_gameboard(gameboard);
		int flag = 0;
		int flag1 = 0;
		while (flag == 0){
			cout << "Please enter a number to fill in the blank." << endl;
			int y;
			cin >> y;

			for (int i = 0; i < size; ++i){
				for (int j=0; j < size; ++j){
					if (gameboard[i][j] == 0){
						gameboard[i][j] = y;
						cout << "i = " << i <<endl;
						cout << "j = " << j <<endl;
						flag1 = 1;
						break;
					}
				if (flag1 == 1){
					
					break;
				}
				}
			}
			draw_gameboard(gameboard);
			flag = 1;
			for (int i = 0; i < size; ++i){
				for (int j=0; j < size; ++j){
					if (gameboard[i][j] == 0){
						flag = 0;
						break;
					}
				}
			}
			cout << "flag = " << flag<<endl;
			//draw_gameboard(gameboard);
		}
			
	}
	if (x == "no")
		cout << "Bye bye!" << endl;
	return 0;
}

void draw_gameboard(int g[size][size]){
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j){
			if (g[i][j] == 0) 
				cout << "¡õ";
			else if (g[i][j] == -1)
					cout << "¡õ";
			else
				cout << g[i][j] << " ";
		}
		cout << endl;
	}
}

void initialize_gameboard(int h[size][size]){
	vector<int> number_set;
	for (int k = 0; k < size; ++k)
		number_set.push_back(k+1);
	vector<int> temp1 = number_set;
	vector<int> temp2 = temp1;
	srand(time(NULL));
	for (int j = 0; j < size; ++j){
		int x = rand() % (size - j);
		h[0][j] = temp1[x];
		temp1.erase(temp1.begin() + x);
		if (j == 0)
			temp2.erase(temp2.begin() + x);
			else if(j == 1){
				int y1 = rand() % (size - j - 1);
				h[j][0] = temp1[y1];
				vector<int>::iterator itr = find(temp2.begin(), temp2.end(), temp1[y1]);
				temp2.erase(itr);
			}
		else{
			int y = rand() % (size - j);
			h[j][0] = temp2[y];
			temp2.erase(temp2.begin() + y);
		}
		}
}

void complete_gameboard(int h[size][size], list<int> &number_set){
	for (int k = 0; k < size; ++k)
		number_set.push_back(k+1);
	forward(h, 1, 1);
}

void forward(int h[size][size], int x, int y){
	for (int i = x; i < size; ++i){
		list<int> line = number_set;
		line.remove(h[i][0]);
		if (i == x){
			for (int n = 1; n < y; ++n)
				line.remove(h[i][n]);
			for (int j = y; j < size; ++j) {
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
				if (temp.empty())
					backward(h, i, j);
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();
					temp_set[i][j] = temp;
					line.remove(h[i][j]);
				}
			}
		}
		else{
			for (int j = 1; j < size; ++j) {
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
				if (temp.empty()){
					backward(h, i, j);
				}
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();
					temp_set[i][j] = temp;
					line.remove(h[i][j]);
				}
			}
		}
	}
}

void backward(int h[size][size], int i, int j){
	if (j == 1){
		if (temp_set[i - 1][size - 1].empty())
			backward(h, (i - 1), (size - 1));
		else{
			h[i - 1][size - 1] = temp_set[i - 1][size - 1].front();
			temp_set[i - 1][size - 1].pop_front();
			forward(h, i, j);
		}
	}
	else{
		if (temp_set[i][j - 1].empty())
			backward(h, (i), (j - 1));
		else{
			h[i][j - 1] = temp_set[i][j - 1].front();
			temp_set[i][j - 1].pop_front();
			forward(h, i, j);
		}
	}
}

void leave_blank(int f[size][size]){
	srand(time(NULL));
	for (int i = 0; i < 12; ++i){
		int x = rand() % size;
		int y = rand() % size;
		f[x][y] = 0;
	}
}
