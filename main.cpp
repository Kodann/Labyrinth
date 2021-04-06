#include "Labirinth.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <locale>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	if (argc != 8) {
		cout << "Формат ввода данных: filein filout start.x start.y finish.x finish.y step_mode." << endl << endl;
		cout << "Пример: in.txt out.txt 5 6 3 8 1";
	}
	else {
		Labirinth l;
		//string way = { "C:\\laba\\" };
		l.load(argv[1]);
		point start;
		point finish;
		start.x = atoi(argv[3]);
		start.y = atoi(argv[4]);
		finish.x = atoi(argv[5]);
		finish.y = atoi(argv[6]);
		cout << l;
		l.find_way(start, finish, atoi(argv[7]));
		cout << l;
		l.save_answer(argv[2]);
	}
	getchar();
	return 0;
}
