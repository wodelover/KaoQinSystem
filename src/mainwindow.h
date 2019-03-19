#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <login.h>
#include <QTimer>

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
    void init();
    void updateAllUser();
    void updateSingle();
    QStringList getAllHeader();

private slots:
    void loginSucess(QString id);
    void quitsystem();
    void timedone();
    void updateUserInfo();

    void on_table_cellChanged(int row, int column);

    void on_table_cellClicked(int row, int column);

    void on_adduser_clicked();

    void on_deleteuser_clicked();

private:
    Ui::MainWindow *ui;
    Login login;
    QTimer m_timer;
    QString m_current_id;
    bool m_update = false;
    bool m_isAdmin = false;
    QString m_table_currentpress_value;
    int m_current_index = -1;
};

#endif // MAINWINDOW_H
