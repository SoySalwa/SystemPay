#include "MongoConnection.h"
#include "mainwindow.h"
#include "QLMessage.h"
#include <QDebug>
#include <string>
#include <iostream>
#include <cstdlib>

AppUsers MongoConnection::currentUser;

MongoConnection::MongoConnection() : client_(mongocxx::uri(std::getenv("MONGO_URI"))),
                                     db_(client_["SystemPay"])
{

    initDatabase();
}

MongoConnection::~MongoConnection() {}

void MongoConnection::initDatabase()
{
    try
    {
        auto ping_cmd = bsoncxx::builder::stream::document{}
                        << "ping" << 1
                        << bsoncxx::builder::stream::finalize;
        db_.run_command(ping_cmd.view());
        std::cout << "✅ Conexión a MongoDB establecida correctamente" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Error de conexión: " << e.what() << std::endl;
        throw;
    }
}

void MongoConnection::createAdministratorUsers()
{
    try
    {
        auto collection = db_["AdminUsersDB"];

        // Convertir a std::string primero
        std::string matricule = "00-ADDM-0-000";
        std::string name = "Administrador";
        std::string typeUser = "Administrador";
        std::string password = "1234";

        auto filter = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("matricule", matricule));

        auto existing = collection.find_one(filter.view());

        if (existing)
        {
            qDebug() << "El usuario administrador ya existe";
            return;
        }

        auto document = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("matricule", matricule),
            bsoncxx::builder::basic::kvp("name", name),
            bsoncxx::builder::basic::kvp("typeUser", typeUser),
            bsoncxx::builder::basic::kvp("password", password));

        auto result = collection.insert_one(document.view());

        if (result)
        {
            qDebug() << "Usuario administrador creado exitosamente";
        }
        else
        {
            qCritical() << "Error al crear usuario administrador";
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "Error en CreateAdministratorUsers:" << e.what();
    }
}

void MongoConnection::insertStudents(
    const QString &matricule,
    const QString &first_name,
    const QString &grades_student,
    const QString &date_joined,
    double &month_amount,
    const QString &school_year)
{
    /*        try
            {
                auto collection = db_["StudentsDB"];

                std::string matricule = matricule_student.toStdString();
                std::string firstName = first_name.toStdString();
                std::string grades = grades_student.toStdString();
                std::string dateJoined = date_joined.toStdString();
                std::string schoolYear = school_year.toStdString();

                auto document = bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("matricule", matricule),
                    bsoncxx::builder::basic::kvp("firstName", firstName),
                    bsoncxx::builder::basic::kvp("grades", grades),
                    bsoncxx::builder::basic::kvp("dateJoined", dateJoined),
                    bsoncxx::builder::basic::kvp("monthAmount", month_amount),
                    bsoncxx::builder::basic::kvp("schoolYear", schoolYear));

                auto result = collection.insert_one(document.view());

                if (result)
                {
                    qDebug() << "Estudiante insertado correctamente";
                }
                else
                {
                    qCritical() << "Error al insertar estudiante";
                }
            }
            catch (const std::exception &e)
            {
                qCritical() << "Error en InsertStudents:" << e.what();
            }
        }

        bool MongoConnection::findStudent(const QString &matricule)
        {
            std::string st_matricule = matricule.toStdString();

            auto collection = db_["StudentsDB"];

            auto filter = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("matricule", st_matricule));

            auto result = collection.find_one(filter.view());

            if (!result)
            {
                throw std::runtime_error("Estudiante no encontrado.");
            }

            auto doc = result->view();
            auto db_matricule = doc["matricule"];

            if (!db_matricule || db_matricule.type() != bsoncxx::type::k_string)
            {
                throw std::runtime_error("Formato de matricula invalido");
            }

            std::string find_matricule = std::string(db_matricule.get_string().value);

            if (find_matricule != st_matricule)
            {
                throw std::runtime_error("Estudinate no encontrado");
            }

            qDebug() << "Estudiante: " << st_matricule << " encontrado.";
            return true;
             */
}

