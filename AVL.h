#pragma once

#include "../header.h"

class AVL {
public:
    class Node {
    public:
        int64_t x, y;
        int64_t value;
        int64_t height;

        Node *left;
        Node *right;
        Node *parent;

        void setPos(int64_t, int64_t);

        explicit Node(int64_t value);
    };

    AVL();

    ~AVL();

    void insert(int64_t value);

    void remove(int64_t value);

    bool contains(int64_t value);

    static void render(QGraphicsScene *scene, Node *root);

    [[nodiscard]] Node *getRoot() const;

    void clickDelete(Node *cur, int64_t x, int64_t y);


private:
    Node *root_;

    void fixHeight(Node *p);

    int64_t heightDif(Node *p);

    Node *rotateLeft(Node *node);

    Node *rotateRight(Node *node);

    Node *balance(Node *node);

    void insert(Node *&node, Node *, int64_t value);

    void remove(Node *&node, int64_t value);

    bool contains(Node *node, int64_t value);

    void deleteTree(Node *node);
};

