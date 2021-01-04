#pragma once
#include "Expression/Base/Expression.h"

//The assumption of the theory regarding a class that derives from it
enum TheoryAssumtion
{
  //class stands the assertions of the theory 
  stand,
  //class is abstract and promise to fulfil the assertions of the theory through its derivates 
  promise,
  //class fulfil the promise of its parent class 
  fullfil,
};
//Theory template where T is the target class
template <typename T>
class Theory
{
};
//Specification for sub theories, _Theory is a theory template, T the target class
template <template <typename, TheoryAssumtion, typename...> class _Theory, TheoryAssumtion _TA, typename T, typename... dbases>
class Theory<_Theory<T, _TA, dbases...>> : public virtual Theory<T>
{
  friend _Theory<T, _TA, dbases...>;

private:
  Theory() = default;
};


