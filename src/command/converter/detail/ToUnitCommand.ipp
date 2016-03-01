namespace Xeth{


template<size_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
#if __HAS_GMP__
        boost::multiprecision::number<boost::multiprecision::gmp_float<50> > value(request.toString().toStdString());
#else
        boost::multiprecision::cpp_dec_float_50 value(request.toString().toStdString());
#endif
        value *= unit;
        return QVariant::fromValue(QString(value.convert_to<boost::multiprecision::cpp_int>().str().c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
