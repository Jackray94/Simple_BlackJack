#ifndef PLAYER_H
#define PLAYER_H
#include "UnitPlayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <string_view>

class Player : public UnitPlayer
{
private:
  Deck deck{};
  std::vector<std::string> Hand{};
public:
  Player(std::string_view name)
    : UnitPlayer{name}
  {
  }

  bool hasBust() override
  {
    return (m_score > c_maxScore);
  }
  bool wantsHit() override  // returns true if player wants a hit
  {
    char answer{};
    do
    {
      std::cout << "Do you want to hit (H / h) or stay (S / s)? ";
      std::cin >> answer;
    }while(answer != 's' || answer != 'S' || answer != 'h' || answer != 'H');
    return (answer == 'H' || answer == 'h');
  }

  std::ostream& print(std::ostream& out) const override
  {
    out << "Player" << m_name << " has a score of << " << m_score << "\nHas cards: \n";
    int it{};
    for(const auto& cardStrings : Hand)
    {
      out << cardStrings.at(it) << " ";
      it++;
    }
    out << '\n';
    return out;
  }

  void updateScore(int value){m_score += value;}

  void drawCard() override
  {
    {
      updateScore(deck.getCardValue());
      Hand.push_back(deck.printCard());
      deck.incrementDeck();
    }
  }

};
#endif
