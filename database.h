#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVector>

class Database
{

public:
        Database(QString db_name);
        ~Database();

        void CreateTable(QString name);
        void Inputing(const QString &name, const QString &surname, const QString &city , const QString &phone);
        void Updating(const QString &condition, const QString &city, const QString &phone);

        QVector<QVector<QString> > &Reading();
        QVector<QVector<QString> > &Searching(const QString &value, int filter);

public:
        QString error;

private:
        QSqlQuery *query;
        QString table_name;
        QVector< QVector<QString> > data;

};

#endif // DATABASE_H
