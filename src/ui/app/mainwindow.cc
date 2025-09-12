#include "mainwindow.h"
#include "DonutWidget.h"
#include "ButtonStyle.h"
#include "WidgetStyle.h"
#include "systembuttons.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
        setupMainUI();
        setupConnections();
        const Theme &t = ThemeManager::instance()->allThemes()[ThemeManager::instance()->currentTheme()];
        applyThemesWidgets(t);
}

void MainWindow::setupMainUI()
{
        mainWidget = new QWidget(this);
        setCentralWidget(mainWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

        // --- Botones principales ---
        QWidget *buttons = new QWidget(mainWidget);
        buttonLayout = new QHBoxLayout(buttons);
        buttonLayout->setContentsMargins(10, 10, 0, 0);

        system_buttons = new SystemButtons(this);
        homeBtn = system_buttons->createButton(":/icons/home.png", "Interfaz Principal", "home", [this]()
                                               { contentArea->setCurrentWidget(homeWidget); });
        addStudentbtn = system_buttons->createButton(":/icons/add.png", "Inscribir Estudiante", "AddStudent", [this]()
                                                     { contentArea->setCurrentWidget(enrollStudentWidget); });
        EnrollStudent = system_buttons->createButton(":/icons/restart.png", "Reinscribir Estudiante", "UpdStudent", [this]()
                                                     { contentArea->setCurrentWidget(enrollStudentWidget); });
        updStudentBtn = system_buttons->createButton(":/icons/card.png", "Realizar Pagos", "ToPay", [this]()
                                                     { contentArea->setCurrentWidget(paymentsWidget); });
        reportsBtn = system_buttons->createButton(":/icons/history.png", "Reportes", "Reports", [this]()
                                                  { contentArea->setCurrentWidget(reportsWidget); });

        homeBtn->setStyleSheet(ButtonStyle::buttonNormalColor());
        addStudentbtn->setStyleSheet(ButtonStyle::buttonNormalColor());
        EnrollStudent->setStyleSheet(ButtonStyle::buttonNormalColor());
        updStudentBtn->setStyleSheet(ButtonStyle::buttonNormalColor());
        reportsBtn->setStyleSheet(ButtonStyle::buttonNormalColor());

        buttonLayout->addWidget(homeBtn);
        buttonLayout->addWidget(addStudentbtn);
        buttonLayout->addWidget(EnrollStudent);
        buttonLayout->addWidget(updStudentBtn);
        buttonLayout->addWidget(reportsBtn);
        mainLayout->addWidget(buttons, 0, Qt::AlignCenter);

        // --- Layout central ---
        QHBoxLayout *centralLayout = new QHBoxLayout();

        // --- Toolbar lateral ---
        toolBar = new QWidget(mainWidget);
        toolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        QVBoxLayout *toolLayout = new QVBoxLayout(toolBar);

        settings = new Settings(this);
        profile = new Profile(this);
        profileBtn = system_buttons->createButton(":/icons/profile.png", "", "Profile", [this]() {
                profile->createUserProfile()->exec();
        });
        payBtn = system_buttons->createButton(":/icons/cash.png", "", "Pay", []() {});
        settingsBtn = system_buttons->createButton(":/icons/settings.png", "", "Settings", [this]()
                                                   { settings->createAppSettings()->exec(); });
        logoutBtn = system_buttons->createButton(":/icons/logout.png", "", "Logout", []() {});

        toolLayout->addWidget(profileBtn);
        toolLayout->addWidget(payBtn);
        toolLayout->addWidget(settingsBtn);
        toolLayout->addWidget(logoutBtn);
        toolLayout->addStretch();
        // --- Content Area ---
        contentArea = new QStackedWidget(mainWidget);
        contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // --- Página Home ---
        homeWidget = new QWidget();
        QVBoxLayout *homeLayout = new QVBoxLayout(homeWidget);

        // Tablas
        QHBoxLayout *statisLayout = new QHBoxLayout();

        QWidget *recentsWidget = new QWidget();

        QVBoxLayout *recentsLayout = new QVBoxLayout(recentsWidget);

        QLabel *recentsTitle = new QLabel("Pagos Recientes");
        recentsTitle->setAlignment(Qt::AlignCenter);

        QTableView *recents = new QTableView();
        recents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        recents->setSelectionBehavior(QAbstractItemView::SelectRows);
        recents->setEditTriggers(QAbstractItemView::NoEditTriggers);
        recents->setMaximumHeight(300);

        recentsLayout->addWidget(recentsTitle);
        recentsLayout->addWidget(recents);

        QWidget *notPayWidget = new QWidget();
        QVBoxLayout *notPayLayout = new QVBoxLayout(notPayWidget);
        QLabel *notPayTitle = new QLabel("Tiempo sin Pagar");
        notPayTitle->setAlignment(Qt::AlignCenter);
        QTableView *notPayStill = new QTableView();
        notPayStill->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        notPayStill->setMaximumHeight(300);
        notPayStill->setSelectionBehavior(QAbstractItemView::SelectRows);
        notPayStill->setEditTriggers(QAbstractItemView::NoEditTriggers);
        notPayLayout->addWidget(notPayTitle);
        notPayLayout->addWidget(notPayStill);

        statisLayout->addWidget(recentsWidget);
        statisLayout->addWidget(notPayWidget);

        DonutWidget *donut = new DonutWidget();
        homeLayout->addLayout(statisLayout);
        homeLayout->addWidget(donut);
        contentArea->addWidget(homeWidget);

        enrollStudentWidget = new QWidget();
        paymentsWidget = new QWidget();
        reportsWidget = new QWidget();

        contentArea->addWidget(enrollStudentWidget);
        contentArea->addWidget(paymentsWidget);
        contentArea->addWidget(reportsWidget);

        centralLayout->addWidget(toolBar);
        centralLayout->addWidget(contentArea, 1);
        mainLayout->addLayout(centralLayout, 1);
}

void MainWindow::setupConnections()
{
        connect(ThemeManager::instance(), &ThemeManager::themeChanged, this, [=](const QString &theme)
                {
        const QColor color = ThemeManager::instance()->allThemes()[theme].iconColor;
        profileBtn->setIcon(QIcon(PixmapUtils::recolorPixmap(":/icons/profile.png", color)));
        payBtn->setIcon(QIcon(PixmapUtils::recolorPixmap(":/icons/cash.png", color)));
        settingsBtn->setIcon(QIcon(PixmapUtils::recolorPixmap(":/icons/settings.png", color)));
        const Theme &t = ThemeManager::instance()->allThemes()[theme];
        applyThemesWidgets(t); });
}

void MainWindow::applyThemesWidgets(const Theme &t)
{
        toolBar->setStyleSheet(WidgetStyle::widgetNavBarColor(t.toolBarColor));
        profileBtn->setStyleSheet(ButtonStyle::buttonNavBarColor(t.hvColor));
        payBtn->setStyleSheet(ButtonStyle::buttonNavBarColor(t.hvColor));
        settingsBtn->setStyleSheet(ButtonStyle::buttonNavBarColor(t.hvColor));
        logoutBtn->setStyleSheet(ButtonStyle::buttonNavBarColor(t.hvColor));

        profileBtn->setIcon(PixmapUtils::recolorPixmap(":/icons/profile.png", t.iconColor));
        payBtn->setIcon(PixmapUtils::recolorPixmap(":/icons/cash.png", t.iconColor));
        settingsBtn->setIcon(PixmapUtils::recolorPixmap(":/icons/settings.png", t.iconColor));
}
