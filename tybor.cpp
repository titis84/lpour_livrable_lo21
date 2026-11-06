#include "tybor.h"

namespace Codex {
    //*****TYBOR*****

    Tybor::Tybor(int niv) : niveau(niv), score(0) {}
    int Tybor::getNiveau() const { return niveau; }
    int Tybor::getScore() const { return score; }
    //void Tybor::prendreCarte();//==============à définir !!==================
}
