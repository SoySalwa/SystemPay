#ifndef MONGOCONNECTION_H
#define MONGOCONNECTION_H

#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>

#include "QLMessage.h"

#include <mongocxx/uri.hpp>
#include <mongocxx/collection.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <QString>
#include <QDebug>
#include <string>
#include <iostream>
#include <QDate>

struct AppUsers
{
    QString matricule;
    QString name;
    QString license;
    QString role;
};

struct PayData
{
    double inscription;
    double reInscription;
    double month;
    double payLate;
    QDate dateCurrent;
    QDate dateLast;
};

class MongoConnection
{
public:
    static MongoConnection &getInstance()
    {
        static MongoConnection instance;
        return instance;
    }
    MongoConnection();
    ~MongoConnection();

    void initDatabase();
    void insertStudents(
        const QString &matricule,
        const QString &first_name,
        const QString &grades_student,
        const QString &date_joined,
        double &month_amount,
        const QString &school_year);
    void createAdministratorUsers();
    void createDatabasePays() const;
    bool validateLogin(const QString &user, const QString &pass);
    bool findStudent(const QString &matricule);
    PayData getPaydata();
    static AppUsers currentUser;

private:
    // Instancia de mongocxx ahora es miembro privado
    mongocxx::client client_;
    mongocxx::database db_;
    QLMessage *ql_message;
    QWidget *content_area;
};

#endif // MONGOCONNECTION_H
