﻿#pragma once

#include "sstd_quick_library_global.hpp"
#include <sstd_memory.hpp>
#include <QtCore/qthread.h>
#include <QtCore/qobject.h>
#include <QtCore/qpointer.h>
#include <mutex>
#include <future>
#include <shared_mutex>

namespace sstd {

    template<typename T>
    inline void wait(const T & arg,std::size_t N) {
        if (false == bool(arg)) {
            return;
        }
        assert(N<(arg->size()));
        (*arg)[N]->wait();
    }

    class _1_SSTD_QUICK_LIBRARY_EXPORT ObjectFuture :
        public QObject,
        public std::future<void>,
        public std::enable_shared_from_this<ObjectFuture>{
        Q_OBJECT
    private:
        using std_future = std::future<void>;
        std::atomic_bool mmm_IsIgnored{false};
    public:
        ObjectFuture(std_future &&);
        ~ObjectFuture();
    public:
        ObjectFuture(const ObjectFuture&) = delete;
        ObjectFuture(ObjectFuture&&) = delete ;
        ObjectFuture&operator=(ObjectFuture&) = delete ;
        ObjectFuture&operator=(ObjectFuture&&) = delete ;
    public:
        void get_value() {
            std_future::get();
        }
        using std_future::valid;
        using std_future::wait_for;
        using std_future::wait_until;
        bool isIgnored() const volatile {
            return mmm_IsIgnored.load();
        }
    public:
        /*if after endCall valid() return false,then the ignored set true ...*/
        Q_SIGNAL void beginCall();
        Q_SIGNAL void endCall();
    private:
        using std_future::get;
    private:
        SSTD_MEMORY_QOBJECT_DEFINE(ObjectFuture)
    };
    using ObjectFuturePointer = std::shared_ptr<ObjectFuture>;

    template<typename ... Args>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runHere(Args && ...);
    template<typename Tuple>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyHere(Tuple &&);

    template<typename ... Args>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runInMainThread(Args && ...);
    template<typename Tuple>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyInMainThread(Tuple &&);

    /*this is private function , never used it direct ... */
    _1_SSTD_QUICK_LIBRARY_EXPORT std::shared_ptr< const sstd::vector< ObjectFuturePointer > > ppp_run_in_main_thread(sstd::vector<std::packaged_task<void(void)>> && arg);
    _1_SSTD_QUICK_LIBRARY_EXPORT std::shared_ptr< const sstd::vector< ObjectFuturePointer > > ppp_run_here(sstd::vector<std::packaged_task<void(void)>> &&);

    class MainThread {
    public:
        template<typename ... Args>
        static std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runInMainThread(Args && ... args) {
            return sstd::runInMainThread(std::forward<Args>(args)...);
        }
        template<typename Tuple>
        static std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyInMainThread(Tuple && arg) {
            return sstd::applyInMainThread(std::forward<Tuple>(arg));
        }
        template<typename ... Args>
        static std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runHere(Args && ... args) {
            return sstd::runHere(std::forward<Args>(args)...);
        }
        template<typename Tuple>
        static std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyHere(Tuple && arg) {
            return sstd::applyHere(std::forward<Tuple>(arg));
        }
    private:
        SSTD_MEMORY_DEFINE(MainThread)
    };

    namespace private_quick_thread_sstd {

        class _1_SSTD_QUICK_LIBRARY_EXPORT RunEventObject : public QObject {
            Q_OBJECT
        public:
            RunEventObject(std::shared_ptr<std::atomic_bool>);
        protected:
            bool event(QEvent *) override;
            std::shared_ptr<std::atomic_bool> mmm_logical_quit;
        private:
            SSTD_MEMORY_QOBJECT_DEFINE(RunEventObject)
        };

    }/*private_sstd*/

    class _1_SSTD_QUICK_LIBRARY_EXPORT QuickThread : public QThread, public sstd::MainThread {
        Q_OBJECT
    public:
        ~QuickThread();
        QuickThread();

        template<typename ... Args>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runInThisThread(Args && ... args) {

            if constexpr ((sizeof...(Args)) == 0) {
                return {};
            } else {
                if (isLogicalQuit()) {
                    return{};
                }
                sstd::vector<std::packaged_task<void(void)>> varCall;
                varCall.reserve(sizeof...(Args));
                (QuickThread::ppp_push_back(&varCall, std::forward<Args>(args)), ...);
                return ppp_Call(std::move(varCall));
            }

        }

        template<typename Tuple>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyInThisThread(Tuple && arg) {
            const static constexpr auto varTupleSize = std::tuple_size_v<std::remove_reference_t<Tuple>>;
            return QuickThread::ppp_apply(this, std::forward < Tuple >(arg), std::make_index_sequence<varTupleSize>{});
        }

        void setLogicalQuit(bool a) {
            mmm_logical_quit->store(a);
        }

        bool isLogicalQuit() const {
            return mmm_logical_quit->load();
        }

