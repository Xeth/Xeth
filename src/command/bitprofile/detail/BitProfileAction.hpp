#pragma once 

#include <QThread>


namespace Xeth{


template<class Operation>
class BitProfileAction : public QThread
{
    public:
        void run();
        static BitProfileAction * Create(const Operation &);

    private:
        BitProfileAction(const Operation &);

    private:
        Operation _operation;
};


}

#include "BitProfileAction.ipp"
