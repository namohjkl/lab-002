#include "match.hpp"
#include "player.hpp"

#include <iostream>

int main()
{
    std::cout << "=== Static objects ===\n";
    Player alice("Alice");
    Player bob("Bob");

    alice.PrintBrief();
    bob.PrintBrief();

    std::cout << "\n=== Composition lifetime demo (nested scope) ===\n";
    {
        Match localMatch(&alice, &bob);
        localMatch.PrintState();

        // Правильное действие
        localMatch.Start();
        localMatch.Finish(Result::Outcome::Draw);

        localMatch.PrintState();
    } // тут должен разрушиться Match, а вместе с ним (композиция) Result

    std::cout << "\nPlayers are still alive after localMatch scope:\n";
    alice.PrintBrief();
    bob.PrintBrief();

    std::cout << "\n=== Aggregation lifetime demo (aggregator destroyed, players live) ===\n";
    Match* dynMatch = new Match(&alice, &bob);
    dynMatch->Start();
    delete dynMatch; // уничтожили агрегатор (Match)

    std::cout << "After deleting Match, calling Player method:\n";
    alice.PrintBrief(); // игрок жив, т.к. агрегирование, не композиция

    std::cout << "\n=== Rule check demo (try to break rule) ===\n";
    Match ruleMatch(&alice, &bob);
    ruleMatch.PrintState();

    // Нарушение: пытаемся завершить матч, который не начат
    ruleMatch.Finish(Result::Outcome::P1Win);

    // Затем корректно
    ruleMatch.Start();
    ruleMatch.Finish(Result::Outcome::P1Win);

    std::cout << "\n=== Reference and pointer demo ===\n";
    Player& refAlice = alice;    // ссылка
    Player* ptrBob = &bob;       // указатель

    refAlice.PrintBrief();
    ptrBob->PrintBrief();

    std::cout << "\n=== Dynamic array of objects (Player[]) ===\n";
    Player* playersArr = new Player[2]; // default ctor
    // имён нет (по умолчанию пустые), но покажем, что массив существует
    playersArr[0].PrintBrief();
    playersArr[1].PrintBrief();
    delete[] playersArr;

    std::cout << "\n=== Array of dynamic objects (Player*[]) ===\n";
    Player** pDynArr = new Player*[2];
    pDynArr[0] = new Player("Carol");
    pDynArr[1] = new Player("Dave");

    pDynArr[0]->PrintBrief();
    pDynArr[1]->PrintBrief();

    delete pDynArr[0];
    delete pDynArr[1];
    delete[] pDynArr;

    std::cout << "\n=== End of program (static dtors will run now) ===\n";
    return 0;
}
