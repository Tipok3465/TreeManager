#include "RBTree.h"

RBTree::Node* NULLPTR = nullptr;

RBTree::RBTree() {
    NULLPTR = new Node;
    NULLPTR->color = BLACK;
    NULLPTR->left = nullptr;
    NULLPTR->right = nullptr;
    root = NULLPTR;
}

void RBTree::deleteTree(RBTree::Node *cur) {
    if (!cur) return;
    deleteTree(cur->left);
    deleteTree(cur->right);
    delete cur;
}

RBTree::~RBTree() {
    deleteTree(root);
}

RBTree::Node* RBTree::find(Node *node, int64_t key) {
    if (node == NULLPTR) {
        return nullptr;
    }
    if (key == node->value) {
        return node;
    }
    if (key < node->value) {
        return find(node->left, key);
    }
    return find(node->right, key);
}

void RBTree::fixDelete(Node *x) {
    Node * s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}


void RBTree::rbTransplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RBTree::Node* RBTree::contains(int64_t k) {
    return find(this->root, k);
}

RBTree::Node *RBTree::maximum(RBTree::Node *node) {
    while (node->right != NULLPTR) {
        node = node->right;
    }
    return node;
}

void RBTree::remove(Node *node, int64_t key) {
    Node* z = NULLPTR;
    Node* x, *y;
    while (node != NULLPTR) {
        if (node->value == key) {
            z = node;
        }
        if (node->value <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (z == NULLPTR) {
        return;
    }
    y = z;
    int64_t y_color = y->color;
    if (z->left == NULLPTR) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == NULLPTR) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = maximum(z->left);
        y_color = y->color;
        x = y->left;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }

        rbTransplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
    }
    delete z;
    z = nullptr;
    if (y_color == BLACK) {
        fixDelete(x);
    }
}

void RBTree::fixInsert(Node *k) {
    Node* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}


void RBTree::leftRotate(Node *x) {
    Node * y = x->right;
    x->right = y->left;
    if (y->left != NULLPTR) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULLPTR) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RBTree::insert(int64_t key) {
    if (this->contains(key)) return;
    Node *node = new Node;
    node->parent = nullptr;
    node->value = key;
    node->left = NULLPTR;
    node->right = NULLPTR;
    node->color = RED;

    Node *y = nullptr;
    Node *x = this->root;

    while (x != NULLPTR) {
        y = x;
        if (node->value < x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->value < y->value) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}

RBTree::Node *RBTree::getRoot() {
    return this->root;
}


void treeFilling(RBTree::Node *&x, int64_t dl) {
    if (x == nullptr || x == NULLPTR) return;
    if (x->left) x->left->x -= dl;
    if (x->right) x->right->x -= dl;
    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(RBTree::Node *x, int mx) {
    if (x == nullptr || x == NULLPTR) return mx;
    mx = std::max(x->x + 50, max_right(x->right, mx));
    mx = std::max(x->x + 50, max_right(x->left, mx));
    return mx;
}

int max_left(RBTree::Node *x, int mx) {
    if (x == nullptr || x == NULLPTR) return mx;
    mx = std::min(x->x, max_left(x->right, mx));
    mx = std::min(x->x, max_left(x->left, mx));
    return mx;
}

void posRecalc(RBTree::Node *&x) {
    if (x == nullptr || x == NULLPTR) return;

    posRecalc(x->left);
    posRecalc(x->right);
    int64_t mr = max_right(x->left, -1e6), ml = max_left(x->right, 1e6);

    int64_t delta = (mr == -1e6 || ml == 1e6 ? 0 : ml - mr);
    if (delta < 0) {
        if (x->left)
            x->left->x -= (abs(delta) / 2 + 25);
        if (x->right)
            x->right->x += (abs(delta) / 2 + 25);

        treeFilling(x->left, (abs(delta) / 2 + 25));
        treeFilling(x->right, -(abs(delta) / 2 + 25));
    }

}

void fixPosition(RBTree::Node *&x) {
    if (x == nullptr || x == NULLPTR) return;
    if (x->parent == nullptr) {
        x->x = -25;
        x->y = -250;
    } else {
        if (x->parent->left == x) {
            x->setPos(x->parent->x - 75, x->parent->y + 250);
        } else {
            x->setPos(x->parent->x + 75, x->parent->y + 250);

        }
    }
    if (x == x->left || x == x->right || x == x->left) exit(-1);
    fixPosition(x->left);
    fixPosition(x->right);
}

void recalc(RBTree::Node *&x) {
    fixPosition(x);
    posRecalc(x);
}

void RBTree::drawTree(Node *x, QGraphicsScene *&scene) {
    if (!x || x == NULLPTR) return;
    auto *ellipse = new QGraphicsEllipseItem(x->x, x->y, 50, 50);
    QPen *pen = new QPen(Qt::black);
    if (x->color == RED) {
        pen->setColor(Qt::red);
        pen->setWidth(1);
    } else {
        pen->setColor(Qt::black);
        pen->setWidth(1);
    }
    ellipse->setPen(*pen);
    if (x->color == RED) {
        ellipse->setBrush(QBrush(QColor(244, 72, 119)));
    } else {
        ellipse->setBrush(QBrush(QColor(99,99,99)));
    }
    ellipse->setZValue(2);
    auto *text = new QGraphicsTextItem(QString::number(x->value));
    text->setZValue(3);
    if (QString::number(x->value).size() <= 5)
        text->setFont(QFont("Rockwell", 13));
    else if (QString::number(x->value).size() <= 7)
        text->setFont(QFont("Rockwell", 11));
    else if (QString::number(x->value).size() <= 10)
        text->setFont(QFont("Rockwell", 9));
    else if (QString::number(x->value).size() <= 13)
        text->setFont(QFont("Rockwell", 7));
    else
        text->setFont(QFont("Rockwell", 5));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center());
    scene->addItem(ellipse);
    scene->addItem(text);
    if (x->parent) {
        auto *line = new QGraphicsLineItem(x->parent->x + 50 / 2.0,
                                           x->parent->y + 50 / 2.0,
                                           x->x + 50 / 2.0,
                                           x->y + 50 / 2.0);
        line->setZValue(1);
        auto uu = QPen(QColor(200, 200, 200));
        uu.setWidth(2);
        line->setPen(uu);
        scene->addItem(line);
    }
    drawTree(x->left, scene);
    drawTree(x->right, scene);

}


void RBTree::render(QGraphicsScene *scene, Node *_root) {
    scene->clear();
    for (int i = -100000; i <= 100000; i += 25)
    {
        scene->addLine(i, -100000, i, 100000);
    }
    for (int i = -100000; i <= 100000; i += 25) {
        scene->addLine(-100000, i, 100000, i);
    }
    recalc(_root);
    drawTree(_root, scene);

}

void RBTree::Node::setPos(int _x, int _y) {
    x = _x;
    y = _y;
}

void RBTree::clickDelete(Node *cur, int x, int y) {
    if (!cur && cur != NULLPTR) return;
    if (x > cur->x && x < cur->x + 50 && y > cur->y && y < cur->y + 50) {
        this->deleteNode(cur->value);
    } else {
        clickDelete(cur->left, x, y);
        clickDelete(cur->right, x, y);
    }
}

void RBTree::deleteNode(int64_t data) {
    remove(this->root, data);
}

void RBTree::delAllTree() {
    while(root != nullptr && root != NULLPTR) {
        remove(root, root->value);
    }
}
