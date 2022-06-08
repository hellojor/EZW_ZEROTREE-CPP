#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <fstream>

#include "ZeroTree.h"
#include "CStatus.h"

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::string;
using std::setw;

int findmax(int** img, int height, int width);
int check_beside(int* FORM1, int FORM_count, int val);
int find_index(int* arr, int len, int num);
const queue<string> split(const string str, const char delimiter);
void EZW_encode(int** img, int height, int width, int& maxVal, string& S1, string& Z1, string& S2, string& D2, string& Z2);
void EZW_decode(int** img, int height, int width, int maxVal, string S1, string Z1, string S2, string D2, string Z2);

int main() {
	int input[8][8] = {
		{ 60, -32,  51,  13,   9,  15,  -2,   9},
		{-20,  21,  15, -12,   7,   2,   8,  -2},
		{ 12,  17,   3, -15,   6,  -9,   5,   8},
		{ -8,  -6, -12,   7,   5,  -7,   1,   3},
		{ -2,  50,  -2,   1,   4,   7,  -2,   3},
		{  3,  -1,  -2,   1,   5,  -1,   4,   2},
		{  2,  -2,   8,   5,   3,   3,   2,   4},
		{  6,  12,   7,   2,  -1,   2,  -5,   6},
	};
	int height = 8;
	int width = 8;
	int** img = new int* [height];
	for (int i = 0; i < height; i++) {
		img[i] = new int[width];
		for (int j = 0; j < width; j++) {
			img[i][j] = input[i][j];
		}
	}

	cout << "==> ORG IMG <==" << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << setw(3) << img[i][j] << "\t";
		}
		cout << endl;
	}

	int maxVal = 0;
	string S1 = "", Z1 = "";
	string S2 = "", D2 = "", Z2 = "";

	EZW_encode(img, height, width, maxVal, S1, Z1, S2, D2, Z2);
	cout << endl << "==> AFTER EZW ENCODE <==" << endl;
	cout << "maxval:" << maxVal << endl;
	cout << "S1:" << S1 << endl;
	cout << "Z1:" << Z1 << endl;
	cout << "S2:" << S2 << endl;
	cout << "D2:" << D2 << endl;
	cout << "Z2:" << Z2 << endl;
	for (int i = 0; i < height; i++) {
		delete img[i];
	}

	std::ofstream fout("data.txt");
	fout << maxVal << endl;
	fout << S1 << endl;
	fout << Z1 << endl;
	fout << S2 << endl;
	fout << D2 << endl;
	fout << Z2 << endl;
	fout.close();

	maxVal = 0;
	S1 = "";
	Z1 = "";
	S2 = "";
	D2 = "";
	Z2 = "";
	// =======================================================================================

	std::ifstream fin("data.txt");
	string s;
	std::getline(fin, s);
	maxVal = stoi(s);
	std::getline(fin, S1);
	std::getline(fin, Z1);
	std::getline(fin, S2);
	std::getline(fin, D2);
	std::getline(fin, Z2);
	fin.close();

	int** img_out;
	img_out = new int* [height];
	for (int i = 0; i < height; i++) {
		img_out[i] = new int[width];
		for (int j = 0; j < width; j++) {
			img_out[i][j] = 0;
		}
	}
	cout << endl << "==> AFTER EZW DECODE <==" << endl;
	EZW_decode(img_out, height, width, maxVal, S1, Z1, S2, D2, Z2);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << setw(3) << img_out[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}

int findmax(int** img, int height, int width) {
	int maxnum = img[0][0];
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (img[i][j] > maxnum) {
				maxnum = img[i][j];
			}
		}
	}
	return maxnum;
}

int check_beside(int* FORM1, int FORM_count, int val) {
	for (int i = 1; i < FORM_count; i += 2) {
		if (val >= FORM1[i - 1] && val <= FORM1[i + 1]) {
			return FORM1[i];
		}
	}
}

int find_index(int* arr, int len, int num) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == num) return i;
	}
	return -1;
}

const queue<string> split(const string str, const char delimiter) {
	queue<string> result;
	std::stringstream ss(str);
	std::string tok;
	
	while (std::getline(ss, tok, delimiter)) {
		result.push(tok);
	}
	return result;
}

