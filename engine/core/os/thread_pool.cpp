#include "thread_pool.hpp"

namespace linky::core {
thread_pool::thread_pool(size_t num)
{
    Expects(num > 0);
    start(num);
}

thread_pool::~thread_pool()
{
    stop_imp();
}

void thread_pool::stop()
{
    std::call_once(m_once, [this](){ stop_imp(); });
}

void thread_pool::add(const task& t)
{
    m_tasks.push_back(t);
}

void thread_pool::add(task&& t)
{
    m_tasks.push_back(t);
}

void thread_pool::start(size_t num)
{
    m_running = true;

    for (size_t i = 0; i < num; ++i){
        m_threads.push_back(std::make_shared<std::thread>(&thread_pool::run_in_thread, this));
    }
}

void thread_pool::stop_imp()
{
    m_running = false;

    for (auto t : m_threads){
        t->join();
    }
    m_threads.clear();
}

void thread_pool::run_in_thread()
{
    while(m_running){
        task t = m_tasks.front();
        m_tasks.pop_front();
        t();
    }
}

}