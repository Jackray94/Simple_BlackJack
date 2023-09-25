#ifndef UNITPLAYER_H
#define UNITPLAYER_H
#include <iostream>
#include <string>
#include <string_view>

class UnitPlayer
{
protected:
  int m_score{};
  static const int c_maxScore{21};
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
  virtual bool wantsHit() = 0; // returns true if player wants a hit
  virtual bool hasBust() = 0;

  std::string_view getName() const{return m_name;}
  int getScore() const{return m_score;}
};
#endif
