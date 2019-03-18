#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_cancel_clicked();

    void on_add_clicked();

    void on_faceselect_clicked();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
