#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QMainWindow>

class BoardController;
class MainApplication: public QMainWindow
{
public:
    MainApplication(QWidget* parent = nullptr);
    ~MainApplication();

private:
    BoardController*    boardController;
};

#endif // MAINAPPLICATION_H
