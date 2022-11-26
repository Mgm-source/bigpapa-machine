#pragma once
#include "pch.h"

namespace M_TMR
{
    class Timer
    {
        // Member variables
        LARGE_INTEGER m_qpFrequency;
        LARGE_INTEGER m_qpCounter;
        uint64_t m_qpCounterMax;
        uint64_t m_qpSecondCounter;

        // Derived timing data uses a canonical tick format.
        uint64_t m_elapsedTicks;
        uint64_t m_totalTicks;
        uint64_t m_leftOverTicks;


        // Members for tracking the framerate.
        uint32_t m_frameCount;
        uint32_t m_framesPerSecond;
        uint32_t m_framesThisSecond;

        // Members for configuring fixed timestep mode.
        bool m_fixedTimeStep;
        uint64_t m_targetElapsedTicks;

    public:

        Timer();
        ~Timer() = default;
        // Getters 
        uint32_t getFrameCount();
        uint32_t getFramePerSecond();
        uint64_t getELapsedTicks();
        uint64_t getTotalTicks();

        double getElapsedSeconds();
        double getTotalSeconds();

        // Setter
        void setFixedTimerStep(bool fixed) { m_fixedTimeStep = fixed; }
        void setTargetElapsedTicks(uint64_t ticks) { m_targetElapsedTicks = ticks; };
        void setTargetElapsedSeconds(double targetElapsed) noexcept { m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

        // Static Function
        static constexpr double TicksToSeconds(uint64_t ticks) noexcept { return static_cast<double>(ticks) / TicksPerSecond; }
        static constexpr uint64_t SecondsToTicks(double seconds) noexcept { return static_cast<uint64_t>(seconds * TicksPerSecond); }

        template<typename CallBackFunc>
        void Tick(const CallBackFunc&);

    private:
        // Static Members
        static constexpr uint64_t TicksPerSecond = 10000000;
    };

    template<typename CallBackFunc>
    inline void Timer::Tick(const CallBackFunc& update)
    {
        LARGE_INTEGER currentCount{};

        if (!QueryPerformanceCounter(&currentCount))
        {
            throw std::exception();
        }

        uint64_t CounterDelta = static_cast<uint64_t>(currentCount.QuadPart - m_qpCounter.QuadPart);

        m_qpCounter = currentCount;
        m_qpSecondCounter += CounterDelta;

        if (CounterDelta > m_qpCounterMax)
        {
            CounterDelta = m_qpCounterMax;
        }

        CounterDelta *= TicksPerSecond;
        CounterDelta /= static_cast<uint64_t>(m_qpFrequency.QuadPart);

        const uint32_t lastFrameCount = m_frameCount;

        if (m_fixedTimeStep)
        {
            // Fixed timestep update logic

            // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
            // the clock to exactly match the target value. This prevents tiny and irrelevant errors
            // from accumulating over time. Without this clamping, a game that requested a 60 fps
            // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
            // accumulate enough tiny errors that it would drop a frame. It is better to just round
            // small deviations down to zero to leave things running smoothly.

            if (static_cast<uint64_t>(std::abs(static_cast<int64_t>(CounterDelta - m_targetElapsedTicks))) < TicksPerSecond / 4000)
            {
                CounterDelta = m_targetElapsedTicks;
            }

            m_leftOverTicks += CounterDelta;

            while (m_leftOverTicks >= m_targetElapsedTicks)
            {
                m_elapsedTicks = m_targetElapsedTicks;
                m_totalTicks += m_targetElapsedTicks;
                m_leftOverTicks -= m_targetElapsedTicks;
                m_frameCount++;

                update();
            }

        }
        else
        {
            // Variable timestep update logic.
            m_elapsedTicks = CounterDelta;
            m_totalTicks += CounterDelta;
            m_leftOverTicks = 0;
            m_frameCount++;

            update();
        }

        // Track the current framerate.
        if (m_frameCount != lastFrameCount)
        {
            m_framesThisSecond++;
        }

        if (m_qpSecondCounter >= static_cast<uint64_t>(m_qpFrequency.QuadPart))
        {
            m_framesPerSecond = m_framesThisSecond;
            m_framesThisSecond = 0;
            m_qpSecondCounter %= static_cast<uint64_t>(m_qpFrequency.QuadPart);
        }

    }

}