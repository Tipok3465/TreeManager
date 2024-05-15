#include "../header.h"

#pragma once

class Splay {
public:
    struct Node {
        int64_t value;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        int x, y;
        void setPos(int x, int y);
    };
private:
    Node *root;
    Node *find(Splay::Node *node, int64_t key);
    void remove(Splay::Node *node, int64_t key);
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void splay(Node *x);
    Node *join(Node *s, Node *t);
    void split(Node *&x, Node *&s, Node *&t);
public:
    Splay();
    void deleteTree(Node *cur);
    ~Splay();
    void clickDelete(Node *cur, int x, int y);
    Node *contains(int64_t k);
    static Node *maximum(Node *node);
    void insert(int64_t key);
    Node *getRoot();
    void deleteNode(int64_t data);
    static void render(QGraphicsScene *scene, Node *root);
    void delAllTree();
};
