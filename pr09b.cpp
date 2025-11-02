template <typename T>
class optional {
public:
    using nil = "nil";

    optional() {}
    optional(T v) : value{v} {}
    optional(const char* c) : nonce{c} {}

    template <typename U>
    static auto from(U val) { return optional<U>(val); }

    template <typename U>
    static auto nothing() { return optional<U>(nil); }

    template <typename U>
    auto map(U(*f)(T)) {
        if (nonce == nil) return nothing<U>();
        return from<U>(f(value));
    }
    template <typename U>
    auto then(optional<U>(*f)(T)) {
        if (nonce == nil) return nothing<U>();
        return f(value);
    }
private:
    T value{};
    const char* nonce{nullptr};
};