void EZW_encode(int** img, int height, int width, int& maxVal, string& S1, string& Z1, string& S2, string& D2, string& Z2) {
	// ==> initial <==
	// init the status table
	CSTATUS** status = new CSTATUS * [height];	// record the CSTATUS of img
	for (int i = 0; i < height; i++) {
		status[i] = new CSTATUS[width];
		for (int j = 0; j < width; j++) {
			status[i][j] = CSTATUS::NONE;
		}
	}

	// build the zero-tree for record the coordinate of the img table
	tree_pointer root = new tnode(0, 0);
	root->child_2 = new tnode(0, 1);
	root->child_3 = new tnode(1, 0);
	root->child_4 = new tnode(1, 1);

	derivative(root->child_2, height / 2);
	derivative(root->child_3, height / 2);
	derivative(root->child_4, height / 2);
	//print_tree(root, img);
	
	// STEP 1: Convert IMG from Time Domain to Freq Domain
	
	// ==> START EZW encode <==

	// ==> First time <==

	// STEP 2: setting thershold T0
	// T0 = 2 ^ M
	// M = floor(log2(max(wij)))
	int T0, R0;
	int M;

	//maxVal = findmax(img, height, width);
	maxVal = img[0][0]; // always at the left up most of the img
	M = floor(log2(double(maxVal)));
	T0 = pow(2, M);

	// STEP 3: setting Rebuild Value R0
	// R0 = (max(wij) + T0) / 2
	R0 = (maxVal + T0) / 2;

	// STEP 4: scan with Z-shape and find out all the status of zero-tree
	check_all(root, img, status, T0, S1);

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << setw(3) << GET_CSTATUS_NAME(status[i][j]) << "\t";
		}
		cout << endl;
	}*/

	// STEP 5: Refining the Rebuild Value table and find out Z1
	// i.e. [32, 46, 60] -> [32, 39, 46, 53, 60]

	int* RVtable1, * buff;
	int RVtable1_count = 3;

	RVtable1 = new int[RVtable1_count];
	RVtable1[0] = T0;
	RVtable1[1] = R0;
	RVtable1[2] = maxVal;

	buff = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i++) {
		buff[i] = RVtable1[i];
	}
	delete[]RVtable1;
	RVtable1_count = RVtable1_count * 2 - 1;
	RVtable1 = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i += 2) {
		RVtable1[i] = buff[i / 2];
	}
	for (int i = 1; i < RVtable1_count; i += 2) {
		RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
	}
	delete[]buff;
	/*for (int i = 0; i < RVtable1_count; i++) {
		cout << RVtable1[i] << ' ';
	}
	cout << endl;*/

	// STEP 6: Refining the Rebuild Value table
	// D1 = NULL , cause first time

	// STEP 7: reset the POS and NEG value 
	// wij <- wij - the Rebuild Value of wij after refining
	
	// W1 will record the node for refining again in second time
	vector<int> W1; 

	queue<tree_pointer> q;
	q.push(root);
	while (q.empty() == false) {
		tree_pointer node = q.front();
		if (!(node->x == -1 && node->y == -1)) {
			if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
				W1.push_back(img[node->y][node->x]);
				Z1 = abs(img[node->y][node->x]) >= RVtable1[int(RVtable1_count / 2)] ? Z1 + "1" : Z1 + "0";

				if (status[node->y][node->x] == CSTATUS::POS) {
					int minus = check_beside(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
					img[node->y][node->x] = img[node->y][node->x] - minus;
				}
				else {
					int minus = check_beside(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
					img[node->y][node->x] = img[node->y][node->x] + minus;
				}
			}
		}
		q.pop();
		if (node->child_1 != nullptr)
			q.push(node->child_1);
		if (node->child_2 != nullptr)
			q.push(node->child_2);
		if (node->child_3 != nullptr)
			q.push(node->child_3);
		if (node->child_4 != nullptr)
			q.push(node->child_4);
	}

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << setw(3) << img[i][j] << "\t";
		}
		cout << endl;
	}*/

	// ==> Second time <==
	
	// clean the status table
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			status[i][j] = CSTATUS::NONE;
		}
	}

	// STEP 2: setting thershold T1
	// T1 = T0 / 2
	int T1;
	T1 = round((float)T0 / 2);

	// STEP 3: setting Rebuild Value R1
	// R1 = R0 / 2
	int R1;
	R1 = round((float)R0 / 2);

	// STEP 4: scan with Z-shape and find out all the status of zero-tree
	check_all(root, img, status, T1, S2);

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << setw(3) << GET_CSTATUS_NAME(status[i][j]) << "\t";
		}
		cout << endl;
	}*/

	// STEP 5: Refining the Rebuild Value table and find out Z1
	// i.e. [32, 46, 60] -> [32, 39, 46, 53, 60]

	int* RVtable2;
	int RVtable2_count = 3;

	RVtable2 = new int[RVtable2_count];
	RVtable2[0] = T1;
	RVtable2[1] = R1;
	RVtable2[2] = T0;

	for (int i = 0; i < 1; i++) {
		buff = new int[RVtable2_count];
		for (int i = 0; i < RVtable2_count; i++) {
			buff[i] = RVtable2[i];
		}
		delete[]RVtable2;
		RVtable2_count += 2;
		RVtable2 = new int[RVtable2_count];
		for (int i = 0; i < RVtable2_count; i += 2) {
			RVtable2[i] = buff[i / 2];
		}
		for (int i = 1; i < RVtable2_count; i += 2) {
			RVtable2[i] = round(((float)RVtable2[i - 1] + (float)RVtable2[i + 1]) / 2);
		}
		delete[]buff;
		/*for (int i = 0; i < RVtable2_count; i++) {
			cout << RVtable2[i] << ' ';
		}
		cout << endl;*/
	}

	// STEP 6: Refining the Rebuild Value table RVtable and get D2

	buff = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i++) {
		buff[i] = RVtable1[i];
	}
	delete[]RVtable1;
	RVtable1_count = RVtable1_count * 2 - 1;
	RVtable1 = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i += 2) {
		RVtable1[i] = buff[i / 2];
	}
	for (int i = 1; i < RVtable1_count; i += 2) {
		RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
	}
	delete[]buff;
	/*for (int i = 0; i < RVtable1_count; i++) {
		cout << RVtable1[i] << ' ';
	}
	cout << endl;*/
	
	string::iterator its = Z1.begin();

	for (vector<int>::iterator it = W1.begin(); it != W1.end(); it++) {
		int n = *it;
		int minus = check_beside(RVtable1, RVtable1_count, abs(n));
		if (*its == '0') {
			D2 = abs(n) >= RVtable1[int(RVtable1_count / 4)] ? D2 + "1" : D2 + "0";
		}
		else {
			D2 = abs(n) >= RVtable1[int(RVtable1_count * 3 / 4)] ? D2 + "1" : D2 + "0";
		}
	}

	// STEP 7: find out Z2

	// clear queue
	while (!q.empty()) {
		q.pop();
	};
	q.push(root);
	while (q.empty() == false) {
		tree_pointer node = q.front();
		if (!(node->x == -1 && node->y == -1)) {
			if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
				Z2 = abs(img[node->y][node->x]) > RVtable2[int(RVtable2_count / 2)] ? Z2 + "1" : Z2 + "0";
			}
		}
		q.pop();
		if (node->child_1 != nullptr)
			q.push(node->child_1);
		if (node->child_2 != nullptr)
			q.push(node->child_2);
		if (node->child_3 != nullptr)
			q.push(node->child_3);
		if (node->child_4 != nullptr)
			q.push(node->child_4);
	}

	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		cout << setw(3) << img[i][j] << "\t";
	//	}
	//	cout << endl;
	//}

	// free memory
	delete[] RVtable1;
	delete[] RVtable2;
	for (int i = 0; i < height; i++) {
		delete status[i];
	}
}

