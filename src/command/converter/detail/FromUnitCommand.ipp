namespace Xeth{



template<uint64_t unit>
QVariant FromUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
        boost::multiprecision::number<boost::multiprecision::gmp_float<100> > result(request.toString().toStdString());
        result /= unit;
        return QVariant::fromValue(QString(result.str(20, std::ios_base::fixed).c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
