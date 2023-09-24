#ifndef DEALER_H
#define DEALER_H
#include "Deck.h"
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
class Dealer
{
private:
  Deck deck{};
  std::string m_name{};
  std::vector<std::string> Hand{};
  int m_score{};
  static const int c_maxScore{21};
public:
  Dealer(std::string_view name)
    : m_name{name}
  {
  }

  friend std::ostream& operator<<(std::ostream& out, const Dealer& d)
  {
    out << "Dealer " << d.m_name << " has a score of << " << d.m_score << "\nHas cards: \n";
    int it{};
    for(const auto& cardStrings : d.Hand)
    {
      out << cardStrings.at(it) << " ";
      it++;
    }
    out << '\n';
    return out;
  }


  void updateScore(int value){m_score++;}
  int getScore() const{return m_score;}

  void drawCard() 
  {
    updateScore(deck.getCardValue());
    Hand.push_back(deck.printCard());
    deck.incrementDeck();
  }

};
#endif
