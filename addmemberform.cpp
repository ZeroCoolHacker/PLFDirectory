#include "addmemberform.h"
#include "ui_addmemberform.h"
#include <QStringList>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

AddMemberForm::AddMemberForm(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberForm)
{
    ui->setupUi(this);
    db = database;
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

bool AddMemberForm::addMember()
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
    auto merital_status      = ui->merital_status->currentText();

    // prepare query
    QSqlQuery q(*db);
    q.prepare("INSERT INTO members(registration_no,name,"
              "father_name,cnic,permanent_contact,"
              "emergency_contact,permanent_address,"
              "temporary_address,city,bloodgroup,"
              "merital_status,guardian_of_member,"
              "relation_with_member,cnic_of_guardian,"
              "legal_study_status,year_of_study,institution,"
              "session_of_degree,license_issuing_bar,licence_number,"
              "city_of_practice,court_of_practice)"
              " VALUES (:registration_no, :name, :father_name, :cnic, :"
              "permanent_contact, :emergency_contact, :permanent_address, :"
              "temporary_address, :city, :bloodgroup, :merital_status, :"
              "guardian_of_member, :relation_with_member, :cnic_of_guardian, :"
              "legal_study_status, :year_of_study, :institution, :session_of_degree, :"
              "license_issuing_bar, :licence_number, :city_of_practice,"
              " :court_of_practice)");
    q.bindValue(":registration_no", registration_number);
    q.bindValue(":name", name);
    q.bindValue(":father_name", father);
    q.bindValue(":cnic", cnic);
    q.bindValue(":permanent_contact", permanent_contact);
    q.bindValue(":emergency_contact", emergency_contact);
    q.bindValue(":permanent_address", permanent_address);
    q.bindValue(":temporary_address", temporary_address);
    q.bindValue(":city", city);
    q.bindValue(":bloodgroup", bloodgroup);
    q.bindValue(":merital_status", merital_status);
    q.bindValue(":guardian_of_member", guardian_name);
    q.bindValue(":relation_with_member", relation_with_member);
    q.bindValue(":cnic_of_guardian", cnic_of_guardian);
    q.bindValue(":legal_study_status", legal_study_status);
    q.bindValue(":year_of_study", year_of_study);
    q.bindValue(":institution", institute);
    q.bindValue(":session_of_degree", session_of_degree);
    q.bindValue(":license_issuing_bar", license_issuing_bar);
    q.bindValue(":licence_number", license_number);
    q.bindValue(":city_of_practice", city_of_practice);
    q.bindValue(":court_of_practice", court_of_practice);

    // execute the query
    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",err.text());
        return false;
    }
    return true;
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
    if (addMember()){
        QMessageBox::information(this, "Member Added",
                                 ui->name_lineedit->text()+" added successfully!!!");
        clearForm();
    } else {
        QMessageBox::critical(this, "Error", "Could not add member to database");
    }
}
