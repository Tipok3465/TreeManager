#include "GraphWidget.h"

#include <cmath>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
        : QGraphicsView(parent)
{
    auto *scene = new QGraphicsScene(this);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_D:
            if (dragMode() == QGraphicsView::NoDrag) {
                setDragMode(QGraphicsView::ScrollHandDrag);
            } else {
                setDragMode(QGraphicsView::NoDrag);
            }
            break;
        case Qt::Key_Equal:
            zoomIn();
            break;
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Enter:
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - event->pixelDelta().y());
    this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - event->pixelDelta().x());
}
#endif

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor)
            .mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        auto coordsInScene = this->mapToScene(event->pos());
        emit mousePressedSignal((int) coordsInScene.x(), (int) coordsInScene.y());
    }
    QGraphicsView::mousePressEvent(event);
}