#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QStatusBar>
#include <QGroupBox>
#include <QVector>
#include <QLinearGradient>
#include <QPalette>

#include "database.h"

class Database;

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        void Layout();
        QLineEdit *edit(QString value);
        QPushButton *button(QString title, QString tip);
        QRadioButton *radiobutton(QString title);
        void TableInputing(QVector<QVector<QString> > &data);

private:
        QTableWidget *table;
        QPushButton *show_btn, *add_btn, *search_btn, *update_btn;
        Database *database;
        QVector<QLineEdit*> edits;
        QVector<QRadioButton*> radios;
        QStatusBar *status;

private slots:
            void slotButton();
};

#endif // WINDOW_H
