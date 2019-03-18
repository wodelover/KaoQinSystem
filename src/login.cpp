#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::closeEvent(QCloseEvent *e)
{
    emit quitsystem();
    e->accept();
}

void Login::on_loginButton_clicked()
{
    QString id = ui->username->text();
    if(id.isEmpty()){
        QMessageBox::warning(this, tr("登录错误"),
                             tr("用户ID不能为空"),
                             QMessageBox::Ok);
        return;
    }
    QString passwd = ui->passwd->text();
    if(passwd.isEmpty()){
        QMessageBox::warning(this, tr("登录错误"),
                             tr("密码不能为空"),
                             QMessageBox::Ok);
        return;
    }
    QString sql_login = "SELECT passwd='";
    sql_login += passwd;
    sql_login += "' from user where userid='";
    sql_login += id;
    sql_login += "';";

    QSqlQuery query(sql_login);
    bool status = false;
    while (query.next()) {
        status = query.value(0).toString().toInt();
    }

    if(!status){
        QMessageBox::warning(this, tr("登录错误"),
                             tr("用户ID或者密码错误"),
                             QMessageBox::Ok);
        return;
    }else {
        emit loginSucess(id);
        this->hide();
    }
}

void Login::on_quitButton_clicked()
{
    this->close();
}
