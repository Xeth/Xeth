#pragma once


namespace Xeth{


template<class BlockChain>
class ChainProgress
{
    public:
        ChainProgress(BlockChain &);
        double getValue() const;
        bool update();


    private:
        BlockChain &_chain;
        double _progress;
};



}

#include "ChainProgress.ipp"
