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
    IMenu(MenuType menuType);
    virtual ~IMenu();

public:
    virtual void CreateMenu() = 0;

private:
    MenuType m_type;
};

#endif // IMENU_H
