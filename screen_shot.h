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

    inline int x()      const {return _x;}
    inline int y()      const {return _y;}
    inline int width()  const {return _width;}
    inline int height() const {return _height;}
    inline int left()   const {return _x;}
    inline int top()    const {return _y;}
    inline int right()  const {return _x+_width;}
    inline int bottom() const {return _y+_height;}

    inline void setX(int x){_x = x;}
    inline void setY(int y){_y = y;}
    inline void setWidth (int width) {_width  = width;}
    inline void setHeight(int height){_height = height;}

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
    inline void setFormat(ImageFormat image_format){_image_format = image_format;}
    inline void setSaveDirectory(QString save_directory){_save_directory = save_directory;}
    // getter
    inline const QString& getTakeScreenShotErrorString()const{return _take_screen_shot_error_string;}

    bool serchGameWindow();
    bool takeScreenShot();
    void setZoom(double zoom);
    const QPixmap& pixmap();

private:
    const Rect _game_window_origin;
    Rect _gameWindow;
    ImageFormat _image_format;
    QString _save_directory;
    QString _take_screen_shot_error_string;
    QPixmap _screen_shot;
};

#endif // SCREENSHOT_H
