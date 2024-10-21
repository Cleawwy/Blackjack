/*

Blackjack is a card game where players play against the dealer of the cards. In the case of a singleplayer blackjack, there is only one player competing with the dealer.
The goal is to get a set of cards in your hand that has a sum of values that is the higher than the dealer’s hand without going over 21.

Gameplay: At the beginning of the game, the dealer will deal two cards each, face up, for himself and the player. 
Since the dealt cards are face up, the player knows the total value of his own and the dealer’s hand. 
The player has a choice to “Hit” or “Stand”. If he chooses to “Hit”, another card is dealt from the deck, face up. 
If he chooses to “Stand”, no more card is dealt and the total value is calculated from whatever cards the player has in his hand. 
The player can choose to “Hit’ as many times to get a higher total value of cards, until he either chooses “Stand” or he goes “Bust” (i.e. the total value of the card goes over 21), which means the player has lost.

Once the player chooses to “Stand” or goes “Bust”, the dealer will draw new cards into the dealer’s hand until he reaches a value of at least 17. 
Once he reaches at least 17, the dealer stops drawing into his own hand.

run the following before starting:
    touch NewDeck.txt
    touch ShuffledDeck.txt

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

bool gameRunning = false;

typedef struct {
    char suit[20];
    char faceValue[10];
    int cardValue;
} Card;

int mainMenu();
void createDeck(Card deck[52]);
void shuffleCards(Card deck[52]);
void dealCards(Card deck[52], int *topCardIndex, Card hand[], int *handSize);
int calculateTotalValue(Card hand[], int handSize, bool isHuman);
int handleAces(int totalValue, int numAces, bool isHuman);
bool hasEnoughCards(int topCardIndex);
void displayHands(Card playerHand[], int playerHandSize, Card dealerHand[], int dealerHandSize, int playerTotal, int dealerTotal);
void saveDeckToFile(const char *filename, Card deck[52]);
void readDeckFromFile(const char *filename, Card deck[52]);
// void createInitialFiles();

void createDeck(Card deck[52]) {
    char* suits[4] = {"Heart", "Diamond", "Spade", "Club"};
    char* faceValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int cardValues[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0};

    int index = 0;

    // Populate the deck
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strncpy(deck[index].suit, suits[i], sizeof(deck[index].suit) - 1);
            deck[index].suit[sizeof(deck[index].suit) - 1] = '\0';
            strncpy(deck[index].faceValue, faceValues[j], sizeof(deck[index].faceValue) - 1);
            deck[index].faceValue[sizeof(deck[index].faceValue) - 1] = '\0';
            deck[index].cardValue = cardValues[j];
            index++;
        }
    }

    // Save the new deck to a file
    saveDeckToFile("NewDeck.txt", deck);
}

void shuffleCards(Card deck[52]) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    // Save the shuffled deck to a file
    saveDeckToFile("ShuffledDeck.txt", deck);
}

void dealCards(Card deck[52], int *topCardIndex, Card hand[], int *handSize) {
    if (*topCardIndex < 52) {
        hand[*handSize] = deck[*topCardIndex];
        (*handSize)++;
        (*topCardIndex)++;
        printf("Dealt card: %s of %s\n", hand[*handSize - 1].faceValue, hand[*handSize - 1].suit);
        printf("Cards left in deck: %d\n", 52 - *topCardIndex);
    } else {
        printf("No more cards in the deck!\n");
    }
}

int handleAces(int totalValue, int numAces, bool isHuman) {
    while (numAces > 0) {
        if (totalValue + 11 <= 21) {
            if (isHuman){
                char AceCheck;
                printf("\nDo you want an Ace of a. 11 or b. 1\n");
                scanf(" %c", &AceCheck);
                if (AceCheck == 'a') {totalValue += 11;} else if(AceCheck == 'b') {totalValue += 1;}
            } else {
                srand(time(NULL));
                int dRAND = rand() % 2;
                int valArr[2] = {11, 1};
                totalValue += valArr[dRAND];
            }
        } else { 
            totalValue += 1;
        }
        numAces--;
    }
    return totalValue;
}


int calculateTotalValue(Card hand[], int handSize, bool isHuman) {
    int totalValue = 0;
    int numAces = 0;

    for (int i = 0; i < handSize; i++) {
       
        // if (strcmp(hand[i].faceValue, "Ace") != 0) {
        //     numAces++;
        // } else {
        if (strcmp(hand[i].faceValue, "Ace") != 0) {
            totalValue += hand[i].cardValue;
        }
        // }
    }
    for (int i = 0; i < handSize; i++) {
        if (strcmp(hand[i].faceValue, "Ace") == 0){
            if (hand[i].cardValue == 0) {
                if (totalValue + 11 <= 21){
                    char chosenAce;
                    if (isHuman){
                        printf("Do you want your ace to be value of (a. 11) or (b. 1)\n");
                        scanf(" %c", &chosenAce);
                        if (chosenAce == 'a'){hand[i].cardValue = 11;}
                        else if (chosenAce == 'b'){hand[i].cardValue = 1;}
                    } else {
                        hand[i].cardValue = 11;
                    }
                } else {
                    hand[i].cardValue = 1;
                }
            }
            totalValue += hand[i].cardValue;
        }
    }

    // if (numAces > 0){
    //     totalValue = handleAces(totalValue, numAces, isHuman);
    // }

    return totalValue;
}

bool hasEnoughCards(int topCardIndex) {
    return (52 - topCardIndex) >= 10;
}

void displayHands(Card playerHand[], int playerHandSize, Card dealerHand[], int dealerHandSize, int playerTotal, int dealerTotal) {
    printf("\nPlayer's Hand:\n");
    for (int i = 0; i < playerHandSize; i++) {
        printf("%s of %s\n", playerHand[i].faceValue, playerHand[i].suit);
    }
    printf("Player's Total Value: %d\n", playerTotal);

    printf("\nDealer's Hand:\n");
    for (int i = 0; i < dealerHandSize; i++) {
        printf("%s of %s\n", dealerHand[i].faceValue, dealerHand[i].suit);
    }
    printf("Dealer's Total Value: %d\n", dealerTotal);
}

void saveDeckToFile(const char *filename, Card deck[52]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < 52; i++) {
        fprintf(file, "%s %s %d\n", deck[i].faceValue, deck[i].suit, deck[i].cardValue);
    }

    fclose(file);
}

void readDeckFromFile(const char *filename, Card deck[52]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < 52; i++) {
        fscanf(file, "%s %s %d", deck[i].faceValue, deck[i].suit, &deck[i].cardValue);
    }

    fclose(file);
}

bool checkBlackjack(int total) {
    return total == 21;
}

void determineWinner(int playerTotal, int dealerTotal, bool playerBlackjack, bool dealerBlackjack) {
    if (playerBlackjack && dealerBlackjack) {
        printf("Both player and dealer have Blackjack! It's a draw.\n");
    } else if (playerBlackjack) {
        printf("Player has Blackjack! Player wins.\n");
    } else if (dealerBlackjack) {
        printf("Dealer has Blackjack! Dealer wins.\n");
    } else if (playerTotal > 21 && dealerTotal > 21) {
        printf("Both player and dealer bust! No one wins.\n");
    } else if (playerTotal > 21) {
        printf("Player busts! Dealer wins.\n");
    } else if (dealerTotal > 21) {
        printf("Dealer busts! Player wins.\n");
    } else if (playerTotal > dealerTotal) {
        printf("Player wins with %d against dealer's %d.\n", playerTotal, dealerTotal);
    } else if (dealerTotal > playerTotal) {
        printf("Dealer wins with %d against player's %d.\n", dealerTotal, playerTotal);
    } else {
        printf("It's a draw with both having %d.\n", playerTotal);
    }
}

int main() {
    int ret = mainMenu();
    if (ret == 1) {
        Card deck[52];
        int topCardIndex = 0;

        // Create and shuffle the deck, then save to files
        createDeck(deck);
        shuffleCards(deck);

        // Read the decks from the files
        readDeckFromFile("NewDeck.txt", deck);
        readDeckFromFile("ShuffledDeck.txt", deck);

        while (1) {
            if (!hasEnoughCards(topCardIndex)) {
                printf("Not enough cards in the deck. Creating and shuffling a new deck.\n");
                createDeck(deck);
                shuffleCards(deck);
                topCardIndex = 0;
            }


            // Initialize hands
            Card playerHand[52];
            Card dealerHand[52];
            int playerHandSize = 0;
            int dealerHandSize = 0;

            // Deal initial cards to player and dealer
            dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
            dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
            dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
            dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);

            // Calculate and print initial total values
            int playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
            int dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);

            displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);

            // Check for Blackjack
            bool playerBlackjack = checkBlackjack(playerTotal);
            bool dealerBlackjack = checkBlackjack(dealerTotal);
            char choice;

            if (playerBlackjack || dealerBlackjack) {
                determineWinner(playerTotal, dealerTotal, playerBlackjack, dealerBlackjack);
            } else {
                while (1) {
                    printf("\nDo you want to Hit or Stand? (h/s): ");
                    scanf(" %c", &choice);
                    if (choice == 'h' || choice == 'H') {
                        dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
                        playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
                        displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                        if (playerTotal > 21) {
                            printf("Player busts! Dealer wins.\n");
                            break;
                        }
                    } else if (choice == 's' || choice == 'S') {
                        printf("Player stands.\n");
                        break;
                    } else {
                        printf("Invalid choice. Please enter 'h' to Hit or 's' to Stand.\n");
                    }
                }

                if (playerTotal <= 21) {
                    // Dealer's turn: Draw cards until total value is at least 17
                    while (dealerTotal < 17) {
                        dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
                        dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);
                        displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                    }

                    // Print final hands and totals
                    displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);

                    // Determine the winner
                    determineWinner(playerTotal, dealerTotal, playerBlackjack, dealerBlackjack);
                }
            }
            // Ask the user if they want to start a new round
            printf("\nDo you want to start a new round? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'n' || choice == 'N') {
                remove("NewDeck.txt");
                remove("ShuffledDeck.txt");
                break;
            }
        }
    }
    return 0;
}

char exitProcess;

int mainMenu() {
    char currentCommand[10];
    char exitProcess[10];

    while (1) {
        printf("a. Start a new game\n");
        printf("b. Get Help on how to play the game\n");
        printf("c. Exit\n");

        // Read the entire line
        fgets(currentCommand, sizeof(currentCommand), stdin);

        // Remove the newline character if present
        currentCommand[strcspn(currentCommand, "\n")] = 0;

        if (strcmp(currentCommand, "c") == 0) {
            return 0;
        } else if (strcmp(currentCommand, "b") == 0) {
            printf("\nBlackjack is a card game where players play against the dealer of the cards. In the case of a singleplayer blackjack, there is only one player competing with the dealer.\nThe goal is to get a set of cards in your hand that has a sum of values that is the higher than the dealers hand without going over 21.\n");
            printf("You can choose to hit as many times as you want, but the dealer hits until he reaches atleast 17.\n");
            printf("You can stand your chosen cards.\n");
            fgets(exitProcess, sizeof(exitProcess), stdin);
            if (exitProcess[0] == '\n') {
                continue;
            }
        } else if (strcmp(currentCommand, "a") == 0) {
            return 1;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }
}
