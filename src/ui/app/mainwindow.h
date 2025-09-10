#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Settings.h"
#include "ThemeManager.h"

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QHeaderView>
#include <QStackedWidget>
class Settings;
class SystemButtons;

class QWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;
    void applyThemesWidgets(const Theme &t);
    void setupMainUI();
    void setupConnections();

private:
    QWidget *mainWidget;
    QStackedWidget *contentArea;
    QHBoxLayout *buttonLayout;
    SystemButtons *system_buttons;
    QWidget *toolBar;
    QWidget *homeWidget;
    QPushButton *homeBtn;
    QPushButton *profileBtn;
    QPushButton *payBtn;
    QPushButton *settingsBtn;
    QPushButton *logoutBtn;
    QPushButton *addStudentbtn;
    QPushButton *EnrollStudent;
    QPushButton *updStudentBtn;
    QPushButton *reportsBtn;
    Settings *settings;

    // Páginas del QStackedWidget
    QWidget *enrollStudentWidget;
    QWidget *paymentsWidget;
    QWidget *reportsWidget;
};

#endif // MAINWINDOW_H