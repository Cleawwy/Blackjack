#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "gfx.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CARD_WIDTH 50
#define CARD_HEIGHT 70
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

typedef struct {
    char suit[20];
    char faceValue[10];
    int cardValue;
} Card;

bool gameRunning = false;
Card deck[52];
int topCardIndex = 0;
Card playerHand[52];
Card dealerHand[52];
int playerHandSize = 0;
int dealerHandSize = 0;
int playerTotal = 0;
int dealerTotal = 0;
bool playerBlackjack = false;
bool dealerBlackjack = false;

void createDeck(Card deck[52]);
void shuffleCards(Card deck[52]);
void dealCards(Card deck[52], int *topCardIndex, Card hand[], int *handSize);
int calculateTotalValue(Card hand[], int handSize, bool isHuman);
void displayHands();
void drawCard(int x, int y, Card card);
void drawButton(int x, int y, const char *label);
bool isButtonClicked(int x, int y, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
void determineWinner();
void resetGame();

int main() {
    gfx_open(WINDOW_WIDTH, WINDOW_HEIGHT, "Blackjack Game");
    createDeck(deck);
    shuffleCards(deck);
    resetGame();

    while (1) {
        gfx_clear();
        displayHands();
        drawButton(50, WINDOW_HEIGHT - 100, "Hit");
        drawButton(200, WINDOW_HEIGHT - 100, "Stand");

        if (gfx_event_waiting()) {
            char c = gfx_wait();
            int x = gfx_xpos();
            int y = gfx_ypos();

            if (isButtonClicked(x, y, 50, WINDOW_HEIGHT - 100, BUTTON_WIDTH, BUTTON_HEIGHT)) {
                dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
                playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
                if (playerTotal > 21) {
                    determineWinner();
                }
            } else if (isButtonClicked(x, y, 200, WINDOW_HEIGHT - 100, BUTTON_WIDTH, BUTTON_HEIGHT)) {
                while (dealerTotal < 17) {
                    dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
                    dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);
                }
                determineWinner();
            }
        }

        gfx_flush();
    }

    return 0;
}

void createDeck(Card deck[52]) {
    char* suits[4] = {"Heart", "Diamond", "Spade", "Club"};
    char* faceValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int cardValues[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0};

    int index = 0;
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
}

void shuffleCards(Card deck[52]) {
    srand(time(NULL));
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void dealCards(Card deck[52], int *topCardIndex, Card hand[], int *handSize) {
    if (*topCardIndex < 52) {
        hand[*handSize] = deck[*topCardIndex];
        (*handSize)++;
        (*topCardIndex)++;
    }
}

int calculateTotalValue(Card hand[], int handSize, bool isHuman) {
    int totalValue = 0;
    int numAces = 0;

    for (int i = 0; i < handSize; i++) {
        if (strcmp(hand[i].faceValue, "Ace") != 0) {
            totalValue += hand[i].cardValue;
        } else {
            numAces++;
        }
    }

    for (int i = 0; i < numAces; i++) {
        if (totalValue + 11 <= 21) {
            totalValue += 11;
        } else {
            totalValue += 1;
        }
    }

    return totalValue;
}

void displayHands() {
    int playerX = 50;
    int playerY = WINDOW_HEIGHT - 200;
    int dealerX = 50;
    int dealerY = 50;

    for (int i = 0; i < playerHandSize; i++) {
        drawCard(playerX + i * (CARD_WIDTH + 10), playerY, playerHand[i]);
    }

    for (int i = 0; i < dealerHandSize; i++) {
        drawCard(dealerX + i * (CARD_WIDTH + 10), dealerY, dealerHand[i]);
    }
}

void drawCard(int x, int y, Card card) {
    gfx_color(255, 255, 255);
    gfx_fill_rectangle(x, y, CARD_WIDTH, CARD_HEIGHT); // Fill the rectangle for the card
    gfx_color(0, 0, 0);
    gfx_rectangle(x, y, CARD_WIDTH, CARD_HEIGHT); // Draw the border
    gfx_text(card.faceValue, x + 5, y + 15, 0); // Draw face value
    gfx_text(card.suit, x + 5, y + 30, 0); // Draw suit
}


void drawButton(int x, int y, const char *label) {
    gfx_color(200, 200, 200);
    gfx_fill_rectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT);
    gfx_color(0, 0, 0);
    gfx_text(label, x + 20, y + 30, 0); // Draw button label
}


bool isButtonClicked(int x, int y, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    return x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight;
}

void determineWinner() {
    if (playerTotal > 21) {
        gfx_text("Player busts! Dealer wins.", 50, WINDOW_HEIGHT / 2, 0);
    } else if (dealerTotal > 21) {
        gfx_text("Dealer busts! Player wins.", 50, WINDOW_HEIGHT / 2, 0);
    } else if (playerTotal > dealerTotal) {
        gfx_text("Player wins!", 50, WINDOW_HEIGHT / 2, 0);
    } else if (dealerTotal > playerTotal) {
        gfx_text("Dealer wins!", 50, WINDOW_HEIGHT / 2, 0);
    } else {
        gfx_text("It's a draw!", 50, WINDOW_HEIGHT / 2, 0);
    }
    gfx_flush();
    sleep(3);
    resetGame();
}


void resetGame() {
    topCardIndex = 0;
    playerHandSize = 0;
    dealerHandSize = 0;
    playerTotal = 0;
    dealerTotal = 0;
    playerBlackjack = false;
    dealerBlackjack = false;
    shuffleCards(deck);
    dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
    dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
    dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
    dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
    playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
    dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);
}
