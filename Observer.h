#ifndef OBSERVER_H
#define OBSERVER_H


class Entity;
class Observer
{
public:
    Observer();
    virtual ~Observer() ;

    virtual void onNotify(const Entity& entity, bool isHuman) = 0;
};

#endif // OBSERVER_H
