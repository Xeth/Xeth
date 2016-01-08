#pragma once

namespace Xeth{

#define JOIN(X, Y) X##Y


//__VA_ARGS__ utils
#define VA_NARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define PARSE_VARGS_20(F, x, ...) F(x), PARSE_VARGS_19(F,__VA_ARGS__)
#define PARSE_VARGS_19(F, x, ...) F(x), PARSE_VARGS_18(F, __VA_ARGS__)
#define PARSE_VARGS_18(F, x, ...) F(x), PARSE_VARGS_17(F, __VA_ARGS__)
#define PARSE_VARGS_17(F, x, ...) F(x), PARSE_VARGS_16(F, __VA_ARGS__)
#define PARSE_VARGS_16(F, x, ...) F(x), PARSE_VARGS_15(F, __VA_ARGS__)
#define PARSE_VARGS_15(F, x, ...) F(x), PARSE_VARGS_14(F, __VA_ARGS__)
#define PARSE_VARGS_14(F, x, ...) F(x), PARSE_VARGS_13(F, __VA_ARGS__)
#define PARSE_VARGS_13(F, x, ...) F(x), PARSE_VARGS_12(F, __VA_ARGS__)
#define PARSE_VARGS_12(F, x, ...) F(x), PARSE_VARGS_11(F, __VA_ARGS__)
#define PARSE_VARGS_11(F, x, ...) F(x), PARSE_VARGS_10(F, __VA_ARGS__)
#define PARSE_VARGS_10(F, x, ...) F(x), PARSE_VARGS_9(F, __VA_ARGS__)
#define PARSE_VARGS_9(F, x, ...) F(x), PARSE_VARGS_8(F, __VA_ARGS__)
#define PARSE_VARGS_8(F, x, ...) F(x), PARSE_VARGS_7(F, __VA_ARGS__)
#define PARSE_VARGS_7(F, x, ...) F(x), PARSE_VARGS_6(F, __VA_ARGS__)
#define PARSE_VARGS_6(F, x, ...) F(x), PARSE_VARGS_5(F, __VA_ARGS__)
#define PARSE_VARGS_5(F, x, ...) F(x), PARSE_VARGS_4(F, __VA_ARGS__)
#define PARSE_VARGS_4(F, x, ...) F(x), PARSE_VARGS_3(F, __VA_ARGS__)
#define PARSE_VARGS_3(F, x, ...) F(x), PARSE_VARGS_2(F, __VA_ARGS__)
#define PARSE_VARGS_2(F, x, ...) F(x), PARSE_VARGS_1(F, __VA_ARGS__)
#define PARSE_VARGS_1(F, x) F(x)


#define PARSE_VARGS_IMPL(F, num, ...) JOIN(PARSE_VARGS_,num)(F, __VA_ARGS__)
#define PARSE_VARGS(F, ...) PARSE_VARGS_IMPL(F, VA_NARGS(__VA_ARGS__), __VA_ARGS__)

}
