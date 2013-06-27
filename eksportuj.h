#ifndef EKSPORTUJ_H
#define EKSPORTUJ_H

#include <QWidget>

namespace Ui {
class Eksportuj;
}

class Eksportuj : public QWidget
{
    Q_OBJECT
    
public:
    explicit Eksportuj(QWidget *parent = 0);
    ~Eksportuj();
    
private:
    Ui::Eksportuj *ui;
};

#endif // EKSPORTUJ_H
