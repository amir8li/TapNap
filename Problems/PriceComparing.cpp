#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int key, freq;
    int height, size;
    Node *left, *right;
    Node(int k) : key(k), freq(1), height(1), size(1), left(NULL), right(NULL) {}
};

int getHeight(Node* n){ return n ? n->height : 0; }
int getSize(Node* n){ return n ? n->size : 0; }

void update(Node* n){
    if(!n) return;
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    n->size = n->freq + getSize(n->left) + getSize(n->right);
}

int balanceFactor(Node* n){
    return getHeight(n->left) - getHeight(n->right);
}

class AvlTree{
public:
    Node* root;
    AvlTree(){ root = NULL; }

    Node* rotateRight(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        update(y);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        update(x);
        update(y);
        return y;
    }

    Node* rebalance(Node* n){
        update(n);
        int bf = balanceFactor(n);
        if(bf > 1){
            if(balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if(bf < -1){
            if(balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insert(Node* node, int key){
        if(!node) return new Node(key);
        if(key == node->key) node->freq++;
        else if(key < node->key) node->left = insert(node->left, key);
        else node->right = insert(node->right, key);
        return rebalance(node);
    }

    int rankLE(Node* node, int val){
        if(!node) return 0;
        if(val < node->key) return rankLE(node->left, val);
        return getSize(node->left) + node->freq + rankLE(node->right, val);
    }
};

int main(){
    int q;
    cin >> q;
    AvlTree tree;

    while(q--){
        int type;
        long long value;
        cin >> type >> value;
        if(type == 1)
            tree.root = tree.insert(tree.root, value);
        else
            cout << tree.rankLE(tree.root, value) << "\n";
    }
    return 0;
}