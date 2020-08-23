#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

const int SIDE = 30;
int universe[SIDE][SIDE]; //�������� �������


void fill_first_generation(int u[SIDE][SIDE], int nRow, int nCol, bool is_random) { // ���������� ������� ���������
	if (is_random) {
		srand(time(nullptr));
		for (int i = 0; i < SIDE; i++) {
			for (int j = 0; j < SIDE; j++) {
				if (rand() > 4000) // rand() ������� ����� � ��������� �� 0 �� 32�. �� ������ ���� ��������, ����� "0" ���������� ������, ��� "1".
					u[i][j] = 0;
				else
					u[i][j] = 1;
			}
		}
	}
	else { // �������
		u[2][4] = 1;
		u[3][5] = 1;
		u[4][3] = 1;
		u[4][4] = 1;
		u[4][5] = 1;
	}
}


void show_array(int u[SIDE][SIDE], int nRow, int nCol) { // ����� ������� ��������� �� �����
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			if (u[i][j] == 0)
				cout << ' '; //����������� ������� ������
			else
				cout << (char)178; // �����. ����� ������
		}
		cout << endl;
	}
}


int count_neighbours(int u[SIDE][SIDE], int i, int j) { // �������� ����� �� ���������(���� �������� ���������� ����������� ������)
	int count = 0;
	if (i == 0 && j == 0) { //����� ������� ����
		count = u[SIDE - 1][SIDE - 1] + u[SIDE - 1][0] + u[SIDE - 1][j + 1] +
			u[0][SIDE - 1] + u[i][j + 1] +
			u[i + 1][SIDE - 1] + u[i + 1][0] + u[i + 1][j + 1];
	}

	else if (i == 0 && j == SIDE - 1) { // ������ ������� ����
		count = u[SIDE - 1][SIDE - 2] + u[SIDE - 1][SIDE - 1] + u[SIDE - 1][0] +
			u[0][SIDE - 2] + u[0][0] +
			u[i + 1][SIDE - 2] + u[i + 1][SIDE - 1] + u[i + 1][0];
	}

	else if (i == SIDE - 1 && j == 0) { //����� ������ ����
		count = u[SIDE - 2][SIDE - 1] + u[SIDE - 2][0] + u[SIDE - 2][j + 1] +
			u[SIDE - 1][SIDE - 1] + u[SIDE - 1][j + 1] +
			u[0][SIDE - 1] + u[0][0] + u[0][j + 1];
	}

	else if (i == SIDE - 1 && j == SIDE - 1) { // ������ ������ ����
		count = u[SIDE - 2][SIDE - 2] + u[SIDE - 2][SIDE - 1] + u[SIDE - 2][0] +
			u[SIDE - 1][SIDE - 2] + u[SIDE - 1][0] +
			u[0][SIDE - 2] + u[0][SIDE - 1] + u[0][0];
	}

	else if (i == 0) { //������� ������
		count = u[SIDE - 1][j - 1] + u[SIDE - 1][j] + u[SIDE - 1][j + 1] +
			u[0][j - 1] + u[0][j + 1] +
			u[i + 1][j - 1] + u[i + 1][j] + u[i + 1][j + 1];
	}

	else if (j == 0) { // ����� ���
		count = u[i - 1][SIDE - 1] + u[i - 1][j] + u[i - 1][j + 1] +
			u[i][SIDE - 1] + u[i][j + 1] +
			u[i + 1][SIDE - 1] + u[i + 1][j] + u[i + 1][j + 1];
	}

	else if (j == SIDE - 1) { //������ ���
		count = u[i - 1][SIDE - 2] + u[i - 1][j] + u[i - 1][0] +
			u[i][SIDE - 2] + u[i][0] +
			u[i + 1][SIDE - 2] + u[i + 1][SIDE - 1] + u[i + 1][0];
	}

	else if (i == SIDE - 1) { // ������ ������
		count = u[SIDE - 2][j - 1] + u[SIDE - 2][j] + u[SIDE - 2][j + 1] +
			u[SIDE - 1][j - 1] + u[SIDE - 1][j + 1] +
			u[0][j - 1] + u[0][j] + u[0][j + 1];
	}

	else //�������� (����� ������)
		count = u[i - 1][j - 1] + u[i - 1][j] + u[i - 1][j + 1] +
		u[i][j - 1] + u[i][j + 1] +
		u[i + 1][j - 1] + u[i + 1][j] + u[i + 1][j + 1];
	return count;
}

void create_next_generation(int u[SIDE][SIDE], int nRow, int nCol) {//�������� ������ ���������, ����������� ������ ����
	int neighbours = 0;
	int universe2[SIDE][SIDE]{};
	int cell;
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			cell = u[i][j];
			neighbours = count_neighbours(u, i, j);
			if (neighbours > 3 || neighbours < 2)
				cell = 0;
			else if (neighbours == 3)
				cell = 1;
			universe2[i][j] = cell;
		}
	}
	show_array(universe2, SIDE, SIDE);

	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			u[i][j] = universe2[i][j];
		}
	}
}


void start_game() { //������ ����
	fill_first_generation(universe, SIDE, SIDE, false);
	show_array(universe, SIDE, SIDE);
	while (true) {
		Sleep(30);
		system("cls");
		create_next_generation(universe, SIDE, SIDE);
	}
}

int main() {
	int test;
	start_game();
	cin >> test;
	return 0;
}