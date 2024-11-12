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
#include <math.h>
#include <unistd.h>

#include "gfx.h"

#define MAX_CARDS 6

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

// Graphics
void clear_text(char* player);

void createMenu(int x, int y){
  int scaleX = 200;
  int scaleY = 60;
  
  gfx_text("A Blackjack Experience", (x/2)-135, y-600, 2);
  gfx_color(255, 255, 255);
  
  int buttonXAlignment = (x/2)-25;
 

  
  int middleYOffset = (y);
  for (int i=0; i<6; i++){
  middleYOffset+=400;
  
  gfx_fillrectangle((x/2)-scaleX, (y/2)-scaleY-200, 400, 600);
  gfx_rectangle((x/2)-scaleX, (y/2)-scaleY-200, 400, 600);
  }
  
  for (int j=0; j<=10; j++){
      for (int i=0; i<=6; i++){
        gfx_rectangle(-50+125*j, -50-(50*j)+225*i, 100, 200);
    }
  }
  
  gfx_color(0, 0, 0);
  gfx_rectangle((x/2)-scaleX/2, y-450, scaleX, scaleY);
  gfx_text("Start", buttonXAlignment, y-435, 2);
  gfx_rectangle((x/2)-scaleX/2, y-350, scaleX, scaleY);
  gfx_text("Help", buttonXAlignment, y-335, 2);
  gfx_rectangle((x/2)-scaleX/2, y-250, scaleX, scaleY);
  gfx_text("Credits", buttonXAlignment-15, y-235, 2);
  gfx_color(255, 255, 255);
  
  }
  
  
void draw_value(char* player, int value, int midpoint){
  char numStr[2];
  sprintf(numStr, "%d", value);
  if (numStr[1] == '\0'){
    midpoint+=5;
  }
  clear_text(player);
  usleep(10000);
  
  gfx_color(0, 0, 0);
  gfx_text(numStr, midpoint-15, 605, 2);
  gfx_flush();
}

// Function to draw the card outline and fill
void draw_card_outline(int x, int y, int width, int height) {
    // Draw card outline with rounded corners
    gfx_color(0, 0, 0);  // Black border
    gfx_rectangle(x, y, width, height);

    // Fill card with light gray color
    gfx_color(240, 240, 240);  // Light gray fill
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            gfx_point(x + i, y + j);
        }
    }
}


