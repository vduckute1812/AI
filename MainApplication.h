#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QMainWindow>

class BoardController;
class MainApplication: public QMainWindow
{
public:
    MainApplication(QWidget* parent = nullptr);
    ~MainApplication();

    void Init();


private:
    BoardController*    m_boardController;
};

#endif // MAINAPPLICATION_H
