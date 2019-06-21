#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QMainWindow>

class BoardController;
class MainApplication: public QMainWindow
{
public:
    MainApplication(QWidget* parent = nullptr);
    ~MainApplication();

//    void BuildMenus();
//    void BuildToolMenus();

//public slots:
//    void UndoAct();
//    void RedoAct();

private:

    QToolBar*				m_undoToolbar;
    QToolBar*				m_modeToolbar;

    QAction*				m_undoAct;
    QAction*				m_redoAct;

};

#endif // MAINAPPLICATION_H
