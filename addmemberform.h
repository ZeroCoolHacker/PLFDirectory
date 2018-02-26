#ifndef ADDMEMBEFORM_H
#define ADDMEMBEFORM_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlDatabase>

namespace Ui {
class AddMemberForm;
}

class AddMemberForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberForm(QSqlDatabase* database,QWidget *parent = 0);

    void initializeModels();
    void setupModels();
    void setupMeritalStatusComboBoxModel();
    void clearForm();
    bool addMember();
    ~AddMemberForm();

private slots:
    void on_reset_pushbutton_clicked();

    void on_addMember_pushbutton_clicked();

private:
    Ui::AddMemberForm *ui;
    QSqlDatabase* db;
    QStringListModel* merital_status_model;
};

#endif // ADDMEMBEFORM_H
