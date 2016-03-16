namespace Xeth{


template<size_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
        boost::multiprecision::cpp_dec_float_50 value(request.toString().toStdString());
        value *= unit;
        boost::multiprecision::cpp_int result(value.str());
        return QVariant::fromValue(QString(result.str().c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
