#pragma once

#include "Expression/Base/Expression.h"
#define BASEYX Base<Y, X>
#define BASEXZ Base<X, Z>
#define BASEYZ Base<Y, Z>

#define BASEX Base<X, void>
#define BASEY Base<Y, void>
#define _BASEYX Base<_Y, _X>
#define _BASEY Base<_Y, void>
template <typename Y, typename X>
struct ThBaseOperator;
template <typename Y, typename X, template <typename, typename> class Base>
struct OperatorRoot : Expression<Base<Y, X>>
{
    DOWNSOLVEOVERRIDE(OperatorRoot)
    virtual void DownSolve() override
    {
        UE_LOG(LogTemp, Warning, TEXT("OperatorRoot downsolve (%d)"), this);
    };
    struct Sym : public Symbol<BASEYX>
    {
        SYMBOL(Sym, BASEYX)
        virtual Y operator()(X x) const override
        {
            return base::express->operator()(x);
        }
    };
    struct Dyn : Base<Y, X>
    {
        CLONEOVERRIDE(Dyn)
        Dyn(std::function<Y(X)> _func) : func(_func){};
        virtual Y operator()(X x) const override
        {
            return func(x);
        }

    private:
        std::function<Y(X)> func;
    };
    virtual Y operator()(X x) const = 0;
};
#define EXPRESSION_SYM_BEGIN(CLASS)   \
    struct Sym : public Symbol<CLASS> \
    {                                 \
        SYMBOL(Sym, CLASS)
#define EXPRESSION_SYM_END() \
    }                        \
    ;

#define EXPRESSION_DYN_BEGIN(CLASS) \
    struct Dyn : public CLASS       \
    {                               \
        CLONEOVERRIDE(Dyn)
#define EXPRESSION_DYN_END() \
    }                        \
    ;
template <typename Y, template <typename, typename> class Base>
struct OperatorRoot<Y, void, Base> : Expression<Base<Y, void>>
{
    DOWNSOLVEOVERRIDE(OperatorRoot)
    virtual void DownSolve() override
    {
        UE_LOG(LogTemp, Warning, TEXT("OperatorRoot downsolve (%d)"), this);
    };
    virtual Y operator()() const = 0;
    struct Sym : public Symbol<BASEY>
    {
        SYMBOL(Sym, BASEY)
        virtual Y operator()() const override
        {
            return base::express->operator()();
        }
    };
    struct Dyn : Base<Y, void>
    {
        CLONEOVERRIDE(Dyn)
        Dyn(std::function<Y()> _func) : func(_func){};
        virtual Y operator()() const override
        {
            return func();
        }

    private:
        std::function<Y()> func;
    };
};

template <typename _Y, typename _X = void, template <typename, typename> class Base = ThBaseOperator>
struct ThOperator : OperatorRoot<_Y, _X, Base>
{
    template <typename Y, typename X, typename Z>
    struct ThOperatorCascade : HBinaryExpression<Base<Y, X>, Base<X, Z>, Base<Y, Z>>
    {
        HBINARY(ThOperatorCascade, BASEYX, BASEXZ, BASEYZ)
        virtual Y operator()(Z z) const override
        {
            return (*base::a)((*base::b)(z));
        };
    };
    template <typename Y, typename X>
    struct ThOperatorCascade<Y, X, void> : HBinaryExpression<Base<Y, X>, BASEX, BASEY>
    {
        HBINARY(ThOperatorCascade, BASEYX, BASEX, BASEY)
        virtual Y operator()() const override
        {
            return (*base::a)((*base::b)());
        };
    };
    template <typename Z>
    Ptr<Base<_Y, Z>> op(Base<_X, Z> &other)
    {
        return new ThOperatorCascade<_Y, _X, Z>(static_cast<Base<_Y, _X> &>(*this), const_cast<Base<_X, Z> &>(other));
    }
    template <typename Z>
    Ptr<Base<_Y, Z>> op(Ptr<Base<_X, Z>> other)
    {
        return op(*other);
    }
};
template <typename _Y, template <typename, typename> class Base>
struct ThOperator<_Y, void, Base> : OperatorRoot<_Y, void, Base>
{
};
template <typename Y, typename X = void>
struct ThBaseOperator : ThOperator<Y, X>
{
};