void EZW_decode(int** img, int height, int width, int maxVal, string S1, string Z1, string S2, string D2, string Z2) {
	// initial
	
	// init the status table
	CSTATUS** status = new CSTATUS * [height];	// record the CSTATUS of img
	for (int i = 0; i < height; i++) {
		status[i] = new CSTATUS[width];
		for (int j = 0; j < width; j++) {
			status[i][j] = CSTATUS::NONE;
		}
	}
	// build the zero-tree for record the coordinate of the img table
	tree_pointer root = new tnode(0, 0);
	root->child_2 = new tnode(0, 1);
	root->child_3 = new tnode(1, 0);
	root->child_4 = new tnode(1, 1);

	derivative(root->child_2, height / 2);
	derivative(root->child_3, height / 2);
	derivative(root->child_4, height / 2);
	//print_tree(root, img);
	
	// ==> first time <==

	// STEP 1: init img with zero
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img[i][j] = 0;
		}
	}

	// STEP 2: find out thershold T0
	int T0;
	int M;

	M = floor(log2(double(maxVal)));
	T0 = pow(2, M);

	// STEP 3: find out the Rebuild Value table
	int R0;
	R0 = (maxVal + T0) / 2;
	int* RVtable1, * buff;
	int RVtable1_count = 3;

	RVtable1 = new int[RVtable1_count];
	RVtable1[0] = T0;
	RVtable1[1] = R0;
	RVtable1[2] = maxVal;

	buff = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i++) {
		buff[i] = RVtable1[i];
	}
	delete[]RVtable1;
	RVtable1_count = RVtable1_count * 2 - 1;
	RVtable1 = new int[RVtable1_count];
	for (int i = 0; i < RVtable1_count; i += 2) {
		RVtable1[i] = buff[i / 2];
	}
	for (int i = 1; i < RVtable1_count; i += 2) {
		RVtable1[i] = round(((float)RVtable1[i - 1] + (float)RVtable1[i + 1]) / 2);
	}
	delete[]buff;
	
	// STEP 4: Scan the img with S1
	queue<string> queueS1 = split(S1, ' ');
	
	//// if print out, queue will become NULL
	//while (!queueS1.empty()) {
	//	cout << queueS1.front() << endl;
	//	queueS1.pop();
	//}

	check_all_decode(root, img, status, queueS1, R0);
	
	// STEP 5: refining with Z1
	string::iterator its = Z1.begin();

	// record the node for refining again
	vector<tree_pointer> Wz1;

	queue<tree_pointer> q;
	q.push(root);
	while (q.empty() == false && its != Z1.end()) {
		tree_pointer node = q.front();
		if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
			Wz1.push_back(node);
			char c = *its;
			int num;
			if (c == '1') {
				num = RVtable1[int(RVtable1_count / 2) + 1];
			}
			else {
				num = RVtable1[int(RVtable1_count / 2) - 1];
			}
			img[node->y][node->x] = img[node->y][node->x] > 0 ? num : -1 * num;
			its++;
		}
		q.pop();
		if (node != nullptr) {
			if (node->child_1 != nullptr)
				q.push(node->child_1);
			if (node->child_2 != nullptr)
				q.push(node->child_2);
			if (node->child_3 != nullptr)
				q.push(node->child_3);
			if (node->child_4 != nullptr)
				q.push(node->child_4);
		}
	}

	// STEP 6: process with D1
	// But D1 = NULL, SKIP

	// ==> second time <==

	// clear the status table
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			status[i][j] = CSTATUS::NONE;
		}
	}

	// STEP 2: find out thershold T1
	int T1;

	T1 = floor((float)T0 / 2);

	// STEP 3: find out the Rebuild Value table
	int R1;
	R1 = floor((float)R0 / 2);
	int* RVtable2;
	int RVtable2_count = 3;

	RVtable2 = new int[RVtable2_count];
	RVtable2[0] = T1;
	RVtable2[1] = R1;
	RVtable2[2] = T0;

	buff = new int[RVtable2_count];
	for (int i = 0; i < RVtable2_count; i++) {
		buff[i] = RVtable2[i];
	}
	delete[]RVtable2;
	RVtable2_count = RVtable2_count * 2 - 1;
	RVtable2 = new int[RVtable2_count];
	for (int i = 0; i < RVtable2_count; i += 2) {
		RVtable2[i] = buff[i / 2];
	}
	for (int i = 1; i < RVtable2_count; i += 2) {
		RVtable2[i] = round(((float)RVtable2[i - 1] + (float)RVtable2[i + 1]) / 2);
	}
	delete[]buff;

	// STEP 4: Scan the img with S2
	queue<string> queueS2 = split(S2, ' ');

	//// if print out, queue will become NULL
	//while (!queueS2.empty()) {
	//	cout << queueS2.front() << endl;
	//	queueS2.pop();
	//}

	check_all_decode(root, img, status, queueS2, R1);

	// STEP 5: refining with Z2
	its = Z2.begin();

	// clear queue
	while (!q.empty()) {
		q.pop();
	};
	q.push(root);
	while (q.empty() == false && its != Z2.end()) {
		tree_pointer node = q.front();
		if (status[node->y][node->x] == CSTATUS::POS || status[node->y][node->x] == CSTATUS::NEG) {
			char c = *its;
			int num;
			if (c == '1') {
				num = RVtable2[int(RVtable2_count / 2) + 1];
			}
			else {
				num = RVtable2[int(RVtable2_count / 2) - 1];
			}
			img[node->y][node->x] = img[node->y][node->x] > 0 ? num : -1 * num;
			its++;
		}
		q.pop();
		if (node != nullptr) {
			if (node->child_1 != nullptr)
				q.push(node->child_1);
			if (node->child_2 != nullptr)
				q.push(node->child_2);
			if (node->child_3 != nullptr)
				q.push(node->child_3);
			if (node->child_4 != nullptr)
				q.push(node->child_4);
		}
	}

	// STEP 6: refining with D2
	its = D2.begin();

	for (vector<tree_pointer>::iterator it = Wz1.begin(); it != Wz1.end(); it++) {
		tree_pointer node = *it;
		char c = *its;
		int index = find_index(RVtable1, RVtable1_count, abs(img[node->y][node->x]));
		if (c == '1') {
			if (img[node->y][node->x] > 0) img[node->y][node->x] = round(((float)RVtable1[index] + (float)RVtable1[index + 1]) / 2);
			else img[node->y][node->x] = -1 * round(((float)RVtable1[index] + (float)RVtable1[index + 1]) / 2);
		}
		else {
			if (img[node->y][node->x] > 0) img[node->y][node->x] = round(((float)RVtable1[index] + (float)RVtable1[index - 1]) / 2);
			else img[node->y][node->x] = -1 * round(((float)RVtable1[index] + (float)RVtable1[index - 1]) / 2);
		}
		its++;
	}

	// free memory
	delete[] RVtable1;
	delete[] RVtable2;
	for (int i = 0; i < height; i++) {
		delete status[i];
	}

}