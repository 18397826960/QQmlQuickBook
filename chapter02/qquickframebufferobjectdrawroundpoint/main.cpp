﻿/*引入各个模块的头文件*/
#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>

#include <ctime>
#include <cstdlib>
#include <sstd_memory.hpp>

#include "Application.hpp"
#include <ConstructQSurface.hpp>
#include "QmlApplicationEngine.hpp"

namespace {

    inline void resetRandom() {
        std::srand(static_cast<int>(std::time(nullptr)));
    }

    inline void loadQtPlugins() {
        QImage varImagePluginForceLoad{ QStringLiteral(":/qqmlquickglobal/image/load.png") };
        (void)varImagePluginForceLoad;
    }

}/*namespace*/

int main(int argc, char ** argv) {
    /*高分屏支持*/
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    /*重置随机数种子*/
    resetRandom();
    /*设置opengl默认格式*/
    sstd::setDefaultFormat();
    /*初始化Qt环境*/
    Application varApp{ argc,argv };
    /*强制运行目录为程序所在目录*/
    QDir::setCurrent(varApp.applicationDirPath());
    /*强制加载Qt插件*/
    loadQtPlugins();
    /*加载Qml环境*/
    QmlApplicationEngine varQmlApplicationEngine;
    /*检查Qml是否加载成功*/
    if (varQmlApplicationEngine.rootObjects().empty()) {
        return -1;
    }
    /*启动主线程事件循环程序*/
    return varApp.exec();
}












