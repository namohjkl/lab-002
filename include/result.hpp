#pragma once

class Result
{
public:
    enum class Outcome
    {
        None,
        P1Win,
        P2Win,
        Draw
    };

private:
    Outcome m_outcome{ Outcome::None };

public:
    Result() = default;
    ~Result();

    void Reset();
    void Set(Outcome outcome);

    Outcome Get() const;
    bool IsSet() const;
};
