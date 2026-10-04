#pragma once

#include <string>
#include <string_view>

class Player
{
private:
    std::string m_name{};
    int m_wins{ 0 };
    int m_draws{ 0 };
    int m_losses{ 0 };

public:
    Player() = default;
    explicit Player(std::string_view name);

    ~Player();

    std::string_view GetName() const;

    // Содержательные методы
    void AddWin();
    void AddDraw();
    void AddLoss();

    void PrintBrief() const;
};
