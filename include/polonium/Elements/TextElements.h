#ifndef TEXTELEMENTS_H
#define TEXTELEMENTS_H

#include "../Element.h"
#include <string>

class TextBase : public PositedElement
{
private:
    int font_size_;
protected:
    std::string text_;
public:
    TextBase(int x,int y,int width,int height,std::string text,int font_size) : PositedElement(x,y,width,height) {text_=text;font_size_=font_size;};
    virtual void Render() override;
    virtual void Test() override {return;};
    ~TextBase(){};
};

class TittleText : public SingleRenderWrapper
{
public:
    TittleText(int x,int y,int width,int height,std::string text,int font_size) : SingleRenderWrapper(TextBase(x,y,width,height,text,font_size)) {};
};

class TextLine : public TextBase
{
public:
    TextLine(int x,int y,int width,int height,std::string text,int font_size) : TextBase(x,y,width,height,text,font_size){};
};

class InputTextBox : public TextBase
{
private:
    void (*EnterInputed_)(std::string text);
    int ch_num;
    bool cover_flag = false;
public:
    InputTextBox(int x,int y,int width,int height,int font_size) : TextBase(x,y,width,height,"",font_size) {};
    void SetCallBack(void (*EnterInputed)(std::string text)) {EnterInputed_ = EnterInputed;};
    virtual void Test() override;
};

#endif