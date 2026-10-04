#pragma once

#include "player.hpp"
#include "result.hpp"

class Match
{
public:
    enum class State
    {
        Planned,
        InProgress,
        Finished
    };

private:
    Player* m_p1{ nullptr };   // агрегация
    Player* m_p2{ nullptr };   // агрегация
    State m_state{ State::Planned };

    Result m_result{};         // композиция

public:
    Match(Player* p1, Player* p2);
    ~Match();

    // Содержательные методы
    bool Start();                           // Planned -> InProgress
    bool Finish(Result::Outcome outcome);   // InProgress -> Finished + обновление статистики

    void PrintState() const;

    // Доступ к части через методы целого (композиция демонстрируется так)
    bool HasResult() const;
    Result::Outcome GetOutcome() const;
};
