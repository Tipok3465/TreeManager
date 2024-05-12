#pragma once

#include "../header.h"


class RBTree {
public:
    enum Color { RED, BLACK };
    struct Node {
        int data;
        Color color;
        Node *left;
        Node *right;
        Node *parent;
        int x, y;
        void setPos(int x, int y);

    };

private:
    Node *root;
    Node* find(Node *node, int key);
    void fixDelete(Node *x);
    void rbTransplant(Node *u, Node *v);
    void deleteNode(Node *node, int key);
    void fixInsert(Node *k);
    static void drawTree(Node *x, QGraphicsScene *&scene);

public:
    RBTree();
    Node* contains(int k);
    void clickDelete(Node *cur, int x, int y);
    static void render(QGraphicsScene *scene, Node *_root);
    Node *minimum(Node *node);
    Node *maximum(Node *node);
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insert(int key);
    Node *getRoot();
    void deleteNode(int data);

};