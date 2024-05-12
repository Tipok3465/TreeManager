#include "App.h"
std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

App::~App() {
    delete window_;
}

App::App(int width, int height) {
    int id = QFontDatabase::addApplicationFont("/Users/noname/Documents/Programming/Applied/TreeManager/resources/main_font.ttf");
    font_family_ = QFontDatabase::applicationFontFamilies(id).at(0);

    back_avl_tree_ = new AVL();
    back_splay_tree_ = new Splay();
    back_car_tree_ = new Treap();
    back_rb_tree_ = new RBTree();


    start_screen_ = new QMainWindow();
    start_screen_->resize(700, 300);
    start_screen_->setStyleSheet("QMainWindow {"
                                 "background: #000;"
                                 "}");

    start_screen_title_ = new QLabel(start_screen_);
    start_screen_title_->resize(300, 40);
    start_screen_title_->move(225, 30);
    start_screen_title_->setFont(QFont(font_family_, 30));
    start_screen_title_->setText("Choose tree type");

    avl_tree_ = new QPushButton(start_screen_);
    avl_tree_->resize(300, 60);
    avl_tree_->move(25, 120);
    avl_tree_->setFont(QFont(font_family_, 30));
    avl_tree_->setText("AVL-tree");
    connect(avl_tree_, SIGNAL(released()), this, SLOT(setAvlTree()));

    rb_tree_ = new QPushButton(start_screen_);
    rb_tree_->resize(300, 60);
    rb_tree_->move(375, 120);
    rb_tree_->setFont(QFont(font_family_, 30));
    rb_tree_->setText("RB-tree");
    connect(rb_tree_, SIGNAL(released()), this, SLOT(setRbTree()));

    cart_tree_ = new QPushButton(start_screen_);
    cart_tree_->resize(300, 60);
    cart_tree_->move(25, 200);
    cart_tree_->setFont(QFont(font_family_, 30));
    cart_tree_->setText("Cartesian-tree");
    connect(cart_tree_, SIGNAL(released()), this, SLOT(setCartTree()));

    splay_tree_ = new QPushButton(start_screen_);
    splay_tree_->resize(300, 60);
    splay_tree_->move(375, 200);
    splay_tree_->setFont(QFont(font_family_, 30));
    splay_tree_->setText("Splay-tree");
    connect(splay_tree_, SIGNAL(released()), this, SLOT(setSplayTree()));

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000000"
                           "}");
    window_->hide();

    settings_ = new Label(window_);
    settings_->resize(40, 40);
    settings_->move(20, 10);
    settings_->setFont(QFont("Rockwell", 40));
    settings_->setText("⚙");
    connect(settings_, SIGNAL(clicked()), this, SLOT(goToSettings()));

    avl_window_ = new QLabel(window_);
    avl_window_->resize(1000, 600);
    avl_window_->setStyleSheet("QLabel {"
                               "background: #000000;"
                               "}");

    avl_edit_tablet_ = new GraphWidget(avl_window_);
    avl_edit_tablet_->resize(980, 580);
    avl_edit_tablet_->move(10, 10);
    avl_edit_tablet_->setStyleSheet("QGraphicsView {"
                                    "background: #d5d5d5; }");
    connect(avl_edit_tablet_, &GraphWidget::mousePressedSignal, this, &App::treeClickChecking);


    avl_edit_scene_ = new QGraphicsScene();
    avl_edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    avl_edit_tablet_->setScene(avl_edit_scene_);
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        avl_edit_scene_->addLine(i, -10000, i, 10000);
//    }
//    for (int i = -10000; i <= 10000; i += 25) {
//        avl_edit_scene_->addLine(-10000, i, 10000, i);
//    }

    avl_tree_text_ = new QLabel(avl_window_);
    avl_tree_text_->resize(300, 40);
    avl_tree_text_->setFont(QFont(font_family_, 30));
    avl_tree_text_->setAlignment(Qt::AlignCenter);
    avl_tree_text_->move(350, 10);
    avl_tree_text_->setText("AVL-tree");
    avl_tree_text_->setStyleSheet("QLabel {"
                                  "background-Color: rgba(0, 0, 0, 0);"
                                  "}");

    rb_window_ = new QLabel(window_);
    rb_window_->resize(1000, 600);
    rb_window_->setStyleSheet("QLabel {"
                               "background: #000000;"
                               "}");

    rb_edit_tablet_ = new GraphWidget(rb_window_);
    rb_edit_tablet_->resize(980, 580);
    rb_edit_tablet_->move(10, 10);
    rb_edit_tablet_->setStyleSheet("QGraphicsView {"
                                    "background: #d5d5d5; }");
    connect(rb_edit_tablet_, &GraphWidget::mousePressedSignal, this, &App::treeClickChecking);

    rb_edit_scene_ = new QGraphicsScene();
    rb_edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    rb_edit_tablet_->setScene(rb_edit_scene_);
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        rb_edit_scene_->addLine(i, -10000, i, 10000);
//    }
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        rb_edit_scene_->addLine(-10000, i, 10000, i);
//    }

    rb_tree_text_ = new QLabel(rb_window_);
    rb_tree_text_->resize(300, 40);
    rb_tree_text_->setFont(QFont(font_family_, 30));
    rb_tree_text_->setAlignment(Qt::AlignCenter);
    rb_tree_text_->move(350, 10);
    rb_tree_text_->setText("RB-tree");
    rb_tree_text_->setStyleSheet("QLabel {"
                                  "background-Color: rgba(0, 0, 0, 0);"
                                  "}");


    car_window_ = new QLabel(window_);
    car_window_->resize(1000, 600);
    car_window_->setStyleSheet("QLabel {"
                               "background: #000000;"
                               "}");

    car_edit_tablet_ = new GraphWidget(car_window_);
    car_edit_tablet_->resize(980, 580);
    car_edit_tablet_->move(10, 10);
    car_edit_tablet_->setStyleSheet("QGraphicsView {"
                                   "background: #d5d5d5; }");
    connect(car_edit_tablet_, &GraphWidget::mousePressedSignal, this, &App::treeClickChecking);

    car_edit_scene_ = new QGraphicsScene();
    car_edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    car_edit_tablet_->setScene(car_edit_scene_);
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        car_edit_scene_->addLine(i, -10000, i, 10000);
//    }
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        car_edit_scene_->addLine(-10000, i, 10000, i);
//    }

    car_tree_text_ = new QLabel(car_window_);
    car_tree_text_->resize(300, 40);
    car_tree_text_->setFont(QFont(font_family_, 30));
    car_tree_text_->setAlignment(Qt::AlignCenter);
    car_tree_text_->move(350, 10);
    car_tree_text_->setText("Cartesian-tree");
    car_tree_text_->setStyleSheet("QLabel {"
                                 "background-Color: rgba(0, 0, 0, 0);"
                                 "}");


    splay_window_ = new QLabel(window_);
    splay_window_->resize(1000, 600);
    splay_window_->setStyleSheet("QLabel {"
                               "background: #000000;"
                               "}");

    splay_edit_tablet_ = new GraphWidget(splay_window_);
    splay_edit_tablet_->resize(980, 580);
    splay_edit_tablet_->move(10, 10);
    splay_edit_tablet_->setStyleSheet("QGraphicsView {"
                                    "background: #d5d5d5; }");
    connect(splay_edit_tablet_, &GraphWidget::mousePressedSignal, this, &App::treeClickChecking);

    splay_edit_scene_ = new QGraphicsScene();
    splay_edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    splay_edit_tablet_->setScene(splay_edit_scene_);
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        splay_edit_scene_->addLine(i, -10000, i, 10000);
//    }
//    for (int i = -10000; i <= 10000; i += 25)
//    {
//        splay_edit_scene_->addLine(-10000, i, 10000, i);
//    }

    splay_tree_text_ = new QLabel(splay_window_);
    splay_tree_text_->resize(300, 40);
    splay_tree_text_->setFont(QFont(font_family_, 30));
    splay_tree_text_->setAlignment(Qt::AlignCenter);
    splay_tree_text_->move(350, 10);
    splay_tree_text_->setText("Splay-tree");
    splay_tree_text_->setStyleSheet("QLabel {"
                                  "background-Color: rgba(0, 0, 0, 0);"
                                  "}");


    tree_settings_ = new QLabel(window_);
    tree_settings_->resize(340, 600);
    tree_settings_->setStyleSheet("QLabel {"
                                  "background: #000;"
                                  "}");
    tree_settings_->hide();

    adding_node_ = new QPushButton(tree_settings_);
    adding_node_->resize(300, 60);
    adding_node_->move(20, 60);
    adding_node_->setFont(QFont(font_family_, 30));
    adding_node_->setText("Add node");
    connect(adding_node_, SIGNAL(released()), this, SLOT(showValueData()));

    adding_some_nodes_ = new QPushButton(tree_settings_);
    adding_some_nodes_->resize(300, 60);
    adding_some_nodes_->move(20, 130);
    adding_some_nodes_->setFont(QFont(font_family_, 30));
    adding_some_nodes_->setText("Add some nodes");
    connect(adding_some_nodes_, SIGNAL(released()), this, SLOT(showRandData()));

    rand_data_ = new QInputDialog();
    rand_data_->setInputMode(QInputDialog::IntInput);
    rand_data_->setIntMinimum(1);
    rand_data_->setIntMaximum(2000);
    rand_data_->setFont(QFont(font_family_, 20));
    rand_data_->setLabelText("Set node count");
    rand_data_->hide();
    connect(rand_data_, SIGNAL(intValueSelected(int)), this, SLOT(addSomeNodes()));

    avl_tree_btn_ = new QPushButton(tree_settings_);
    avl_tree_btn_->resize(150, 60);
    avl_tree_btn_->move(10, 470);
    avl_tree_btn_->setFont(QFont(font_family_, 20));
    avl_tree_btn_->setText("AVL-tree");
    connect(avl_tree_btn_, SIGNAL(released()), this, SLOT(setAvlTree()));

    rb_tree_btn_ = new QPushButton(tree_settings_);
    rb_tree_btn_->resize(150, 60);
    rb_tree_btn_->move(180, 470);
    rb_tree_btn_->setFont(QFont(font_family_, 20));
    rb_tree_btn_->setText("RB-tree");
    connect(rb_tree_btn_, SIGNAL(released()), this, SLOT(setRbTree()));

    car_tree_btn_ = new QPushButton(tree_settings_);
    car_tree_btn_->resize(150, 60);
    car_tree_btn_->move(10, 530);
    car_tree_btn_->setFont(QFont(font_family_, 20));
    car_tree_btn_->setText("Cartesian-tree");
    connect(car_tree_btn_, SIGNAL(released()), this, SLOT(setCartTree()));

    splay_tree_btn_ = new QPushButton(tree_settings_);
    splay_tree_btn_->resize(150, 60);
    splay_tree_btn_->move(180, 530);
    splay_tree_btn_->setFont(QFont(font_family_, 20));
    splay_tree_btn_->setText("Splay-tree");
    connect(splay_tree_btn_, SIGNAL(released()), this, SLOT(setSplayTree()));
    settings_->raise();

    value_data_ = new QMainWindow();
    value_data_->resize(180, 120);
    value_data_->setFont(QFont(font_family_, 18));

    value_data_label_ = new QLabel(value_data_);
    value_data_label_->resize(180, 30);
    value_data_label_->setFont(QFont(font_family_, 20));
    value_data_label_->setAlignment(Qt::AlignCenter);
    value_data_label_->setText("Set node value");

    value_data_edit_ = new QLineEdit(value_data_);
    value_data_edit_->resize(140, 26);
    value_data_edit_->setFont(QFont(font_family_, 15));
    value_data_edit_->move(20, 40);

    reject_value_data_ = new QPushButton(value_data_);
    reject_value_data_->resize(80, 40);
    reject_value_data_->move(5, 70);
    reject_value_data_->setFont(QFont(font_family_, 15));
    reject_value_data_->setText("Reject");
    connect(reject_value_data_, SIGNAL(released()), this, SLOT(hideData()));

    setting_value_data_ = new QPushButton(value_data_);
    setting_value_data_->resize(80, 40);
    setting_value_data_->move(95, 70);
    setting_value_data_->setFont(QFont(font_family_, 15));
    setting_value_data_->setText("Accept");
    connect(setting_value_data_, SIGNAL(released()), this, SLOT(addNode()));

    installEventFilter(this);

}

