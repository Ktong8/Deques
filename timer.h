#pragma once
#include <chrono>
#include <iostream>

namespace timer {
    class ScopedTimer {
    public:
        ScopedTimer(std::string name)
            : start_{std::chrono::high_resolution_clock::now()}
            , name_{std::move(name)} {}
        ~ScopedTimer() {
            std::cout << "destructing\n";
            auto end = std::chrono::high_resolution_clock::now();
            auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
            std::cout << "closing\n";
            std::cout << name_ << " took " << dur.count() << " microseconds to run\n";
        }
    private:
        std::string name_;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    };

    template <typename F, typename... Ts>
    void timeFunction(F&& f, std::string name, Ts&&... args) {
        ScopedTimer timer{name};
        std::forward<F>(f)(std::forward<Ts>(args)...);
        std::cout << "done\n";
    }
}
