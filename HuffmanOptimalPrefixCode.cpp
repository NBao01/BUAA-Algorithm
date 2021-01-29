//
// Created by NBao on 2021/01/29.
//

#include <iostream>
#include <queue>

#define N 6

int F[N + 1] = {-1, 45, 13, 12, 16, 9, 5};

class Node {
public:
    int freq;
    Node *left;
    Node *right;
    Node(int freq);
    // friend class cmp;
};

Node::Node(int freq) {
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
}

class cmp {
public:
    bool operator() (const Node *a,const Node *b)
    {
        return a->freq > b->freq;
    }
};

int main() {
    std::priority_queue<Node *, std::vector<Node *>, cmp> Q;
    for (int i = 1; i <= N; i++) {
        Q.push(new Node(F[i]));
    }

    for (int i = 1; i <= N - 1; i++) {
        Node* x = Q.top();
        Q.pop();
        Node* y = Q.top();
        Q.pop();
        Node* z = new Node(x->freq + y->freq);
        z->left = x;
        z->right = y;
        Q.push(z);
    }

    Node* root = Q.top();
    return 0;
}
