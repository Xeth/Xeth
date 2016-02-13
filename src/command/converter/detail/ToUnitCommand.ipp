namespace Xeth{


template<uint64_t unit>
QVariant ToUnitCommand<unit>::operator()(const QVariant &request)
{
    boost::multiprecision::cpp_int value(request.toString().toStdString());
    boost::multiprecision::cpp_dec_float_50 result(value);
    result /= unit;
    return QVariant::fromValue(QString(result.str().c_str()));
}


}
