
struct interface // superclass
{
    virtual void f() = 0;
    virtual void g() = 0;
};

struct impl {
    void f() {}
    void g() {}
};

struct a : public interface, public impl {
    void f() override { impl::f(); }
    void g() override { impl::g(); }
};

int main() {

    a x;
    x.f();
    x.g();

}
