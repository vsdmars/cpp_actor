#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

using namespace std;

auto switch_to_new_thread(std::jthread& out) {
  struct awaitable {
    std::jthread* p_out;

    bool await_ready() { 
      cout << "DBG-await_ready\n";
      return false; 
    }

    void await_suspend(std::coroutine_handle<> h) {
      cout << "DBG-await_suspend\n";
      std::jthread& out = *p_out;
      cout << "DBG-await_suspend old tid: " << out.get_id() << "\n";

      if (out.joinable()) throw std::runtime_error("Output jthread parameter not empty");

      out = std::jthread([h] {
        cout << "DBG-inside new thread, about to call h.resume() " << " tid: " 
          << std::this_thread::get_id() << "\n";
        
        h.resume(); }
      );

      // Potential undefined behavior: accessing potentially destroyed *this
      // std::cout << "New thread ID: " << p_out->get_id() << '\n';
      std::cout << "DBG-await_suspend New thread ID: " << out.get_id() << '\n';  // this is OK
    }

    void await_resume() {}
  };

  cout << "DBG-switch_to_new_thread before return awaitable\n";
  return awaitable{&out};
}

struct task {
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

task resuming_on_new_thread(std::jthread& out) {
  std::cout << "Coroutine started on thread: " << 
    std::this_thread::get_id() << " out jthread: " << out.get_id() << '\n';

  cout << "DBG-1\n";

  co_await switch_to_new_thread(out);
  
  cout << "DBG-2\n";
  
  // awaiter destroyed here
  std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << 
    " out jthread: " << out.get_id() << '\n';
}

int main() {
  std::jthread out;
  resuming_on_new_thread(out);
  
  std::this_thread::sleep_for(std::chrono::seconds(5));
  cout << "main thread: " << std::this_thread::get_id() << "\n";
}