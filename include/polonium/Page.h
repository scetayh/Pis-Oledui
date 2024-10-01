#ifndef PAGE_H
#define PAGE_H

#include "Element.h"
#include <list>

class Page
{
private:
    std::list<Element*> items_;
public:
    virtual void MainLoop();
    virtual void AddElement(Element* element){items_.push_back(element);}
};

#endif