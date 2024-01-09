// Copyright (c) 2023-2024 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace linky::concurrency {

using task = std::function<void()>;

class thread_pool {
public:
    thread_pool(const thread_pool&) = delete;
    auto operator=(const thread_pool&) -> thread_pool = delete;
    
    thread_pool(size_t num = std::thread::hardware_concurrency());
    ~thread_pool();

    void stop();
    void add(const task& t);
    void add(task&& t);
private:
    void start(size_t num);
    void stop_imp();
    void run_in_thread();

private:
    std::once_flag m_once;
    std::atomic<bool> m_running = true;
    std::condition_variable m_available;
    mutable std::mutex m_mutex;
    std::list<task> m_tasks;
    std::list<std::shared_ptr<std::thread>> m_threads;
};
}