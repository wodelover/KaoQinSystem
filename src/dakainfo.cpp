#include "dakainfo.h"
#include "ui_dakainfo.h"
#include <QSqlError>
#include <QSqlQuery>


DakaInfo::DakaInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DakaInfo)
{
    ui->setupUi(this);
}

DakaInfo::~DakaInfo()
{
    delete ui;
}

void DakaInfo::setUserId(QString userid, bool isadmin)
{
    QSqlQuery query("SHOW FULL COLUMNS FROM `daka`;");
    QStringList list;
    while (query.next()) {
        list.append(query.value(0).toString());
    }
    list.pop_front();
    ui->table->setColumnCount(list.size());
    ui->table->setHorizontalHeaderLabels(list);

    QString sql_str;

    if(isadmin){
        sql_str = "SELECT * FROM daka;";
    }else {
        sql_str = "SELECT * FROM daka where userid='" + userid + "';";
    }
    QSqlQuery query1(sql_str);
    query1.exec();
    int cnt = 0 ;
    while(query1.next()){
        if(cnt==ui->table->rowCount())
            ui->table->insertRow(cnt);

        for(int i = 0; i < list.size(); i++){
            QString temp = query1.value(i+1).toString();

            if(i+1==3){
                if(temp=='1'){
                    ui->table->setItem(cnt,i,new QTableWidgetItem("打卡成功"));
                }else{
                    ui->table->setItem(cnt,i,new QTableWidgetItem("打卡失败"));
                }

            }else{
                ui->table->setItem(cnt,i,new QTableWidgetItem(temp));
            }
        }
        cnt++;
    }
}
