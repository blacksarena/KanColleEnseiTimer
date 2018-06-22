#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <stdio.h>
#include <QtWidgets>
#include <QtCore>

enum ImageFormat{
    png = 0,
    jpg,
    bmp
};

class Rect
{
public:
    Rect():_x(0), _y(0), _width(0), _height(0){;}
    Rect(int x, int y, int width, int height):_x(x), _y(y), _width(width), _height(height){;}
    virtual ~Rect(){;}

    int x()      const {return _x;}
    int y()      const {return _y;}
    int width()  const {return _width;}
    int height() const {return _height;}
    int left()   const {return _x;}
    int top()    const {return _y;}
    int right()  const {return _x+_width;}
    int bottom() const {return _y+_height;}

    void setX(int x){_x = x;}
    void setY(int y){_y = y;}
    void setWidth (int width) {_width  = width;}
    void setHeight(int height){_height = height;}

private:
    int _x;
    int _y;
    int _width;
    int _height;
};

class ScreenShot
{
public:
    ScreenShot();

    // setter
    void setFormat(ImageFormat image_format){_image_format = image_format;}
    void setSaveDirectory(QString save_directory){_save_directory = save_directory;}
    // getter
    QString getTakeScreenShotErrorString()const{return _take_screen_shot_error_string;}

    bool serchGameWindow();
    bool takeScreenShot();

private:
    Rect _gameWindow;
    ImageFormat _image_format;
    QString _save_directory;
    QString _take_screen_shot_error_string;
};

#endif // SCREENSHOT_H
