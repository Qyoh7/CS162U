#include <iostream>
#include "CardTypes.h"
#pragma once
using std::cout;

class Card
{
    public:
        Card(Rank rank = Ace, Suit suit = Spades)
        {
            m_rank = rank;
            m_suit = suit;
        }
        void display()
        {
            cout << m_rank << " of " << m_suit << "\n";
        }

        void setRank(Rank rank) { m_rank = rank; }
        void setSuit(Suit suit) { m_suit = suit; }

        Rank getRank() { return m_rank; }
        Suit getSuit() { return m_suit; };

    private:
        Rank m_rank;
        Suit m_suit;

};
