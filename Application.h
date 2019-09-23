#ifndef APPLICATION_H
#define APPLICATION_H

#include "GUI/MenuFactory.h"
#include "GUI/MenuManager.h"
#include "GUI/Menus/IMenu.h"

class Application :
        public Singleton<Application>
{
public:
    void Init();
    void Update();
    void Destroy();
};

#endif // APPLICATION_H
