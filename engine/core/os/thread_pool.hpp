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
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <future>
#include <functional>
#include <type_traits>

namespace linky::core {
class thread_pool {
public:
    thread_pool(const thread_pool&) = delete;
    thread_pool(thread_pool&&) noexcept = delete;
    thread_pool& operator=(const thread_pool&) = delete;
    thread_pool& operator=(thread_pool&&) noexcept = delete;

    ~thread_pool();
private:
    void worker();
private:
    std::atomic<bool> m_running = true;
    std::condition_variable m_available;
    mutable std::mutex m_mutex;
    std::queue<std::function<void()>> m_tasks;
    std::vector<std::thread> m_threads;
};
}