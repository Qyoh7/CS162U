#include "Card.hpp"
#include "CardTypes.h"

class Deck
{
    private:
        Card m_deck[52];
        Card m_currentCard;

    public:
        Deck()
        {
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                {
                    for (const auto& rank : Rank)
                    {
                        m_deck[i] = rank
                    }
                }
            }

        }

}
