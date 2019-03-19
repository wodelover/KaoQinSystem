#include "adduser.h"
#include "ui_adduser.h"
#include <QFileDialog>
#include <QStringList>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_cancel_clicked()
{
    this->close();
}

void AddUser::on_add_clicked()
{
    QString userid = ui->userid->text();
    if(userid==""){
        QMessageBox::warning(this,"添加用户","用户ID不能为空");
        return;
    }
    QString sql_str = "SELECT * from `user` where userid = '" + userid + "';";

    QSqlQuery query(sql_str);
    if(query.first()){
        QMessageBox::warning(this,"添加用户","用户ID已经存在");
        return;
    }
    QString username = ui->username->text();
    if(username==""){
        QMessageBox::warning(this,"添加用户","用户名字不能为空");
        return;
    }
    QString passwd = ui->passwd->text();
    if(passwd==""){
        QMessageBox::warning(this,"添加用户","用户密码不能为空");
        return;
    }
    QString age = ui->age->text();
    if(age.toInt() <= 0){
        QMessageBox::warning(this,"添加用户","用户年龄设置错误");
        return;
    }
    QString facepath = ui->facepath->text();
    if(facepath==""){
        QMessageBox::warning(this,"添加用户","用户年龄不能为空");
        return;
    }
    if(!facepath.endsWith(".png")&&!facepath.endsWith(".jpg")&&!facepath.endsWith(".bmp")){
        QMessageBox::warning(this,"添加用户","图片格式选择错误");
        return;
    }

    QString sex = ui->sex->currentText();
    int type = ui->type->currentIndex();


    QString sql_add = "INSERT INTO `user` VALUES(" + QString::number(type) + ",'"
            + userid + "','"
            + username + "','"
            + passwd + "','"
            + age + "','"
            + sex +"','"
            + facepath +" ');";
    if(!query.exec(sql_add)){
        QMessageBox::information(this,"添加用户","添加用户出现错误");
    }
    emit addUserDone();
    QMessageBox::information(this,"添加用户","添加成功");
}

void AddUser::on_faceselect_clicked()
{
    QString name = QFileDialog::getOpenFileName();
    QFileInfo info(name);
    ui->facepath->setText(info.absoluteFilePath());
}
