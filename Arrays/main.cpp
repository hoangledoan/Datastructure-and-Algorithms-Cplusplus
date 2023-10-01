#include "game.hpp"

int main()
{
    Scores score(4);
    score.add(GameEntry("", 5));
    score.add(GameEntry("", 4));
    score.add(GameEntry("", 6));
    score.add(GameEntry("", 3));
    score.print();
    score.remove(0);
    score.print();
    return 0;
}