#ifndef RANKINGTEXT_HPP
#define RANKINGTEXT_HPP

#include "convert.hpp"
#include "Texte2D.hpp"

class RankingText: public Texte2D{
public:
  RankingText(const int& rank);
  ~RankingText();

  void update();

private:
  const int& pCurrentRank;
};

#endif // RANKINGTEXT_HPP
