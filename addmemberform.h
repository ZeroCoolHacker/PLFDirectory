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
    explicit AddMemberForm(QSqlDatabase* database,QString id="null", QWidget *parent = 0);

    void initializeModels();
    void setupModels();
    void setupMeritalStatusComboBoxModel();
    void clearForm();
    bool addMember();
    void disableForm();
    void loadUserData();
    bool isAnyFieldEmpty();
    void loadNewRegistrationNumber();
    ~AddMemberForm();

private slots:
    void on_reset_pushbutton_clicked();
    void on_addMember_pushbutton_clicked();
    void on_upload_button_toolbutton_clicked();

private:
    Ui::AddMemberForm *ui;
    QSqlDatabase* db;
    QStringListModel* merital_status_model;
    QString id;
    QString picpath;
};

#endif // ADDMEMBEFORM_H
