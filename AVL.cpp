#include "AVL.h"

AVL::Node::Node(int64_t value) : value(value),
                             height(1),
                             x(0), y(0),
                             left(nullptr),
                             right(nullptr),
                             parent(nullptr) {}


AVL::AVL() : root_(nullptr) {}

AVL::~AVL() {
    deleteTree(root_);
}

int64_t getHeight(AVL::Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void AVL::fixHeight(Node *p) {
    int64_t hl = getHeight(p->left);
    int64_t hr = getHeight(p->right);
    p->height = std::max(hl, hr) + 1;
}

void AVL::deleteTree(Node *node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void AVL::insert(int64_t value) {
    insert(root_, nullptr, value);
}

void AVL::insert(Node *&node, Node *prev, int64_t value) {
    if (node == nullptr) {
        node = new Node(value);
        node->parent = prev;
    } else if (value < node->value) {
        insert(node->left, node, value);
    } else if (value > node->value) {
        insert(node->right, node, value);
    }
    node = balance(node);
}

void AVL::remove(int64_t value) {
    remove(root_, value);
}

void AVL::remove(Node *&node, int64_t value) {
    if (node == nullptr) {
        return;
    }
    if (value < node->value) {
        remove(node->left, value);
    } else if (value > node->value) {
        remove(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node *temp = node;
            node = node->right;
            node->parent = temp->parent;
            delete temp;
        } else if (node->right == nullptr) {
            Node *temp = node;
            node = node->left;
            node->parent = temp->parent;
            delete temp;
        } else {
            Node *temp = node->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            node->value = temp->value;
            remove(node->left, temp->value);
        }
    }
    node = balance(node);
}

bool AVL::contains(int64_t value) {
    return contains(root_, value);
}

bool AVL::contains(Node *node, int64_t value) {
    if (node == nullptr) {
        return false;
    } else if (value < node->value) {
        return contains(node->left, value);
    } else if (value > node->value) {
        return contains(node->right, value);
    } else {
        return true;
    }
}

AVL::Node *AVL::rotateLeft(Node *q) {
    Node *p = q->right;
    p->parent = q->parent;
    q->parent = p;
    q->right = p->left;
    p->left = q;
    if (q->right != nullptr)
        q->right->parent = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}


AVL::Node *AVL::rotateRight(Node *p) {

    Node *q = p->left;
    q->parent = p->parent;
    p->parent = q;

    p->left = q->right;
    q->right = p;
    if (p->left != nullptr)
        p->left->parent = p;

    fixHeight(p);
    fixHeight(q);
    return q;
}

int64_t AVL::heightDif(Node *p) {
    return getHeight(p->right) - getHeight(p->left);
}


AVL::Node *AVL::balance(Node *p) {
    if (!p) return nullptr;
    fixHeight(p);
    if (heightDif(p) == 2) {
        if (heightDif(p->right) < 0) {
            p->right = rotateRight(p->right);
        }

        return rotateLeft(p);
    }
    if (heightDif(p) == -2) {
        if (heightDif(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

void AVL::Node::setPos(int64_t _x, int64_t _y) {
    x = _x;
    y = _y;
}


void treeFilling(AVL::Node *&x, int64_t dl) {
    if (x == nullptr) return;
    if (x->left) x->left->x -= dl;
    if (x->right) x->right->x -= dl;
    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int64_t maxRight(AVL::Node *x, int64_t mx) {
    if (x == nullptr) return mx;
    mx = std::max(x->x + 50, maxRight(x->right, mx));
    mx = std::max(x->x + 50, maxRight(x->left, mx));
    return mx;
}

int64_t maxLeft(AVL::Node *x, int64_t mx) {
    if (x == nullptr) return mx;
    mx = std::min(x->x, maxLeft(x->right, mx));
    mx = std::min(x->x, maxLeft(x->left, mx));
    return mx;
}

void posRecalc(AVL::Node *&x) {
    if (x == nullptr) return;
    posRecalc(x->left);
    posRecalc(x->right);
    int64_t mr = maxRight(x->left, -1e6);
    int64_t ml = maxLeft(x->right, 1e6);

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

void fixPosition(AVL::Node *&x) {
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

void recalc(AVL::Node *&x) {
    fixPosition(x);
    posRecalc(x);
}

void paintTree(AVL::Node *x, QGraphicsScene *&scene) {
    if (!x) return;
    auto *ellipse = new QGraphicsEllipseItem(x->x, x->y, 50, 50);
    ellipse->setBrush(QBrush(QColor(99,99,99)));
    ellipse->setZValue(2);
    auto *text = new QGraphicsTextItem(QString::number(x->value));
    text->setDefaultTextColor(QColor(255, 255, 255));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center());
    text->setFont(QFont("Rockwell", 12));
    text->setZValue(3);
    scene->addItem(ellipse);
    scene->addItem(text);
    if (x->parent) {
        auto *line = new QGraphicsLineItem(x->parent->x + 50 / 2.0,
                                           x->parent->y + 50 / 2.0,
                                           x->x + 50 / 2.0,
                                           x->y + 50 / 2.0);
        line->setZValue(1);
        auto uu = QPen(QColor(200,200,200));
        uu.setWidth(2);
        line->setPen(uu);
        scene->addItem(line);
    }
    paintTree(x->left, scene);
    paintTree(x->right, scene);

}


void AVL::render(QGraphicsScene *scene, AVL::Node *root) {
    scene->clear();
    for (int i = -100000; i <= 100000; i += 25)
    {
        scene->addLine(i, -100000, i, 100000);
    }
    for (int i = -100000; i <= 100000; i += 25) {
        scene->addLine(-100000, i, 100000, i);
    }
    recalc(root);
    paintTree(root, scene);

}


AVL::Node *AVL::getRoot() const {
    return root_;
}

void AVL::clickDelete(Node *cur, int64_t x, int64_t y) {
    if (!cur) return;
    if (x > cur->x && x < cur->x + 50 && y > cur->y && y < cur->y + 50) {
        this->remove(cur->value);
    } else {
        clickDelete(cur->left, x, y);
        clickDelete(cur->right, x, y);
    }
}