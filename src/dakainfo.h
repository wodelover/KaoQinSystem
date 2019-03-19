#ifndef DAKAINFO_H
#define DAKAINFO_H

#include <QDialog>

namespace Ui {
class DakaInfo;
}

class DakaInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DakaInfo(QWidget *parent = nullptr);
    ~DakaInfo();
    void setUserId(QString userid,bool isadmin);

private:
    Ui::DakaInfo *ui;
};

#endif // DAKAINFO_H
