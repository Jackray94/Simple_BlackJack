#include "Deck.h"

void Deck::createDeckandShuffle()
{
  for(int i{0}; i < m_deck.size(); i++)
  {
    m_deck.at(i).rank = static_cast<Card::Rank>(i%13);
    m_deck.at(i).suit = static_cast<Card::Suit>(i/13);
  }
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(m_deck.begin(), m_deck.end(), mt);
}

int Deck::getCardValue()
{
    int cardValue{};
    Card::Rank rankForComparison{};
    if(std::find(m_deck.begin(), m_deck.end(), m_deck[m_index]) == std::end(m_deck))
      assert(false && "Invalid index");
    else
      rankForComparison = m_deck[m_index].rank;
    switch(rankForComparison)
    {
        case (Card::Rank::two) : cardValue = 2; break;
        case (Card::Rank::three) : cardValue = 3; break;
        case (Card::Rank::four) : cardValue = 4 ; break;
        case (Card::Rank::five) : cardValue = 5 ; break;
        case (Card::Rank::six) : cardValue = 6 ; break;
        case (Card::Rank::seven) : cardValue = 7 ; break;
        case (Card::Rank::eight) : cardValue = 8 ; break;
        case (Card::Rank::nine) : cardValue = 9 ; break;
        case (Card::Rank::ten) : cardValue = 10; break;
        case (Card::Rank::jack) : cardValue = 10; break;
        case (Card::Rank::queen) : cardValue = 10; break;
        case (Card::Rank::king) : cardValue = 10; break;
        case (Card::Rank::ace) : cardValue = 11; break;
    }
    return cardValue;
}

std::string Deck::printCard()
{
    std::string card_string{};
    Card::Rank rankForComparison{m_deck[m_index].rank};
    Card::Suit suitForComparison{m_deck[m_index].suit};
    switch(rankForComparison) 
    {
        case(Card::Rank::two)     :    card_string = "2"  ;       break;
        case(Card::Rank::three)   :    card_string = "3"  ;       break;           
        case(Card::Rank::four)    :    card_string = "4"  ;       break;
        case(Card::Rank::five)    :    card_string = "5"  ;       break;
        case(Card::Rank::six)     :    card_string = "6"  ;       break;
        case(Card::Rank::seven)   :    card_string = "7"  ;       break;
        case(Card::Rank::eight)   :    card_string = "8"  ;       break;
        case(Card::Rank::nine)    :    card_string = "9"  ;       break;
        case(Card::Rank::ten)     :    card_string = "T"  ;       break;
        case(Card::Rank::jack)    :    card_string = "J"  ;       break;
        case(Card::Rank::queen)   :    card_string = "Q"  ;       break;
        case(Card::Rank::king)    :    card_string = "K"  ;       break;
        case(Card::Rank::ace)     :    card_string = "A"  ;       break;
    }

    switch(suitForComparison) 
    {
        case (Card::Suit::spade)  :    card_string += "S" ;         break;
        case (Card::Suit::club)   :    card_string += "C" ;         break;
        case (Card::Suit::diamond):    card_string += "D" ;         break;
        case (Card::Suit::heart)  :    card_string += "H" ;         break;
    }

    return card_string;
}