void App::setAvlTree() {
    AVL::render(avl_edit_scene_, back_avl_tree_->getRoot());
    start_screen_->hide();
    window_->show();
    avl_window_->show();
    rb_window_->hide();
    car_window_->hide();
    splay_window_->hide();
    settings_->raise();
}

void App::setRbTree() {
    back_rb_tree_->render(rb_edit_scene_, back_rb_tree_->getRoot());
    start_screen_->hide();
    window_->show();
    avl_window_->hide();
    rb_window_->show();
    car_window_->hide();
    splay_window_->hide();
    settings_->raise();
}

void App::setCartTree() {
    Treap::render(car_edit_scene_, back_car_tree_->getRoot());
    start_screen_->hide();
    window_->show();
    avl_window_->hide();
    rb_window_->hide();
    car_window_->show();
    splay_window_->hide();
    settings_->raise();
}

void App::setSplayTree() {
    Splay::render(splay_edit_scene_, back_splay_tree_->getRoot());
    start_screen_->hide();
    window_->show();
    avl_window_->hide();
    rb_window_->hide();
    car_window_->hide();
    splay_window_->show();
    settings_->raise();
}

void App::goToSettings() {
    if (tree_settings_->isHidden()) {
        tree_settings_->show();
    } else {
        tree_settings_->hide();
    }
    settings_->raise();
}

