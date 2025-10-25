// Implementation inheritance
struct A {
    void f() {}
};

struct B : public A {
    void f() {}
};

struct C : public A {
    void f() {}
};

// Interface inheritance
struct Interface // superclass
{
    virtual void f() = 0;
    virtual void g() = 0;
};

struct Impl {
    void f() {}
    void g() {}
};

struct Adaptor : public Interface, public Impl {
    void f() override { Impl::f(); }
    void g() override { Impl::g(); }
};

// Virtual inheritance
struct Top // superclass
{
    char c;
};

struct MidA : virtual Top
{
    char c;
};

struct MidB : virtual Top
{
    char c;
};

class Bot : MidA, MidB
{
    char c;
public:
    void f()
    {
        c + Top::c + MidA::c + MidB::c;
    }
};

void var (A& arg) {
    arg.f(); // ?
}

int main() {
    A a; var(a);
    B b; var(b);
    C c; var(c);
}
