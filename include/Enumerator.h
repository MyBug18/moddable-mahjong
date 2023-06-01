#pragma once

#include <coroutine>

template <typename T>
struct Enumerator
{
    struct promise_type
    {
        T current;

        auto get_return_object()
        {
            return Enumerator<T>{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept
        {
            return std::suspend_always{};
        }

        void return_void() noexcept {}

        auto yield_value(T combination) noexcept
        {
            current = std::move(combination);
            return std::suspend_always{};
        }

        void unhandled_exception()
        {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> coro_handle;

    explicit Enumerator<T>(std::coroutine_handle<promise_type> handle) : coro_handle(handle) {}

    ~Enumerator()
    {
        if (coro_handle)
        {
            coro_handle.destroy();
        }
    }

    bool move_next()
    {
        coro_handle.resume();
        return !coro_handle.done();
    }

    const T& current() const
    {
        return coro_handle.promise().current;
    }
};
