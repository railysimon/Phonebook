#include "database.h"

Database::Database(QString db_name) : table_name("List")
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_name);
    db.setUserName("Andriana");
    db.setPassword("0000");
    db.setHostName("localhost");

    if(!db.open())
    {
        error = "Can not open db manager. " + db.lastError().text();
        qDebug() << "Can not open db manager";
    }

    query = new QSqlQuery(db);
}

Database::~Database()
{

}

void Database::CreateTable(QString name)
{
    table_name = name;

    QString table = "CREATE TABLE " + name + "("
                                             "Name VARCHAR(20),"
                                             "Surname VARCHAR(20),"
                                             "City VARCHAR(15),"
                                             "Phone VARCHAR(20)"
                                             ");";
    if(!query->exec(table))
    {
        error = "Unable to create table!";
        qDebug() << "Unable to create table!";
    }
}

void Database::Inputing(const QString &name, const QString &surname, const QString &city, const QString &phone)
{
    QString tamplate = "INSERT INTO " + table_name + "(Name, Surname, City, Phone)"
                       "VALUES('%1', '%2', '%3', '%4');";

    QString command = tamplate.arg(name)
                        .arg(surname)
                        .arg(city)
                        .arg(phone);

    if(!query->exec(command))
    {
        error = "Error with inputing data!";
        qDebug() << "Error with inputing data!";
    }
}

void Database::Updating(const QString &condition, const QString &city, const QString &phone)
{
    QString command = "UPDATE List SET City = \""
            + city + "\", Phone = \"" + phone + "\" WHERE Name = \""+ condition +"\";";

    if(!query->exec(command))
    {
        error = "Error with updating data!";
        qDebug() << "Error with updating data!";
    }

}

QVector< QVector<QString> > &Database::Reading()
{
    data.clear();

    if(!query->exec("SELECT * FROM " + table_name + ";"))
    {
        error = "Unable to read data!";
        qDebug() << "Unable to read data!";
    }

    while(query->next())
    {
        QVector<QString> row;

        for(int i=0; i<4; i++)
            row.push_back(query->value(i).toString());

        data.push_back(row);
    }

    return data;
}

QVector<QVector<QString> > &Database::Searching(const QString &value, int filter)
{
    data.clear();

    if(filter == 1)
    {
        if(!query->exec("SELECT * FROM List WHERE Name = \"" + value + "\";"))
        {
            error = "Unable to search data!";
            qDebug() << "Unable to search data!";
        }
    }
    else if(filter == 2)
    {
        if(!query->exec("SELECT * FROM List WHERE Surname = \"" + value + "\";"))
        {
            error = "Unable to search data!";
            qDebug() << "Unable to search data!";
        }
    }
    else if(filter == 3)
    {
        if(!query->exec("SELECT * FROM List WHERE City = \"" + value + "\";"))
        {
            error = "Unable to search data!";
            qDebug() << "Unable to search data!";
        }
    }
    else
    {
        if(!query->exec("SELECT * FROM List WHERE Phone = \"" + value + "\";"))
        {
            error = "Unable to search data!";
            qDebug() << "Unable to search data!";
        }
    }

    while(query->next())
    {
        QVector<QString> row;

        for(int i=0; i<4; i++)
            row.push_back(query->value(i).toString());

        data.push_back(row);
    }

    return data;
}
