#include <coroutine>
#include <iostream>
using namespace std;

struct promise;
 
struct coroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};
 
struct promise
{
    coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
};
 
struct S
{
    int i;
    coroutine f()
    {
        std::cout << i;
        co_return;
    }
};

void good()
{
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        std::cout << i << "\n";
        cout << "in lambda\n";
        co_return;
    }(0);
    // lambda destroyed
    cout << "before call resume\n";
    h.resume(); // no problem, i has been copied to the coroutine
                // frame as a by-value parameter
    h.destroy();
}

int main() {
  good();
}