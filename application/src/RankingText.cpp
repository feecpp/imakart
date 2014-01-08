#include "RankingText.hpp"
#include <iostream>

RankingText::RankingText(const int& rank):
  Texte2D::Texte2D(glimac::convertToIntString(rank)), pCurrentRank(rank)
  {}

RankingText::~RankingText(){}

void RankingText::update(){
  myText = glimac::convertToIntString(pCurrentRank);
  myText = "Rank " +myText + "/4";
  setPosition(10, 510, 20);
}
