#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QMainWindow>

class BoardController;
class MainApplication: public QMainWindow
{
public:
    MainApplication(QWidget* parent = nullptr);
    ~MainApplication();

    bool isAIplayer() const;

    void Init();


private:
    BoardController*    m_boardController;
};

#endif // MAINAPPLICATION_H
