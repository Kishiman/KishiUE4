#pragma once
#ifndef NO_UE4
#include "Runtime/Core/Public/Containers/Array.h"
// #include "Templates/SharedPointer.h"
// #include "Templates/UniquePtr.h"
#endif
#include <functional>

#ifdef NO_UE4
    ///////////////////////////////
    /// UObject definition macros
    ///////////////////////////////

    // These macros wrap metadata parsed by the Unreal Header Tool, and are otherwise
    // ignored when code containing them is compiled by the C++ compiler
    #define UPROPERTY(...)
    #define UFUNCTION(...)
    #define USTRUCT(...)
    #define UMETA(...)
    #define UPARAM(...)
    #define UENUM(...)
    #define UDELEGATE(...)
    #define RIGVM_METHOD(...)
#endif
#define THIS static_cast<const T &>(*this)
#define CCTHIS const_cast<T&>(*this)
#define CC_THIS(X) const_cast<X*>(this)
#define SCTHIS(X) const_cast<X&>(static_cast<const X&>(*this))
#define SC_CAST(T,ref) const_cast<T&>(static_cast<const T&>(*ref))

