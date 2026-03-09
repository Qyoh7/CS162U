class Card
{
    private:
        enum Suit
        {
            Ace = 1,
            Deuce = 2,
            Trey = 3,
            Four = 4,
            Five = 5,
            Six = 6,
            Seven = 7,
            Eight = 8,
            Nine = 9,
            Ten = 10,
            Jack = 11,
            Queen = 12,
            King = 13
        };
        enum Rank
        {
            Spades,
            Hearts,
            Clubs,
            Diamonds
        };
        m_rank = Rank;
        m_suit = Suit;
    public:
        Card()
        {

        }
        Card(Rank rank=Ace, Suit=Spades)
        {

        }
};