#pragma once

#include "Expression/Base/Expression.h"
#include "ThOperator.h"

template <typename Y, typename X>
struct ThBaseOperatorInt;
template <typename S>
S Zero() { return 0; }
#define EXPRESSION_ADD_BEGIN(CLASS)             \
    struct CLASS##Add : BinaryExpression<CLASS> \
    {                                           \
        BINARY(CLASS##Add, CLASS)
#define EXPRESSION_ADD_END(CLASS)                                          \
    }                                                                      \
    ;                                                                      \
    Ptr<CLASS> operator+(CLASS &other) const                               \
    {                                                                      \
        return new CLASS##Add(SCTHIS(CLASS), static_cast<CLASS &>(other)); \
    }

#define EXPRESSION_SUB_BEGIN(CLASS)             \
    struct CLASS##Sub : BinaryExpression<CLASS> \
    {                                           \
        BINARY(CLASS##Sub, CLASS)
#define EXPRESSION_SUB_END(CLASS)                                          \
    }                                                                      \
    ;                                                                      \
    Ptr<CLASS> operator-(CLASS &other) const                               \
    {                                                                      \
        return new CLASS##Sub(SCTHIS(CLASS), static_cast<CLASS &>(other)); \
    }

#define EXPRESSION_SEQ_BEGIN(CLASS)             \
    struct CLASS##SEQ : BinaryExpression<CLASS> \
    {                                           \
        BINARY(CLASS##SEQ, CLASS)
#define EXPRESSION_SEQ_END(CLASS)                                          \
    }                                                                      \
    ;                                                                      \
    Ptr<CLASS> operator|(CLASS &other) const                               \
    {                                                                      \
        return new CLASS##SEQ(SCTHIS(CLASS), static_cast<CLASS &>(other)); \
    }
#define EXPRESSION_OPP_BEGIN(CLASS)            \
    struct CLASS##Opp : UnaryExpression<CLASS> \
    {                                          \
        UNARY(CLASS##Opp, CLASS)

#define EXPRESSION_OPP_END(CLASS)             \
    }                                         \
    ;                                         \
    Ptr<CLASS> operator-() const              \
    {                                         \
        return new CLASS##Opp(SCTHIS(CLASS)); \
    }
template <typename _Y, typename _X = void, template <typename, typename> class Base = ThBaseOperatorInt>
struct ThOperatorInt : ThOperator<_Y, _X, Base>
{
    template <typename Y, typename X>
    struct ThOperatorAdd : BinaryExpression<Base<Y, X>>
    {
        BINARY(ThOperatorAdd, BASEYX)
        virtual Y operator()(X x) const override
        {
            return (*base::a)(x) + (*base::b)(x);
        };
    };
    template <typename Y, typename X>
    struct ThOperatorSub : BinaryExpression<Base<Y, X>>
    {
        BINARY(ThOperatorSub, BASEYX)
        virtual Y operator()(X x) const override
        {
            return (*base::a)(x) - (*base::b)(x);
        };
    };
    template <typename Y, typename X>
    struct ThOperatorOpp : UnaryExpression<Base<Y, X>>
    {
        UNARY(ThOperatorOpp, BASEYX)
        virtual Y operator()(X x) const override
        {
            return -(*base::express)(x);
        };
    };
    //****************************Specification*****************************
    template <typename Y>
    struct ThOperatorAdd<Y, void> : BinaryExpression<Base<Y, void>>
    {
        BINARY(ThOperatorAdd, BASEY)
        virtual Y operator()() const override
        {
            return (*base::a)() + (*base::b)();
        };
    };
    template <typename Y>
    struct ThOperatorSub<Y, void> : BinaryExpression<Base<Y, void>>
    {
        BINARY(ThOperatorSub, BASEY)
        virtual Y operator()() const override
        {
            return (*base::a)() - (*base::b)();
        };
    };
    template <typename Y>
    struct ThOperatorOpp<Y, void> : UnaryExpression<Base<Y, void>>
    {
        UNARY(ThOperatorOpp, BASEY)
        virtual Y operator()() const override
        {
            return -(*base::express)();
        };
    };
    Ptr<_BASEYX> operator+(_BASEYX &other) const
    {
        return new ThOperatorAdd<_Y, _X>(SCTHIS(_BASEYX), static_cast<_BASEYX &>(other));
    }
    Ptr<_BASEYX> operator-(_BASEYX &other) const
    {
        return new ThOperatorSub<_Y, _X>(SCTHIS(_BASEYX), static_cast<_BASEYX &>(other));
    }
    Ptr<_BASEYX> operator-() const
    {
        return new ThOperatorOpp<_Y, _X>(SCTHIS(_BASEYX));
    }
};
template <typename Y, typename X = void>
struct ThBaseOperatorInt : ThOperatorInt<Y, X>
{
};
template <typename _Y, typename _X, template <typename, typename> class Base>
Ptr<_BASEYX> operator+(Ptr<Base<_Y, _X>> a, _BASEYX &other)
{
    return (*a) + other;
};
template <typename _Y, typename _X, template <typename, typename> class Base>
Ptr<_BASEYX> operator-(Ptr<Base<_Y, _X>> a, _BASEYX &other)
{
    return (*a) - other;
};

template <typename _Y, typename _X, template <typename, typename> class Base>
Ptr<_BASEYX> operator-(Ptr<Base<_Y, _X>> a)
{
    return -(*a);
};
