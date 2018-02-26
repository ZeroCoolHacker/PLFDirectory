#include "addmembeform.h"
#include "ui_addmembeform.h"

AddMembeForm::AddMembeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMembeForm)
{
    ui->setupUi(this);
}

AddMembeForm::~AddMembeForm()
{
    delete ui;
}
