#include "Card.h"
#include "Dealer.h"
#include "Deck.h"
#include "Player.h"
#include "UnitPlayer.h"
#include <iostream>
#include <vector>
#include <memory> // smart pointers

int main()
{
  auto dealer{std::make_unique<Dealer>("Dan")};

  //std::vector <std::unique_ptr<UnitPlayer>> v // <-- compiler shows an error for this
  std::vector <UnitPlayer*> v // <-- replace with line 14 to see comipler error
  {
    new Player{"Joe"},
    new Player{"Jack"}
  };

  std::cout << "Dealer two cards and flips their first card\n";
  dealer->drawCard();
  std::cout << *dealer << '\n';

// draw first cards
  for(const auto& elements : v)
  {
    elements->drawCard();
    std::cout << *elements << '\n';
  }

//prompt players if they want to hit
  for(const auto& elements : v)
  {
    while (elements->wantsHit() && !elements->hasBust())
    {
      elements->drawCard();
      std::cout << *elements << '\n';
    }
  }

  std::cout << "Dealer flips their last card\n";
  dealer->drawCard();
  std::cout << *dealer << '\n';

  for(const auto& elements : v )
  {
    //I need to change this , so has bust is checked first. Plus make dealer not polymorphic
    if (elements->hasBust())
      std::cout << elements->getName() << " has bust\n";
    else if(elements->getScore() > dealer->getScore())
      std::cout << elements->getName() << " won this hand\n";
    else if (elements->getScore() <= dealer->getScore()) //for now ties will be a dealer win
      std::cout << "Dealer " << elements->getName() << " won this hand\n";
  }

  return 0;
}
