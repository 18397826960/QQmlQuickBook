﻿#pragma once

#include <functional>
#include <sstd_memory.hpp>

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>
#include <QtCore/qobject.h>
#include <QtCore/qbytearray.h>
#include <QtGui/qtextformat.h>
class QTextFrame;

namespace sstd {

    class TextFrameItem : public QObject {
        Q_OBJECT
    public:
        TextFrameItem(QObject * /**/ = nullptr);
        QTextFrame * getTextFrame() const { return $m$TextFrame; }
        void setTextFrame(QTextFrame * arg) { $m$TextFrame = arg; }
        double getContentTextWidth() const { return $m$RealTextWidth; }
        void setContentTextWidth(const double &arg) { $m$RealTextWidth = arg; }
        double getContentTextHeight()const { return $m$RealTextHeight; }
        void setContentTextHeigth(const double &arg) { $m$RealTextHeight = arg; }
    public:
        static void setTextData(QTextFrame *, TextFrameItem*);
        static TextFrameItem* getTextData(QTextFrame *);
    public:
        virtual QByteArray getQmlBackgroundDelegateData() const = 0;
        virtual QString getHtmlTitle() const = 0;
        virtual QList<QString> getHtmlData() const = 0;
        virtual double getFrameMinHeight() const = 0;
        virtual QTextFrameFormat getFrameFormat() const = 0;
        virtual bool getPureLeftEmpty() const = 0;
        virtual bool getTitleAlignRight() const = 0;
    private:
        SSTD_MEMORY_QOBJECT_DEFINE(TextFrameItem)
    private:
        using Super = QObject;
        QTextFrame * $m$TextFrame = nullptr;
        double $m$RealTextWidth = -1;
        double $m$RealTextHeight = -1;
    };

}/*namespace sstd*/















