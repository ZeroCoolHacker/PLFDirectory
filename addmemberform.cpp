#include "addmemberform.h"
#include "ui_addmemberform.h"
#include <QStringList>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>

AddMemberForm::AddMemberForm(QSqlDatabase *database, QString registration_no, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberForm)
{
    ui->setupUi(this);
    db = database;
    qDebug() << "ui setup complete";
    initializeModels();
    setupModels();
    qDebug() << "All Models are setup properly";
    if (registration_no != "null") {
        id = registration_no;
        disableForm();
        loadUserData();
    }
}

void AddMemberForm::initializeModels()
{
    QStringList status;
    status << "Married" << "Single" << "Widowed";
    merital_status_model = new QStringListModel(status);
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

void AddMemberForm::disableForm()
{
    ui->registration_number_spinbox->setReadOnly(true);
    ui->name_lineedit->setReadOnly(true);
    ui->father_name_lineedit->setReadOnly(true);
    ui->cnic_lineedit->setReadOnly(true);
    ui->permanent_contact->setReadOnly(true);
    ui->emergency_contact->setReadOnly(true);
    ui->permanent_address_lineedit->setReadOnly(true);
    ui->temporary_address->setReadOnly(true);
    ui->city_lineedit->setReadOnly(true);
    ui->bloodgroup->setReadOnly(true);
    ui->merital_status->currentText();
    ui->guardian_name->setReadOnly(true);
    ui->relation_with_member->setReadOnly(true);
    ui->cnic_of_guardian->setReadOnly(true);
    ui->legal_study_status->setReadOnly(true);
    ui->year_of_study->setReadOnly(true);
    ui->institute_name->setReadOnly(true);
    ui->session_of_degree->setReadOnly(true);
    ui->license_issuing_bar->setReadOnly(true);
    ui->license_number->setReadOnly(true);
    ui->city_of_practice->setReadOnly(true);
    ui->court_of_practice->setReadOnly(true);
}

void AddMemberForm::loadUserData()
{
    QSqlQuery q(*db);
    q.prepare("select * from members where registration_no=:id");
    q.bindValue(":id", id);
    qDebug() << "ID : " << id;
    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",err.text());
        return;
    }
    //get the data
    while (q.next()){
        auto name                = q.value(q.record().indexOf("name")).toString();
        auto father              = q.value(q.record().indexOf("father_name")).toString();
        auto cnic                = q.value(q.record().indexOf("cnic")).toString();
        auto permanent_contact   = q.value(q.record().indexOf("permanent_contact")).toString();
        auto emergency_contact   = q.value(q.record().indexOf("emergency_contact")).toString();
        auto permanent_address   = q.value(q.record().indexOf("permanent_address")).toString();
        auto temporary_address   = q.value(q.record().indexOf("temporary_address")).toString();
        auto city                = q.value(q.record().indexOf("city")).toString();
        auto bloodgroup          = q.value(q.record().indexOf("bloodgroup")).toString();
        auto guardian_name       = q.value(q.record().indexOf("guardian_of_member")).toString();
        auto relation_with_member = q.value(q.record().indexOf("relation_with_member")).toString();
        auto cnic_of_guardian    = q.value(q.record().indexOf("cnic_of_guardian")).toString();
        auto legal_study_status  = q.value(q.record().indexOf("legal_study_status")).toString();
        auto year_of_study       = q.value(q.record().indexOf("year_of_study")).toString();
        auto institute           = q.value(q.record().indexOf("institution")).toString();
        auto session_of_degree   = q.value(q.record().indexOf("session_of_degree")).toString();
        auto license_issuing_bar = q.value(q.record().indexOf("license_issuing_bar")).toString();
        auto license_number      = q.value(q.record().indexOf("license_number")).toString();
        auto city_of_practice    = q.value(q.record().indexOf("city_of_practice")).toString();
        auto court_of_practice   = q.value(q.record().indexOf("court_of_practice")).toString();
        auto merital_status      = q.value(q.record().indexOf("merital_status")).toString();
        qDebug() << name << father << merital_status ;
        // display data
        ui->registration_number_spinbox->setValue(id.toLongLong());
        ui->name_lineedit->setText(name);
        ui->father_name_lineedit->setText(father);
        ui->cnic_lineedit->setText(cnic);
        ui->permanent_contact->setText(permanent_contact);
        ui->emergency_contact->setText(emergency_contact);
        ui->permanent_address_lineedit->setText(permanent_address);
        ui->temporary_address->setText(temporary_address);
        ui->city_lineedit->setText(city);
        ui->bloodgroup->setText(bloodgroup);
        ui->guardian_name->setText(guardian_name);
        ui->relation_with_member->setText(relation_with_member);
        ui->cnic_of_guardian->setText(cnic_of_guardian);
        ui->legal_study_status->setText(legal_study_status);
        ui->year_of_study->setText(year_of_study);
        ui->institute_name->setText(institute);
        ui->license_number->setText(license_number);
        ui->city_of_practice->setText(city_of_practice);
        ui->session_of_degree->setText(session_of_degree);
        ui->license_issuing_bar->setText(license_issuing_bar);
        ui->court_of_practice->setText(court_of_practice);
        ui->merital_status->setCurrentText(merital_status);
    }
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
