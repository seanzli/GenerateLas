#pragma once

#include <deque>
#include <vector>
#include <mutex>
#include <atomic>

template <class T>
class Buffer {
public:
    Buffer() {}
    Buffer(const int& size) {
        m_buffer_len.store(size);    
    }
    ~Buffer() {}

    size_t size() {return m_buffer.size();}
    size_t max_size() {return m_buffer_len.load();}
    size_t resize(unsigned int _size) { 
        m_buffer_len.store(_size);
        return m_buffer_len.load();
    }

    T pop_front() {
        if (m_buffer.size() == 0)
            return T();
        std::lock_guard<std::mutex> lg(m_mutex);
        T out = m_buffer.front();
        m_buffer.pop_front();
        return out;
    }

    T pop_back() {
        if (m_buffer.size() == 0)
            return T();
        std::lock_guard<std::mutex> lg(m_mutex);
        T out = m_buffer.back();
        m_buffer.pop_back();
        return out;
    }

    std::vector<T> pop_front(const int n) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (n >= m_buffer.size()) {
            std::vector<T> out(m_buffer.begin(), m_buffer.end());
            m_buffer.clear();
            return out;
        } else {
            std::vector<T> out(m_buffer.begin(), m_buffer.begin() + n);
            m_buffer.erase(m_buffer.begin(), m_buffer.begin() + n);
            return out;
        }
        return std::vector<T>();
    }

    std::vector<T> pop_back(const int n) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (n >= m_buffer.size()) {
            std::vector<T> out(m_buffer.begin(), m_buffer.end());
            m_buffer.clear();
            return out;
        } else {
            std::vector<T> out(m_buffer.end() - n, m_buffer.end());
            m_buffer.erase(m_buffer.end() - n, m_buffer.end());
            return out;
        }
        return std::vector<T>();
    }

    size_t push_front(const T& value) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_buffer.size() < m_buffer_len.load()) 
            m_buffer.push_front(value);
        return m_buffer.size();
    }
    size_t push_front(std::vector<T>& vec) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.begin(), vec.begin(), vec.end());
        if (m_buffer.size() > m_buffer_len.load()) 
            m_buffer.erase(m_buffer.begin(),m_buffer.end() - m_buffer_len);
        return m_buffer.size();
    }

    size_t push_back(std::vector<T>& vec) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.end(), vec.begin(), vec.end());
        if (m_buffer.size() > m_buffer_len.load())
            m_buffer.erase(m_buffer.begin(),m_buffer.end() - m_buffer_len);
        return m_buffer.size();
    }

    size_t push_back(const T& value) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.push_back(value);
        if (m_buffer.size() > m_buffer_len.load())
            m_buffer.pop_front();
        return m_buffer.size();
    }
    void clear() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.clear();
    }

private:
    std::atomic<unsigned int> m_buffer_len;
    std::deque<T> m_buffer;
    std::mutex m_mutex;
};