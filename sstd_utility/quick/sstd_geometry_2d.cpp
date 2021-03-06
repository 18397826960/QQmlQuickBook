﻿#include "sstd_geometry_2d.hpp"
#include <boost/circular_buffer.hpp>
#include <boost/bimap.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

#ifndef getPrivate
#define getPrivate() static_cast< ThisP * >( getThisPrivate() )
#endif

#ifndef getConstPrivate
#define getConstPrivate() static_cast< const ThisP * >( getThisPrivate() )
#endif

namespace this_cpp_file {
    typedef sstd::list< sstd::Scene2DItemBasic * > DrawOrderList;
    class Information {
    public:
        sstd::Scene2DItemBasic * item;
        DrawOrderList::const_iterator itemDrawPos;
    private:
        SSTD_MEMORY_DEFINE(Information)
    };
    using Number = qreal;
    typedef boost::geometry::model::point<
        Number,
        2,
        boost::geometry::cs::cartesian/*笛卡尔坐标系*/
    > Point2D/*点*/;
    typedef boost::geometry::model::box<Point2D> Box2D/*索引矩形*/;
    typedef std::pair<Box2D, std::shared_ptr<Information>> KeyValue/*键值对*/;
    typedef boost::geometry::index::linear<8> Algorithm/*算法*/;
    class Equal {
    public:
        bool operator()(const KeyValue & a, const KeyValue & b) const {
            return a.second->item == b.second->item;
        }
    };
    typedef sstd::allocator<KeyValue> Allocator/*内存*/;
    typedef boost::geometry::index::indexable<KeyValue> IndexGetter/*辅助类*/;
    typedef boost::geometry::index::rtree< KeyValue,
        Algorithm,
        IndexGetter,
        Equal,
        Allocator> RTree/*RTree*/;

}/*this_cpp_file*/
using namespace this_cpp_file;

namespace sstd {

    namespace private_scene_2d {

        PrivateBasic::~PrivateBasic() {
        }

        Basic::~Basic() {
            delete thisp;
        }

        Basic::Basic(PrivateBasic * arg) : thisp(arg) {
        }


    }/*private_scene_2d*/

    class _0_PrivateScene2D : public private_scene_2d::PrivateBasic {
        class SetLess : public std::less<void> {
        public:
            bool operator()(sstd::Scene2DItemBasic * a, sstd::Scene2DItemBasic *b) const {
                return a < b;
            }
            bool operator()(const sstd::unique_ptr<sstd::Scene2DItemBasic> & a, sstd::Scene2DItemBasic *b) const {
                return a.get() < b;
            }
            bool operator()(sstd::Scene2DItemBasic * a, const sstd::unique_ptr<sstd::Scene2DItemBasic> &b) const {
                return a < b.get();
            }
            bool operator()(const sstd::unique_ptr<sstd::Scene2DItemBasic> & a, const sstd::unique_ptr<sstd::Scene2DItemBasic> &b) const {
                return a.get() < b.get();
            }
        };
    public:
        RTree mmm_RTree;
        using IndexedKeyValue = this_cpp_file::KeyValue;
        this_cpp_file::DrawOrderList mmm_DrawOrderList;
        std::map<
            sstd::Scene2DItemBasic *,
            IndexedKeyValue,
            SetLess,
            sstd::allocator< std::pair<sstd::Scene2DItemBasic * const,
            IndexedKeyValue > > > mmm_Items;

        void insert(sstd::Scene2DItemBasic * arg) {
            auto[varPos, varIsInsert] = mmm_Items.emplace(std::move(arg), this_cpp_file::KeyValue{});
            if (false == varIsInsert) {
                return;
            }
            auto varData = varPos->first;
            mmm_DrawOrderList.push_front(varData);
            varPos->second.second = sstd::make_shared<this_cpp_file::Information>();
            {
                const auto varBoundingRect = varData->sceneBoundingRect();
                const auto varTopLeft = varBoundingRect.topLeft();
                const auto varBottomRight = varBoundingRect.bottomRight();
                varPos->second.first = {
                    {varTopLeft.x(),varTopLeft.y()},
                    {varBottomRight.x(),varBottomRight.y()} };
                varPos->second.second->item = varData;
                varPos->second.second->itemDrawPos = mmm_DrawOrderList.begin();
            }
            mmm_RTree.insert(varPos->second);
        }

