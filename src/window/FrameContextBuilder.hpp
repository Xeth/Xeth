#pragma once

#include <QWebFrame>

#include "facade/Facade.hpp"
#include "detail/FacadeLinker.hpp"

namespace Xeth{


class FrameContextBuilder
{
    public:
        FrameContextBuilder(Facade &facade);

        void buildContext(QWebFrame *);

    private:
        Facade &_facade;
};


}
