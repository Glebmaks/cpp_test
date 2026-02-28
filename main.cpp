#include <cstddef>
#include <string>
#include <iostream>

struct Tracer {
    static inline std::size_t ctor = 0;
    static inline std::size_t dtor = 0;
    static inline std::size_t copy_ctor = 0;
    static inline std::size_t move_ctor = 0;
    static inline std::size_t copy_assign = 0;
    static inline std::size_t move_assign = 0;

    std::string s;

    Tracer() {
        ++ctor;
    }
    explicit Tracer(std::string str) : s(std::move(str)) {
        ++ctor;
    }

    Tracer(const Tracer& other) : s(other.s) {
        ++copy_ctor;
    }

    Tracer(Tracer&& other) noexcept : s(std::move(other.s)) {
        ++move_ctor;
    }

    Tracer& operator=(const Tracer& other) {
        if (this != &other) {
            s = other.s;
            ++copy_assign;
        }
        return *this;
    }

    Tracer& operator=(Tracer&& other) noexcept {
        if (this != &other) {
            s = std::move(other.s);
            ++move_assign;
        }
        return *this;
    }

    ~Tracer() {
        ++dtor;
    }

    static void reset() {
        ctor = 0;
        dtor = 0;
        copy_ctor = 0;
        move_ctor = 0;
        copy_assign = 0;
        move_assign = 0;
    }
};

int main() {
    Tracer::reset();

    Tracer a;
    Tracer b("hello");
    Tracer c = b;
    Tracer d = std::move(b);

    a = c;
    d = std::move(a);

    std::cout << "ctor - " << Tracer::ctor << "\n";
    std::cout << "dtor - " << Tracer::dtor << "\n";
    std::cout << "copy_ctor - " << Tracer::copy_ctor << "\n";
    std::cout << "move_ctor - " << Tracer::move_ctor << "\n";
    std::cout << "copy_assign - " << Tracer::copy_assign << "\n";
    std::cout << "move_assign - " << Tracer::move_assign << "\n";

    return 0;
}