#pragma once

#include "Kishi/KishiTheory.h"
#define BASEYX Base<Y, X>
#define BASEXZ Base<X, Z>
#define BASEYZ Base<Y, Z>

#define BASEX Base<X, void>
#define BASEY Base<Y, void>
#define _BASEYX Base<_Y, _X>
#define _BASEY Base<_Y, void>
template <typename Y, typename X>
struct ThBaseFunc;
template <typename Y, typename X, template <typename, typename> class Base>
struct FuncRoot : Expression<Base<Y, X>>
{
    DOWNSOLVEOVERRIDE(FuncRoot)
    virtual void DownSolve() override
    {
        UE_LOG(LogTemp, Warning, TEXT("FuncRoot downsolve (%d)"), this);
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
template <typename Y, template <typename, typename> class Base>
struct FuncRoot<Y, void, Base> : Expression<Base<Y, void>>
{
    DOWNSOLVEOVERRIDE(FuncRoot)
    virtual void DownSolve() override
    {
        UE_LOG(LogTemp, Warning, TEXT("FuncRoot downsolve (%d)"), this);
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

template <typename _Y, typename _X = void, template <typename, typename> class Base = ThBaseFunc>
struct ThFunc : FuncRoot<_Y, _X, Base>
{
    template <typename Y, typename X, typename Z>
    struct ThFuncCascade : HBinaryExpression<Base<Y, X>, Base<X, Z>, Base<Y, Z>>
    {
        HBINARY(ThFuncCascade, BASEYX, BASEXZ, BASEYZ)
        virtual Y operator()(Z z) const override
        {
            return (*base::a)((*base::b)(z));
        };
    };
    template <typename Y, typename X>
    struct ThFuncCascade<Y, X, void> : HBinaryExpression<Base<Y, X>, BASEX, BASEY>
    {
        HBINARY(ThFuncCascade, BASEYX, BASEX, BASEY)
        virtual Y operator()() const override
        {
            return (*base::a)((*base::b)());
        };
    };
    template <typename Z>
    Ptr<Base<_Y, Z>> op(Base<_X, Z> &other)
    {
        return new ThFuncCascade<_Y, _X, Z>(static_cast<Base<_Y, _X> &>(*this), const_cast<Base<_X, Z> &>(other));
    }
    template <typename Z>
    Ptr<Base<_Y, Z>> op(Ptr<Base<_X, Z>> other)
    {
        return op(*other);
    }
};
template <typename _Y, template <typename, typename> class Base>
struct ThFunc<_Y, void, Base> : FuncRoot<_Y, void, Base>
{
};
template <typename Y, typename X=void>
struct ThBaseFunc : ThFunc<Y, X>
{
};
