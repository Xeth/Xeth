namespace Xeth{


template<size_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
        boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > value(request.toString().toStdString());
        value *= unit;
        return QVariant::fromValue(QString(value.convert_to<boost::multiprecision::cpp_int>().str().c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
