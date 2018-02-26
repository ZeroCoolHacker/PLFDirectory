#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmemberform.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{
    AddMemberForm* form = new AddMemberForm(&db);
    form->showMaximized();
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
