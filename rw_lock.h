#pragma once
#include <mutex>

class RWLock {
public:
    template<class Func>
    void read(Func func) {
        read_.lock();
        ++blocked_readers_;
        if (blocked_readers_ == 1)
            global_.lock();
        read_.unlock();
        try {
            func();
        } catch(...) {
            end_read();
            throw;
        }
        end_read();
    }

    template<class Func>
    void write(Func func) {
        std::lock_guard<std::mutex> lock(global_);
        func();
    }

private:
    std::mutex read_;
    std::mutex global_;
    int blocked_readers_ = 0;

    void end_read() {
        read_.lock();
        --blocked_readers_;
        if (!blocked_readers_)
            global_.unlock();
        read_.unlock();
    }
};
