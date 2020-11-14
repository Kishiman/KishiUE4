#pragma once
#include "KishiLibDependencies.h"
#include "ThClone.h"
#include "ThEqual.h"
#include "ThOperator.h"
#include "ThOperatorInt.h"
#include "ThOperatorLV.h"

template <typename T>
Ptr<T> Clone(const Ptr<T> &object)
{
    return object->Clone();
};

