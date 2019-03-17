#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(db_ip);
    db.setUserName(db_username);
    db.setPassword(db_userpasswd);
    db.setDatabaseName(db_databasename);
    bool status = db.open();
    if(!status)
        qDebug()<<__FILE__<<" line "<<__LINE__<<":init database false:"<<db.lastError().text();
    return status;
}
