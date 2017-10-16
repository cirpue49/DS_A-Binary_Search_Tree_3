//
//  main.cpp
//  binary_search_tree_1
//
//  Created by 村上候助 on 2017/10/11.
//  Copyright © 2017 村上候助. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <cstdlib>

//#define NIL Nodes a.parent = -1
using namespace std;

struct Node {
    int key;
    Node *parent, *left, *right;
};

Node *nil;
Node *root;


void init(int key){
    nil = (Node *) malloc(sizeof(Node));
    nil->parent = nil->left = nil->right = nil;
    nil->key = -1;
    
    root = (Node *) malloc(sizeof(Node));
    root->key = key;
    root->left = root->right = nil;
}

Node* init_node(int key){
    Node *node = (Node *) malloc(sizeof(Node));
    node->parent = node->left = node->right = nil;
    node->key = key;
    return node;
}

void insert(Node* z){
    Node *y = nil;
    Node *x = root;
    while(x != nil){
        y = x;
        if(z->key  < x->key) x = x->left;
        else x = x->right;
    }
    
    z->parent = y;
    
    if(y==nil) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    
}

void find(Node* x,int key){
    while(x != nil && key != x->key ){
        if(key < x->key) x = x->left;
        else x = x-> right;
    }
    if (x==nil) cout << "no" << endl;
    else cout << "yes" << endl;
}

void in_parse(Node* u){
    if (u->key == -1) return;
    in_parse(u->left);
    cout <<" "<<u->key;
    in_parse(u->right);
}

void pre_order(Node* u){
    if (u->key == -1) return;
    cout <<" "<<u->key;
    pre_order(u->left);
    pre_order(u->right);
}

Node* get_minnimum(Node* x){
    while(x->left != nil) x = x->left;
    return x;
}

Node* get_successor(Node* x){
    if (x->right != nil) return get_minnimum(x->right);

    Node* y;
    y = x->parent;
    while(y != nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}


void delete_node(Node* z, int key){
    while(z != nil && key != z->key ){
        if(key < z->key) z = z->left;
        else z = z-> right;
    }
    Node *y;
    Node *x;
    if(z->left == nil || z->right == nil) y = z;
    else y = get_successor(z);
    
    if(y->left != nil) x = y->left;
    else x = y->right;
    
    if (x != nil) x->parent = y->parent;
    
    if (y->parent == nil) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    
    if(y != z) z->key = y->key;
}


int main(int argc, const char * argv[]) {
    int n, i, key, find_num;
    int ini = 0;
    char command[10];
    scanf("%d", &n);
    //    Node nodes[n];
    for(i = 0; i < n; i++){
        scanf("%s", command);
        if(command[0] == 'p'){
            in_parse(root);
            cout <<endl;
            pre_order(root);
            cout<<endl;
            ini ++;
        }
        else if(command[0] == 'f') {
            scanf("%d", &find_num);
            find(root, find_num);
        }
        else if(command[0] == 'd'){
            scanf("%d", &find_num);
            delete_node(root, find_num);
        }
        else{
            scanf("%d", &key);
            if(i==ini) init(key);
            else {
                Node* z = init_node(key);
                insert(z);
            }
        }
    }
    return 0;
}


