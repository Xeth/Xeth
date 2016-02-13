namespace Xeth{


template<uint64_t unit>
QVariant FromUnitCommand<unit>::operator()(const QVariant &request)
{
    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > value(request.toString().toStdString());
    value *= unit;
    return QVariant::fromValue(QString(value.str(0, std::ios_base::fixed).c_str()));
}


}
