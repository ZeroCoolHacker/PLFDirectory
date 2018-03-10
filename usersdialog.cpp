#include "usersdialog.h"
#include "ui_usersdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

UsersDialog::UsersDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);
    db = database;
    setupModel();
}

void UsersDialog::setupModel()
{
    QSqlQuery q(*db);
    q.prepare("select id, type, username from users");

    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",
                              "Couldn't load users Error:" + err.text());
    }
    users_model->setQuery(q);
    ui->users_tableview->setModel(users_model);
}

UsersDialog::~UsersDialog()
{
    delete ui;
}
