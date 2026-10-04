#include "match.hpp"

#include <iostream>

static const char* ToString(Match::State s)
{
    switch (s)
    {
        case Match::State::Planned:    return "Planned";
        case Match::State::InProgress: return "InProgress";
        case Match::State::Finished:   return "Finished";
    }
    return "Unknown";
}

Match::Match(Player* p1, Player* p2)
    : m_p1(p1)
    , m_p2(p2)
{
    if (m_p1 == nullptr || m_p2 == nullptr)
    {
        std::cout << "[error] Match created with null player pointer(s)\n";
    }
}

Match::~Match()
{
    std::cout << "[dtor] Match destroyed\n";
}

bool Match::Start()
{
    if (m_state != State::Planned)
    {
        std::cout << "[رفض] Can't start: match is not Planned\n";
        return false;
    }
    if (m_p1 == nullptr || m_p2 == nullptr)
    {
        std::cout << "[رفض] Can't start: players are not set\n";
        return false;
    }

    m_state = State::InProgress;
    std::cout << "Match started: " << m_p1->GetName() << " vs " << m_p2->GetName() << "\n";
    return true;
}

bool Match::Finish(Result::Outcome outcome)
{
    // Проверка правила: нельзя завершить, если не идёт
    if (m_state != State::InProgress)
    {
        std::cout << "[rule] Can't finish: match is not InProgress\n";
        return false;
    }

    m_result.Set(outcome);
    m_state = State::Finished;

    // Обновление статистики (простая логика)
    if (outcome == Result::Outcome::P1Win)
    {
        m_p1->AddWin();
        m_p2->AddLoss();
    }
    else if (outcome == Result::Outcome::P2Win)
    {
        m_p1->AddLoss();
        m_p2->AddWin();
    }
    else if (outcome == Result::Outcome::Draw)
    {
        m_p1->AddDraw();
        m_p2->AddDraw();
    }

    std::cout << "Match finished\n";
    return true;
}

void Match::PrintState() const
{
    std::cout << "Match{" 
              << (m_p1 ? m_p1->GetName() : "null") << " vs "
              << (m_p2 ? m_p2->GetName() : "null")
              << "} state=" << ToString(m_state)
              << " resultSet=" << (m_result.IsSet() ? "yes" : "no")
              << "\n";
}

bool Match::HasResult() const
{
    return m_result.IsSet();
}

Result::Outcome Match::GetOutcome() const
{
    return m_result.Get();
}
