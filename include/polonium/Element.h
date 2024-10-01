#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <iostream>

/// @brief 所有元素的基类
class Element
{
public:
    /// @brief 元素绘制自身的方法
    virtual void Render() {};
    /// @brief 测试事件是否被引发的方法，此方法将在每次渲染后被调用
    virtual void Test() {};
    virtual ~Element(){};
};

/// @brief 这个类用于描述“有位置”的元素
class PositedElement : public Element
{
public:
    /// @brief 从位置构造一个“有位置”的元素
    /// @param x 元素左上角的横坐标
    /// @param y 元素左上角的纵坐标
    /// @param width 元素的长（默认为0）
    /// @param height 元素的宽（默认为0）
    PositedElement(int x,int y,int width = 0,int height = 0){X=x,Y=y,Height=height,Width=width;};
    int X,Y,Width,Height;
};

/// @brief 这是用来包装只需要渲染一次的元素的类
class SingleRenderWrapper : public Element
{
private:
    Element element_;
    bool Render_Needed = true;
public:
    SingleRenderWrapper(Element element) {element_ = element;};
    virtual void Render() override;
    virtual void Test() override {element_.Test();};
    ~SingleRenderWrapper(){};
};


#endif