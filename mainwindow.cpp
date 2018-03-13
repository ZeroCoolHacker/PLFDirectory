#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmemberform.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QSortFilterProxyModel>
#include <QDebug>
#include "usersdialog.h"

MainWindow::MainWindow(User *user_logged_in, QWidget *parent) :
    QMainWindow(parent),
    user(user_logged_in),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addPermanentWidget(ui->status);
    ui->statusBar->addPermanentWidget(ui->user_label);
    ui->user_label->setText(user->username()+" logged in,");
    setupConnection();
    setupMembersModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{
    if (user->type() != "standard"){
        AddMemberForm* form = new AddMemberForm(&db, "null", this);
    //    setAttribute(Qt::WA_DeleteOnClose);
        form->exec();
    } else {
        QMessageBox::warning(this, "Access Denied!",
                             "You do not have permission to add  new member.");
    }
}


void MainWindow::setupConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath()+"/Records/database.db";
    QFile dbFile(path);
    if(!dbFile.exists()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Database","No database Exists."
                                              "Do you want to open your own database?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply==QMessageBox::Yes)
            path = QFileDialog::getOpenFileName(this,"Database",QDir::currentPath());
        else{
            qApp->closeAllWindows();
            qApp->exit(0);
        }
    }
    db.setDatabaseName(path);
    qDebug() << path;
    if(db.open())
        ui->status->setText("Database Connected");
    else
        ui->status->setText("Database not connected");
}

void MainWindow::setupMembersModel()
{
    QSqlQuery q(db);
    q.prepare("select registration_no,"
              "name,cnic, city, bloodgroup"
              ", institution, court_of_practice from members");

    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",
                              "Couldn't load members Error:" + err.text());
    }
    members_model->setQuery(q);
    member_search_proxy_model->setSourceModel(members_model);
    ui->members_tableview->setModel(member_search_proxy_model);
    ui->members_tableview->hideColumn(2);
    ui->members_tableview->hideColumn(3);
    ui->members_tableview->hideColumn(4);
    ui->members_tableview->hideColumn(5);
    ui->members_tableview->hideColumn(6);
}

void MainWindow::on_registrationsearch_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(0);
}

void MainWindow::on_namesearch_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(1);
}

void MainWindow::on_citysearch_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(3);
}


void MainWindow::on_bloodgroupsearch_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(4);
}

void MainWindow::on_members_tableview_doubleClicked(const QModelIndex &index)
{
    if(!ui->members_tableview->currentIndex().isValid())
        return;
    QModelIndexList indexes = ui->members_tableview->
            selectionModel()->selectedRows();
    if(!indexes.at(0).isValid())
        return;

    QString id = indexes.at(0).data().toString();
    qDebug() << "Registration number passed : " << id;
    AddMemberForm* detail = new AddMemberForm(&db,id, this);
//    detail->setAttribute(Qt::WA_DeleteOnClose);
    detail->exec();
}

void MainWindow::on_refresh_list_pushbutton_clicked()
{
    setupMembersModel();
}

void MainWindow::on_collegesearch_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(5);
}

void MainWindow::on_practicing_court_lineedit_textChanged(const QString &arg1)
{
    member_search_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    member_search_proxy_model->setFilterRegExp(arg1);
    member_search_proxy_model->setFilterKeyColumn(6);
}

void MainWindow::on_actionUsers_triggered()
{
    if (user->type() == "admin"){
        UsersDialog *dialog = new UsersDialog(&db, this);
        dialog->setModal(true);
        dialog->exec();
    } else {
        QMessageBox::warning(this, "Access Denied!",
                             "You don't have access to access this information");
    }
}
