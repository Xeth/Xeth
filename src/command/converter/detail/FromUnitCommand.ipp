namespace Xeth{



template<size_t unit>
QVariant FromUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
#if __HAS_GMP__
        boost::multiprecision::number<boost::multiprecision::gmp_float<50> > result(request.toString().toStdString());
#else
        boost::multiprecision::cpp_dec_float_50 result(request.toString().toStdString());
#endif

        result /= unit;
        return QVariant::fromValue(QString(result.str(20, std::ios_base::fixed).c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
