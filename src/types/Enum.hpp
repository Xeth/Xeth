#include <QObject>

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace Xeth{

#define ESCAPE_ENUM_STRING(r,data, Name) BOOST_PP_STRINGIZE(Name)

#define DECLARE_ENUM_CLASS(CLASS_NAME, ...)                                                                                                   \
static const char * BOOST_PP_CAT(CLASS_NAME,_names)[] = {BOOST_PP_SEQ_FOR_EACH(ESCAPE_ENUM_STRING,,BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))};   \
class CLASS_NAME : public QObject                                                                                                             \
{                                                                                                                                             \
    public:                                                                                                                                   \
        enum Value {__VA_ARGS__};                                                                                                             \
    public:                                                                                                                                   \
        inline CLASS_NAME(){}                                                                                                                 \
        inline CLASS_NAME(CLASS_NAME::Value value): _value(value){}                                                                           \
        inline CLASS_NAME(const CLASS_NAME &copy) : QObject(), _value(copy._value){}                                                          \
        inline static const char * ToString(CLASS_NAME::Value value){ return BOOST_PP_CAT(CLASS_NAME,_names)[value];}                         \
        inline operator Value() const { return _value;}                                                                                       \
        inline operator const char *() const {return toString();}                                                                             \
        inline CLASS_NAME & operator = (const CLASS_NAME &e){_value=e._value; return *this;}                                                  \
        inline CLASS_NAME & operator = (const CLASS_NAME::Value value){_value=value; return *this;}                                           \
        inline bool operator == (const CLASS_NAME &e) const {return _value==e._value;}                                                        \
        inline bool operator < (const CLASS_NAME &e) const {return _value<e._value;}                                                          \
        inline bool operator > (const CLASS_NAME &e) const {return _value>e._value;}                                                          \
   public slots:                                                                                                                              \
        inline const char *toString() const { return BOOST_PP_CAT(CLASS_NAME,_names)[_value];}                                                \
        inline Value toInt() const { return _value;}                                                                                          \
    private:                                                                                                                                  \
        Value _value;                                                                                                                         \
}


}