        void remove(sstd::Scene2DItemBasic * arg) {
            auto varPos = mmm_Items.find(arg);
            if (varPos == mmm_Items.end()) {
                return;
            }
            mmm_RTree.remove(varPos->second);
            mmm_DrawOrderList.erase(varPos->second.second->itemDrawPos);
            mmm_Items.erase(varPos);
        }

    private:
        SSTD_MEMORY_DEFINE(_0_PrivateScene2D)
    };

    Scene2D::Scene2D() :Scene2D(sstdNew<_0_PrivateScene2D>()) {

    }

    Scene2D::Scene2D(private_scene_2d::PrivateBasic* arg) : Basic(arg) {
        getPrivate()->super = this;
    }

    Scene2D::~Scene2D() {

    }

    Scene2DItemBasic::~Scene2DItemBasic() {
        ppp_destory();
    }

    void Scene2D::addItem(Scene2DItemBasic * item) {
        getPrivate()->insert(std::move(item));
    }

    QQuickItem * Scene2DItemBasic::getTarget()const {
        return mmm_target;
    }

    void Scene2DItemBasic::setTarget(QQuickItem * a) {
        if (a == mmm_target) {
            return;
        }
        onTargetChanged();
        mmm_target = a;
        this->targetChanged();
    }

    QRectF Scene2DItemBasic::sceneBoundingRect() const {
        const auto varPath = this->sceneBoundingPath();
        if (false == bool(varPath)) {
            return {};
        }
        if (varPath->size() < 3) {
            return{};
        }
        auto[minX, maxX] = std::minmax_element(varPath->begin(), varPath->end(),
            [](const auto &l, const auto & r) {
            return l.x() < r.x();
        });
        auto[minY, maxY] = std::minmax_element(varPath->begin(), varPath->end(),
            [](const auto &l, const auto & r) {
            return l.y() < r.y();
        });
        const auto varWidth = maxX->x() - minX->x();
        const auto varHeight = maxY->y() - minY->y();
        if (varWidth < std::numeric_limits<double>::epsilon()) {
            return{};
        }
        if (varHeight < std::numeric_limits<double>::epsilon()) {
            return{};
        }
        return { minX->x(),minY->y(),varWidth,varHeight };
    }

    Scene2D * Scene2DItemBasic::getScene2D() const {
        return mmm_scene;
    }

    void Scene2DItemBasic::setScene2D(Scene2D * a) {
        if (a == mmm_scene) {
            return;
        }
        onSceneChanged();
        mmm_scene = a;
        if (mmm_scene) {
            mmm_scene->addItem(this);
        }
        this->scene2DChanged();
    }

    void Scene2DItemBasic::onSceneChanged() {
        if (mmm_scene == nullptr) {
            return;
        }
        mmm_scene->removeItem(this);
    }

    void Scene2DItemBasic::onTargetChanged() {
        if ( mmm_scene == nullptr ) {
            return;
        }
        mmm_scene->removeItem(this);
        mmm_scene->addItem( this );
    }

    void Scene2DItemBasic::onDesotyedThis() {
        if ( mmm_scene == nullptr ) {
            return;
        }
        mmm_scene->removeItem(this);
    }

    private_scene_2d::PrivateBasic::PrivateBasic(){

    }

    Scene2DItemBasic::Scene2DItemBasic(QObject *a) : QObject(a) {
        this_super = this;
        connect(
            this,&Scene2DItemBasic::ppp_destory,
            this,&Scene2DItemBasic::onDesotyedThis,
            Qt::DirectConnection);
    }

    void Scene2D::removeItem(Scene2DItemBasic *) {
    }

    private_scene_2d::DestoryScene2DItemBasic::~DestoryScene2DItemBasic() {
        this_super->ppp_destory();
    }

}/*namespace sstd*/















