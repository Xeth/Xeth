namespace Xeth{


template<size_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
#ifdef __HAS_GMP__
        boost::multiprecision::number<boost::multiprecision::gmp_float<50> > value(request.toString().toStdString());
#else
        boost::multiprecision::cpp_dec_float_50 value(request.toString().toStdString());
#endif
        value *= unit;
        boost::multiprecision::cpp_int result(value.str(20, std::ios_base::fixed));
        return QVariant::fromValue(QString(result.str().c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
