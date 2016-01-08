
namespace Xeth{

template<class Criterion, class Arg1>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1)
{
    addCriterion(minBlock, new Criterion(arg1));
}

template<class Criterion, class Arg1, class Arg2>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1, const Arg2 &arg2)
{
    addCriterion(minBlock, new Criterion(arg1, arg2));
}

template<class Criterion, class Arg1, class Arg2, class Arg3>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
   addCriterion(minBlock, new Criterion(arg1, arg2, arg3));
}




}
