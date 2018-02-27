#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setupConnection();
    void setupMembersModel();
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_registrationsearch_lineedit_textChanged(const QString &arg1);

    void on_namesearch_lineedit_textChanged(const QString &arg1);

    void on_citysearch_lineedit_textChanged(const QString &arg1);

    void on_sessionyearsearch_lineedit_textChanged(const QString &arg1);

    void on_bloodgroupsearch_lineedit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel* members_model;
    QSortFilterProxyModel* member_search_proxy_model;
};

#endif // MAINWINDOW_H