void App::showValueData() {
    value_data_->show();
}

void App::showRandData() {
    rand_data_->show();
}

void App::addSomeNodes() {
    int cnt = rand_data_->intValue();
    for (int i = 0; i < cnt; ++i) {
        if (!avl_window_->isHidden()) {
            int64_t data = rnd() % 10000000;
            while (back_avl_tree_->contains(data)) data = rnd() % 10000000;
            back_avl_tree_->insert(data);
        }
        if (!car_window_->isHidden()) {
            int64_t data = rnd() % 1000000000;
            while (back_car_tree_->contains(data)) data = rnd() % 1000000000;
            int64_t prior = rnd() % 1000000;
            back_car_tree_->insert(data, prior);
        }
        if (!splay_window_->isHidden()) {
            int64_t data = rnd() % 10000000;
            while (back_splay_tree_->contains(data)) data = rnd() % 10000000;
            back_splay_tree_->insert(data);
        }
        if (!rb_window_->isHidden()) {
            int64_t data = rnd() % 10000000;
            while (back_rb_tree_->contains(data)) data = rnd() % 10000000;
            back_rb_tree_->insert(data);
        }
    }
    if (!avl_window_->isHidden()) AVL::render(avl_edit_scene_, back_avl_tree_->getRoot());
    if (!car_window_->isHidden()) Treap::render(car_edit_scene_, back_car_tree_->getRoot());
    if (!splay_window_->isHidden()) Splay::render(splay_edit_scene_, back_splay_tree_->getRoot());
    if (!rb_window_->isHidden()) RBTree::render(rb_edit_scene_, back_rb_tree_->getRoot());
}

