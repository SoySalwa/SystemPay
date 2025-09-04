#ifndef GENERATEMATSTUDENT_H
#define GENERATEMATSTUDENT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QString>
#include <QSet>
#include <cctype>
#include <QRegularExpression>

class StudentIDGenerator {
public:
    StudentIDGenerator() {
        usedGradeCodes.clear();
    }

    QString generateID(const QString& grade, int gradeNumber, int studentCount) {
        int year = QDate::currentDate().year();
        QString yearPart = QString::number(year).right(2);
        QString gradeCode = getUniqueLetterCode(grade);
        QString gradeNumberPart = QString::number(gradeNumber);
        QString studentCountPart = QString("%1").arg(studentCount, 3, 10, QChar('0'));
        return QString("%1-%2-%3-%4").arg(yearPart, gradeCode, gradeNumberPart, studentCountPart);
    }

private:
    QSet<QString> usedGradeCodes;

    QString getUniqueLetterCode(const QString& grade) {
        static QString baseCode = grade.toUpper().remove(QRegularExpression("[^A-Z]")); // Convertir a mayúsculas y eliminar caracteres no alfabéticos
        if (baseCode.length() < 4) {
            baseCode = baseCode.leftJustified(4, 'X'); // Rellenar con 'X' si es menor a 4 caracteres
        } else {
            baseCode = baseCode.left(4); // Limitar a 4 caracteres si es mayor a 4
        }

        QString generatedCode;
        int suffix = 0;
        do {
            generatedCode = baseCode;
            if (suffix > 0) {
                // Si ya se usó el código base, ajustar las últimas letras para mantener unicidad
                QString suffixStr = QString::number(suffix, 36).toUpper(); // Convertir número a base 36 (usa letras y números)
                generatedCode = generatedCode.left(4 - suffixStr.length()) + suffixStr;
            }
            suffix++;
        } while (usedGradeCodes.contains(generatedCode));

        usedGradeCodes.insert(generatedCode);
        return generatedCode;
    }
};

#endif // GENERATEMATSTUDENT_H
