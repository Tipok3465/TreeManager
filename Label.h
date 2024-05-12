#pragma once
#include "header.h"

class Label : public QLabel
{
Q_OBJECT
public:
    explicit Label(QWidget* parent = nullptr) : QLabel(parent) {}

    void mousePressEvent(QMouseEvent* event) override {
        QLabel::mousePressEvent(event);
        emit clicked();
    }

signals:
    void clicked();

public slots:
};