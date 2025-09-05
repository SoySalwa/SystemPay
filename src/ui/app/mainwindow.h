#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Settings.h"

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QHeaderView>
class SystemButtons;

class QWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    QWidget *mainWidget;
    QHBoxLayout *buttonLayout;
    SystemButtons *system_buttons;
    Settings *settings;
};

#endif // MAINWINDOW_H