    private:
        template<typename ... Args>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > friend runHere(Args && ...);
        template<typename Tuple>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > friend applyHere(Tuple &&);
        template<typename ... Args>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > friend runInMainThread(Args && ...);
        template<typename Tuple>
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > friend applyInMainThread(Tuple &&);
    protected:
        void run() override;
    private:
        std::shared_ptr<std::atomic_bool> mmm_logical_quit;
        std::shared_mutex mmm_Mutex;
        private_quick_thread_sstd::RunEventObject * mmm_CallObject{ nullptr };
        Q_SLOT void ppp_on_finished();
    private:
        template<typename T>
        static inline void ppp_push_back(sstd::vector<std::packaged_task<void(void)>> * a, T && v) {
            a->emplace_back(std::forward<T>(v));
        }
        static inline void ppp_push_back(sstd::vector<std::packaged_task<void(void)>> * a, std::packaged_task<void(void)> && v) {
            a->push_back(std::move(v));
        }
        template<typename Tuple, std::size_t... I>
        static inline std::shared_ptr< const sstd::vector< ObjectFuturePointer > >
            ppp_apply(QuickThread *d, Tuple && t, const std::index_sequence<I...> &) {
            return d->runInThisThread(std::get<I>(std::forward<Tuple>(t))...);
        }
    private:
        std::shared_ptr< const sstd::vector< ObjectFuturePointer > > ppp_Call(sstd::vector<std::packaged_task<void(void)>> &&);
    private:
        SSTD_MEMORY_QOBJECT_DEFINE(QuickThread)
    };

    template<typename ... Args>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runInMainThread(Args && ... args) {
        if constexpr ((sizeof...(Args)) == 0) {
            return {};
        } else {
            sstd::vector<std::packaged_task<void(void)>> varCall;
            varCall.reserve(sizeof...(Args));
            (QuickThread::ppp_push_back(&varCall, std::forward<Args>(args)), ...);
            return ppp_run_in_main_thread(std::move(varCall));
        }
    }

    template<typename Tuple, std::size_t... I>
    static inline std::shared_ptr< const sstd::vector< ObjectFuturePointer > >
        _1_ppp_apply(Tuple && t, const std::index_sequence<I...> &) {
        return runInMainThread(std::get<I>(std::forward<Tuple>(t))...);
    }

    template<typename Tuple>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyInMainThread(Tuple && arg) {
        const static constexpr auto varTupleSize = std::tuple_size_v<std::remove_reference_t<Tuple>>;
        return _1_ppp_apply(std::forward < Tuple >(arg), std::make_index_sequence<varTupleSize>{});
    }

    template<typename ... Args>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > runHere(Args && ... args) {
        if constexpr ((sizeof...(Args)) == 0) {
            return{};
        } else {
            sstd::vector<std::packaged_task<void(void)>> varCall;
            varCall.reserve(sizeof...(Args));
            (QuickThread::ppp_push_back(&varCall, std::forward<Args>(args)), ...);
            return ppp_run_here(std::move(varCall));
        }
    }

    template<typename Tuple, std::size_t... I>
    static inline std::shared_ptr< const sstd::vector< ObjectFuturePointer > >
        _2_ppp_apply(Tuple && t, const std::index_sequence<I...> &) {
        return runHere(std::get<I>(std::forward<Tuple>(t))...);
    }

    template<typename Tuple>
    std::shared_ptr< const sstd::vector< ObjectFuturePointer > > applyHere(Tuple && arg) {
        const static constexpr auto varTupleSize = std::tuple_size_v<std::remove_reference_t<Tuple>>;
        return _2_ppp_apply(std::forward < Tuple >(arg), std::make_index_sequence<varTupleSize>{});
    }

    template<typename ... K>
    class _2_tuple {
    };

    template<std::size_t N, std::size_t I, typename T, typename Tuple>
    class _1_tuple_size;

    template<std::size_t N, std::size_t I, typename T, typename T0, template<typename  > class Tuple>
    class _1_tuple_size<N, I, T, Tuple<T0>> {
    public:
        constexpr const static std::size_t value = std::is_same_v<T, T0> ? I : N;
    };

    template<std::size_t N, std::size_t I, typename T, typename T0, typename T1, typename ...TN, template<typename ...> class Tuple>
    class _1_tuple_size<N, I, T, Tuple<T0, T1, TN...>> {
    public:
        constexpr const static std::size_t value = std::is_same_v<T, T0> ? I :
            _1_tuple_size<N, 1 + I, T, Tuple<T1, TN...>>::value;
    };

    template<typename T, typename Tuple>
    class tuple_index;

    template<typename T, typename ... U, template<typename ...> class Tuple>
    class tuple_index<T, Tuple<U...>> {
    public:
        constexpr const static std::size_t value = _1_tuple_size<sizeof...(U), 0, T, _2_tuple<U...>>::value;
        static_assert(value != (sizeof...(U)), "can not find type in tuple");
    };

}/*namespace sstd*/












