#ifndef IMENU_H
#define IMENU_H


class IMenu
{
public:
    enum MenuType
    {
        k_LoginMenu,
        k_MainMenu,
        k_PlayGameMenu,
        k_ScoreMenu,
        k_OptionMenu
    };
public:
    IMenu();
//    virtual ~IMenu();

public:
//    virtual void CreateMenu();

private:

};

#endif // IMENU_H
