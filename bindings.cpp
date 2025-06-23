#include <nanobind/nanobind.h>
namespace nb = nanobind;

class A {
public:
    A() = default;
    virtual ~A() = default;
    virtual int foo() const = 0;
};

class B : virtual public A {
public:
    B(int _a, int _b) : a(_a), b(_b) { }
    int foo() const override { return a * b; }
    int a, b;
};

class C : virtual public A {
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

    nb::class_<A>(m, "A").def("foo", &A::foo);

    nb::class_<B, A>(m, "B")
        .def(nb::init<int, int>())
        .def_rw("a", &B::a)
        .def_rw("b", &B::b);

    nb::class_<C, A>(m, "C").def("bar", &C::bar).def_rw("x", &C::x);

    // NOTE: Nanobind does not support multiple inheritance, so this Pybind11
    // syntax does not work anymore.
    // nb::class_<D, B, C>(m, "D").def(nb::init<int, int>());

    // Define D as if it was only a child of C and bind the inherited methods of
    // B directly.
    nb::class_<D, C>(m, "D")
        .def(nb::init<int, int>())
        .def("foo", &D::foo)
        .def_rw("a", &D::a)
        .def_rw("b", &D::b);
}