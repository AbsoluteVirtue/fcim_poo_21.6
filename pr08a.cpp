// Cost of Abstractions in Embedded Systems - Marcell Juhasz - C++ on Sea 2025
// https://www.youtube.com/watch?v=m2uGMI3c91c

// Static polymorphism

template <class T> 
concept IPin = requires (T pin) {
    { pin.set() } -> std::same_as<void>;
    { pin.reset() } -> std::same_as<void>;
};

template <IPin T> 
class CLed {
private:
    bool  m_state{false};
    T* m_pin{nullptr};
public:
    CLed() = delete;
    CLed(T* pin) : m_pin{pin} { m_pin->reset(); }
    ...
};

class CPin {
private:
    std::uint8_t m_pin{0};
public:
    CPin() = delete;
    CPin(std::uint8_t pin) : m_pin{pin} {}
    void set() const {
        CBitSetResetRegister::set_pin(m_pin);
    }
    void reset() const {
        CBitSetResetRegister::reset_pin(m_pin);
    }
};

static_assert(IPin<CPin>);
