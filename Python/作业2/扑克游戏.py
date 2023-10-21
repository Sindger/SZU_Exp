import random


class Card():
    def __init__(self, rank, suit):
        """ 扑克牌14个等级，从2，3，4，...,10, J, Q, K, A
            扑克牌花色： S代表黑桃，H代表红桃，C代表梅花，D代表方块
        """
        assert suit in {'S', 'H', 'C', 'D'}
        assert rank in range(2, 15)

        self.rank = rank
        self.suit = suit

    suit_str = {'S': "\u2660", 'H': "\u2661", 'C': "\u2663", 'D': "\u2662"}
    rank_str = {n: str(n) for n in range(2, 11)}
    rank_str[11] = 'J';
    rank_str[12] = 'Q';
    rank_str[13] = 'K';
    rank_str[14] = 'A'

    def __str__(self):  # 输出，如'2♡'
        return f"{self.rank_str[self.rank]}{self.suit_str[self.suit]}"

    def __repr__(self):  # Card(2,'H')
        return f"Card({self.rank},'{self.suit}')"

    def __gt__(self, other):
        if not isinstance(other,Card):
            return TypeError('Illgal Type!')
        if self.rank>other.rank:
            return True
        return False

    def __lt__(self, other):
        if not isinstance(other,Card):
            return TypeError('Illgal Type!')
        if self.rank<other.rank:
            return True
        return False

    def __eq__(self, other):
        if not isinstance(other, Card):
            return TypeError('Illgal Type!')
        if self.rank == other.rank:
            return True
        return False


class Hand():
    def __init__(self, cards=[]):
        self.cards = []
        self.receive_cards(cards)

    def receive_cards(self, cards):
        self.cards+=cards

    def receive_card(self, card):
        self.cards.append(card)

    def shuffle(self):
        if self.cards:
            random.shuffle(self.cards)

    def give_card(self):
        if self.cards:
            card=self.cards[0]
            del self.cards[0]
            return card
        else:
            return None

    def give_cards(self):
        cards=self.cards.copy()
        self.cards.clear()
        return cards

    def __iter__(self):
        yield from self.cards

    def __repr__(self):
        return f"Hand({self.cards})"

    def __str__(self):
        return str([str(card) for card in self.cards])

    @property  # 设置属性，这样可以使用 对象.num_cards 访问，而不是 对象.num_cards()
    def num_cards(self):
        return len(self.cards)


class Deck(Hand):
    def __init__(self):
        self.cards=[]
        #self.cards = [Card(2, "H"), Card(2, "S"), Card(3, "D"), Card(3, "S")]  # 仅供测试用，补充上句后可注释
        for i in ('H','S','D','S'):
            for j in range(2,15):
                self.cards.append(Card(j,i))
        self.size = self.num_cards
        self.shuffle()


class Player(Hand):
    def __init__(self, name, cards=[]):
        self.name=name
        self.cards=cards.copy()

    def __repr__(self):
        return f"Player({repr(self.name)}, {[c for c in self]})"

    def __str__(self):
        return f"<{repr(self.name)} has {[str(c) for c in self]}>"


class Game():
    def __init__(self, players):
        self.players = players
        self.deck = Deck()

    def deal(self):
        deck=Deck()
        while deck.num_cards !=0:
            self.players[0].receive_card(deck.give_card())
            self.players[1].receive_card(deck.give_card())

    def turn(self):
        card=Hand()
        while self.players[0].num_cards>0 and self.players[1].num_cards>0:
            card.receive_card(self.players[0].give_card())
            card.receive_card(self.players[1].give_card())
            print(card,end="")
            if card.cards[card.num_cards-2]>card.cards[card.num_cards-1]:
                self.players[0].receive_cards(card.give_cards())
                print("=> "+self.players[0].name)
                return self.players[0]
            elif card.cards[card.num_cards-2]<card.cards[card.num_cards-1]:
                self.players[1].receive_cards(card.give_cards())
                print("=> "+self.players[1].name)
                return self.players[1]
            else:
                print("=> tie")
                continue
        if self.players[0].num_cards==0 and self.players[0].num_cards>0:
            self.players[1].receive_cards(temp.give_cards())
            print("=> "+self.players[1].name)
            return self.players[1]
        elif self.players[1].num_cards==0 and self.players[1].num_cards>0:
            self.players[0].receive_cards(temp.give_cards())
            print("=> " + self.players[0].name)
            return self.players[0]
        else:
            print("=> tie")
            return None


    def play(self):
        self.deal()  # 发牌
        winner = None
        while self.players[0].num_cards>0 and self.players[1].num_cards>0:
            self.players[0].shuffle()
            self.players[1].shuffle()
            winner=self.turn()
        if winner:
            print(winner.name+" wins!")
        else:
            print("No Winner!")
        return winner


def test_Card():
    cards = [Card(3, 'S'), Card(14, 'D'), Card(10, 'D'), Card(14, 'H')]
    print("cards:", cards)  # cards: [Card(3,'S'), Card(14,'D'), Card(10,'D'), Card(14,'H')]
    print("max:", max(cards))  # max: A♢
    print("min:", min(cards))  # min: 3♠
    print("position of max card:", cards.index(max(cards)))  # position of max card: 1
    print("regular sorted:", [str(c) for c in sorted(cards)])  # regular sorted: ['3♠', '10♢', 'A♢', 'A♡']
    print("reverse sorted:", [str(c) for c in sorted(cards, reverse=True)])  # reverse sorted: ['A♢', 'A♡', '10♢', '3♠']


def test_Hand():
    h = Hand()
    h.receive_card(Card(2, 'S'))
    h.receive_cards([Card(13, 'H'), Card(7, 'C')])
    print("hand:", h)  # hand: ['2♠', 'K♡', '7♣']
    print("num_cards:", h.num_cards)  # num_cards: 3
    print("give card:", h.give_card())  # give card: 2♠
    print("rest of cards:", [str(c) for c in h.give_cards()])  # rest of cards: ['K♡', '7♣']
    print("give card:", h.give_card())  # None


def test_Deck():
    d = Deck()
    print(d)  # ['3♢', '3♠', '2♠', '2♡']
    print("size of deck:", d.size)  # size of deck: 4
    print("give card:", d.give_card())  # give card: 3♢
    print("rest of cards:", [str(c) for c in d.give_cards()])  # rest of cards: ['3♠', '2♠', '2♡']


def test_Player():
    p = Player('Pam')
    p.receive_card(Card(10, 'H'))
    print(p)  # <'Pam' has ['10♡']>


def test_Game():
    game = Game([Player("A"), Player("B")])
    game.play()

if __name__=="__main__":
    #test_Card()
    #test_Hand()
    #test_Deck()
    #test_Player()
    test_Game()
""" 
例子1:
at start <'A' has ['2♡', '3♢']>
at start <'B' has ['2♠', '3♠']>
['2♡', '2♠'] => Tie
['3♢', '3♠', '2♡', '2♠'] => Tie
No Winner

例子2:
at start <'A' has ['2♡', '2♠']>
at start <'B' has ['3♠', '3♢']>
['2♡', '3♠'] => B
['2♠', '3♠'] => B
B wins!"""
