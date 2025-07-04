#include <nanobind/nanobind.h>
namespace nb = nanobind;

#define TEST_DIAMOND 1

#if TEST_DIAMOND
class A {
public:
    A() = default;
    virtual ~A() = default;
    virtual int foo() const = 0;
};
#endif

#if TEST_DIAMOND
class B : virtual public A
#else
class B
#endif
{
public:
    B(int _a, int _b) : a(_a), b(_b) { }
    virtual int foo() const /*override*/ { return a * b; }
    int a, b;
};

#if TEST_DIAMOND
class C : virtual public A
#else
class C
#endif
{
public:
    C() = default;
    virtual int bar() const { return x * 42; }
    double x = 1.0;
};

class D : public B, public C {
public:
    D(int _a, int _b) : B(_a, _b) { }
};

NB_MODULE(testbed, m)
{
    m.doc() = "Minimal working example for Nanobind";

#if TEST_DIAMOND
    nb::class_<A>(m, "A").def("foo", &A::foo);
#endif

#if TEST_DIAMOND
    nb::class_<B, A>(m, "B")
#else
    nb::class_<B>(m, "B")
#endif
        .def(nb::init<int, int>())
        .def("foo", &B::foo)
        .def_rw("a", &B::a)
        .def_rw("b", &B::b);

#if TEST_DIAMOND
    nb::class_<C, A>(m, "C")
#else
    nb::class_<C>(m, "C")
#endif
        .def("bar", &C::bar)
        .def_rw("x", &C::x);

    // NOTE: Nanobind does not support multiple inheritance, so this Pybind11
    // syntax does not work anymore.
    // nb::class_<D, B, C>(m, "D").def(nb::init<int, int>());

    // Define D as if it were only a child of C and bind the inherited methods
    // of B directly.
    nb::class_<D, C>(m, "D")
        .def(nb::init<int, int>())
        // Inherited from B
        .def("foo", &D::foo)
        .def_rw("a", &D::a)
        .def_rw("b", &D::b)
        // Inherited from C
        // NOTE: Normally, you would not need to redefine `bar` and `x` here,
        // but since `D` is not a direct child of `B`, we need to explicitly
        // rebind them to ensure they are accessible.
        .def("bar", &D::bar)
        .def_rw("x", &D::x);
}