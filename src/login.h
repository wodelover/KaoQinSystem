#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void closeEvent(QCloseEvent *e);

private slots:
    void on_loginButton_clicked();

    void on_quitButton_clicked();

signals:
    void loginSucess(QString id);
    void quitsystem();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
