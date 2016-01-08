#pragma once


#include <boost/lexical_cast.hpp>

#include <eth-connector/BigInt.hpp>

namespace Xeth{


typedef Ethereum::Connector::BigInt BigInt;

}

//namespace boost{

//template<class T>
//T lexical_cast(const Xeth::BigInt &val)
//{
//    return boost::lexical_cast<T>(val.str());
//}

//template<>
//std::string lexical_cast(const Xeth::BigInt &val)
//{
//    return val.str();
//}

//}
