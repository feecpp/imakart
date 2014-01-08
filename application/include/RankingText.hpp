#ifndef RANKINGTEXT_HPP
#define RANKINGTEXT_HPP

#include "convert.hpp"
#include "Texte2D.hpp"

class RankingText: public Texte2D{
public:
  RankingText(const float* rank);
  ~RankingText();

  void update();

private:
  const float* pCurrentRank;
};

#endif // RANKINGTEXT_HPP
