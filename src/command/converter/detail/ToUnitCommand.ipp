namespace Xeth{


template<size_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    try
    {
        boost::multiprecision::cpp_dec_float_50 value(request.toString().toStdString());
        value *= unit;
        std::string result = value.str(20, std::ios_base::fixed);
        std::size_t point = result.find('.');
        if(point != std::string::npos)
        {
            result.erase(point, result.size()-point);
        }
        return QString(result.c_str());
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}


}
