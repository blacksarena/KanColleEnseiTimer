#include "screen_shot.h"

ScreenShot::ScreenShot()
:_gameWindow(0, 0, 800, 480)
,_image_format(ImageFormat::png)
,_save_directory("")
,_take_screen_shot_error_string("")
{
}

bool ScreenShot::serchGameWindow()
{
    QPoint brouser_pos(-1, -1);
    FILE *fp = NULL;
    char ret[512] = {0};
    char window_id[11] = {0};
    char xwininfo_command[64] = "xwininfo -id ";
    QString window_x;
    QString window_y;
    QString window_width;
    QString window_height;
    QStringList window_x_splited;
    QStringList window_y_splited;
    QStringList window_width_splited;
    QStringList window_height_splited;
    QSize window_size;

#ifdef __linux__
    fp = popen("wmctrl -xl | grep \"艦隊これくしょん -艦これ- - オンラインゲーム - DMM GAMES\"", "r");// 検索文字列はシェルに任せよう
    if(fp == NULL){
        if(fp != NULL){
            pclose(fp);
        }
        return false;
    }
    fgets(ret, sizeof(ret), fp);
    if(ret[0] != '0'){// 正常にウィンドウが特定された場合、先頭にウィンドウID(0xNNNNNNNN)が入るので、これでもエラー処理可能
        qDebug() << "window not find.";
        if(fp != NULL){
            pclose(fp);
        }
        return false;
    }
    strncpy(window_id, ret, 10);
    strcat(xwininfo_command, window_id);
    pclose(fp);
    fp = popen(xwininfo_command, "r");
    if(fp == NULL){
        if(fp != NULL){
            pclose(fp);
        }
        return false;
    }
    fgets(ret, sizeof(ret), fp);
    fgets(ret, sizeof(ret), fp);
    fgets(ret, sizeof(ret), fp);
    fgets(ret, sizeof(ret), fp);// abs x
    window_x = ret;
    window_x_splited = window_x.split(" ");
    fgets(ret, sizeof(ret), fp);// abs y
    window_y = ret;
    window_y_splited = window_y.split(" ");
    brouser_pos = QPoint(window_x_splited[6].toInt(), window_y_splited[6].toInt());
    qDebug() << "game_window_pos: " << brouser_pos;
    fgets(ret, sizeof(ret), fp);// Relative upper-left x
    fgets(ret, sizeof(ret), fp);// Relative upper-left y
    fgets(ret, sizeof(ret), fp);// width
    window_width = ret;
    window_width_splited = window_width.split(" ");
    fgets(ret, sizeof(ret), fp);// height
    window_height = ret;
    window_height_splited = window_height.split(" ");
    window_size = QSize(window_width_splited[3].toInt(), window_height_splited[3].toInt());
    qDebug() << window_size;
#elif _WIN32// windows 32bit, 64bit
#elif __APPLE__// MacOS
#else// other
#endif

    QPixmap screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0, brouser_pos.x(), brouser_pos.y(), window_size.width(), window_size.height());
    QPixmap scaledPixmap = screenPixmap.scaled(screenPixmap.width()/1, screenPixmap.height()/1);
    QLabel *image_label = new QLabel;
    image_label->setPixmap(scaledPixmap);
    //image_label->show();
    QImage clip_gameWindow = screenPixmap.toImage();

    // 横方向が白一色になるまでyをインクリメント
    bool white_out = false;
    bool line_skip = false;
    QColor pixel;
    int x = 0, pix_x = 0, y = 0;
    for(y = 0; y < screenPixmap.height()-_gameWindow.height() && white_out == false; ++y){
        for(x = 0; x < screenPixmap.width()-_gameWindow.width() && white_out == false; ++x){
            line_skip = false;
            for(pix_x = 0; pix_x < _gameWindow.width() && line_skip == false; ++pix_x){
                pixel = clip_gameWindow.pixel(x+pix_x, y);
                if(pixel.red() != 255 || pixel.green() != 255 || pixel.blue() != 255){
                    //qDebug() << "line skip y:" << y;
                    line_skip = true;
                    continue;
                }
                //qDebug() << "x, y:" << x+pix_x << "," << y;
                if(pix_x == _gameWindow.width()-1){
                    pixel = clip_gameWindow.pixel(x+pix_x-799, y);
                    //qDebug() << "rgb: " << pixel.red() << pixel.green() << pixel.blue();
                    line_skip = true;
                    white_out = true;
                    //qDebug() << "find x, y:" << x << "," << y;
                    continue;
                }
            }
        }
    }
    if(white_out == false){
        return false;
    }

    // 横方向が白一色から外れるまでyをインクリメント
    for(; y < screenPixmap.height()-_gameWindow.height() && white_out == true; ++y){
        for(pix_x = 0; pix_x < _gameWindow.width() && white_out == true; ++pix_x){
            pixel = clip_gameWindow.pixel(x+pix_x, y);
            if(pixel.red() != 255 || pixel.green() != 255 || pixel.blue() != 255){
                // y軸固定
                y--;
                white_out = false;
                continue;
            }
        }
    }
    if(white_out == true){
        return false;
    }
    //qDebug() << "find x, y:" << x << "," << y;
    QLabel *yFixed = new QLabel;
    yFixed->setPixmap(screenPixmap.copy(x, y, _gameWindow.width(), _gameWindow.height()));
    //yFixed->show();

    // 縦方向が白一色になるまでxをインクリメント
    for(x = 0, white_out = false; x < screenPixmap.width()-_gameWindow.width() && white_out == false; ++x){
        for(int pix_y = 0, line_skip = false; pix_y < _gameWindow.height() && line_skip == false; ++pix_y){
            pixel = clip_gameWindow.pixel(x, y+pix_y);
            //qDebug() << "rgb: " << pixel.red() << pixel.green() << pixel.blue();
            if(pixel.red() <= 240 || pixel.green() <= 240 || pixel.blue() <= 240){
                //qDebug() << "x whiteout line skip y:" << y+pix_y;
                line_skip = true;
                continue;
            }
            //qDebug() << "x, y:" << x << "," << y+pix_y;
            if(pix_y == _gameWindow.height()-1){
                line_skip = true;
                white_out = true;
                //qDebug() << "x whiteout find x, y:" << x << "," << y;
            }
        }
    }
    if(white_out == false){
        return false;
    }

    // 縦方向が白一色から外れるまでxをインクリメント
    white_out = true;
    for(x = 0; x < screenPixmap.width()-_gameWindow.width() && white_out == true; ++x){
        pixel = clip_gameWindow.pixel(x, y);
        if(pixel.red() != 255 || pixel.green() != 255 || pixel.blue() != 255){
            // x軸固定
            x--;
            white_out = false;
            continue;
        }
    }
    if(white_out == true){
        return false;
    }
    qDebug() << "find x, y:" << x << "," << y;
    QLabel *xyFixed = new QLabel;
    _gameWindow.setX(brouser_pos.x()+x);
    _gameWindow.setY(brouser_pos.y()+y);
    //xyFixed->setPixmap(screenPixmap.copy(_gameWindow.x(), _gameWindow.y(), _gameWindow.width(), _gameWindow.height()));
    xyFixed->setPixmap(QGuiApplication::primaryScreen()->grabWindow(0).copy(_gameWindow.x(), _gameWindow.y(), _gameWindow.width(), _gameWindow.height()));
#ifdef _DEBUG
    xyFixed->show();
#endif// _DEBUG

    return true;
}

bool ScreenShot::takeScreenShot()
{
    QPixmap screen_shot = QGuiApplication::primaryScreen()->grabWindow(0).copy(_gameWindow.x(), _gameWindow.y(), _gameWindow.width(), _gameWindow.height());
    QString image_format;
    _take_screen_shot_error_string = "";
    switch(_image_format){
    case ImageFormat::png:
        image_format = ".png";
        break;
    case ImageFormat::jpg:
        image_format = ".jpg";
        break;
    case ImageFormat::bmp:
        image_format = ".bmp";
        break;
    default:
        _take_screen_shot_error_string = "unknown format.";
        return false;
        break;
    }

    //qDebug() << QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+image_format;
    if(!screen_shot.save(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+image_format)){
        _take_screen_shot_error_string = "not exist file path.";
        return false;
    }
    return true;
}
