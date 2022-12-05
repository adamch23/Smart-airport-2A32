#ifndef DUMESSENGERCONNECTIONDIALOG_H
#define DUMESSENGERCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DuMessengerConnectionDialog;
}
namespace DuarteCorporation
{
class DuMessengerConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuMessengerConnectionDialog(QWidget *parent = nullptr);
    ~DuMessengerConnectionDialog();
    QString nomHost() const;
    qint16 port() const;

private slots:
    void on_accepter_clicked();

    void on_annuler_clicked();

private:
    Ui::DuMessengerConnectionDialog *ui;
    QString nHostnom;
    qint16 mport;
};

inline QString DuMessengerConnectionDialog :: nomHost() const
{
    return nHostnom;
}

inline qint16 DuMessengerConnectionDialog :: port() const
{
    return mport;
}
}
#endif // DUMESSENGERCONNECTIONDIALOG_H
