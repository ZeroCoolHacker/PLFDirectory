#ifndef ADDMEMBEFORM_H
#define ADDMEMBEFORM_H

#include <QDialog>
#include <QStringListModel>


namespace Ui {
class AddMemberForm;
}

class AddMemberForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberForm(QWidget *parent = 0);

    void initializeModels();
    void setupModels();
    void setupMeritalStatusComboBoxModel();
    void clearForm();
    ~AddMemberForm();

private slots:
    void on_reset_pushbutton_clicked();

    void on_addMember_pushbutton_clicked();

private:
    Ui::AddMemberForm *ui;
    QStringListModel* merital_status_model;
};

#endif // ADDMEMBEFORM_H
