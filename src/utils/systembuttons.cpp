#include "systembuttons.h"
#include "MongoConnection.h"
#include "QLMessage.h"
#include "GenerateMatStudent.h"

SystemButtons::SystemButtons(QObject *parent)
    : QObject(parent)
{
}
QPushButton *SystemButtons::createButton(const QString &icon_path, const QString &label, const QString &objectName, const std::function<void()> &onClick)
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(icon_path));
    button->setIconSize(QSize(24, 24));
    button->setText(label);
    button->setProperty("label", label);
    button->setObjectName(objectName);
    button->setToolTip(label);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (objectName == "add_student")
    {
        addStudentBtn = button;
    }
    connect(button, &QPushButton::clicked, button, [=]()
            {

        if (active_button && active_button != button) {
            active_button->setChecked(false);
            emit buttonDeactivated(active_button);
        }

        if (onClick) onClick(); });
    return button;
}

void SystemButtons::onAddStudentClicked()
{
    /*   contentArea = SystemPay::getInstance().getContentArea();

      if (!contentArea)
      {
          qDebug() << "Error: contentArea es nullptr";
          return;
      }

      if (contentArea->layout())
      {
          contentArea->setLayout(new QVBoxLayout);
      }

      addStudentBtn->setEnabled(false);

      // Conexión a la base de datos
      PayData data_pay = MongoConnection::getInstance().getPaydata();

      // Widget principal para el formulario
      QWidget *student_layout = new QWidget();
      student_layout->setObjectName("st_layout");
      student_layout->setStyleSheet("background-color: #0e0e0e;");

      // Layout principal
      QVBoxLayout *mainStudentLayout = new QVBoxLayout(student_layout);
      // mainStudentLayout->setContentsMargins(20, 20, 20, 20);
      mainStudentLayout->setSpacing(20);

      // Nuevo widget para los elementos del formulario
      QWidget *newStudentLayout = new QWidget();
      newStudentLayout->setStyleSheet("background-color: none; border-radius: 10px;");
      newStudentLayout->setFixedWidth(550);
      newStudentLayout->setFixedHeight(450);

      // Layout para el formulario
      QVBoxLayout *toolLayout = new QVBoxLayout(newStudentLayout);
      toolLayout->setContentsMargins(15, 10, 15, 10);

      // Título
      QLabel *title_name = new QLabel("Registrar nuevo estudiante");
      title_name->setStyleSheet("color: white;font-size: 14pt;");

      // Campo para nombres de estudiantes
      QLineEdit *StudentNames = new QLineEdit();
      StudentNames->setObjectName("StudentsNames");
      StudentNames->setPlaceholderText("Nombres del estudiante");

      // ComboBox para seleccionar la categoría de grado
      QComboBox *gradeCategory = new QComboBox();
      gradeCategory->setObjectName("CategoryGrades");
      gradeCategory->addItem("Selecciona una categoría...");
      gradeCategory->addItem("Inicial");
      gradeCategory->addItem("Primaria");
      gradeCategory->addItem("Secundaria");

      // ComboBox para seleccionar el grado
      QComboBox *gradeComboBox = new QComboBox();
      gradeComboBox->setObjectName("Grades");

      // ComboBox para seleccionar el año escolar
      QComboBox *schoolYear = new QComboBox();
      schoolYear->setObjectName("school_year");
      schoolYear->addItem("Selecciona el año Escolar...");
      schoolYear->addItem("2025 - 2026");

      connect(schoolYear, &QComboBox::currentIndexChanged, this, [=]()
              {
            if (schoolYear->currentIndex() == 0) {
                return message.messageAlert(student_layout, "Selecciona el año escolar.");
            } });

      // Conectar la señal de cambio de categoría con la actualización de grados
      connect(gradeCategory, &QComboBox::currentTextChanged, this, [=](const QString &category)
              {
            gradeComboBox->clear();
            gradeComboBox->addItem("Sin Seleccionar...");
            if (category == "Inicial") {
                gradeComboBox->addItem("Pre-Kinder");
                gradeComboBox->addItem("Kinder");
                gradeComboBox->addItem("Pre-Primario");
            } else if (category == "Primaria") {
                gradeComboBox->addItem("Primero");
                gradeComboBox->addItem("Segundo");
                gradeComboBox->addItem("Tercero");
                gradeComboBox->addItem("Cuarto");
                gradeComboBox->addItem("Quinto");
                gradeComboBox->addItem("Sexto");
            } else if (category == "Secundaria") {
                gradeComboBox->addItem("Primero Secundaria");
                gradeComboBox->addItem("Segundo Secundaria");
                gradeComboBox->addItem("Tercero Secundaria");
                gradeComboBox->addItem("Cuarto Secundaria");
                gradeComboBox->addItem("Quinto Secundaria");
                gradeComboBox->addItem("Sexto Secundaria");
            } });

      // Estilo para campos de entrada y ComboBox
      QString LineStyle(
          "QLineEdit {"
          "color: #ffffff;"
          "border: 1px solid #ffffff;"
          "background-color: #000320;"
          "margin-bottom: 20px;"
          "font-size: 12pt;"
          "padding: 12px;"
          "}"
          "QComboBox {"
          "color: #ffffff;"
          "background-color: #000320;"
          "border: 1px solid #ffffff;"
          "font-size: 14pt;"
          "padding: 12px;"
          "}"
          "QDateEdit {"
          "color: #ffffff;"
          "background-color: #000320;"
          "border: 1px solid #ffffff;"
          "font-size: 14pt;"
          "}");

      // Campo para fecha de ingreso
      QDateEdit *datePay = new QDateEdit();
      datePay->setObjectName("DateStudent");
      datePay->setCalendarPopup(true);
      datePay->setDate(QDate::currentDate());
      datePay->setEnabled(false);

      // Layout para botones
      QHBoxLayout *button_layout = new QHBoxLayout();

      if (!StudentNames)
      {
          message.messageAlert(student_layout, "Ingresa el nombre del estudiante.");
      }
      QLineEdit *registrationAmount = new QLineEdit();

      double dbPay = data_pay.inscription;
      // Campo para el monto de inscripción
      registrationAmount->setObjectName("InscriptionAmount");
      registrationAmount->setText(QString::number(dbPay, 'f', 2));
      registrationAmount->setPlaceholderText("Monto de inscripción");
      registrationAmount->setEnabled(false);

      // Botón de inscripción
      QPushButton *btnInscrip = new QPushButton("Inscribir");
      btnInscrip->setObjectName("btnInscription");
      QPushButton *closeBtn = new QPushButton("Cerrar");

      // Estilo para botones
      QString buttonStyle = R"(
            QPushButton {
                color: white;
                background-color: #0055ff;
                border: none;
                font-size: 12pt;
                padding: 10px 20px;
                border-radius: 5px;
            }
            QPushButton:hover {
                background-color: #0033cc;
            }
            QPushButton:pressed {
                background-color: #001a80;
            }
            )";
      btnInscrip->setStyleSheet(buttonStyle);
      closeBtn->setStyleSheet(buttonStyle);

      // Conectar la señal de cambio de texto del monto de inscripción
      connect(registrationAmount, &QLineEdit::textChanged, this, [this, dbPay, registrationAmount, btnInscrip, student_layout]()
              {
                QString payAmountText = registrationAmount->text();
                bool ok;
                int amountPay = payAmountText.toInt(&ok);

                // Si el texto no es un número válido, deshabilitar el botón
                if (!ok) {
                    message.messageAlert(student_layout, "La cantidad de inscripción no es válida.");
                    btnInscrip->setEnabled(false);
                    return;
                }

                // Si el monto ingresado es menor o mayor que el monto de la base de datos, deshabilitar el botón
                if (amountPay < dbPay) {
                    message.messageAlert(student_layout, "La inscripción no puede ser menor que " + QString::number(dbPay));
                    btnInscrip->setEnabled(false);
                } else if (amountPay > dbPay) {
                    message.messageAlert(student_layout, "La inscripción no puede ser mayor que " + QString::number(dbPay));
                    btnInscrip->setEnabled(false);
                } else {
                    // Si el monto es correcto, habilitar el botón
                    btnInscrip->setEnabled(true);
                } });

      // Conectar botones a acciones
      connect(btnInscrip, &QPushButton::clicked, this, [this]()
              { onBtnInscriptionClicked(); });
      connect(closeBtn, &QPushButton::clicked, this, [this]()
              { onBtnCloseClicked(); });

      // Añadir widgets al layout de botones
      button_layout->addWidget(btnInscrip);
      button_layout->addWidget(closeBtn);

      // Añadir widgets al layout del formulario
      toolLayout->addWidget(title_name);
      toolLayout->addWidget(StudentNames);
      toolLayout->addWidget(gradeCategory);
      toolLayout->addWidget(gradeComboBox);
      toolLayout->addWidget(schoolYear);
      toolLayout->addWidget(datePay);
      toolLayout->addWidget(registrationAmount);

      // Añadir layouts al layout principal
      mainStudentLayout->addWidget(newStudentLayout);
      mainStudentLayout->addLayout(button_layout);

      // Añadir el widget de estudiantes al área de contenido
      contentArea->layout()->addWidget(student_layout); */
}

