#include "Treap.h"

Treap::Node *Treap::find(Node *node, int64_t key) {
    if (node == nullptr || key == node->value) {
        return node;
    }
    if (key < node->value) {
        return find(node->left, key);
    }
    return find(node->right, key);
}

Treap::Treap() {
    root = nullptr;
}

Treap::Node *Treap::contains(int64_t k) {
    return find(this->root, k);
}

void Treap::insert(int64_t key, int64_t prior) {
    Node *node = new Node;
    node->value = key;
    node->priority = prior;
    insert(root, node);
}

void Treap::split(Treap::Node* t, int key, Treap::Node* &lhs, Treap::Node*& rhs) {
    if (t == nullptr) {
        lhs = nullptr;
        rhs = nullptr;
    } else if (key < t->value) {
        split(t->left, key, lhs, t->left);
        rhs = t;
    } else {
        split(t->right, key, t->right, rhs);
        lhs = t;
    }
}

void Treap::merge(Treap::Node*& t, Treap::Node* left, Treap::Node* right) {
    if (left == nullptr || right == nullptr) {
        if (left != nullptr) {
            t = left;
        } else {
            t = right;
        }
    } else if (left->priority > right->priority) {
        merge(left->right, left->right, right);
        t = left;
    } else {
        merge(right->left, left, right->left);
        t = right;
    }
}

bool is_in_treap(Treap::Node* tree, Treap::Node* cur) {
    if (tree == nullptr)
        return false;
    if (tree->value == cur->value) {
        return true;
    } else if (tree->value < cur->value) {
        return is_in_treap(tree->right, cur);
    } else {
        return is_in_treap(tree->left, cur);
    }
}

void Treap::insert(Treap::Node*& t, Treap::Node* it) {
    if (is_in_treap(t, it))
        return;
    if (t == nullptr) {
        t = it;
    }
    else if (it->priority > t->priority) {
        split(t, it->value, it->left, it->right);
        t = it;
    } else {
        if (it->value < t->value) {
            insert(t->left, it);
        } else {
            insert(t->right, it);
        }
    }
}

void Treap::remove(Node*& t, int key) {
    if (t->value == key) {
        merge(t, t->left, t->right);
    } else {
        remove(key < t->value ? t->left : t->right, key);
    }
}

Treap::Node *Treap::getRoot() {
    return this->root;
}

void Treap::deleteNode(int64_t data) {
    remove(root, data);
}


void Treap::Node::setPos(int64_t _x, int64_t _y) {
    x = _x;
    y = _y;
}


void treeFilling(Treap::Node *&x, int64_t dl) {
    if (x == nullptr) return;

    if (x->left) x->left->x -= dl;
    if (x->right) x->right->x -= dl;

    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(Treap::Node *x, int mx) {
    if (x == nullptr) return mx;
    mx = std::max(x->x + 50, max_right(x->right, mx));
    mx = std::max(x->x + 50, max_right(x->left, mx));
    return mx;
}

int max_left(Treap::Node *x, int mx) {
    if (x == nullptr) return mx;
    mx = std::min(x->x, max_left(x->right, mx));
    mx = std::min(x->x, max_left(x->left, mx));
    return mx;
}

void posRecalc(Treap::Node *&x) {
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

void seekParent(Treap::Node* x, Treap::Node* par = nullptr) {
    if (x == nullptr) return;
    x->parent = par;
    seekParent(x->left, x);
    seekParent(x->right, x);
}

void fixPosition(Treap::Node *&x) {
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

void recalc(Treap::Node *&x) {
    seekParent(x);
    fixPosition(x);
    posRecalc(x);
}

void drawTree(Treap::Node *x, QGraphicsScene *&scene) {
    if (!x) return;
    auto *ellipse = new QGraphicsEllipseItem(x->x, x->y, 50, 50);
    ellipse->setZValue(2);
    ellipse->setBrush(QBrush(QColor(99,99,99)));
    auto *text = new QGraphicsTextItem(QString::number(x->value));
    text->setZValue(3);
    text->setFont(QFont("Rockwell", 12));
    text->setDefaultTextColor(QColor(255, 255, 255));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center() - QPointF(0, 8));
    auto *textPrior = new QGraphicsTextItem(QString::number(x->priority));
    textPrior->setZValue(3);
    textPrior->setFont(QFont("Rockwell", 10));
    textPrior->setPos(ellipse->boundingRect().center() - textPrior->boundingRect().center() + QPointF(0, 8));

    scene->addItem(ellipse );
    scene->addItem(text);
    scene->addItem(textPrior);

    if (x->parent) {
        auto *line = new QGraphicsLineItem(x->parent->x + 50 / 2.0,
                                           x->parent->y + 50 / 2.0, x->x + 50 / 2.0,
                                           x->y + 50 / 2.0);
        line->setZValue(1);
        auto uu = QPen(QColor(200,200,200));
        uu.setWidth(2);
        line->setPen(uu);
        scene->addItem(line);
    }
    drawTree(x->left, scene);
    drawTree(x->right, scene);

}


void Treap::render(QGraphicsScene *scene, Node *_root) {
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

void Treap::clickDelete(Node *cur, int64_t x, int64_t y) {
    if (!cur) return;
    if (x > cur->x && x < cur->x + 50 && y > cur->y && y < cur->y + 50) {
        this->deleteNode(cur->value);
    } else {
        clickDelete(cur->left, x, y);
        clickDelete(cur->right, x, y);
    }
}


