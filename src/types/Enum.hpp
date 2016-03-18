#include "macros.hpp"

#include <QObject>

namespace Xeth{

#define ESCAPE_ENUM_NAME(x) #x

#define DECLARE_ENUM_CLASS(CLASS_NAME, ...)                                                                                       \
static const char * JOIN(CLASS_NAME,_names)[] = {PARSE_VARGS(ESCAPE_ENUM_NAME, __VA_ARGS__)};                                     \
class CLASS_NAME : public QObject                                                                                                 \
{                                                                                                                                 \
    public:                                                                                                                       \
        enum Value {__VA_ARGS__};                                                                                                 \
    public:                                                                                                                       \
        inline CLASS_NAME(){}                                                                                                     \
        inline CLASS_NAME(CLASS_NAME::Value value): _value(value){}                                                               \
        inline CLASS_NAME(const CLASS_NAME &copy) : QObject(), _value(copy._value){}                                              \
        inline static const char * ToString(CLASS_NAME::Value value){ return JOIN(CLASS_NAME,_names)[value];}                     \
        inline operator Value() const { return _value;}                                                                           \
        inline operator const char *() const {return toString();}                                                                 \
        inline CLASS_NAME & operator = (const CLASS_NAME &e){_value=e._value; return *this;}                                      \
        inline CLASS_NAME & operator = (const CLASS_NAME::Value value){_value=value; return *this;}                               \
        inline bool operator == (const CLASS_NAME &e) const {return _value==e._value;}                                            \
        inline bool operator < (const CLASS_NAME &e) const {return _value<e._value;}                                              \
        inline bool operator > (const CLASS_NAME &e) const {return _value>e._value;}                                              \
   public slots:                                                                                                                  \
        inline const char *toString() const { return JOIN(CLASS_NAME,_names)[_value];}                                            \
        inline Value toInt() const { return _value;}                                                                              \
    public:                                                                                                                       \
        static const int Max = VA_NARGS(__VA_ARGS__);                                                                             \
        static const int Min = 0;                                                                                                 \
        static const int Mask = ((1 << Max) - 1);                                                                                 \
    private:                                                                                                                      \
        Value _value;                                                                                                             \
}

}
