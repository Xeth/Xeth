#pragma once


namespace Xeth{


template<class BlockChain>
class ChainProgress
{
    public:
        ChainProgress(const BlockChain &);
        double getValue() const;
        bool update();


    private:
        BlockChain _chain;
        time_t _firstBlockTime;
        double _progress;
};



}

#include "ChainProgress.ipp"
