#ifndef CARD_H
#define CARD_H
class Card
{
public:
  enum class  Rank
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
    ace,

//    maxRank
  };
  enum class Suit
  {
    spade,
    club,
    diamond,
    heart,

//    maxSuit
  };
public:
  Rank rank;
  Suit suit;
};
#endif
