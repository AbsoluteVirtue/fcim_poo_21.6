// https://www.youtube.com/watch?v=zI0DOKN6zr0
// Rethink Polymorphism in C++ - Nicolai Josuttis - C++ on Sea 2025
#include <vector>

struct GeoObj {             // Abstract Base Class
    GeoObj() = default;
    virtual void draw() const = 0;
    virtual ~GeoObj() = default;
};

class Circle : public GeoObj {
    int x;
    int y;
    int rad;
public:
    Circle(int x, int y, int r);
    virtual void draw() const override;
};

class Line : public GeoObj {
    int x1;
    int y1;
    int x2;
    int y2;
public:
    Line(int w, int x, int y, int z);
    virtual void draw() const override;
}; 

void example1() {
    std::vector<GeoObj*> v; // heterogeneous collection
    Line a = {1, 2, 3, 4};
    Circle b = {4, 42, 69};
    v.push_back(&a);
    v.push_back(&b);
    for (auto p : v) {
        p->draw();          // polymorphic call
    }
}

void example2() {
    auto create() {
        std::vector<GeoObj*> v; // heterogeneous collection
        Line a = {1, 2, 3, 4};
        Circle b = {4, 42, 69};
        v.push_back(&a);
        v.push_back(&b);
        return v; // !
    }

    auto val = create();    // elements of vector are out of scope
    for (auto p : val) {
        p->draw();          // polymorphic call (ERROR)
    }

    // ... possible interruption here

    val.clear();            // remove all elements in the vector
}

void example3() {
    auto create() {
        std::vector<GeoObj*> v; // heterogeneous collection
        v.push_back(new Line{1, 2, 3, 4});
        v.push_back(new Circle{4, 42, 69});
        return v;
    }

    auto val = create();
    for (auto p : val) {
        p->draw();          // polymorphic call
    }

    // ... possible interruption here

    // memory leak without explicit "delete" call beforehand
    for (auto p : val) {
        delete p;
        p = nullptr;
    }
    val.clear();            // remove all elements in the vector
}

void example4() {
    auto create() {
        std::vector<GeoObj*> v; // heterogeneous collection
        v.push_back(new Line{1, 2, 3, 4});
        v.push_back(new Circle{4, 42, 69});
        return v;
    }

    auto val = create();
    try {
        for (auto p : v) {
            p->draw();          // polymorphic call
        }
    } catch (const std::exception&) {
        // memory leak without explicit "delete" call beforehand
        for (auto p : val) {
            delete p;
            p = nullptr;
        }
        val.clear();
        throw; // rethrow exception
    }
    // memory leak without explicit "delete" call beforehand
    for (auto p : val) {
        delete p;
        p = nullptr;
    }
    val.clear();
}

class Picture {
    std::vector<GeoObj*> v;
public:
    void push_back(GeoObj* gp) {
        v.push_back(gp);
    }
    // encapsulate "delete" calls:
    ~Picture() {
        for (auto p : v) {
            delete p;
            p = nullptr;
        }
        v.clear();
    }
    // encapsulate "new" calls:
    void insert(int w, int x, int y, int z) {
        v.push_back(new Line{w, x, y, z});
    }
    void insert(int x, int y, int r) {
        v.push_back(new Circle{wx, y, r});
    }
    // or with perfect forwarding:
    template <class T, class... Types> void insert(Types&&... args) {
        v.push_back(new T{std::forward<Types>(args)...});
    }
    // disable copying to avoid multiple owners:
    Picture(const Picture&) = delete;
    Picture& operator=(const Picture&) = delete;
};

void example5() {
    auto create() {
        Picture v;
        v.push_back(1, 2, 3, 4);
        v.push_back(4, 42, 69);
        return v;
    }

    auto val = create();
    // Picture's destructor will cleanup resources automatically
}

void example6() {
    // Smart pointers instead of "class Picture"
    #include <shared_ptr>
    using GeoPtr = std::shared_ptr<GeoObj>;

    auto create() {
        std::vector<GeoPtr> v;
        v.push_back(std::make_shared<Line>(1, 2, 3, 4));
        v.push_back(std::make_shared<Circle>(4, 42, 69));
        return v;
    }

    auto val = create();
    for (const auto &p : val) {
        p->draw();          // polymorphic call
    }

    // ...

    val.clear();            // shared_ptr object calls "delete" here
}

void example7() {
    // Smart pointers instead of "class Picture"
    #include <unique_ptr>
    using GeoPtr = std::unique_ptr<GeoObj>;

    auto create() {
        std::vector<GeoPtr> v;
        v.push_back(std::move(std::make_unique<Line>(1, 2, 3, 4)));
        v.push_back(std::move(std::make_unique<Circle>(4, 42, 69)));
        return v;
    }

    auto val = create();
    for (const auto &p : val) {
        p->draw();          // polymorphic call
    }

    // ...
    
    val.clear();            // shared_ptr object calls "delete" here
}

void example8() {
    template <class GeoObj> // replace superclass with type parameter
    void draw_elements(const std::vector<GeoObj>& val) {
        // val is a homogeneous collection
        for (const auto &v : val) {
            v.draw();       // polymorphic call
        }
    }
}

void example9() {
    #include <variant>
    using GeoVar = std::variant<Circle, Line>;

    auto create() {
        std::vector<GeoVar> v; // heterogeneous collection again
        v.push_back(Line(1, 2, 3, 4));
        v.push_back(Circle(4, 42, 69));
        return v;
    }

    auto val = create();
    for (const auto& v : val) {
        // visitor pattern
        std::visit(
            [] (const auto& o) {    // lambda function for local vtable
                o.draw();           // polymorphic call
            }, v);
    }

    val.clear();
    /*
        + no pointers
        + no new/delete
        + objects located together
        + no common base class
        + no virtual functions
        - all elements have maximum size
        - copying by value is performance-heavy
        - closed set of alternatives
    */ 
}