// Function to draw a number or letter using a pixel pattern
void draw_number_or_letter(int x, int y, int r, int g, int b, int value) {
    gfx_color(r, g, b);  // Set color for the character

    // Define pixel patterns for numbers 0 to 10 and letter A
    int patterns[11][15][9] = {
        // 0
        {{0, 0, 1, 1, 1, 1, 1, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 1
        {{0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0, 0},
         {0, 0, 1, 0, 1, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 2
        {{0, 0, 1, 1, 1, 1, 1, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 3
        {{1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 1, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 4
         {{0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 1, 0, 1, 0, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 0, 0},
         {0, 1, 0, 0, 0, 1, 0, 0, 0},
         {1, 0, 0, 0, 0, 1, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 5
        {{1, 1, 1, 1, 1, 1, 1, 1, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 1, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 6
        {{0, 1, 1, 1, 1, 1, 1, 1, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 1, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
          // 7
        {{1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 8
        {{0, 1, 1, 1, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 9
        {{0, 1, 1, 1, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {1, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}}};
        // Draw the pattern for the given value (2 to 9 or 'A')
        if (value >= 2 && value <= 9) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[value][i][j] == 1) {
                        gfx_point(x + j, y + i);
                    }
                }
            }
        } else if (value == 10) {
            // Draw '1'
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[1][i][j] == 1) {
                        gfx_point(x + j, y + i);
                    }
                }
            }
            // Draw '0' next to '1'
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[0][i][j] == 1) {
                        gfx_point(x + j + 10, y + i);
                    }
                }
            }
        }
    }

// Function to draw the letter 'A' pixel by pixel
void draw_large_A(int x, int y, int r, int g, int b) {
    gfx_color(r, g, b);  // Set color for 'A'
    
    // Draw the 'A' shape using individual pixels
    int a_pattern[15][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 9; j++) {
            if (a_pattern[i][j] == 1) {
                gfx_point(x + j, y + i);
            }
        }
    }
}

// Function to draw a big heart using gfx_fillcircle and pixels
void draw_big_heart(int x, int y) {
    gfx_color(255, 0, 0);  // Red color for heart

    // Draw the two circles for the top of the heart
    gfx_fillcircle(x - 7, y, 15);  // Left circle, bigger and overlapping
    gfx_fillcircle(x + 6, y, 15);  // Right circle, bigger and overlapping

    // Draw the bottom part of the heart using pixels to seamlessly blend with the circles
    for (int i = -15; i <= 15; i++) {
        for (int j = 0; j <= 20; j++) {
            if ((abs(i) + j <= 17) && (j >= abs(i) - 5)) {  // Adjust to blend with circles
                gfx_point(x + i, y + j);
            }
        }
    }
}

// Function to draw the club symbol using gfx_fillcircle
void draw_club(int x, int y) {
    gfx_color(0, 0, 0);  // Black color for club

    // Draw three overlapping circles for the top part of the club
    gfx_fillcircle(x - 6, y + 7, 15);  // Left circle
    gfx_fillcircle(x + 6, y + 7, 15);  // Right circle
    gfx_fillcircle(x, y - 4, 15);      // Bottom circle

    // Draw the stem of the club
    for (int i = -2; i <= 2; i++) {
        for (int j = 15; j <= 30; j++) {
            gfx_point(x + i, y + 5);
        }
    }
      
    for (int j = 0; j <= 25; j++) {
        for (int i = -j / 4; i <= j / 4; i++) {
            gfx_point(x + i, y - 4 + j);
        }
    }
}

// Function to draw the spade symbol using an inverted heart
void draw_spade(int x, int y) {
     int y_offset = 10;  // Add this offset to move the spade down

      gfx_color(0, 0, 0);  // Black color for spade

      // Draw the two circles for the top of the heart (inverted for spade)
      gfx_fillcircle(x - 7, y + y_offset, 15);  // Left circle
      gfx_fillcircle(x + 6, y + y_offset, 15);  // Right circle

      // Draw the bottom part of the heart (inverted for spade) using pixels to seamlessly blend with the circles
      for (int i = -15; i <= 15; i++) {
          for (int j = 0; j <= 20; j++) {
              if ((abs(i) + j <= 17) && (j >= abs(i) - 5)) {  // Adjust to blend with circles
                  gfx_point(x + i, y - j + y_offset);  // Flipped vertically with offset
              }
          }
      }
    
      for (int j = 0; j <= 25; j++) {
        for (int i = -j / 4; i <= j / 4; i++) {
            gfx_point(x + i, y - 10 + j + y_offset);
        }
    }
}

// Function to draw the diamond symbol with adjustments to centering and elongation
void draw_diamond(int x, int y) {
    gfx_color(255, 0, 0);  // Red color for diamond

    // Draw diamond using a simple elongated rhombus shape
    for (int i = -10; i <= 10; i++) {
        for (int j = -15; j <= 15; j++) {  // Elongate the diamond vertically
            if (abs(i) + abs(j * 2 / 3) <= 10) {  // Adjust shape to be more centered and elongated
                gfx_point(x + i, y + j);
            }
        }
    }
}

// Function to draw a symbol at the center of the card
void draw_symbol(int x, int y, char suit) {
    switch (suit) {
        case 'H':  // Heart
            draw_big_heart(x, y);
            break;
        case 'S':  // Spade
            draw_spade(x, y);
            break;
        case 'D':  // Diamond
            draw_diamond(x, y+5);
            break;
        case 'C':  // Club
            draw_club(x, y+3);
            break;
    }
}

int draw_P=0;
int draw_D=0;

void draw_card(char *player, int card_number, int value, char suit) {
    int base_x;
    int y;
    if (strcmp(player, "Dealer") == 0 && card_number == draw_D) {
        draw_D++;
        base_x = 550;
        y = 150;
    } else if (strcmp(player, "Person") == 0 && card_number == draw_P) {
        draw_P++;
        base_x = 550;
        y = 350;
    } else {
        return;
    }
    usleep(250000);
    
    int card_width = 100;
    int card_height = 150;

    if (card_number >= 0 && card_number < MAX_CARDS) {
        int x = base_x + (card_number - MAX_CARDS / 2) * (card_width + 10);
        draw_card_outline(x, y, card_width, card_height);

        // Draw card value and suit
        int r, g, b;
        if (suit == 'H' || suit == 'D') {
            r = 255; g = 0; b = 0;
        } else {
            r = 0; g = 0; b = 0;
        }
        if (value >= 2 && value < 10) {
            draw_number_or_letter(x + 5, y + 5, r, g, b, value);
            draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);
        } else if (value == 10){
            draw_number_or_letter(x + 5, y + 5, r, g, b, value);
            draw_number_or_letter(x + card_width - 23, y + card_height - 15, r, g, b, value);
        } else if (value == 1 || value == 11) {
            draw_large_A(x + 5, y + 3, r, g, b);
            draw_large_A(x + card_width - 12, y + card_height - 19, r, g, b);
        }
        
        switch (value){
            case 2:
                  draw_symbol(x  + card_width / 2, (y + card_height / 2) + 20, suit);
                  draw_symbol(x  + card_width / 2, (y + card_height / 2) - 35, suit);
            break;
            case 3:
                  draw_symbol(x + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 10, suit);
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 50, suit);
            break;
            case 4:
                  draw_symbol(x - 18 + card_width / 2, y + card_height / 2 - 30, suit);
                  draw_symbol(x - 18 + card_width / 2, y + card_height / 2 + 15, suit);
                  
                  draw_symbol(x + 18 + card_width / 2, y + card_height / 2 - 30, suit);
                  draw_symbol(x + 18 + card_width / 2, y + card_height / 2 + 15, suit);
            break;
            case 5: 
                  draw_symbol(x - 17 + card_width / 2, y + card_height / 2 - 45, suit);
                  draw_symbol(x + 17 + card_width / 2, y + card_height / 2 - 45, suit);
                  
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 7, suit);
    
                  draw_symbol(x - 17 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x + 17 + card_width / 2, y + card_height / 2 + 30, suit);
            break;
            case 6:
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 50, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 50, suit);
            break;
            case 7:
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 50, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 30, suit);
                  
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 50, suit);
            break;
            case 8:
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 50, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 30, suit);
                  draw_symbol(x + card_width / 2, y + card_height / 2 + 10, suit);
                  
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 10, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 30, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 50, suit);
            break;
            case 9:
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 7, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 42, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 28, suit);
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 63, suit);
                  
                  draw_symbol(x + card_width / 2, y + card_height / 2 - 15, suit);
                  
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 7, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 42, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 28, suit);
                  draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 63, suit);
            break;
            case 10:
                  draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 5, suit);
            break;
            default:
                 draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);
            break;
        }
    }
    gfx_flush();
}

