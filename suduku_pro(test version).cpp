#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

const int size = 9;
int gameboard[size][size];
list<int> temp_set[size][size]; 
int r = sqrt(size);
list<int> number_set;

void draw_gameboard(int [][size]);
void initialize_gameboard(int [][size]);
void complete_gameboard(int [][size], list<int> &);
void forward(int [][size], int, int);
void backward(int [][size], int, int);
int main()
{
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j)
			gameboard[i][j] = 0;
	}
	//initialize_gameboard(gameboard);
	gameboard[0][0] = 1;
	gameboard[0][1] = 4;
	gameboard[0][2] = 7;
	gameboard[0][3] = 2;
	gameboard[0][4] = 5;
	gameboard[0][5] = 3;
	gameboard[0][6] = 9;
	gameboard[0][7] = 6;
	gameboard[0][8] = 8;
	gameboard[1][0] = 2;
	gameboard[2][0] = 6;
	gameboard[3][0] = 4;
	gameboard[4][0] = 3;
	gameboard[5][0] = 8;
	gameboard[6][0] = 9;
	gameboard[7][0] = 5;
	gameboard[8][0] = 7;
	draw_gameboard(gameboard);
	complete_gameboard(gameboard, number_set);
	draw_gameboard(gameboard);
	return 0;
}

void draw_gameboard(int g[size][size]){
	for (int i = 0; i < size; ++i){
		for (int j=0; j < size; ++j){
			if (g[i][j] == 0) 
				cout << "  ";
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
	}
	vector<int>::iterator itr = find(temp2.begin(), temp2.end(), h[0][0]);
	temp2.erase(itr);
	vector<int> temp3 = temp2;
	vector<int>::iterator itr1 = find(temp2.begin(), temp2.end(), h[0][1]);
	temp2.erase(itr1);
	vector<int>::iterator itr2 = find(temp2.begin(), temp2.end(), h[0][2]);
	temp2.erase(itr2);
	for (int l = 1; l < size; ++l){
		if (l == 1 || l == 2){
			int y = rand() % (size - l - 2);
			h[l][0] = temp2[y];
			temp2.erase(temp2.begin() + y);
			vector<int>::iterator itr3 = find(temp3.begin(), temp3.end(), h[l][0]);
			temp3.erase(itr3);
		}
		else{
			int z = rand() % (size - l);
			h[l][0] = temp3[z];
			temp3.erase(temp3.begin() + z);
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
						if (j == 1){
							temp.remove(h[i + 1][j - 1]);
							temp.remove(h[i + 2][j - 1]);
						}
						break;
					case 2:
						if (j == 2){
							temp.remove(h[i + 1][j - 2]);
							temp.remove(h[i + 2][j - 2]);
						}
						break;
					case 3:
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 1][j + 2]);
						break;
					case 4:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j + 1]);
						if (j == 1)
							temp.remove(h[i + 1][j - 1]);
						break;
					case 5:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j - 2]);
						if (j == 2)
							temp.remove(h[i + 1][j - 2]);
						break;
					case 6:
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 1][j + 2]);
						temp.remove(h[i - 2][j + 1]);
						temp.remove(h[i - 2][j + 2]);
						break;
					case 7:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 2][j - 1]);
						temp.remove(h[i - 2][j + 1]);
						break;
					case 8:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j - 2]);
						temp.remove(h[i - 2][j - 1]);
						temp.remove(h[i - 2][j - 2]);
						break;
				}
				if (temp.empty()){
					draw_gameboard(gameboard);
					cout << "backwards" << endl;
					backward(h, i, j);
				}
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();
					temp_set[i][j] = temp;
					line.remove(h[i][j]);
					draw_gameboard(gameboard);
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
						if (j == 1){
							temp.remove(h[i + 1][j - 1]);
							temp.remove(h[i + 2][j - 1]);
						}
						break;
					case 2:
						if (j == 2){
							temp.remove(h[i + 1][j - 2]);
							temp.remove(h[i + 2][j - 2]);
						}
						break;
					case 3:
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 1][j + 2]);
						break;
					case 4:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j + 1]);
						if (j == 1)
							temp.remove(h[i + 1][j - 1]);
						break;
					case 5:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j - 2]);
						if (j == 2)
							temp.remove(h[i + 1][j - 2]);
						break;
					case 6:
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 1][j + 2]);
						temp.remove(h[i - 2][j + 1]);
						temp.remove(h[i - 2][j + 2]);
						break;
					case 7:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j + 1]);
						temp.remove(h[i - 2][j - 1]);
						temp.remove(h[i - 2][j + 1]);
						break;
					case 8:
						temp.remove(h[i - 1][j - 1]);
						temp.remove(h[i - 1][j - 2]);
						temp.remove(h[i - 2][j - 1]);
						temp.remove(h[i - 2][j - 2]);
						break;
				}
				if (temp.empty()){
				//	draw_gameboard(gameboard);
				//	cout << "backwards" << endl;
					backward(h, i, j);
				}
				else
					{
					h[i][j] = temp.front();
					temp.pop_front();
					temp_set[i][j] = temp;
					line.remove(h[i][j]);
				//	draw_gameboard(gameboard);
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
