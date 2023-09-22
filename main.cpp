#include <iostream>
#include <vector>
#include <string>
#include <random> // for mt19937
#include <algorithm> // for shuffle
#include <chrono>
#include <cassert>

class Card
{
public:
  enum Rank
  {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace
  };
  enum Suit
  {
    spade,
    club,
    diamond,
    heart
  };

  Rank rank;
  Suit suit;
};

class Deck // LEFT OFF here
{
private:
  std::vector<Card> m_deck{std::vector<Card>(5*52)};
  int m_it{};
public:
  Deck() 
  {
    createDeckandShuffle();
  }

  void createDeckandShuffle()
  {
    for(int i{0}; i < m_deck.size(); i++)
    {
      m_deck.at(i).rank = static_cast<Card::Rank>(i%13);
      m_deck.at(i).suit = static_cast<Card::Suit>(i/13);
    }
    static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    std::shuffle(m_deck.begin(), m_deck.end(), mt);
  }

  int getCardValue()
  {
      int cardValue{};
      switch(m_deck.at(m_it).rank)
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
          default :
              assert(false && "should never happen"); break;

      }
      return cardValue;
  }

  std::string printCard()
  {
      std::string card_string{};
      switch(m_deck.at(m_it).rank) 
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
          default:
             card_string = "?"           ;        break;
      }

      switch(m_deck.at(m_it).suit) 
      {
          case (Card::Suit::spade)  :    card_string += "S" ;         break;
          case (Card::Suit::club)   :    card_string += "C" ;         break;
          case (Card::Suit::diamond):    card_string += "D" ;         break;
          case (Card::Suit::heart)  :    card_string += "H" ;         break;
          default:
             card_string = "?";         break;
      }

      // Increment iterator here, that iterates over shuffled deck vector. printCard() calls right after getCardValue(), which needs to occur before iterating to next card in deck that is ready to be drawn
      m_it++;
      return card_string;
  }
};

class UnitPlayer
{
protected:
  int m_score{};
  const int c_MAXSCORE{21};
  std::string m_name{};
public:
  UnitPlayer(std::string_view name)
    : m_name{name}
  {
  }

  friend std::ostream& operator<<(std::ostream& out, const UnitPlayer& p)
  {
    return p.print(out);
  }

  virtual std::ostream& print(std::ostream& out) const = 0;
  virtual void drawCard() = 0;

  std::string_view getName() const{return m_name;}
  int getScore() const{return m_score;}
};

class Player : public UnitPlayer
{
private:
  Deck m_deck{};
  std::vector<std::string> Hand{};
public:
  Player(std::string_view name)
    : UnitPlayer{name}
  {
  }

  bool hasBust()  
  {
    return (m_score > c_MAXSCORE);
  }
  bool wantsHit()  // returns true if player wants a hit
  {
    char answer{};
    std::cout << "Do you want to hit (H / h) or stay (S / s)?";
    std::cin >> answer;
    assert((answer == 's' || answer == 'S' || answer == 'h' || answer == 'H') && "Must select h/H/s/S\n");
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

  void updateScore(int value){m_score++;}

  void drawCard() override
  {
    updateScore(m_deck.getCardValue());
    Hand.push_back(m_deck.printCard());
  }

};

class Dealer : public UnitPlayer
{
private:
  Deck m_deck{};
  std::vector<std::string> Hand{};
public:
  Dealer(std::string_view name)
    : UnitPlayer{name}
  {
  }

  std::ostream& print(std::ostream& out) const override
  {
    out << "Dealer " << m_name << " has a score of << " << m_score << "\nHas cards: \n";
    int it{};
    for(const auto& cardStrings : Hand)
    {
      out << cardStrings.at(it) << " ";
      it++;
    }
    out << '\n';
    return out;
  }

  void updateScore(int value){m_score++;}

  void drawCard() override
  {
    updateScore(m_deck.getCardValue());
    Hand.push_back(m_deck.printCard());
  }

};



int main()
{
  std::vector <UnitPlayer*> v
  {
    new Dealer{"Dan"}, // set the dealer as first element, which v.at(0) gets used specifically later
    new Player{"Joe"},
    new Player{"Jack"}
  };

// draw first cards
  for(const auto& elements : v)
  {
    elements->drawCard();
    std::cout << *elements << '\n';
  }

//prompt players if they want to hit
  for(const auto& elements : v)
  {
    if(Player* p{dynamic_cast<Player*>(elements)})
    {
      while (p->wantsHit() && !p->hasBust())
      {
        p->drawCard();
        std::cout << *p << '\n';
      }
    }
  }

  //dealer shows their other card
  v.at(0)->drawCard();
  std::cout << *v.at(0) << '\n';
  int dealerScore{v.at(0)->getScore()};
  for(const auto& elements : v )
  {
    if(elements->getScore() > dealerScore)
      std::cout << elements->getName() << " won this hand\n";
    else if (elements->getScore() <= dealerScore)
      std::cout << "Dealer " << elements->getName() << " won this hand\n";
    else
      if(Player* p{dynamic_cast<Player*>(elements)})
        if (p->hasBust())
          std::cout << elements->getName() << " has bust\n";
  }

  return 0;
}
