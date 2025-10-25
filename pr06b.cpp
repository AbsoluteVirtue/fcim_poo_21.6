// Cost of Abstractions in Embedded Systems - Marcell Juhasz - C++ on Sea 2025
// https://www.youtube.com/watch?v=m2uGMI3c91c

// Dynamic polymorphism
class IPin {
public:
    virtual void set() = 0;
    virtual void reset() = 0;
};

class CLed {
private:
    bool  m_state{false};
    IPin* m_pin{nullptr};
public:
    CLed() = delete;
    CLed(IPin* pin) : m_pin{pin} { m_pin->reset(); }
};

class CPin : public IPin {
private:
    std::uint8_t m_pin{0};
public:
    CPin() = delete;
    CPin(std::uint8_t pin) : m_pin{pin} {}
    void set() override {
        CBitSetResetRegister::set_pin(m_pin);
    }
    void reset() override {
        CBitSetResetRegister::reset_pin(m_pin);
    }
};
