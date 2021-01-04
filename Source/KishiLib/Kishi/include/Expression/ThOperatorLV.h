#pragma once

#include "Expression/Base/Expression.h"
#include "ThOperatorInt.h"
template <typename Y, typename X>
struct ThBaseOperatorLV;
template <typename S>
S Unit() { return 1; }

#define EXPRESSION_MUL_BEGIN(CLASS, S)              \
    struct CLASS##Mul : UnaryExpression_A<CLASS, S> \
    {                                               \
        UNARY_A(CLASS##Mul, CLASS, S)
#define EXPRESSION_MUL_END(CLASS, S)                  \
    }                                                 \
    ;                                                 \
    Ptr<CLASS> operator*(S scalar) const              \
    {                                                 \
        return new CLASS##Mul(SCTHIS(CLASS), scalar); \
    }

#define EXPRESSION_DIV_BEGIN(CLASS, S)              \
    struct CLASS##Div : UnaryExpression_A<CLASS, S> \
    {                                               \
        UNARY_A(CLASS##Div, CLASS, S)
#define EXPRESSION_DIV_END(CLASS, S)                  \
    }                                                 \
    ;                                                 \
    Ptr<CLASS> operator/(S scalar) const              \
    {                                                 \
        return new CLASS##Div(SCTHIS(CLASS), scalar); \
    }
template <typename _Y, typename _X = void, template <typename, typename> class Base = ThBaseOperatorLV>
struct ThOperatorLV : ThOperatorInt<_Y, _X, Base>
{
    template <typename Y, typename X, typename S>
    struct ThOperatorMul : UnaryExpression_A<Base<Y, X>, S>
    {
        UNARY_A(ThOperatorMul, BASEYX, S)
        virtual Y operator()(X x) const override
        {
            return (*base::express)(x) * (base::a);
        };
    };
    template <typename Y, typename S>
    struct ThOperatorMul<Y, void, S> : UnaryExpression_A<Base<Y, void>, S>
    {
        UNARY_A(ThOperatorMul, BASEY, S)
        virtual Y operator()() const override
        {
            return (*base::express)() * (base::a);
        };
    };
    template <typename Y, typename X, typename S>
    struct ThOperatorDiv : UnaryExpression_A<Base<Y, X>, S>
    {
        UNARY_A(ThOperatorDiv, BASEYX, S)
        virtual Y operator()(X x) const override
        {
            return (*base::express)(x) / (base::a);
        };
    };
    template <typename Y, typename S>
    struct ThOperatorDiv<Y, void, S> : UnaryExpression_A<Base<Y, void>, S>
    {
        UNARY_A(ThOperatorDiv, BASEY, S)
        virtual Y operator()() const override
        {
            return (*base::express)() / (base::a);
        };
    };
    template <typename Y, typename X, typename S>
    struct ThOperatorLerp : BinaryExpression_A<Base<Y, X>, S>
    {
        BINARY_A(ThOperatorLerp, BASEYX, S)
        virtual Y operator()(X x) const override
        {
            return ((*base::a)(x)*base::c) + (*base::b(x) * (Unit<S>() - base::c));
        };
    };
    template <typename Y, typename S>
    struct ThOperatorLerp<Y, void, S> : BinaryExpression_A<Base<Y, void>, S>
    {
        BINARY_A(ThOperatorLerp, BASEY, S)
        virtual Y operator()() const override
        {
            return ((*base::a)() * base::c) + (*base::b() * (Unit<S>() - base::c));
        };
    };
    template <typename S>
    Ptr<Base<_Y, _X>> operator*(S other) const
    {
        return new ThOperatorMul<_Y, _X, S>(SCTHIS(_BASEYX), other);
    }
    template <typename S>
    Ptr<Base<_Y, _X>> operator/(S other) const
    {
        return new ThOperatorDiv<_Y, _X, S>(SCTHIS(_BASEYX), other);
    }
    template <typename S>
    static Ptr<Base<_Y, _X>> lerp(_BASEYX &l, _BASEYX &r, S lerp_factor)
    {
        return new ThOperatorLerp<_Y, _X, S>(l, r, lerp);
    }
};

template <typename Y, typename X = void>
struct ThBaseOperatorLV : ThOperatorLV<Y, X>
{
};
template <typename Y, typename X, typename S, template <typename, typename> class Base>
Ptr<Base<Y, X>> operator*(Ptr<Base<Y, X>> a, S b)
{
    return (*a) * b;
}
template <typename Y, typename X, typename S, template <typename, typename> class Base>
Ptr<Base<Y, X>> operator*(S a, Base<Y, X> &b)
{
    return b * a;
}
template <typename Y, typename X, typename S, template <typename, typename> class Base>
Ptr<Base<Y, X>> operator*(S a, Ptr<Base<Y, X>> b)
{
    return (*b) * a;
}
template <typename Y, typename X, typename S, template <typename, typename> class Base>
Ptr<Base<Y, X>> operator/(Ptr<Base<Y, X>> a, S b)
{
    return (*a) / b;
}
