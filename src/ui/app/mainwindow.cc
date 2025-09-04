#include "mainwindow.h"
#include "systembuttons.h"
#include "DonutWidget.h"
#include "ButtonStyle.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QWidget *buttons = new QWidget(mainWidget);
    buttons->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    buttonLayout = new QHBoxLayout(buttons);
    buttonLayout->setContentsMargins(10, 10, 0, 0);
    mainLayout->addWidget(buttons, 0, Qt::AlignCenter);
    SystemButtons system_buttons = SystemButtons(this);
    QPushButton *addStudentbtn = system_buttons.createButton(":/icons/add.png", "Inscribir Estudiante", "AddStudent", []()
                                                             {
                                                                 // This lambda is intentionally left empty for now.
                                                             });
    QPushButton *EnrollStudent = system_buttons.createButton(":/icons/restart.png", "Reinscribir Estudiante", "UpdStudent", []()
                                                             {
                                                                 // This lambda is intentionally left empty for now.
                                                             });
    QPushButton *updStudentBtn = system_buttons.createButton(":/icons/card.png", "Realizar Pagos", "ToPay", []()
                                                             {
                                                                 // This lambda is intentionally left empty for now.
                                                             });
    QPushButton *reportsBtn = system_buttons.createButton(":/icons/history.png", "Reportes", "Reports", []()
                                                          {
                                                              // This lambda is intentionally left empty for now.
                                                          });

    addStudentbtn->setStyleSheet(ButtonStyle::buttonNormalColor());
    EnrollStudent->setStyleSheet(ButtonStyle::buttonNormalColor());
    updStudentBtn->setStyleSheet(ButtonStyle::buttonNormalColor());
    reportsBtn->setStyleSheet(ButtonStyle::buttonNormalColor());

    QWidget *statics = new QWidget(mainWidget);
    QHBoxLayout *statisLayout = new QHBoxLayout(statics);

    // --- Tabla 1 ---
    QWidget *recentsWidget = new QWidget(statics);
    QVBoxLayout *recentsLayout = new QVBoxLayout(recentsWidget);

    QLabel *recentsTitle = new QLabel("Pagos Recientes", recentsWidget);
    recentsTitle->setAlignment(Qt::AlignCenter);
    recentsTitle->setStyleSheet("font-size: 14px;background-color: #454545");

    QTableView *recents = new QTableView(recentsWidget);
    recents->setSelectionBehavior(QAbstractItemView::SelectRows);
    recents->setEditTriggers(QAbstractItemView::NoEditTriggers);

    recentsLayout->addWidget(recentsTitle);
    recentsLayout->addWidget(recents);

    // --- Tabla 2 ---
    QWidget *notPayWidget = new QWidget(statics);
    QVBoxLayout *notPayLayout = new QVBoxLayout(notPayWidget);

    QLabel *notPayTitle = new QLabel("Tiempo sin Pagar", notPayWidget);
    notPayTitle->setAlignment(Qt::AlignCenter);
    notPayTitle->setStyleSheet("font-size: 14px;background-color: #454545");

    QTableView *notPayStill = new QTableView(notPayWidget);
    notPayStill->setSelectionBehavior(QAbstractItemView::SelectRows);
    notPayStill->setEditTriggers(QAbstractItemView::NoEditTriggers);

    notPayLayout->addWidget(notPayTitle);
    notPayLayout->addWidget(notPayStill);

    // --- Agregar tablas al layout horizontal ---
    statisLayout->addWidget(recentsWidget);
    statisLayout->addWidget(notPayWidget);

    QWidget *toolBar = new QWidget(mainWidget);
    QVBoxLayout *toolLayout = new QVBoxLayout(toolBar);
    QPushButton *profileBtn = system_buttons.createButton(":/icons/profile.png", "", "Profile", []()
                                                          {
                                                              // This lambda is intentionally left empty for now.
                                                          });
    QPushButton *payBtn = system_buttons.createButton(":/icons/cash.png", "", "Pay", []()
                                                      {
                                                          // This lambda is intentionally left empty for now.
                                                      });
    QPushButton *settingsBtn = system_buttons.createButton(":/icons/settings.png", "", "Settings", []()
                                                           {
                                                               // This lambda is intentionally left empty for now.
                                                           });
    QPushButton *logoutBtn = system_buttons.createButton(":/icons/logout.png", "", "Logout", []()
                                                         {
                                                             // This lambda is intentionally left empty for now.
                                                         });

    DonutWidget *donut = new DonutWidget(this);

    toolLayout->addWidget(profileBtn);
    toolLayout->addWidget(payBtn);
    toolLayout->addWidget(settingsBtn);
    toolLayout->addWidget(logoutBtn);

    // --- Agregar botón y tablas al layout principal ---
    buttonLayout->addWidget(addStudentbtn);
    buttonLayout->addWidget(EnrollStudent);
    buttonLayout->addWidget(updStudentBtn);
    buttonLayout->addWidget(reportsBtn);

    mainLayout->addWidget(toolBar, 0);
    mainLayout->addWidget(statics, 0, Qt::AlignCenter | Qt::AlignVCenter);
    mainLayout->addWidget(donut, Qt::AlignCenter);
    mainLayout->addStretch(2);
}