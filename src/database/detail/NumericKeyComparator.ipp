
namespace Xeth{

template<class Value>
int NumericKeyComparator<Value>::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const
{
    return Compare(*reinterpret_cast<const Value *>(a.data()), *reinterpret_cast<const Value *>(b.data()));
}


template<class Value>
int NumericKeyComparator<Value>::Compare(Value a, Value b) const
{
    if (a < b) return -1;
    if (a > b) return +1;
    return 0;
}


template<class Value>
const char* NumericKeyComparator<Value>::Name() const { return "NumericKeyComparator"; }

template<class Value>
void NumericKeyComparator<Value>::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }

template<class Value>
void NumericKeyComparator<Value>::FindShortSuccessor(std::string*) const { }


}
