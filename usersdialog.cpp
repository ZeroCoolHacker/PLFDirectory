#include "usersdialog.h"
#include "ui_usersdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "user.h"
#include <QStringListModel>
#include <QStringList>
#include <QDebug>
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
    //view users in the database
    QSqlQuery q(*db);
    q.prepare("select id, type, username from users");

    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",
                              "Couldn't load users Error:" + err.text());
    }
    users_model->setQuery(q);
    ui->users_tableview->setModel(users_model);

    //populate the account types combobox
    QStringList types;
    types << "standard" << "admin" << "manager";
    QStringListModel *model = new QStringListModel(types);
    ui->accout_type_combobox->setModel(model);
}

bool UsersDialog::isAnyFieldEmpty()
{
   if (ui->username_lineedit->text().isEmpty()
           || ui->password_lineedit->text().isEmpty()
           || ui->accout_type_combobox->currentIndex() == -1)
       return true;
   return false;
}



UsersDialog::~UsersDialog()
{
    delete ui;
}

void UsersDialog::on_addaccount_pushButton_clicked()
{
    if (isAnyFieldEmpty()){
        QMessageBox::information(this, "Empty Fields", "Fill the remaining fields");
        return;
    }
    QString username = ui->username_lineedit->text();
    QString password = ui->password_lineedit->text();
    QString type = ui->accout_type_combobox->currentText();
    User *user = new User(username, type);
    user->setPassword(password);
    //prepare the query
    QSqlQuery q(*db);
    q.prepare("insert into users(type, username, password)"
              " values (:type, :username, :password); ");
    q.bindValue(":type", user->type());
    q.bindValue(":username", user->username());
    q.bindValue(":password", user->password());
    if (!q.exec()){
        QMessageBox::warning(this, "Failed",
                             "Could not add user into database"
                             " due to error : " + q.lastError().text());
                return;
    }
    QMessageBox::information(this, "Success!", "New user added successfully");
    setupModel();
}

void UsersDialog::on_removeaccount_pushButton_2_clicked()
{
    if (!ui->users_tableview->currentIndex().isValid()) return;

    QModelIndexList indexes = ui->users_tableview->
            selectionModel()->selectedRows();
    if(!indexes.at(0).isValid())
        return;

    QString id = indexes.at(0).data().toString();
    qDebug() << "Account Id : " << id;
    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Are You Sure?\n",
                                  "You can not undo this action."
                                  "Do you want to continue?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if(reply == QMessageBox::Yes){
        QSqlQuery q(*db);
        q.prepare("delete from users where id=:id");
        q.bindValue(":id", id);
        if (!q.exec()){
            QMessageBox::warning(this, "Failed",
                                 "Could not remove the user"
                                 " due to error : " + q.lastError().text());
                    return;
        }
        setupModel();
    }
}
