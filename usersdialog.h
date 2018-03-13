#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
class UsersDialog;
}

class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersDialog(QSqlDatabase *database, QWidget *parent = 0);
    void setupModel();
    bool isAnyFieldEmpty();
    ~UsersDialog();

private slots:
    void on_addaccount_pushButton_clicked();

    void on_removeaccount_pushButton_2_clicked();

private:
    Ui::UsersDialog *ui;
    QSqlDatabase *db;
    QSqlQueryModel *users_model = new QSqlQueryModel();
};

#endif // USERSDIALOG_H