void App::hideData() {
    value_data_edit_->clear();
    value_data_->hide();
}

void App::addNode() {
    if (!avl_window_->isHidden()) {
        back_avl_tree_->insert(value_data_edit_->text().toLongLong());
        AVL::render(avl_edit_scene_, back_avl_tree_->getRoot());
        value_data_edit_->clear();
    }
    if (!splay_window_->isHidden()) {
        back_splay_tree_->insert(value_data_edit_->text().toLongLong());
        Splay::render(splay_edit_scene_, back_splay_tree_->getRoot());
        value_data_edit_->clear();
    }
    if (!car_window_->isHidden()) {
        int prior = (int)(rnd() % 1000000);
        if (back_car_tree_->contains(value_data_edit_->text().toLongLong())) return;
        while (back_car_tree_->contains(prior)) prior = (int)(rnd() % 1000000);
        back_car_tree_->insert(value_data_edit_->text().toLongLong(), (float)prior);
        Treap::render(car_edit_scene_, back_car_tree_->getRoot());
        value_data_edit_->clear();
    }
    if (!rb_window_->isHidden()) {
        back_rb_tree_->insert(value_data_edit_->text().toLongLong());
        RBTree::render(rb_edit_scene_, back_rb_tree_->getRoot());
        value_data_edit_->clear();
    }
    value_data_edit_->clear();
    value_data_->hide();
}

void App::treeClickChecking(int x, int y) {
    if (!avl_window_->isHidden()) {
        back_avl_tree_->clickDelete(back_avl_tree_->getRoot(), x, y);
        AVL::render(avl_edit_scene_, back_avl_tree_->getRoot());
    }
    if (!car_window_->isHidden()) {
        back_car_tree_->clickDelete(back_car_tree_->getRoot(), x, y);
        Treap::render(car_edit_scene_, back_car_tree_->getRoot());
    }
    if (!splay_window_->isHidden()) {
        back_splay_tree_->clickDelete(back_splay_tree_->getRoot(), x, y);
        Splay::render(splay_edit_scene_, back_splay_tree_->getRoot());
    }
    if (!rb_window_->isHidden()) {
        back_rb_tree_->clickDelete(back_rb_tree_->getRoot(), x, y);
        RBTree::render(rb_edit_scene_, back_rb_tree_->getRoot());
    }
}

//void App::HoverInNode(Node *node) {
//    cur_node_data_ = new QLabel();
//    QString text = QString::fromStdString(" " + std::to_string(node->getValue()));
//    cur_node_data_->resize(std::max((int)text.size()*8, 50), 26);
////    cur_node_data_->resize(200, 26);
//    cur_node_data_->setText(text);
//    cur_node_data_->setStyleSheet("QLabel {"
//                                  "background-Color: #aaa;"
//                                  "Color: #000;"
//                                  "border-radius: 5px;"
//                                  "}");
//    cur_node_data_->move(node->x()-75, node->y() - 75);
//    cur_node_data_->raise();
//    if (!rb_window_->isHidden()) {
//        rb_edit_scene_->addWidget(cur_node_data_);
//    }
//    if (!avl_window_->isHidden()) {
//        avl_edit_scene_->addWidget(cur_node_data_);
//    }
//    if (!car_window_->isHidden()) {
//        car_edit_scene_->addWidget(cur_node_data_);
//    }
//    if (!splay_window_->isHidden()) {
//        splay_edit_scene_->addWidget(cur_node_data_);
//    }
//}
//
//void App::HoverOutNode(Node *node) {
//    delete cur_node_data_;
//    cur_node_data_ = nullptr;
//}