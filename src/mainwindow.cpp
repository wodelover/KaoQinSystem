#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlstr.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDialog>
#include <adduser.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&login,SIGNAL(loginSucess(QString)),this,SLOT(loginSucess(QString)));
    connect(&login,SIGNAL(quitsystem()),this,SLOT(quitsystem()));
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(timedone()));

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(db_ip);
    db.setUserName(db_username);
    db.setPassword(db_userpasswd);
    db.setDatabaseName(db_databasename);
    bool status = db.open();
    if(!status)
    {
        qDebug()<<__FILE__<<"line"<<__LINE__<<":init database false:"<<db.lastError().text();
        QMessageBox::warning(this, tr("DB Error"),
                             tr("Connect DataBase Error."),
                             QMessageBox::Ok);
        m_timer.setInterval(1);
        m_timer.start();
    }
    login.exec();
}

void MainWindow::updateAllUser()
{
    m_update = false;
    ui->table->clear();

    QStringList list = getAllHeader();

    ui->table->setColumnCount(list.size());
    ui->table->setHorizontalHeaderLabels(list);

    QSqlQuery query(sql_all_infos);
    int cnt = 0 ;
    while (query.next()) {
        if(cnt==ui->table->rowCount())
            ui->table->insertRow(cnt);

        for(int i = 0; i < list.size(); i++){
            QString temp = query.value(i).toString();

            if(i==0){
                if(temp=="0"){
                    ui->table->setItem(cnt,i,new QTableWidgetItem("管理员"));
                }
                else if (temp=="1") {
                    ui->table->setItem(cnt,i,new QTableWidgetItem("普通用户"));
                }
            }else{
                ui->table->setItem(cnt,i,new QTableWidgetItem(temp));
            }
        }
        cnt++;
    }
    m_update = true;
}

void MainWindow::updateSingle()
{
    m_update = false;
    ui->table->clear();

    QStringList list = getAllHeader();

    ui->table->setColumnCount(list.size());
    ui->table->setHorizontalHeaderLabels(list);

    QString sql_str = "SELECT * from user where userid = '";
    sql_str += m_current_id;
    sql_str += "';";

    QSqlQuery query(sql_str);
    int cnt = 0 ;
    while (query.next()) {
        if(cnt==ui->table->rowCount())
            ui->table->insertRow(cnt);

        for(int i = 0; i < list.size(); i++){
            QString temp = query.value(i).toString();

            if(i==0){
                if(temp=="0"){
                    ui->table->setItem(cnt,i,new QTableWidgetItem("管理员"));
                }
                else if (temp=="1") {
                    ui->table->setItem(cnt,i,new QTableWidgetItem("普通用户"));
                }
            }else{
                ui->table->setItem(cnt,i,new QTableWidgetItem(temp));
            }
        }
        cnt++;
    }
    m_update = true;
}

QStringList MainWindow::getAllHeader()
{
    QSqlQuery query(sql_all_fields);
    QStringList list;
    while (query.next()) {
        list.append(query.value(0).toString());
    }
    return list;
}

void MainWindow::loginSucess(QString id)
{
    m_current_id = id;

    QString sql_user_type = "SELECT type from user where userid = '";
    sql_user_type += m_current_id;
    sql_user_type += "';";
    int type = 1;
    QSqlQuery query(sql_user_type);
    while (query.next()) {
        type = query.value(0).toString().toInt();
    }
    if(type==0){
        m_isAdmin = true;
        updateAllUser();
    }else {
        m_isAdmin = false;
        updateSingle();
    }
}

void MainWindow::quitsystem()
{
    m_timer.setInterval(1);
    m_timer.start();
}

void MainWindow::timedone()
{
    this->close();
}

void MainWindow::updateUserInfo()
{
    updateAllUser();
}

void MainWindow::on_table_cellChanged(int row, int column)
{
    if(m_update){
        QString now_str = ui->table->item(row,column)->text();
        if(column==0){// 更新身份
            if(m_isAdmin){
                if(now_str=="管理员"){
                    QString sql_str = "UPDATE user set type = 0 where userid = '";
                    sql_str += ui->table->item(row,1)->text();
                    sql_str += "';";
                    QSqlQuery query(sql_str);
                    if(!query.exec()){
                        QMessageBox::warning(this,"更新错误","更新失败,数据库错误.");
                    }
                }else if(now_str=="普通用户"){
                    QString sql_str = "UPDATE user set type = 1 where userid = '";
                    sql_str += ui->table->item(row,1)->text();
                    sql_str += "';";
                    QSqlQuery query(sql_str);
                    if(!query.exec()){
                        QMessageBox::warning(this,"更新错误","更新失败,数据库错误.");
                    }
                }
            }
            else{
                updateSingle();
                QMessageBox::warning(this,"输入错误","您当前身份为普通用户");
            }
        }
        else if (column==1) { //更新ID
            if(m_isAdmin){
                QStringList list = getAllHeader();

                QString sql_str = "UPDATE user set ";
                sql_str += list[column];
                sql_str += " = '" + now_str + "' where userid = '";
                sql_str += m_table_currentpress_value;
                sql_str += "';";
                QSqlQuery query(sql_str);
                if(!query.exec()){
                    QMessageBox::warning(this,"更新错误","ID 已经存在.");
                }
            }else{
                updateSingle();
                QMessageBox::warning(this,"更新错误","您没有权限修改ID");
            }
        }
        else{
            QStringList list = getAllHeader();

            QString sql_str = "UPDATE user set ";
            sql_str += list[column];
            sql_str += " = '" + now_str + "' where userid = '";
            sql_str += ui->table->item(row,1)->text();
            sql_str += "';";
            QSqlQuery query(sql_str);
            if(!query.exec()){
                if(m_isAdmin){
                    updateAllUser();
                }else {
                    updateSingle();
                }
                QMessageBox::warning(this,"更新错误","更新失败,数据库错误.");
            }
        }
    }
}

void MainWindow::on_table_cellClicked(int row, int column)
{
    m_table_currentpress_value = ui->table->item(row,column)->text();
}

void MainWindow::on_adduser_clicked()
{
    AddUser adduser;

    connect(&adduser,SIGNAL(addUserDone()),this,SLOT(updateUserInfo()));

    adduser.exec();
}

void MainWindow::on_deleteuser_clicked()
{
    updateAllUser();
}
