# Element（元素）

在Polonium框架中，Element类是最基本的组成单位。

> polonium 钋
> element 元素

所有显示在屏幕上的对象都继承自Element类。

Element类要求实现2个方法：

- Render()方法：每次渲染页面（Page）时，Page会依次地调用每一个Element的Render方法。元素需要在Render方法中渲染自身。
- Test()方法：作为每个元素的事件侦测器，在渲染页面完成后，Page会依次调用每一个Element的Test方法，让元素可以侦测事件。

例如，这是TextBase（所有需要显示文字的类的基类）的头文件:

```cpp
class TextBase : public PositedElement
{
private:
    std::string text_;
    int font_size_;
public:
    TextBase(int x,int y,int width,int height,std::string text,int font_size) : PositedElement(x,y,width,height) {text_=text;font_size_=font_size;};
    virtual void Render() override;
    virtual void Test() override {return;};
    ~TextBase(){};
};
```

由于TextBase类没有事件需要侦测，Test方法不进行任何操作。

这是Render方法的实现：

```cpp
void TextLine::Render()
{
    std::cout << text_ << std::endl;
    OLED_ShowString(X,Y,(unsigned char *)text_.c_str(),font_size_,1);
}
```

下面是Polonium框架提供的一些用于继承的基类：

```
TextBase : 需要显示文字的对象
```