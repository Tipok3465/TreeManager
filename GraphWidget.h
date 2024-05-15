#pragma once
#include "header.h"

class Node;

class GraphWidget : public QGraphicsView
{

Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr); // конструктор

public slots:
    void zoomIn();  // приближение
    void zoomOut(); // отдаление
protected:
    void keyPressEvent(QKeyEvent *event) override; // нажатие кнопки
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override; // скроллинг колёсика мыши
#endif
    void mousePressEvent(QMouseEvent *event) override; // нажатие кнопки мыши
    void scaleView(qreal scaleFactor);                 // изменение масштаба
signals:
    void mousePressedSignal(int x, int y);
private:
    QLabel* data_tablet_;
    int x = 0;
    int y = 0;
};
