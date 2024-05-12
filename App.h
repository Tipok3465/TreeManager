#include "header.h"
#include "Label.h"
#include "GraphWidget.h"
#include "Trees/AVL.h"
#include "Trees/Treap.h"
#include "Trees/Splay.h"
#include "Trees/RBTree.h"

#pragma once

class App : public QMainWindow {
    Q_OBJECT

public:
    App(int width, int height);
    ~App() override;

    void render() {
        start_screen_->show();
    }

private slots:
    void setAvlTree();
    void setRbTree();
    void setCartTree();
    void setSplayTree();
    void showValueData();
    void showRandData();
    void hideData();
    void addNode();
    void addSomeNodes();
    void goToSettings();
    void treeClickChecking(int, int);
private:
    AVL* back_avl_tree_;
    Treap* back_car_tree_;
    Splay* back_splay_tree_;
    RBTree* back_rb_tree_;
    QString font_family_;
    QMainWindow* start_screen_;
    QLabel* start_screen_title_;
    QPushButton* avl_tree_;
    QPushButton* rb_tree_;
    QPushButton* cart_tree_;
    QPushButton* splay_tree_;
    QMainWindow* window_;
    Label* settings_;
    QLabel* avl_window_;
    QLabel* avl_tree_text_;
    QLabel* rb_window_;
    QLabel* rb_tree_text_;
    QLabel* car_window_;
    QLabel* car_tree_text_;
    QLabel* splay_window_;
    QLabel* splay_tree_text_;
    GraphWidget* avl_edit_tablet_;
    QGraphicsScene* avl_edit_scene_;
    GraphWidget* rb_edit_tablet_;
    QGraphicsScene* rb_edit_scene_;
    GraphWidget* car_edit_tablet_;
    QGraphicsScene* car_edit_scene_;
    GraphWidget* splay_edit_tablet_;
    QGraphicsScene* splay_edit_scene_;
    QPainter* painter_;
    QLabel* tree_settings_;
    QPushButton* adding_node_;
    QPushButton* adding_some_nodes_;
    QInputDialog* rand_data_;
    QPushButton* avl_tree_btn_;
    QPushButton* rb_tree_btn_;
    QPushButton* car_tree_btn_;
    QPushButton* splay_tree_btn_;
    QMainWindow* value_data_;
    QLabel* value_data_label_;
    QLineEdit* value_data_edit_;
    QPushButton* setting_value_data_;
    QPushButton* reject_value_data_;
    Node* node;
    QLabel* cur_node_data_;
};