#include "window.h"

Window::Window(QWidget *parent): QDialog(parent)
{
    Layout();
}

Window::~Window()
{

}

void Window::Layout()
{
    QString name[] = {"Name", "Surname", "City", "Phone"};
    QLineEdit *tmp;
    QRadioButton *rbtmp;

    QHBoxLayout *top_layer = new QHBoxLayout;
    tmp = edit("Phonebook");
    edits.push_back(tmp);

    top_layer->addWidget(tmp);
    top_layer->addWidget(button("Open", "Open or create phonebook"));

    QGroupBox *top_layer_box = new QGroupBox;
    top_layer_box->setLayout(top_layer);
    top_layer_box->setStyleSheet("border: none;");

    QHBoxLayout *middle_layer = new QHBoxLayout;
    table = new QTableWidget;
    table->setMinimumWidth(416);
    table->setStyleSheet("background: rgba(255, 204, 204, 20); border: none;");
    middle_layer->addWidget(table);

    QVBoxLayout *search_unit = new QVBoxLayout;
    search_unit->setAlignment(Qt::AlignTop);
    tmp = edit("value");
    edits.push_back(tmp);
    search_unit->addWidget(tmp);

    QHBoxLayout *first_row = new QHBoxLayout;
    rbtmp = radiobutton("Name");
    rbtmp->setChecked(true);
    radios.push_back(rbtmp);
    first_row->addWidget(rbtmp);
    rbtmp = radiobutton("Surname");
    radios.push_back(rbtmp);
    first_row->addWidget(rbtmp);

    QHBoxLayout *second_row = new QHBoxLayout;
    rbtmp = radiobutton("City");
    radios.push_back(rbtmp);
    second_row->addWidget(rbtmp);
    rbtmp = radiobutton("Phone");
    radios.push_back(rbtmp);
    second_row->addWidget(rbtmp);

    search_unit->addSpacing(15);
    search_unit->addLayout(first_row);
    search_unit->addSpacing(15);
    search_unit->addLayout(second_row);

    search_unit->addSpacing(15);
    search_btn = button("Search", "Search");
    search_btn->setEnabled(false);

    search_unit->addWidget(search_btn);
    middle_layer->addLayout(search_unit);

    QHBoxLayout *new_layer = new QHBoxLayout;
    for(int i=0; i<4; i++)
    {
        tmp = edit(name[i]);
        edits.push_back(tmp);
        new_layer->addWidget(tmp);
    }

    QVBoxLayout *bottom_layer = new QVBoxLayout;
    bottom_layer->addLayout(new_layer);

    QHBoxLayout *bottom_layer_buttons = new QHBoxLayout;
    add_btn = button("Add", "Add new field to phonebook");
    add_btn->setEnabled(false);
    update_btn = button("Update", "Updating city and phone");
    update_btn->setEnabled(false);

    QHBoxLayout *bottom_layer_condition = new QHBoxLayout;
    QLabel *lbl = new QLabel("Condition: ");
    lbl->setFont(QFont("Ubuntu", 10, QFont::Cursive));
    bottom_layer_condition->addWidget(lbl);
    tmp = edit("Name");
    edits.push_back(tmp);
    bottom_layer_condition->addWidget(tmp);

    bottom_layer_buttons->addWidget(add_btn);
    bottom_layer_buttons->addWidget(update_btn);
    bottom_layer->addLayout(bottom_layer_condition);
    bottom_layer->addLayout(bottom_layer_buttons);

    QGroupBox *bottom_layer_box = new QGroupBox();
    bottom_layer_box->setLayout(bottom_layer);

    show_btn = button("Show", "Show whole phonebook");
    show_btn->setEnabled(false);

    status = new QStatusBar;
    status->setStyleSheet("background: rgba(110, 100, 110, 100); color: white; "
                          "font-weight: bold;");
//    status->setGraphicsEffect(new QGraphicsDropShadowEffect);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(top_layer_box);
    layout->addLayout(middle_layer);
    layout->addWidget(bottom_layer_box);
    layout->addWidget(show_btn);
    layout->addWidget(status);
    this->setLayout(layout);

    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.5, QColor(199, 142, 135));
    gradient.setColorAt(1, QColor(103, 38, 56));
    QPalette pal;
    pal.setBrush(this->backgroundRole(), gradient);
    this->setPalette(pal);

    this->setFixedSize(640, 480);
}

