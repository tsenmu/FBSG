#ifndef COLORSTATUS_H
#define COLORSTATUS_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class ColorStatus;
}

class ColorStatus : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorStatus(QWidget *parent = 0);
    ~ColorStatus();
    void set(int index);
    
private:
    Ui::ColorStatus *ui;
    QList<QLabel*> labels;
};

#endif // COLORSTATUS_H
