namespace Xeth{


template<uint64_t unit>
QVariant FromUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
        boost::multiprecision::cpp_dec_float_50 result(request.toString().toStdString());
        result /= unit;
        return QVariant::fromValue(QString(result.str().c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
