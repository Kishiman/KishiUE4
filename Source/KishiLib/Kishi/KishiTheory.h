#pragma once

#include <memory>
#include "./KishiData.h"
#include "./KishiTraits.h"
#include "./KishiLibCompatibility.h"
#include "CoreMinimal.h"

enum TheoryAssumtion
{
  fullfil = 0,
  promise = 1,
  stand = 2,
};

template <typename T>
class Theory
{
};

template <template <typename, TheoryAssumtion, typename...> class _Theory, TheoryAssumtion _TA, typename T, typename... dbases>
class Theory<_Theory<T, _TA, dbases...>> : public virtual Theory<T>
{
  friend _Theory<T, _TA, dbases...>;

private:
  Theory() = default;
};
template <typename T>
struct Ptr
{

public:
  Ptr(const T *p) : ptr(p) {}
  Ptr(T *p) : ptr(p) {}
  Ptr(void *p) : ptr(static_cast<T *>(p)) {}
  Ptr(const T &obj) : ptr(const_cast<T *>(&obj)) {}
  Ptr(T &obj) : ptr(&obj) {}
  virtual ~Ptr() = default;
  T *operator->() const
  {
    return ptr;
  };
  T &operator*() const
  {
    return (*ptr);
  };
  operator T &() const
  {
    return (*ptr);
  };
  template <typename Z>
  operator Ptr<Z>() const
  {
    return Ptr<Z>(static_cast<Z *>(ptr));
  };
  template <typename Z>
  operator Z &() const
  {
    return static_cast<Z &>(*ptr);
  };
  template <typename Z>
  operator Z *() const
  {
    return static_cast<Z *>(ptr);
  };

private:
  T *ptr;
};
template <typename T>
struct Expression
{

  virtual ~Expression()
  {
    UE_LOG(LogTemp, Warning, TEXT("Expression Destractor (%d)'deleted'"), this);
  }
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("Expression UpSolve (%d)'Harmless'"), this);
  }
  virtual void DownSolve() = 0;
  virtual void *Clone() = 0;
};

#define DOWNSOLVEOVERRIDE(S) \
public:                      \
  virtual ~S()               \
  {                          \
    DownSolve();             \
  }

#define CLONEOVERRIDE(S)         \
public:                          \
  S(S &other) = default;         \
  S(const S &other) = default;   \
  virtual void *Clone() override \
  {                              \
    return new S(*this);         \
  }

template <typename T>
struct UnaryExpression : public T
{
  DOWNSOLVEOVERRIDE(UnaryExpression)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this, express);
    if (express != nullptr)
      express->UpSolve();
  };
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("UnaryExpression UpSolve (%d)'deleted'"), this);
    delete this;
  }
  virtual void *Clone() override
  {
    express = static_cast<T *>(express->Clone());
    return this;
  }
  UnaryExpression(T *exp) : express(exp) {}
  UnaryExpression(Ptr<T> exp) : express(exp.operator->()) {}
  UnaryExpression(T &exp) : express(&exp) {}
  UnaryExpression(const T &exp) : express(&(SC_CAST(T, exp))) {}

protected:
  T *express;
};

#define UNARY(S, T)                \
public:                            \
  using base = UnaryExpression<T>; \
  S(T *exp) : base(exp){};         \
  S(Ptr<T> exp) : base(exp){};     \
  S(T &exp) : base(exp){};         \
  S(const T &exp) : base(exp){};

template <typename T, typename A>
struct UnaryExpression_A : public T
{
  DOWNSOLVEOVERRIDE(UnaryExpression_A)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this, express);
    if (express != nullptr)
      express->UpSolve();
  };
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("UnaryExpression UpSolve (%d)'deleted'"), this);
    delete this;
  }
  virtual void *Clone() override
  {
    express = static_cast<T *>(express->Clone());
    return this;
  }
  UnaryExpression_A(T *exp, A a) : express(exp), a(a) {}
  UnaryExpression_A(Ptr<T> exp, A a) : express(exp.operator->()), a(a) {}
  UnaryExpression_A(T &exp, A a) : express(&exp), a(a) {}
  UnaryExpression_A(const T &exp, A a) : express(&(SC_CAST(T, exp))), a(a) {}

protected:
  T *express;
  A a;
};
#define UNARY_A(S, T, A)                \
public:                                 \
  using base = UnaryExpression_A<T, A>; \
  S(T *exp, A a) : base(exp, a){};      \
  S(Ptr<T> exp, A a) : base(exp, a){};  \
  S(T &exp, A a) : base(exp, a){};      \
  S(const T &exp, A a) : base(exp, a){};

