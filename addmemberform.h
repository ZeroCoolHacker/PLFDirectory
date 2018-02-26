#ifndef ADDMEMBEFORM_H
#define ADDMEMBEFORM_H

#include <QDialog>

namespace Ui {
class AddMembeForm;
}

class AddMemberForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddMembeForm(QWidget *parent = 0);
    ~AddMembeForm();

private:
    Ui::AddMembeForm *ui;
};

#endif // ADDMEMBEFORM_H
