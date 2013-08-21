#ifndef ___INANITY_META_CALLABLE_IPP___
#define ___INANITY_META_CALLABLE_IPP___

#include "Callable.hpp"
#include "Tuple.hpp"

BEGIN_INANITY_META

//******* Callable для функций

#define a1 args.first
#define a2 args.rest.first
#define a3 args.rest.rest.first
#define a4 args.rest.rest.rest.first
#define a5 args.rest.rest.rest.rest.first
#define a6 args.rest.rest.rest.rest.rest.first
#define a7 args.rest.rest.rest.rest.rest.rest.first
#define a8 args.rest.rest.rest.rest.rest.rest.rest.first
#define a9 args.rest.rest.rest.rest.rest.rest.rest.rest.first
#define b1 (((C*)args.first)->*callee)

template <typename R>
struct Callable<R (*)()>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)();
	typedef VoidTuple Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(); }
};
template <typename R, typename A1>
struct Callable<R (*)(A1)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1);
	typedef Tuple<A1, VoidTuple> Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1); }
};
template <typename R, typename A1, typename A2>
struct Callable<R (*)(A1, A2)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2);
	typedef Tuple<A1, Tuple<A2, VoidTuple> > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2); }
};
template <typename R, typename A1, typename A2, typename A3>
struct Callable<R (*)(A1, A2, A3)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, VoidTuple> > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3); }
};
template <typename R, typename A1, typename A2, typename A3, typename A4>
struct Callable<R (*)(A1, A2, A3, A4)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3, A4);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, VoidTuple> > > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3, a4); }
};
template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Callable<R (*)(A1, A2, A3, A4, A5)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3, A4, A5);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, VoidTuple> > > > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3, a4, a5); }
};
template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Callable<R (*)(A1, A2, A3, A4, A5, A6)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3, A4, A5, A6);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, VoidTuple> > > > > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3, a4, a5, a6); }
};
template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Callable<R (*)(A1, A2, A3, A4, A5, A6, A7)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3, A4, A5, A6, A7);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, VoidTuple> > > > > > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3, a4, a5, a6, a7); }
};
template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Callable<R (*)(A1, A2, A3, A4, A5, A6, A7, A8)>
{
	enum { isMethod = 0 };
	typedef R (*CalleeType)(A1, A2, A3, A4, A5, A6, A7, A8);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, Tuple<A8, VoidTuple> > > > > > > > Args;
	typedef R ReturnType;
	static inline R Call(CalleeType callee, const Args& args) { return callee(a1, a2, a3, a4, a5, a6, a7, a8); }
};

//******* Callable для методов

template <typename R, typename C>
struct Callable<R (C::*)()>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)();
	typedef Tuple<ptr<C>, VoidTuple> Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(); }
};
template <typename R, typename C, typename A1>
struct Callable<R (C::*)(A1)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1);
	typedef Tuple<ptr<C>, Tuple<A1, VoidTuple> > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2); }
};
template <typename R, typename C, typename A1, typename A2>
struct Callable<R (C::*)(A1, A2)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, VoidTuple> > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3); }
};
template <typename R, typename C, typename A1, typename A2, typename A3>
struct Callable<R (C::*)(A1, A2, A3)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, VoidTuple> > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
struct Callable<R (C::*)(A1, A2, A3, A4)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3, A4);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, VoidTuple> > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Callable<R (C::*)(A1, A2, A3, A4, A5)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3, A4, A5);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, VoidTuple> > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3, A4, A5, A6);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, VoidTuple> > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6, A7)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3, A4, A5, A6, A7);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, VoidTuple> > > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7, a8); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6, A7, A8)>
{
	enum { isMethod = 1 };
	typedef R (C::*CalleeType)(A1, A2, A3, A4, A5, A6, A7, A8);
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, Tuple<A8, VoidTuple> > > > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7, a8, a9); }
};

//******* Callable для константных методов

