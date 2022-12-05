#include "DuMessengerConnectionDialog.h"
#include "ui_DuMessengerConnectionDialog.h"
namespace DuarteCorporation
{
DuMessengerConnectionDialog::DuMessengerConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMessengerConnectionDialog)
{
    ui->setupUi(this);
}

DuMessengerConnectionDialog::~DuMessengerConnectionDialog()
{
    delete ui;
}

void DuMessengerConnectionDialog::on_accepter_clicked()
{
  nHostnom= ui->nomhost->text();
  mport = ui->port->value();
  accept();
}

void DuMessengerConnectionDialog::on_annuler_clicked()
{
  reject();
}
}

