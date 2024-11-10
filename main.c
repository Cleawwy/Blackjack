/*
 * Blackjack Game - Created by Mohammad Shebaro - 24004149
 * 
 * Copyright © 2024. All rights reserved.
 *
 * Permission is hereby granted to use, modify, and distribute this code 
 * for educational and personal purposes, provided that this copyright 
 * notice and disclaimer are included in all copies or substantial portions 
 * of the software.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <time.h>

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
int handleAces(int totalValue, Card hand[], int handSize, bool isHuman);
bool hasEnoughCards(int topCardIndex);
void displayHands(Card playerHand[], int playerHandSize, Card dealerHand[], int dealerHandSize, int playerTotal, int dealerTotal);
void saveDeckToFile(const char *filename, Card deck[52]);
void readDeckFromFile(const char *filename, Card deck[52]);

void createDeck(Card deck[52]) {
    char* suits[4] = {"Heart", "Diamond", "Spade", "Club"};
    char* faceValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int cardValues[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0};

    int index = 0;

    // Add cards to Deck (UNSHUFFLED)
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

    // Save the new deck to NewDeck.txt
    saveDeckToFile("NewDeck.txt", deck);
}

void shuffleCards(Card deck[52]) {
    srand(time(NULL)); // Create a new seed to actually randomize
    // Shuffle New Cards Deck (Fisher-Yates Algorithm)
    // The way this works is by swapping the element of the array with a random index including the last
    // O(n) complexity
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    // Save the shuffled deck to ShuffledDec.t.xt
    saveDeckToFile("ShuffledDeck.txt", deck);
}

void dealCards(Card deck[52], int *topCardIndex, Card hand[], int *handSize) {
    // Deal cards from top of shuffled deck unless empty
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

int handleAces(int totalValue, Card hand[], int handSize, bool isHuman) {
   for (int i = 0; i < handSize; i++) {
        if (strcmp(hand[i].faceValue, "Ace") == 0){
            if (hand[i].cardValue == 0) {
                if (totalValue + 11 <= 21){
                    hand[i].cardValue = 11;    
                } else {
                    hand[i].cardValue = 1;
                }
            }
            totalValue += hand[i].cardValue;
        }
    }
    return totalValue;
}


int calculateTotalValue(Card hand[], int handSize, bool isHuman) {
    int totalValue = 0;

    for (int i = 0; i < handSize; i++) {
        if (strcmp(hand[i].faceValue, "Ace") != 0) {
            totalValue += hand[i].cardValue;
        }
    }

    totalValue = handleAces(totalValue, hand, handSize, isHuman);

    return totalValue;
}


// Modifiable function for minimum cards for new game
bool hasEnoughCards(int topCardIndex) {
    return (52 - topCardIndex) >= 10;
}

void displayHands(Card playerHand[], int playerHandSize, Card dealerHand[], int dealerHandSize, int playerTotal, int dealerTotal) {
    // Duality checks is a boolean that changes if a player's ace has the value 11
    // Duality changes if a player stands and loses but has an 11 save.
    bool playerDuality = false;
    bool dealerDuality = false;

    int maxHandSize = (playerHandSize > dealerHandSize) ? playerHandSize : dealerHandSize;

    printf("\nPlayers's Hand:         \t\tDealer's Hand      ");
    printf("\n---------------         \t\t-------------     ");
    printf("\n");

    for (int i = 0; i < maxHandSize; i++) {
        // Print player's hand if there are still cards
        if (i < playerHandSize) {
            printf("%i: %s of %s", i + 1, playerHand[i].faceValue, playerHand[i].suit);
            if (strcmp(playerHand[i].faceValue, "Ace") == 0 && playerHand[i].cardValue == 11) {
                playerDuality = true;
            }
        } else {
            printf("                   ");  // Empty space if no more player cards
        }

        printf("    \t\t\t");

        // Print dealer's hand if there are still cards
        if (i < dealerHandSize) {
            printf("%i: %s of %s", i + 1, dealerHand[i].faceValue, dealerHand[i].suit);
            if (strcmp(dealerHand[i].faceValue, "Ace") == 0 && dealerHand[i].cardValue == 11) {
                dealerDuality = true;
            }
        }

        printf("\n");  // Move to the next line after printing both hands
    }

    if (playerDuality == true){
        printf("Total: %d or %d", playerTotal-10, playerTotal);
    } else {
        printf("Total: %d", playerTotal);
    }

    if (dealerDuality == true){
        printf("\t\t\t\tTotal: %d or %d", dealerTotal-10, dealerTotal);
    } else {
        printf("\t\t\t\tTotal: %d", dealerTotal);
    }

    printf("\n");
}

// Function to Save Deck to file
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


// Function to Read Deck from file
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

// Checks Player/Dealer Blackjack
bool checkBlackjack(int total) {
    return total == 21;
}

// If-Else for Win/Lose Conditions
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

// Main Function
int main(){
    // Prompt mainMenu and proceed after start
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

        // Game Loop Functionality
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
                        
                        bool p_hasAceSave = false;
                        for (int i = 0; i<=playerHandSize-1; i++){
                            if (strcmp(playerHand[i].faceValue, "Ace") == 0 && playerHand[i].cardValue == 11){
                                p_hasAceSave = true;
                            }
                        }
                    
                        if (playerTotal > 21) {
                            if (p_hasAceSave == true){
                                for (int i = 0; i<=playerHandSize-1; i++){
                                    if (strcmp(playerHand[i].faceValue, "Ace") == 0 && playerHand[i].cardValue == 11){
                                        playerHand[i].cardValue = 1;
                                        
                                    }
                                }
                            } else if (p_hasAceSave == false){
                                playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
                                displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                                printf("Player busts! Dealer wins.\n");
                                break;
                            }
                        }
                        playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
                        displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                    } else if (choice == 's' || choice == 'S') {
                        printf("Player stands.\n");
                        break;
                    } else {
                        printf("Invalid choice. Please enter 'h' to Hit or 's' to Stand.\n");
                    }
                }
                bool d_hasAceSave = false;
                if (playerTotal <= 21) {
                    // Dealer's turn: Draw cards until total value is at least 17
                    while (dealerTotal < 17) {
                        dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);

                         for (int i = 0; i<=dealerHandSize-1; i++){
                            if (strcmp(dealerHand[i].faceValue, "Ace") == 0 && dealerHand[i].cardValue == 11){
                                d_hasAceSave = true;
                            }
                        }

                        dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);
                        if (d_hasAceSave == true && dealerTotal > 21){
                             for (int i = 0; i<=dealerHandSize-1; i++){
                                if (strcmp(dealerHand[i].faceValue, "Ace") == 0 && dealerHand[i].cardValue == 11){
                                    dealerHand[i].cardValue = 1;
                                }
                            }
                        }

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
            int exitGame = 0;
            while (1){
                scanf(" %c", &choice);
                if (choice == 'n' || choice == 'N') {
                    remove("NewDeck.txt");
                    remove("ShuffledDeck.txt");
                    exitGame = 1;
                    break;
                } else if (choice == 'y' || choice == 'Y') {
                    break;
                } else {
                    printf("Please enter a valid character (y/n): ");
                }
            }
            if (exitGame==1){break;}
        }
    }
    return 0;
}

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
            // Checks if player presses Enter to go back to Main Menu
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