template <typename R, typename C>
struct Callable<R (C::*)() const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)() const;
	typedef Tuple<ptr<C>, VoidTuple> Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(); }
};
template <typename R, typename C, typename A1>
struct Callable<R (C::*)(A1) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1) const;
	typedef Tuple<ptr<C>, Tuple<A1, VoidTuple> > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2); }
};
template <typename R, typename C, typename A1, typename A2>
struct Callable<R (C::*)(A1, A2) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, VoidTuple> > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3); }
};
template <typename R, typename C, typename A1, typename A2, typename A3>
struct Callable<R (C::*)(A1, A2, A3) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, VoidTuple> > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
struct Callable<R (C::*)(A1, A2, A3, A4) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3, A4) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, VoidTuple> > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Callable<R (C::*)(A1, A2, A3, A4, A5) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3, A4, A5) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, VoidTuple> > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3, A4, A5, A6) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, VoidTuple> > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6, A7) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3, A4, A5, A6, A7) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, VoidTuple> > > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7, a8); }
};
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Callable<R (C::*)(A1, A2, A3, A4, A5, A6, A7, A8) const>
{
	enum { isMethod = 1 };
	typedef R (C::* CalleeType)(A1, A2, A3, A4, A5, A6, A7, A8) const;
	typedef Tuple<ptr<C>, Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, Tuple<A8, VoidTuple> > > > > > > > > Args;
	typedef R ReturnType;
	typedef C ClassType;
	static inline R Call(CalleeType callee, const Args& args) { return b1(a2, a3, a4, a5, a6, a7, a8, a9); }
};

//******* Callable для конструкторов

template <typename C>
struct CallableConstructor<void (C::*)()>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)();
	typedef VoidTuple Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C()); }
};
template <typename C, typename A1>
struct CallableConstructor<void (C::*)(A1)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1);
	typedef Tuple<A1, VoidTuple> Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1)); }
};
template <typename C, typename A1, typename A2>
struct CallableConstructor<void (C::*)(A1, A2)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2);
	typedef Tuple<A1, Tuple<A2, VoidTuple> > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2)); }
};
template <typename C, typename A1, typename A2, typename A3>
struct CallableConstructor<void (C::*)(A1, A2, A3)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, VoidTuple> > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3)); }
};
template <typename C, typename A1, typename A2, typename A3, typename A4>
struct CallableConstructor<void (C::*)(A1, A2, A3, A4)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3, A4);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, VoidTuple> > > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3, a4)); }
};
template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct CallableConstructor<void (C::*)(A1, A2, A3, A4, A5)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3, A4, A5);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, VoidTuple> > > > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3, a4, a5)); }
};
template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct CallableConstructor<void (C::*)(A1, A2, A3, A4, A5, A6)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3, A4, A5, A6);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, VoidTuple> > > > > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3, a4, a5, a6)); }
};
template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct CallableConstructor<void (C::*)(A1, A2, A3, A4, A5, A6, A7)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3, A4, A5, A6, A7);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, VoidTuple> > > > > > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3, a4, a5, a6, a7)); }
};
template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct CallableConstructor<void (C::*)(A1, A2, A3, A4, A5, A6, A7, A8)>
{
	enum { isMethod = 0 };
	typedef void (C::*CalleeType)(A1, A2, A3, A4, A5, A6, A7, A8);
	typedef Tuple<A1, Tuple<A2, Tuple<A3, Tuple<A4, Tuple<A5, Tuple<A6, Tuple<A7, Tuple<A8, VoidTuple> > > > > > > > Args;
	typedef ptr<C> ReturnType;
	typedef C ClassType;
	static inline ptr<C> Call(const Args& args) { return NEW(C(a1, a2, a3, a4, a5, a6, a7, a8)); }
};

#undef a1
#undef a2
#undef a3
#undef a4
#undef a5
#undef a6
#undef a7
#undef a8
#undef a9
#undef b1

END_INANITY_META

#endif