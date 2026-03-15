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

        void SetRank(Rank rank) { m_rank = rank; }
        void SetSuit(Suit suit) { m_suit = suit; }

        Rank GetRank() { return m_rank; }
        Suit GetSuit() { return m_suit; };

    private:
        Rank m_rank;
        Suit m_suit;

};
