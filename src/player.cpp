#include "player.hpp"

#include <iostream>

Player::Player(std::string_view name)
    : m_name(name)
{
}

Player::~Player()
{
    std::cout << "[dtor] Player destroyed: " << m_name << "\n";
}

std::string_view Player::GetName() const
{
    return m_name;
}

void Player::AddWin()
{
    ++m_wins;
}

void Player::AddDraw()
{
    ++m_draws;
}

void Player::AddLoss()
{
    ++m_losses;
}

void Player::PrintBrief() const
{
    std::cout << "Player{" << m_name << "} W:" << m_wins
              << " D:" << m_draws
              << " L:" << m_losses << "\n";
}
