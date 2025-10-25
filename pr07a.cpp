// Итераторы, чаcть 1

class vector {
    int *data{new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9}};

public:
    class iterator {
        int *p{nullptr};

    public:
        iterator() = delete;
        iterator(int *d) : p(d) {}
        iterator &operator++() {
            p++;
            return *this;
        }
        int &operator*() { return *p; }
        friend bool operator!=(const iterator &a, const iterator &b) {
            return a.p != b.p;
        }
    };
    auto begin() { return iterator(data); }
    auto end() { return iterator(data + 10); }
};

class list {
    struct node {
        int data{0};
        node *next{nullptr};
    };

    node *hd = new node{1, new node{2, new node{3, new node{4, new node{5, nullptr}}}}};

public:
    class iterator {
        node *p{nullptr};

    public:
        iterator() = default;
        iterator(node *d) : p(d) {}
        iterator &operator++() {
            p = p->next;
            return *this;
        }
        int &operator*() {
            return p->data;
        }
        friend bool operator!=(const iterator &a, const iterator &b) {
            return a.p != b.p;
        }
    };
    auto begin() { return iterator(hd); }
    auto end() { return iterator(); }
};

#include <iostream>

void print(auto c) {
    using std::cout;
    for (auto it = c.begin(); it != c.end(); ++it) {
        auto e = *it;
        cout << e << " ";
    }
    cout << "\n";
}

int main()
{
    list l;   vector v;
    print(l); print(v);
}
