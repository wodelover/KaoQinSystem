#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


const QString db_ip = "localhost";
const QString db_username = "root";
const QString db_userpasswd = "123456";
const QString db_databasename = "kaoqin";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool init();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
