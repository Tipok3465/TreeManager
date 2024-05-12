#include "Splay.h"

Splay::Splay() {
    root = nullptr;
}

void Splay::deleteNode(int64_t data) {
    remove(this->root, data);
}

Splay::Node *Splay::getRoot() {
    return this->root;
}

void Splay::insert(int64_t key) {
    auto *node = new Splay::Node;
    node->value = key;
    Splay::Node *y = nullptr;
    Splay::Node *x = this->root;

    while (x != nullptr) {
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
    splay(node);
}

Splay::Node *Splay::maximum(Splay::Node *node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Splay::Node *Splay::contains(int64_t k) {
    Splay::Node *x = find(this->root, k);
    if (x) {
        splay(x);
    }
    return x;
}

void Splay::split(Splay::Node *&x, Splay::Node *&s, Splay::Node *&t) {
    splay(x);
    if (x->right) {
        t = x->right;
        t->parent = nullptr;
    } else {
        t = nullptr;
    }
    s = x;
    s->right = nullptr;
    x = nullptr;
}

Splay::Node *Splay::join(Splay::Node *s, Splay::Node *t) {
    if (!s) {
        return t;
    }
    if (!t) {
        return s;
    }
    Splay::Node *x = maximum(s);
    splay(x);
    x->right = t;
    t->parent = x;
    return x;
}

void Splay::leftRotate(Splay::Node *x) {
    Splay::Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
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

void Splay::rightRotate(Splay::Node *x) {
    Splay::Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
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

void Splay::splay(Splay::Node *x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x == x->parent->left) {
                rightRotate(x->parent);
            } else {
                leftRotate(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
            leftRotate(x->parent);
            rightRotate(x->parent);
        } else {
            rightRotate(x->parent);
            leftRotate(x->parent);
        }
    }
}

void Splay::remove(Splay::Node *node, int64_t key) {
    Splay::Node *x = nullptr;
    Splay::Node *t, *s;
    while (node != nullptr) {
        if (node->value == key) {
            x = node;
        }
        if (node->value <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (x == nullptr) {
        return;
    }
    split(x, s, t);
    if (s->left) {
        s->left->parent = nullptr;
    }
    root = join(s->left, t);
    delete s;
    s = nullptr;
}

Splay::Node *Splay::find(Splay::Node *node, int64_t key) {
    if (node == nullptr || key == node->value) {
        return node;
    }
    if (key < node->value) {
        return find(node->left, key);
    }
    return find(node->right, key);
}


void Splay::Node::setPos(int _x, int _y) {
    x = _x;
    y = _y;
}


void treeFilling(Splay::Node *&x, int dl) {
    if (x == nullptr) return;
    if (x->left) x->left->x -= dl;
    if (x->right) x->right->x -= dl;
    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(Splay::Node *x, int mx) {
    if (x == nullptr) return mx;
    mx = std::max(x->x + 50, max_right(x->right, mx));
    mx = std::max(x->x + 50, max_right(x->left, mx));
    return mx;
}

int max_left(Splay::Node *x, int mx) {
    if (x == nullptr) return mx;
    mx = std::min(x->x, max_left(x->right, mx));
    mx = std::min(x->x, max_left(x->left, mx));
    return mx;
}

void posRecalc(Splay::Node *&x) {
    if (x == nullptr) return;

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

void fixPosition(Splay::Node *&x) {
    if (x == nullptr) return;
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
    fixPosition(x->left);
    fixPosition(x->right);
}

void recalc(Splay::Node *&x) {
    fixPosition(x);
    posRecalc(x);
}

void drawTree(Splay::Node *x, QGraphicsScene *&scene) {
    if (!x) return;
    auto *ellipse = new QGraphicsEllipseItem(x->x, x->y, 50, 50);
    ellipse->setBrush(QBrush(QColor(99,99,99)));
    ellipse->setZValue(2);
    auto *text = new QGraphicsTextItem(QString::number(x->value));
    text->setDefaultTextColor(QColor(255, 255, 255));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center());
    text->setZValue(3);
    text->setFont(QFont("Rockwell", 12));
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


void Splay::render(QGraphicsScene *scene, Node *root) {
    scene->clear();
    for (int i = -100000; i <= 100000; i += 25)
    {
        scene->addLine(i, -100000, i, 100000);
    }
    for (int i = -100000; i <= 100000; i += 25) {
        scene->addLine(-100000, i, 100000, i);
    }
    recalc(root);
    drawTree(root, scene);

}

void Splay::clickDelete(Node *cur, int x, int y) {
    if (!cur) return;
    if (x > cur->x && x < cur->x + 50 && y > cur->y && y < cur->y + 50) {
        this->deleteNode(cur->value);
    } else {
        clickDelete(cur->left, x, y);
        clickDelete(cur->right, x, y);
    }
}