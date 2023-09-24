#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <chrono>
#include <algorithm>

class Deck // LEFT OFF here
{
private:
  static inline std::vector<Card> m_deck{std::vector<Card>(5*52)};// Made static to share between players and dealer who use the same deck
  static inline int m_index{}; // Made static to share between players and dealer who use the same deck
public:
  Deck() 
  {
    createDeckandShuffle();
  }

  void createDeckandShuffle();
  int getCardValue();
  std::string printCard();
  void incrementDeck(){m_index++;}
};

#endif