void clear_text(char* player){
  gfx_color(25,70,25);

  int i, j, x, y;
    // clear X from 610 - 670;
    // clear Y from 603-640;
  if (strcmp("Person", player) == 0){
      x = 610;
      y = 640;
  } else if (strcmp("Dealer", player) == 0){
      return;
  }
  for (int i = x; i<= x+70; i++){
      for (int j = y; j>=y-40; j--){
          gfx_point(i, j);
      }
}
  gfx_flush();
}

// Function to draw circular buttons with text (outline only)
void draw_button(int x, int y, char *text) {
    // Draw the circle outline for the button
    gfx_color(0, 0, 0);
    gfx_circle(x, y, 100);

    // Draw the button text
    if (strcmp(text, "Hit") == 0){
        x -=15;
    } else {
        x-=28;
    }
    y -=12;
    gfx_text(text, x, y, 2);
    gfx_flush();
}

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
    int pIter = 0;
    int dIter = 0;
    for (int i = 0; i < maxHandSize; i++) {
        // Print player's hand if there are still cards
        if (i < playerHandSize) {
              printf("%i: %s of %s", i + 1, playerHand[i].faceValue, playerHand[i].suit);
              draw_card("Person", pIter, playerHand[i].cardValue, playerHand[i].suit[0]);
              pIter++;
            
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
            draw_card("Dealer", dIter, dealerHand[i].cardValue, dealerHand[i].suit[0]);
            dIter++;
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
    //int ret = mainMenu();
    //if (ret == 1) {
    

    int screenX = 1280;
    int screenY = 830;

    gfx_open(screenX, screenY, "A Blackjack Experience");
    gfx_clear_color(128, 128, 128);
    gfx_clear();

    // Draw the casino floor background
    for (int x = 0; x < screenX; x++) {
        for (int y = 0; y < screenY; y++) {
            if (((x / 20) % 2 == 0 && (y / 20) % 2 == 0) || ((x / 20) % 2 == 1 && (y / 20) % 2 == 1)) {
                gfx_color(20, 85, 20);  // Darker red
            } else {
                gfx_color(30, 100, 30);  // Softer red
            }
            gfx_point(x, y);
        }
    }

    // Draw the main table
    int center_x = 650;
    int center_y = 375;
    int radius_x = 500;
    int radius_y = 350;

    int border_thickness = 30;
    for (int i = 0; i < border_thickness; i++) {
        gfx_color(81 + i, 51 + i * 0.5, 17 + i * 0.3);
        for (int x = center_x - (radius_x + i); x <= center_x + (radius_x + i); x++) {
            for (int y = center_y; y <= center_y + (radius_y + i) * sqrt(1 - ((x - center_x) * (x - center_x)) / (double)((radius_x + i) * (radius_x + i))); y++) {
                gfx_point(x, y);
            }
        }
    }

    gfx_color(25,70,25);
    for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
        for (int y = center_y; y <= center_y + radius_y * sqrt(1 - ((x - center_x) * (x - center_x)) / (double)(radius_x * radius_x)); y++) {
            gfx_point(x, y);
        }
    }

    for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
        for (int y = 0; y <= center_y; y++) {
            gfx_point(x, y);
        }
    }

    // Draw buttons for Hit and Stand using circular outlines
    draw_button((screenX/2)-100, 600, "Stand");
    draw_button((screenX/2)+100, 600, "Hit");
    
    
    int x_between = ((screenX/2)+(screenX/2))/2;
    gfx_text("Total:", x_between-33, 570, 2);
    gfx_line(x_between-33, 595, x_between+37, 595);
   // gfx_text("2", x_between-15, 605, 2);
    // between buttons ((screenX/2)+100)+(screenX/2)-100)/2; 600

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

            draw_value("Person", playerTotal, ((screenX/2)+(screenX/2))/2);
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
                    while (1) {
                        char c = gfx_wait();
                        if (c == 1) {
                            printf("%d %d\n", gfx_xpos(), gfx_ypos());
                            int xPos = gfx_xpos();
                            int yPos = gfx_ypos();
                            int standButtonX = (screenX / 2) - 100;
                            int hitButtonX = (screenX / 2) + 100;
                            int detectRad = 50;
                            
                            double standDist = sqrt((xPos - standButtonX) * (xPos - standButtonX) + (yPos - 600) * (yPos - 600));
                            double hitDist = sqrt((xPos - hitButtonX) * (xPos - hitButtonX) + (yPos - 600) * (yPos - 600));

                            if (standDist <= detectRad) {
                                printf("Stand button clicked!\n");
                                choice = 'S';
                                break;
                            } else if (hitDist <= detectRad) {
                                printf("Hit button clicked!\n");
                                choice = 'H';
                                break;
                            }
                        }
                    }
                    //scanf(" %c", &choice);
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
                                draw_value("Person", playerTotal, ((screenX/2)+(screenX/2))/2);
                                displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                                printf("Player busts! Dealer wins.\n");
                                break;
                            }
                        }
                        playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
                        draw_value("Person", playerTotal, ((screenX/2)+(screenX/2))/2);
                        displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                    } else if (choice == 's' || choice == 'S') {
                        printf("Player stands.\n");
                        break;
                    } else {
                        printf("Invalid choice. Please enter 'h' to Hit or 's' to Stand.\n");
                    }
                }
                bool d_hasAceSave = false;

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
                    draw_value("Person", playerTotal, ((screenX/2)+(screenX/2))/2);
                    displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                    gfx_flush();
                    // Determine the winner
                    determineWinner(playerTotal, dealerTotal, playerBlackjack, dealerBlackjack);
                
            }
            // Ask the user if they want to start a new round
            
            printf("\nDo you want to start a new round? (y/n): ");
            int exitGame = 0;
            /*while (1){
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
            if (exitGame==1){break;}*/
            while(1){};
        }
    //}
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
