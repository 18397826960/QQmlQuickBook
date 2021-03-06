TEMPLATE = subdirs

sstd_core_library.file = $$PWD/sstd_utility/sstd_core_library/sstd_core_library.pro
SUBDIRS += sstd_core_library

buildinstall.file = $$PWD/buildinstall/buildinstall.pro
buildinstall.depends = sstd_core_library
SUBDIRS += buildinstall

sstd_quick_library.file = $$PWD/sstd_utility/sstd_quick_library.pro
sstd_quick_library.depends = buildinstall
SUBDIRS += sstd_quick_library

hellowworld.file = $$PWD/chapter01/hellowworld/hellowworld.pro
hellowworld.depends = buildinstall
SUBDIRS += hellowworld

checkfileformat.file = $$PWD/chapter01/checkfileformat/checkfileformat.pro
checkfileformat.depends = buildinstall
SUBDIRS += checkfileformat

memory.file = $$PWD/chapter01/memory/memory.pro
memory.depends = buildinstall
SUBDIRS += memory

function.file = $$PWD/chapter01/function/function.pro
function.depends = buildinstall
SUBDIRS += function

qquickwindowopengldraw.file = $$PWD/chapter02/qquickwindowopengldraw/qquickwindowopengldraw.pro
qquickwindowopengldraw.depends = buildinstall
SUBDIRS += qquickwindowopengldraw

qwidgetopengldraw.file = $$PWD/chapter02/qwidgetopengldraw/qwidgetopengldraw.pro
qwidgetopengldraw.depends = buildinstall
SUBDIRS += qwidgetopengldraw

qwindowopengldraw.file = $$PWD/chapter02/qwindowopengldraw/qwindowopengldraw.pro
qwindowopengldraw.depends = buildinstall
SUBDIRS += qwindowopengldraw

computeshaderaddbuffer.file = $$PWD/chapter02/computeshaderaddbuffer/computeshaderaddbuffer.pro
computeshaderaddbuffer.depends = buildinstall
SUBDIRS += computeshaderaddbuffer

computeshaderfilterimage.file = $$PWD/chapter02/computeshaderfilterimage/computeshaderfilterimage.pro
computeshaderfilterimage.depends = buildinstall
SUBDIRS += computeshaderfilterimage

computeshaderinvertimage.file = $$PWD/chapter02/computeshaderinvertimage/computeshaderinvertimage.pro
computeshaderinvertimage.depends = buildinstall
SUBDIRS += computeshaderinvertimage

chat.file = $$PWD/chapter03/chat/chat.pro
chat.depends = buildinstall
SUBDIRS += chat

qsgdrawpoint.file = $$PWD/chapter02/qsgdrawpoint/qsgdrawpoint.pro
qsgdrawpoint.depends = buildinstall
SUBDIRS += qsgdrawpoint

qsgdrawtexturepoint.file = $$PWD/chapter02/qsgdrawtexturepoint/qsgdrawtexturepoint.pro
qsgdrawtexturepoint.depends = buildinstall
SUBDIRS += qsgdrawtexturepoint

qquickframebufferobjectdrawroundpoint.file = $$PWD/chapter02/qquickframebufferobjectdrawroundpoint/qquickframebufferobjectdrawroundpoint.pro
qquickframebufferobjectdrawroundpoint.depends = buildinstall
SUBDIRS += qquickframebufferobjectdrawroundpoint

qsgdrawuserender.file = $$PWD/chapter02/qsgdrawuserender/qsgdrawuserender.pro
qsgdrawuserender.depends = buildinstall
SUBDIRS += qsgdrawuserender

animationandstate.file = $$PWD/chapter04/animationandstate/animationandstate.pro
animationandstate.depends = buildinstall
SUBDIRS += animationandstate

qmlsingleton.file = $$PWD/chapter03/qmlsingleton/qmlsingleton.pro
qmlsingleton.depends = buildinstall
SUBDIRS += qmlsingleton

qmlcontex.file = $$PWD/chapter03/qmlcontex/qmlcontex.pro
qmlcontex.depends = buildinstall
SUBDIRS += qmlcontex

computeshaderthreaddraw.file = $$PWD/chapter02/computeshaderthreaddraw/computeshaderthreaddraw.pro
computeshaderthreaddraw.depends = buildinstall
SUBDIRS += computeshaderthreaddraw

quickrendercontrol.file = $$PWD/chapter02/quickrendercontrol/quickrendercontrol.pro
quickrendercontrol.depends = buildinstall
SUBDIRS += quickrendercontrol

quickrendertoimage.file = $$PWD/chapter02/quickrendertoimage/quickrendertoimage.pro
quickrendertoimage.depends = buildinstall
SUBDIRS += quickrendertoimage

visualcoordinates.file = $$PWD/chapter01/visualcoordinates/visualcoordinates.pro
visualcoordinates.depends = buildinstall
SUBDIRS += visualcoordinates

quickchart.file = $$PWD/chapter04/quickchart/quickchart.pro
quickchart.depends = buildinstall
SUBDIRS += quickchart

quickchartdeep.file = $$PWD/chapter04/quickchartdeep/quickchartdeep.pro
quickchartdeep.depends = buildinstall
SUBDIRS += quickchartdeep

quickchartimageborder.file = $$PWD/chapter04/quickchartimageborder/quickchartimageborder.pro
quickchartimageborder.depends = buildinstall
SUBDIRS += quickchartimageborder

multimediaplayer.file = $$PWD/chapter05/multimediaplayer/multimediaplayer.pro
multimediaplayer.depends = buildinstall
SUBDIRS += multimediaplayer

runcontrol.file = $$PWD/chapter01/runcontrol/runcontrol.pro
runcontrol.depends = buildinstall
SUBDIRS += runcontrol

