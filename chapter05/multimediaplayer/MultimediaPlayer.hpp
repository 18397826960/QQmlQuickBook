﻿#pragma once
#include <QtCore/qobject.h>
#include <QtCore/qthread.h>
#include <QtGui/qimage.h>
#include <sstd_memory.hpp>
#include <quick/sstd_QThread.hpp>

namespace sstd {

    class PlayerPrivate;
    class Player :
        public QObject,
        public virtual sstd::memory_lock::VirtualClassBasic {
        Q_OBJECT
    public:
        void setLocalFile(const QString &);
        inline bool open();
        bool start(QThread *, double=0);
        inline const QString & getError()const;
    public:
        Player();
        Q_SIGNAL void finished();
        Q_SIGNAL void imageChanged(const QImage & );
    public:
        inline bool isStarted() const;
        inline bool isOpen() const;
    private:
        bool * mmm_IsStart;
        bool * mmm_ISLocalFile;
        bool * mmm_IsConstruct;
        QString * mmm_LocalFileName;
        PlayerPrivate * mmm_Private;
        QString * mmm_ErrorString;
    private:
        bool ppp_construct_local();
        bool ppp_construct_net();
        bool ppp_construct();
    private:
        SSTD_MEMORY_QOBJECT_DEFINE(Player)
    };

    bool Player::isStarted() const {
        return *mmm_IsStart;
    }

    bool Player::isOpen() const {
        return *mmm_IsConstruct;
    }

    inline bool Player::open() {
        (*mmm_IsConstruct) = ppp_construct();
        return *mmm_IsConstruct;
    }

    inline const QString & Player::getError()const {
        return *mmm_ErrorString;
    }

    class PlayerThread : public sstd::QuickThread {
        Q_OBJECT
    public:
        PlayerThread();
    public:
        void stop();
        void start(Player *,double=0);
        inline void start();
        inline bool isPlayerSet()const;
    private:
        double mmm_StartPos{ 0 };
        Player * mmm_Player{ nullptr };
        using Super = sstd::QuickThread;
    protected:
        inline void quit();
    private:
        bool mmm_isPlayerSet{false};
    private:
        SSTD_MEMORY_QOBJECT_DEFINE(PlayerThread)
    };

    inline void PlayerThread::start() {
        Super::start();
    }

    inline void PlayerThread::quit() {
        Super::quit();
    }

    inline bool PlayerThread::isPlayerSet() const {
        return mmm_isPlayerSet;
    }
        
}/*namespace sstd*/