QLineEdit *Window::edit(QString value)
{
    QLineEdit *line = new QLineEdit(value);
    line->setStyleSheet("background: rgb(255, 250, 246); "
                        "border: 1px solid gray; font-family: Amsdam cyr-lat;");

    return line;
}

QPushButton *Window::button(QString title, QString tip)
{
    QPushButton *btn = new QPushButton(title);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setToolTip(tip);
    btn->setStyleSheet("QPushButton:hover {background: rgb(233, 231, 235); } "
                       "QPushButton {background: rgb(225, 198, 172);  "
                       "font-family: v_CCAdamKubert; border: 1px solid white; }");
    btn->setMinimumSize(80, 20);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(slotButton()));

    return btn;
}

QRadioButton *Window::radiobutton(QString title)
{
    QRadioButton *radio = new QRadioButton(title);
    radio->setFont(QFont("Amsdam cyr-lat", 10, QFont::Cursive));

    return radio;
}

void Window::slotButton()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if(btn->text() == "Open")
    {
        bool exist = false; // for Windows may be applicationDirPath
        if(QFile::exists(edits[0]->text())) exist = true;

        database = new Database(edits[0]->text());
        if(!exist) database->CreateTable("List");
        if(!database->error.isEmpty())
        {
            status->showMessage(database->error, 3000);
            database->error.clear();
        }
        else status->showMessage("Phonebook is opened!", 3000);

        add_btn->setEnabled(true);
        show_btn->setEnabled(true);
        search_btn->setEnabled(true);
        update_btn->setEnabled(true);
    }

    if(btn->text() == "Add")
    {
        database->Inputing(edits[2]->text(), edits[3]->text(), edits[4]->text(), edits[5]->text());
        if(!database->error.isEmpty())
        {
            status->showMessage(database->error, 3000);
            database->error.clear();
        }
       else status->showMessage("Adding is successfuly!", 3000);

        edits[2]->clear();
        edits[3]->clear();
        edits[4]->clear();
        edits[5]->clear();
    }

    if(btn->text() == "Show")
    {
        QVector< QVector<QString> > data = database->Reading();
        if(!database->error.isEmpty())
        {
            status->showMessage(database->error, 3000);
            database->error.clear();
        }
        else status->showMessage("Reading is successfully!", 3000);

        TableInputing(data);
    }

    if(btn->text() == "Search")
    {
        QVector< QVector<QString> > data;

        if(radios[0]->isChecked()) data = database->Searching(edits[1]->text(), 1);
        if(radios[1]->isChecked()) data = database->Searching(edits[1]->text(), 2);
        if(radios[2]->isChecked()) data = database->Searching(edits[1]->text(), 3);
        if(radios[3]->isChecked()) data = database->Searching(edits[1]->text(), 4);

        if(!database->error.isEmpty())
        {
            status->showMessage(database->error, 3000);
            database->error.clear();
        }
        else status->showMessage("Searching is successfully!", 3000);

        TableInputing(data);
    }

    if(btn->text() == "Update")
    {
        database->Updating(edits[6]->text(), edits[4]->text(), edits[5]->text());
        if(!database->error.isEmpty())
        {
            status->showMessage(database->error, 3000);
            database->error.clear();
        }
        else status->showMessage("Updating is successfully!", 3000);
    }
}

void Window::TableInputing(QVector< QVector<QString> > &data)
{
    table->clear();

    QTableWidgetItem *item;

    table->setRowCount(data.size());
    table->setColumnCount(4);

    QStringList headers;
    headers << "Name" << "Surname" << "City" << "Phone";
    table->setHorizontalHeaderLabels(headers);

    for(int i=0; i<data.size(); i++)
        for(int j=0; j<4; j++)
        {
            item = new QTableWidgetItem(data[i][j]);
            table->setItem(i, j, item);
        }
}
