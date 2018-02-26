#include "addmemberform.h"
#include "ui_addmemberform.h"
#include <QStringList>
#include <QString>

AddMemberForm::AddMemberForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberForm)
{
    ui->setupUi(this);
    initializeModels();
    setupModels();
}

void AddMemberForm::initializeModels()
{
    if (merital_status_model == 0) {
        QStringList status;
        status << "Married" << "Single" << "Widowed";
        merital_status_model = new QStringListModel(status);
    }
}

void AddMemberForm::setupModels()
{
  setupMeritalStatusComboBoxModel();
}

void AddMemberForm::setupMeritalStatusComboBoxModel()
{
    ui->merital_status->setModel(merital_status_model);
}

void AddMemberForm::clearForm()
{
    ui->registration_number_spinbox->clear();
    ui->name_lineedit->clear();
    ui->father_name_lineedit->clear();
    ui->cnic_lineedit->clear();
    ui->permanent_contact->clear();
    ui->emergency_contact->clear();
    ui->permanent_address_lineedit->clear();
    ui->temporary_address->clear();
    ui->city_lineedit->clear();
    ui->bloodgroup->clear();
    ui->merital_status->currentText();
    ui->guardian_name->clear();
    ui->relation_with_member->clear();
    ui->cnic_of_guardian->clear();
    ui->legal_study_status->clear();
    ui->year_of_study->clear();
    ui->institute_name->clear();
    ui->session_of_degree->clear();
    ui->license_issuing_bar->clear();
    ui->license_number->clear();
    ui->city_of_practice->clear();
    ui->court_of_practice->clear();
}

AddMemberForm::~AddMemberForm()
{
    delete ui;
}

void AddMemberForm::on_reset_pushbutton_clicked()
{
    clearForm();
}

void AddMemberForm::on_addMember_pushbutton_clicked()
{
    //gather data
    auto registration_number = ui->registration_number_spinbox->text();
    auto name                = ui->name_lineedit->text();
    auto father              = ui->father_name_lineedit->text();
    auto cnic                = ui->cnic_lineedit->text();
    auto permanent_contact   = ui->permanent_contact->text();
    auto emergency_contact   = ui->emergency_contact->text();
    auto permanent_address   = ui->permanent_address_lineedit->text();
    auto temporary_address   = ui->temporary_address->text();
    auto city                = ui->city_lineedit->text();
    auto bloodgroup          = ui->bloodgroup->text();
    auto guardian_name       = ui->guardian_name->text();
    auto relation_with_member = ui->relation_with_member->text();
    auto cnic_of_guardian    = ui->cnic_of_guardian->text();
    auto legal_study_status  = ui->legal_study_status->text();
    auto year_of_study       = ui->year_of_study->text();
    auto institute           = ui->institute_name->text();
    auto session_of_degree   = ui->session_of_degree->text();
    auto license_issuing_bar = ui->license_issuing_bar->text();
    auto license_number      = ui->license_number->text();
    auto city_of_practice    = ui->city_of_practice->text();
    auto court_of_practice   = ui->court_of_practice->text();
}
