// Lock-free SPSC queue using ring buffer.
// Safe for exactly one producer and one consumer thread.
// Keeps one slot empty to distinguish full from empty.

#pragma once

#include <atomic>
#include <cstddef>
#include <type_traits>
#include <cassert>
#include <utility>
#include <memory>

/// Cache line size in bytes for optimal memory alignment
constexpr std::size_t cacheline_t = 64;

// Lock-free SPSC queue. Capacity is rounded up to power of 2.
template <class T>
class SPSCQueue {
    static_assert(std::is_nothrow_move_constructible_v<T> || std::is_copy_constructible_v<T>,
                  "T must be nothrow move-constructible or copy-constructible");

public:
    // Constructor rounds capacity up to next power of 2
    explicit SPSCQueue(std::size_t capacity_pow2)
        : capacity_(round_up_pow2(capacity_pow2)),
          mask_(capacity_ - 1),
          buffer_(std::allocator<T>{}.allocate(capacity_)) {}

    ~SPSCQueue() {
        // Drain any remaining elements
        T tmp;
        while (try_pop(tmp)) {}
        std::allocator<T>{}.deallocate(buffer_, capacity_);
    }

    SPSCQueue(const SPSCQueue&) = delete;
    SPSCQueue& operator=(const SPSCQueue&) = delete;

    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool empty()  const noexcept { return head_.load(std::memory_order_acquire) == tail_.load(std::memory_order_acquire); }
    [[nodiscard]] bool full()   const noexcept { return size() == capacity_ - 1; }
    [[nodiscard]] std::size_t size() const noexcept {
        auto t = tail_.load(std::memory_order_acquire);
        auto h = head_.load(std::memory_order_acquire);
        return h - t;  // head is always >= tail
    }

    // Producer: construct element in-place, returns false if full
    template <class... Args>
    [[nodiscard]] bool try_emplace(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args&&...>) {
        auto h = head_.load(std::memory_order_relaxed);
        auto t = tail_.load(std::memory_order_acquire);
        if (h - t == capacity_) return false;                 // full (1 slot left unused)
        new (buffer_ + (h & mask_)) T(std::forward<Args>(args)...);
        head_.store(h + 1, std::memory_order_release);
        return true;
    }

    [[nodiscard]] bool try_push(const T& v) {
        return try_emplace(v);
    }
    [[nodiscard]] bool try_push(T&& v) {
        return try_emplace(std::move(v));
    }

    // Consumer: move element out and destroy, returns false if empty
    [[nodiscard]] bool try_pop(T& out) noexcept(std::is_nothrow_move_assignable_v<T> || std::is_nothrow_move_constructible_v<T>) {
        auto t = tail_.load(std::memory_order_relaxed);
        auto h = head_.load(std::memory_order_acquire);
        if (t == h) return false;                        // empty
        T* slot = buffer_ + (t & mask_);
        out = std::move(*slot);
        slot->~T();
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }

private:
    // Bit manipulation to round up to next power of 2
    static std::size_t round_up_pow2(std::size_t x) {
        assert(x >= 2);
        --x;
        x |= x >> 1; x |= x >> 2; x |= x >> 4;
        x |= x >> 8; x |= x >> 16; x |= x >> 32;
        return x + 1;
    }

    // Cache-line aligned to prevent false sharing
    alignas(cacheline_t) std::atomic<std::size_t> head_{0};  // Producer index
    alignas(cacheline_t) std::atomic<std::size_t> tail_{0};  // Consumer index
    alignas(cacheline_t) T* buffer_;
    const std::size_t capacity_;  // Always power of 2
    const std::size_t mask_;      // capacity - 1, for fast modulo
};
