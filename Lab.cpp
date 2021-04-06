
#include "Labirinth.h"
#include <queue>

using namespace std;

void Labirinth::load(const string& filename) {
	ifstream file(filename);
	string buff;
	int i = 0;
	while (!file.eof()) {
		string number;
		int y = 0;
		matrix.push_back(vector<int>());
		getline(file, buff, '\n');
		for (int j = 0; j < buff.size(); j++) {
			if ((buff[j] != ' ') && (j != buff.size() - 1)) {
				number.push_back(buff[j]);
			}
			else {
				if (j == buff.size() - 1) {
					number.push_back(buff[j]);
					y++;
				}
				if (number.size())
					matrix[i].push_back(stoi(number));
				for (y; y > 0; y--) {
					number.pop_back();
				}
				y = -1;
			}
			y++;
		}
		i++;
	}
	file.close();
}

void Labirinth::find_way(const point& start, const point& finish, bool step_mode) {
	if (start.y < matrix.size() && start.x < matrix[0].size() && finish.y < matrix.size() && finish.x < matrix[0].size()) {
		if (matrix[start.y][start.x] != -1 && matrix[finish.y][finish.x] != -1) {
			bool flag = 0;
			int d = 1, steps = 0, number = 0, number1 = 1;
			int Xstep[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
			int Ystep[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
			queue<point> myQueue;
			point k, tmp;
			vector <point> back_way;
			if (step_mode) {
				steps = 8;
			}
			else {
				steps = 4;
			}
			k.x = start.x;
			k.y = start.y;
			myQueue.push(k);
			while (flag == 0) {
				for (int i = 0; i < number1 && flag == 0; i++) {
					k = myQueue.front();
					myQueue.pop();
					for (int j = 0; j < steps; j++) {
						int Y = k.y + Ystep[j];
						int X = k.x + Xstep[j];
						if ((X < matrix[0].size() && X >= 0) && (Y < matrix.size() && Y >= 0)) {
							if (matrix[Y][X] == 0) {
								matrix[Y][X] = d;
								tmp.x = X;
								tmp.y = Y;
								myQueue.push(tmp);
								number++;
							}
						}
						if (X == finish.x && Y == finish.y || (myQueue.size() == 0 && j == 7) || (myQueue.size() == 0 && j == 3)) {
							matrix[Y][X] = d;
							tmp.x = X;
							tmp.y = Y;
							flag = 1;
							break;
						}
					}
				}
				number1 = number;
				number = 0;
				d++;
			}
			if (tmp.x == finish.x && tmp.y == finish.y) {
				length = d;
				for (int i = d; i >= 0; i--) {
					for (int j = 0; j < steps; j++) {
						int Y = tmp.y + Ystep[j];
						int X = tmp.x + Xstep[j];
						if ((X < matrix[0].size() && X >= 0) && (Y < matrix.size() && Y >= 0)) {
							if (matrix[Y][X] == i - 2) {
								back_way.push_back(tmp);
								tmp.y = Y;
								tmp.x = X;
								break;
							}
						}
					}
				}
				for (int i = 0; i < matrix.size(); i++) {
					for (int j = 0; j < matrix[i].size(); j++) {
						if (matrix[i][j] > 0)
							matrix[i][j] = 0;
					}
				}
				for (int i = back_way.size() - 1; i > 0; i--) {
					matrix[back_way[i].y][back_way[i].x] = back_way.size() - i;
				}
				matrix[tmp.y][tmp.x] = 1;
				matrix[finish.y][finish.x] = -3;
				matrix[start.y][start.x] = -2;
			}
			else {
				for (int i = 0; i < matrix.size(); i++) {
					for (int j = 0; j < matrix[i].size(); j++) {
						if (matrix[i][j] > 0)
							matrix[i][j] = 0;
					}
				}
				cout << "Между точками нет прохода" << endl << endl;
			}
		}
		else {
			cout << "Вы указали непроходимые точки" << endl << endl;
		}
	}
	else {
		cout << "Вы указали непроходимые точки" << endl << endl;
	}
}

void Labirinth::save_answer(const string& filename) {
	ofstream file(filename);
	file << *this;
	file.close();
}

ostream & operator<<(ostream& out, const Labirinth& o)
{
	for (auto it = o.matrix.begin(); it != o.matrix.end(); ++it) {
		for (auto it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
			if (*it1 >= 0)
				out << " ";
			out << *it1 << " ";
		}
		out << endl;
	}
	out << endl;
	return out;
}