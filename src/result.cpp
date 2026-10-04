#include "result.hpp"

#include <iostream>

Result::~Result()
{
    std::cout << "[dtor] Result destroyed\n";
}

void Result::Reset()
{
    m_outcome = Outcome::None;
}

void Result::Set(Outcome outcome)
{
    m_outcome = outcome;
}

Result::Outcome Result::Get() const
{
    return m_outcome;
}

bool Result::IsSet() const
{
    return m_outcome != Outcome::None;
}
