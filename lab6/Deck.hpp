#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include "Card.hpp"
#include "CardTypes.h"

class Deck
{
    private:
        Card m_deck[52];
        int m_currentCard;

        int getRand() { return rand(); }
    public:
        Deck()
        {
            int suit = 0;
            int rank = 1;
            for (int i = 0; i < 52; i++)
            {
                m_deck[i].setRank((Rank)rank);
                m_deck[i].setSuit((Suit)suit);
                if (rank == 13)
                {
                    rank = 1;
                    suit++;
                }
                else {
                    rank++;
                }
            }
            m_currentCard = 51;
        }

        void shuffle()
        {
            std::default_random_engine rng(static_cast<unsigned int>(std::time(0)));
            std::shuffle(m_deck, m_deck + 52, rng);
            m_currentCard = 51;
        }

        Card deal()
        {
            if (m_currentCard < 0)
            {
                cout << "No more cards left in the deck\n";
                return Card();
            }
            return m_deck[m_currentCard--];
        }
};
