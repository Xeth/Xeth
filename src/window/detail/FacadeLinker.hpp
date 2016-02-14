#pragma once 


#include <QObject>
#include <QWebFrame>


#include "facade/Facade.hpp"


namespace Xeth{


class FacadeLinker : public QObject
{
    Q_OBJECT
    public:
        FacadeLinker(QWebFrame *frame, Facade *facade);

    public slots:

        void linkAll();
        void linkObjects();
        void linkEvents();

    private:
        QWebFrame *_frame;
        Facade *_facade;

};


}
