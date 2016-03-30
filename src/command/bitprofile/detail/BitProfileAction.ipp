namespace Xeth{


template<class Operation>
BitProfileAction<Operation>::BitProfileAction(const Operation &op) :
    _operation(op)
{}


template<class Operation>
BitProfileAction<Operation> * BitProfileAction<Operation>::Create(const Operation &op)
{
    return new BitProfileAction<Operation>(op);
}


template<class Operation>
void BitProfileAction<Operation>::run()
{
    _operation();
    deleteLater();
}


}
