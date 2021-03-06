﻿/*QmlSigleton.cpp*/
#include "QmlSigleton.hpp"
#include <QtCore/qcoreapplication.h>
#include <QtQml/qqmlengine.h>

QmlSigleton::QmlSigleton() {
    /*cplusplus own the data ... */
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

inline QObject * QmlSigleton::instance() {
    static auto varAns = sstd::make_unique<QmlSigleton>();
    return varAns.get();
}

QColor QmlSigleton::getMyColor() const{
    return this->mmm_MyColor.getData();
}

static inline void registerThis() {
    qmlRegisterSingletonType<QmlSigleton>("myqml.qmlsigleton",
        1, 0,
        "QmlSigleton",
        [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject * {
        return QmlSigleton::instance();
        (void)engine;
        (void)scriptEngine;
    });
}
Q_COREAPP_STARTUP_FUNCTION(registerThis)

//g++ error ???
//namespace sstd {
//    namespace qmlsigleton {
//        extern template class DataItem<QColor>;
//    }/*qmlsigleton*/
//}/*sstd*/