void SystemButtons::onUpdStudentClicked() {}
void SystemButtons::onReportsClicked() {}
void SystemButtons::onPayStudent() {}

QWidget *SystemButtons::onlogoutButton()
{
    /* WindowsHandlers* windows_handlers = new WindowsHandlers;
     SystemPay* system_pay = new SystemPay;

     return windows_handlers->createWindowLogin(system_pay->contentArea); */
    return nullptr;
}

void SystemButtons::onBtnInscriptionClicked()
{
    /* // Obtener widgets
    QLineEdit *studentNamesEdit = findChild<QLineEdit *>("StudentsNames");
    QComboBox *categoryGradesBox = findChild<QComboBox *>("CategoryGrades");
    QComboBox *gradesBox = findChild<QComboBox *>("Grades");
    QDateEdit *dateEdit = findChild<QDateEdit *>("DateStudent");
    QLineEdit *inscriptionAmountEdit = findChild<QLineEdit *>("InscriptionAmount");
    QComboBox *schoolYearBox = findChild<QComboBox *>("school_year");

    QLMessage *ql_message = new QLMessage();

    // Validar que todos los widgets existan
    if (!studentNamesEdit || !categoryGradesBox || !gradesBox ||
        !dateEdit || !inscriptionAmountEdit || !schoolYearBox)
    {
        qDebug() << "Error: No se encontraron todos los campos requeridos.";
        return;
    }

    // Obtener valores de los widgets
    QString studentName = studentNamesEdit->text();
    QString categoryGrade = categoryGradesBox->currentText();
    QString grade = gradesBox->currentText();
    QString date = dateEdit->text();
    QString inscriptionAmountStr = inscriptionAmountEdit->text();
    QString schoolYear = schoolYearBox->currentText();

    // Validar campos vacíos
    if (studentName.isEmpty() || categoryGrade.isEmpty() || grade.isEmpty())
    {
        ql_message->messageAlert(nullptr, "Los campos no pueden estar vacíos.");
        return;
    }

    // Generar matrícula
    StudentIDGenerator idGenerator;
    int studentCount = 1; // ⚠️ Aquí deberías poner la lógica real para contar
    QString matricule = idGenerator.generateID(grade, categoryGrade.toInt(), studentCount);

    if (matricule.isEmpty())
    {
        ql_message->messageAlert(nullptr, "No se pudo inscribir al estudiante");
        return;
    }

    // Convertir monto
    double monthAmount = inscriptionAmountStr.toDouble();

    // Insertar en MongoDB
    MongoConnection::getInstance().insertStudents(
        studentName, // nombre del estudiante
        grade,       // grado
        date,        // fecha
        monthAmount, // monto
        schoolYear   // año escolar
    ); */
}

void SystemButtons::onBtnCloseClicked() {};