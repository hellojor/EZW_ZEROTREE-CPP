#ifndef ZEROTREE_H
#define ZEROTREE_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <queue>

#include "CStatus.h"

using std::cout;
using std::endl;
using std::setw;
using std::queue;

typedef struct tnode* tree_pointer;
struct tnode {
	int x, y;
	tree_pointer child_1, child_2, child_3, child_4;

	tnode(int y, int x)
		:x(x), y(y), child_1(nullptr), child_2(nullptr), child_3(nullptr), child_4(nullptr) {};

	void show(int val = 0) {
		cout << "(" << setw(1) << y << ", " << setw(1) << x << ") [" << setw(3) << val << "] -> ";
	}
};

void derivative(tree_pointer r, int count) {
	tree_pointer root = r;
	if (count < 2 || root == nullptr) return;

	// derivative to become Quaternary zero-ree

	if (root->x == 0 && root->y == 0) // (0, 0) don't to derivative
		return;
	root->child_1 = new tnode(root->y * 2, root->x * 2);
	root->child_2 = new tnode(root->y * 2, root->x * 2 + 1);
	root->child_3 = new tnode(root->y * 2 + 1, root->x * 2);
	root->child_4 = new tnode(root->y * 2 + 1, root->x * 2 + 1);

	derivative(root->child_1, count / 2);
	derivative(root->child_2, count / 2);
	derivative(root->child_3, count / 2);
	derivative(root->child_4, count / 2);

}

void ZTR_chain(tree_pointer root, CSTATUS** status) {
	if (root == nullptr) return;

	// make all child become ZTR

	if (root->child_1 != nullptr) status[root->child_1->y][root->child_1->x] = CSTATUS::ZTR;
	if (root->child_2 != nullptr) status[root->child_2->y][root->child_2->x] = CSTATUS::ZTR;
	if (root->child_3 != nullptr) status[root->child_3->y][root->child_3->x] = CSTATUS::ZTR;
	if (root->child_4 != nullptr) status[root->child_4->y][root->child_4->x] = CSTATUS::ZTR;

	if (root->child_1 != nullptr) ZTR_chain(root->child_1, status);
	if (root->child_2 != nullptr) ZTR_chain(root->child_2, status);
	if (root->child_3 != nullptr) ZTR_chain(root->child_3, status);
	if (root->child_4 != nullptr) ZTR_chain(root->child_4, status);

}

// =======================================================================================================================================
// encode


bool check_subtree(tree_pointer root, int** img, int T) {
	if (root == nullptr) return false;
	bool s1 = false;
	bool s2 = false;
	bool s3 = false;
	bool s4 = false;
	bool s5 = false;
	bool s6 = false;
	bool s7 = false;
	bool s8 = false;

	if (root->child_1 != nullptr) s1 = (img[root->child_1->y][root->child_1->x] >= T);
	if (root->child_2 != nullptr) s2 = (img[root->child_2->y][root->child_2->x] >= T);
	if (root->child_3 != nullptr) s3 = (img[root->child_3->y][root->child_3->x] >= T);
	if (root->child_4 != nullptr) s4 = (img[root->child_4->y][root->child_4->x] >= T);

	if (root->child_1 != nullptr) s5 = check_subtree(root->child_1, img, T);
	if (root->child_2 != nullptr) s6 = check_subtree(root->child_2, img, T);
	if (root->child_3 != nullptr) s7 = check_subtree(root->child_3, img, T);
	if (root->child_4 != nullptr) s8 = check_subtree(root->child_4, img, T);

	// any child or sub-child >= threshold ?

	return s1 | s2 | s3 | s4 | s5 | s6 | s7 | s8;
}

void check_status(tree_pointer root, int** img, CSTATUS** status, int T0, string& S1) {
	if (status[root->y][root->x] == CSTATUS::ZTR) { // SKIP the ZTR
		return;
	}

	// POS: wij > 0 and abs(wij) >= threshold
	// NEG: wij < 0 and abs(wij) >= threshold
	// ZTR: abs(wij) < threshold and all the child of subtree < threshold
	// HZ : abs(wij) >= threshold and one of the child of subtree >= threshold

	if (abs(img[root->y][root->x]) >= T0) {
		if (img[root->y][root->x] > 0)
			status[root->y][root->x] = CSTATUS::POS;
		else
			status[root->y][root->x] = CSTATUS::NEG;
	}
	else {
		status[root->y][root->x] = check_subtree(root, img, T0) ? CSTATUS::HZ : CSTATUS::ZTR; // check any val of subtree >= T ?

		// if a node is ZTR, then make its childs become ZTR too
		if (status[root->y][root->x] == CSTATUS::ZTR) { // make all the subtree become ZTR
			ZTR_chain(root, status);
		}
	}
	S1 += (GET_CSTATUS_NAME(status[root->y][root->x]) + " ");
	/*cout << GET_CSTATUS_NAME(status[root->y][root->x]) << "\t";
	root->show();
	cout << endl;*/
}

void check_all(tree_pointer root, int** img, CSTATUS** status, int T0, string& S1) {
	if (root == nullptr) return;
	
	// using BFS Algorithm to scan the zero-tree with Z-shape

	queue<tree_pointer> q;
	q.push(root);
	while (q.empty() == false) {
		tree_pointer node = q.front();
		if (node != nullptr) check_status(node, img, status, T0, S1);
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
}

// =======================================================================================================================================
// decode

void check_status_decode(tree_pointer root, int** img, CSTATUS** status, queue<string>& queueS1, int R0) {
	// POS: wij = R0
	// NEG: wij = R0
	// ZTR: wij = 0 and all the child of subtree = 0
	// HZ : wij = 0
	string s = queueS1.front();
	
	if (s == "POS") {
		status[root->y][root->x] = CSTATUS::POS;
		if (img[root->y][root->x] == 0) img[root->y][root->x] = R0;
	}
	else if (s == "NEG") {
		status[root->y][root->x] = CSTATUS::NEG;
		if (img[root->y][root->x] == 0) img[root->y][root->x] = -1 * R0;
	}
	else if (s == "HZ") {
		status[root->y][root->x] = CSTATUS::HZ;
		if (img[root->y][root->x] == 0) img[root->y][root->x] = 0;
	}
	else {
		status[root->y][root->x] = CSTATUS::ZTR;
		if (img[root->y][root->x] == 0) img[root->y][root->x] = 0;
		ZTR_chain(root, status);
	}
	queueS1.pop();
}

void check_all_decode(tree_pointer root, int** img, CSTATUS** status, queue<string>& queueS1, int R0) {
	if (root == nullptr) return;

	// using BFS Algorithm to scan the zero-tree with Z-shape

	queue<tree_pointer> q;
	q.push(root);
	while (q.empty() == false && queueS1.empty() == false) {
		tree_pointer node = q.front();
		if (node != nullptr && status[node->y][node->x] == CSTATUS::NONE) {
			check_status_decode(node, img, status, queueS1, R0);
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
}


#endif // !1