template <typename T>
struct BinaryExpression : public T
{
  DOWNSOLVEOVERRIDE(BinaryExpression)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("BINARY downsolve (%d) upsolve(%d), upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("BinaryExpression UpSolve (%d)'deleted'"), this);
    delete this;
  }
  BinaryExpression(T *a, T *b) : a(a), b(b){};
  BinaryExpression(Ptr<T> a, Ptr<T> b) : a(a.operator->()), b(b.operator->()){};
  BinaryExpression(T &a, T &b) : a(&a), b(&b){};
  BinaryExpression(const T &a,const T &b) : a(&(SC_CAST(T,a))), b(&(SC_CAST(T,a))){};
  virtual void *Clone() override
  {
    a = static_cast<T *>(a->Clone());
    b = static_cast<T *>(b->Clone());
    return this;
  }

protected:
  T *a;
  T *b;
};

#define BINARY(S, T)                    \
public:                                 \
  using base = BinaryExpression<T>;     \
  S(T *a, T *b) : base(a, b){};         \
  S(Ptr<T> a, Ptr<T> b) : base(a, b){}; \
  S(T &a, T &b) : base(a, b){};         \
  S(const T &a, const T &b) : base(a, b){};

template <typename T, typename C>
struct BinaryExpression_A : public T
{
  DOWNSOLVEOVERRIDE(BinaryExpression_A)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("BINARY downsolve (%d) upsolve(%d), upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("BinaryExpression_A UpSolve (%d)'deleted'"), this);
    delete this;
  }
  BinaryExpression_A(T *a, T *b, C c) : a(a), b(b), c(c){};
  BinaryExpression_A(Ptr<T> a, Ptr<T> b, C c) : a(a.operator->()), b(b.operator->()), c(c){};
  BinaryExpression_A(T &a, T &b, C c) : a(&a), b(&b), c(c){};
  BinaryExpression_A(const T &a,const T &b,C c) : a(&(SC_CAST(T,a))), b(&(SC_CAST(T,b))),c(c){};

  virtual void *Clone() override
  {
    a = static_cast<T *>(a->Clone());
    b = static_cast<T *>(b->Clone());
    return this;
  }

protected:
  T *a;
  T *b;
  C c;
};

#define BINARY_A(S, T, C)                       \
public:                                         \
  using base = BinaryExpression_A<T, C>;        \
  S(T *a, T *b, C c) : base(a, b, c){};         \
  S(Ptr<T> a, Ptr<T> b, C c) : base(a, b, c){}; \
  S(T &a, T &b, C c) : base(a, b, c){};         \
  S(const T &a, const T &b, C c) : base(a, b, c){};

template <typename A, typename B, typename T>
struct HBinaryExpression : public T
{
  DOWNSOLVEOVERRIDE(HBinaryExpression)

  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("HBINARY downsolve (%d) upsolve(%d), upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve()
  {
    UE_LOG(LogTemp, Warning, TEXT("HBinaryExpression UpSolve (%d)'deleted'"), this);
    delete this;
  }
  HBinaryExpression(A *a, B *b) : a(a), b(b){};
  HBinaryExpression(Ptr<A> a, Ptr<B> b) : a(a.operator->()), b(b.operator->()){};
  HBinaryExpression(A &a, B &b) : a(&a), b(&b){};
    HBinaryExpression(const T &a,const T &b) : a(&(SC_CAST(A,a))), b(&(SC_CAST(B,b))){};

  virtual void *Clone() override
  {
    a = static_cast<A *>(a->Clone());
    b = static_cast<B *>(b->Clone());
    return this;
  }

protected:
  A *a;
  B *b;
};

#define HBINARY(S, A, B, T)                 \
public:                                     \
  using base = HBinaryExpression<A, B, T>;  \
  S(A *a, B *b) : base(a, b){};             \
  S(Ptr<A> a, Ptr<B> b) : base(a, b){};     \
  S(A &a, B &b) : base(a, b){};             \
  S(const A &a, const B &b) : base(a, b){};

template <typename T>
struct Symbol : public T
{
  DOWNSOLVEOVERRIDE(Symbol)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this, express);
    if (express != nullptr)
      express->UpSolve();
  };
  Symbol(T *exp) : express(exp){};
  Symbol(Ptr<T> exp) : express(exp.operator->()){};
  Symbol(const T *exp) : express(const_cast<T *>(exp)){};
  Symbol(Symbol &&other) : express(other.express)
  {
    UE_LOG(LogTemp, Warning, TEXT("calling Clone constructor %d"), this);
    other.express = nullptr;
  }
  Symbol(Symbol &other) : Symbol(std::move(other))
  {
  }
  virtual void *Clone() override
  {
    T *result = static_cast<T *>(express);
    express = nullptr;
    return static_cast<T *>(result->Clone());
  }

protected:
  T *express;
};

#define SYMBOL(S, T)                  \
public:                               \
  using base = Symbol<T>;             \
  S(T *exp) : base(exp){};            \
  S(Ptr<T> exp) : base(exp){};        \
  S(base &&other) : base(other){};    \
  S(base &other) : base(other){};     \
  S(S &&other) : base(other){};       \
  S(S &other) : base(other){};        \
  S &operator=(Ptr<T> exp)            \
  {                                   \
    base::express = exp.operator->(); \
    return *this;                     \
  }
