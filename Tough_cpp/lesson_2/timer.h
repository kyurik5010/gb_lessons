//
// Created by Юрий Михайлович on 17.04.2022.
//

#ifndef TOUGH_CPP_LSN2_TIMER_H
#define TOUGH_CPP_LSN2_TIMER_H

#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now()
                                                    -m_beg).count();
    }
public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }
    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

#endif //TOUGH_CPP_LSN2_TIMER_H