void MongoConnection::createDatabasePays() const
{
    try
    {
        auto collection = db_["PaysDB"];

        QDate date = QDate::currentDate();
        int year = date.year();
        int month = date.month();

        QDate initial_date(year, month, 25);
        QDate last_date;

        if (month == 12)
        {
            last_date = QDate(year + 1, 1, 5);
        }
        else
        {
            last_date = QDate(year, month + 1, 5);
        }

        qDebug() << "Initial Date: " << initial_date.toString("yyyy-MM-dd");
        qDebug() << "Last Date: " << last_date.toString("yyyy-MM-dd");

        QString date_format = initial_date.toString("yyyy-MM-dd");
        QString last_format = last_date.toString("yyyy-MM-dd");

        std::string dateStr = date_format.toStdString();
        std::string lastStr = last_format.toStdString();

        auto filter = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("date_current", dateStr));

        auto existing = collection.find_one(filter.view());

        if (existing)
        {
            qDebug() << "La base de datos de pagos ya existe.";
            return;
        }

        auto document = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("inscription", 1000.00),
            bsoncxx::builder::basic::kvp("reinscription", 1000.00),
            bsoncxx::builder::basic::kvp("month", 500.00),
            bsoncxx::builder::basic::kvp("payLate", 100.00),
            bsoncxx::builder::basic::kvp("date_current", dateStr),
            bsoncxx::builder::basic::kvp("date_last", lastStr));

        auto result = collection.insert_one(document.view());

        if (result)
        {
            qDebug() << "Base de datos de pagos creada correctamente.";
        }
        else
        {
            qCritical() << "Error al crear base de datos de pagos.";
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "Error en createDatabasePays:" << e.what();
    }
}

PayData MongoConnection::getPaydata()
{
    PayData data_pay{};
    try
    {
        auto collection = db_["PaysDB"];
        auto filter = bsoncxx::builder::basic::make_document(); // vacío = obtener el primer registro
        auto result = collection.find_one(filter.view());

        if (!result)
            throw std::runtime_error("No se encontró información de pagos.");

        auto doc = result->view();

        data_pay.inscription = doc["inscription"].get_double().value;
        data_pay.reInscription = doc["reinscription"].get_double().value;
        data_pay.month = doc["month"].get_double().value;
        data_pay.payLate = doc["payLate"].get_double().value;

        QString currentDateStr = QString::fromStdString(std::string(doc["date_current"].get_string().value));
        QString lastDateStr = QString::fromStdString(std::string(doc["date_last"].get_string().value));

        data_pay.dateCurrent = QDate::fromString(currentDateStr, "yyyy-MM-dd");
        data_pay.dateLast = QDate::fromString(lastDateStr, "yyyy-MM-dd");
    }
    catch (const std::exception &e)
    {
        qCritical() << "Error en getPayData:" << e.what();
    }

    return data_pay;
}

bool MongoConnection::validateLogin(const QString &user, const QString &pass)
{
    try
    {
        // Conversión temprana a std::string
        std::string username = user.toStdString();
        std::string password = pass.toStdString();

        auto collection = db_["AdminUsersDB"];

        auto filter = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("matricule", username));

        auto result = collection.find_one(filter.view());

        if (!result)
        {
            throw std::runtime_error("Usuario no encontrado");
        }

        auto doc = result->view();
        auto pass_field = doc["password"];

        if (!pass_field || pass_field.type() != bsoncxx::type::k_string)
        {
            throw std::runtime_error("Formato de contraseña inválido");
        }

        std::string stored_pass = std::string(pass_field.get_string().value);
        if (password != stored_pass)
        {
            throw std::runtime_error("Contraseña incorrecta");
        }
        MongoConnection::currentUser.matricule = user;

        if (doc["name"])
        {
            MongoConnection::currentUser.name = QString::fromStdString(std::string(doc["name"].get_string().value));
        }

        qDebug() << "Validación de login exitosa";
        return true;
    }
    catch (const std::exception &e)
    {
        qCritical() << "Error en ValidateLogin:" << e.what();
        throw;
    }
}
