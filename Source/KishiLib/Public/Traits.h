#include "CoreMinimal.h"
#include "UObject/Interface.h"
// #include <cassert>
#define frac(x) x - floor(x)

#define H_BPI(CLASS,I)                                                                \
	CLONEOVERRIDE(CLASS)                                                            \
public:                                                                             \
	CLASS() = default;                                                              \
	CLASS(TScriptInterface<I> _interface) : interface(_interface){}; \
	operator TScriptInterface<I>() const                                               \
	{                                                                               \
		return interface;                                                           \
	};                                                                              \
                                                                                    \
private:                                                                            \
	TScriptInterface<I> interface;

#define H_PROXY(CLASS, I, PROXIED)                          \
public:                                                     \
	CLASS() = default;                                      \
	~CLASS() { delete proxied; };                           \
	CLASS(PROXIED *_proxied) : proxied(_proxied){};         \
	static CLASS *New(PROXIED *_proxied)                    \
	{                                                       \
		auto proxy = NewObject<CLASS>();                    \
		proxy->proxied = _proxied;                          \
		return proxy;                                       \
	};                                                      \
	static TScriptInterface<I> NewScript(PROXIED *_proxied) \
	{                                                       \
		auto proxy = NewObject<CLASS>();                    \
		proxy->proxied = _proxied;                          \
		TScriptInterface<I> result;                         \
		result.SetObject(proxy);                            \
		return result;                                      \
	};                                                      \
	operator PROXIED *() const                              \
	{                                                       \
		return proxied;                                     \
	};                                                      \
                                                            \
private:                                                    \
	PROXIED *proxied;