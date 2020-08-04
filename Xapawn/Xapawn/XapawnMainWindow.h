#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XapawnMainWindow.h"

class XapawnMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    XapawnMainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::XapawnMainWindowClass ui;
};
