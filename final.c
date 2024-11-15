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


void clear_text(char* player);
  
void draw_value(char* player, int value, int midpoint, int aceCalc){
  char numStr[20];
  int yaxis;
  if (strcmp("Person", player) == 0){
    yaxis = 605;
  } else if (strcmp("Dealer", player) == 0){
    yaxis = 55;
  }

  if (aceCalc == 1){
    sprintf(numStr, "%d or %d", value-10, value);
  } else {
    sprintf(numStr, "%d", value);
  }
  if (numStr[1] == '\0'){
    midpoint+=5;
  }
  clear_text(player);
  usleep(10000);
  
  gfx_color(0, 0, 0);
  gfx_text(numStr, midpoint-15, yaxis, 2);
  gfx_flush();
}


void draw_card_outline(int x, int y, int width, int height) {
    
    

    
    gfx_color(240, 240, 240);  
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            gfx_point(x + i, y + j);
        }
    }
}



void draw_number_or_letter(int x, int y, int r, int g, int b, int value) {
    gfx_color(r, g, b);  
  
    
    int patterns[14][15][9] = {
        
        {{0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 1, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 1, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        
        {{0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0, 0},
         {0, 0, 1, 0, 1, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        
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
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
         
        {{0, 0, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
         
        {{0, 1, 1, 1, 1, 1, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 1, 1, 1, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
         
        {{1, 1, 1, 0, 0, 1, 1, 1, 0},
         {0, 1, 0, 0, 0, 1, 0, 0, 0},
         {0, 1, 0, 0, 1, 0, 0, 0, 0},
         {0, 1, 0, 1, 0, 0, 0, 0, 0},
         {0, 1, 1, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 1, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 0, 0, 0, 0},
         {0, 1, 0, 0, 0, 1, 0, 0, 0},
         {1, 1, 1, 0, 0, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
         };
        
        if (value != 10) {
            if (value > 11){
                value -= 2;
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[value][i][j] == 1) {
                        gfx_point(x + j, y + i);
                    }
                }
            }
        } else if (value == 10) {
            
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[1][i][j] == 1) {
                        gfx_point(x-1 + j, y + i);
                    }
                }
            }
            
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 9; j++) {
                    if (patterns[0][i][j] == 1) {
                        gfx_point(x-1 + j + 8, y + i);
                    }
                }
            }
        }
    }


void draw_large_A(int x, int y, int r, int g, int b) {
    gfx_color(r, g, b);  
    
    
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


void draw_big_heart(int x, int y) {
    gfx_color(255, 0, 0);  

    
    gfx_fillcircle(x - 7, y, 15);  
    gfx_fillcircle(x + 6, y, 15);  

    
    for (int i = -15; i <= 15; i++) {
        for (int j = 0; j <= 20; j++) {
            if ((abs(i) + j <= 17) && (j >= abs(i) - 5)) {  
                gfx_point(x + i, y + j);
            }
        }
    }
}


void draw_club(int x, int y) {
    gfx_color(0, 0, 0);  

    
    gfx_fillcircle(x - 6, y + 7, 15);  
    gfx_fillcircle(x + 6, y + 7, 15);  
    gfx_fillcircle(x, y - 4, 15);      

    
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


void draw_spade(int x, int y) {
     int y_offset = 10;  

      gfx_color(0, 0, 0);  

      
      gfx_fillcircle(x - 7, y + y_offset, 15);  
      gfx_fillcircle(x + 6, y + y_offset, 15);  

      
      for (int i = -15; i <= 15; i++) {
          for (int j = 0; j <= 20; j++) {
              if ((abs(i) + j <= 17) && (j >= abs(i) - 5)) {  
                  gfx_point(x + i, y - j + y_offset);  
              }
          }
      }
    
      for (int j = 0; j <= 25; j++) {
        for (int i = -j / 4; i <= j / 4; i++) {
            gfx_point(x + i, y - 10 + j + y_offset);
        }
    }
}


void draw_diamond(int x, int y) {
    gfx_color(255, 0, 0);  

    
    for (int i = -10; i <= 10; i++) {
        for (int j = -15; j <= 15; j++) {  
            if (abs(i) + abs(j * 2 / 3) <= 10) {  
                gfx_point(x + i, y + j);
            }
        }
    }
}


void draw_symbol(int x, int y, char suit) {
    switch (suit) {
        case 'H':  
            draw_big_heart(x, y);
            break;
        case 'S':  
            draw_spade(x, y);
            break;
        case 'D':  
            draw_diamond(x, y+5);
            break;
        case 'C':  
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
        base_x = 845;
        y = 120;
    } else if (strcmp(player, "Person") == 0 && card_number == draw_P) {
        draw_P++;
        base_x = 845;
        y = 380;
    } else {
        return;
    }
    usleep(250000);
    
    int card_width = 100;
    int card_height = 150;

    if (card_number >= 0 && card_number < MAX_CARDS) {
        int x = base_x + (card_number - MAX_CARDS / 2) * (card_width + 10);
        if (card_number > 0){x-=85 * card_number;}
        draw_card_outline(x, y, card_width, card_height);

        
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
            draw_number_or_letter(x + card_width - 23+4, y + card_height - 15, r, g, b, value);
        } else if (value == 1 || value == 11) {
            draw_large_A(x + 5, y + 3, r, g, b);
            draw_large_A(x + card_width - 12, y + card_height - 19, r, g, b);
        } else if (value > 11){
            gfx_color(r, g, b);
            gfx_rectangle(x+10, y+20, card_width-20, card_height-40);
            
            draw_number_or_letter(x + 5 + 10, y + card_height - 15 - 20, r, g, b, value);
            draw_number_or_letter(x + card_width - 13 - 10, y + 5 + 20, r, g, b, value);
            
            draw_number_or_letter(x + 5, y + 5, r, g, b, value);
            draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);
        }

        /*
        x = x + (card_number - MAX_CARDS / 2) * (card_width + 10);
        draw_card_outline(x, y, card_width, card_height);
        
        r = 0; g = 0; b = 0;
        value = 12;
        suit = 'D';

        gfx_color(r, g, b);
        gfx_rectangle(x+10, y+20, card_width-20, card_height-40);
        
        draw_number_or_letter(x + 5 + 10, y + card_height - 15 - 20, r, g, b, value);
        draw_number_or_letter(x + card_width - 13 - 10, y + 5 + 20, r, g, b, value);
        
        draw_number_or_letter(x + 5, y + 5, r, g, b, value);
        draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);

        gfx_color(0, 0, 0);
        gfx_rectangle(x, y, card_width, card_height);
        gfx_rectangle(x-1, y-1, card_width, card_height);

        */

        /*
        x = 300;
        y = 300;


        x = x + (MAX_CARDS / 2) * (card_width + 10);
        draw_card_outline(x, y, card_width, card_height);

        r = 255; g = 0; b = 0;

        draw_number_or_letter(x + 5, y + 5, r, g, b, value);
        draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);

        draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 30, suit);
        draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 50, suit);
        draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 10, suit);
        
        draw_symbol(x + card_width / 2, y + card_height / 2 - 30, suit);
        draw_symbol(x + card_width / 2, y + card_height / 2 + 10, suit);
        
        draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 10, suit);
        draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 30, suit);
        draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 50, suit);
        */

        /*

        int card_width = 100;
        int card_height = 150;
        
        int x = 550;
        int y = 150;
        gfx_color(0, 0, 0);
        gfx_rectangle(x+10, y+20, card_width-20, card_height-40);
        
        draw_number_or_letter(x + 5 + 10, y + card_height - 15 - 20, r, g, b, value);
        draw_number_or_letter(x + card_width - 13 - 10, y + 5 + 20, r, g, b, value);
        
        draw_number_or_letter(x + 5, y + 5, r, g, b, value);
        draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);
        gfx_color(0, 0, 0);  
        gfx_rectangle(x, y, card_width, card_height);
        gfx_rectangle(x-1, y-1, card_width, card_height);
        draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);

        gfx_flush();

        */
        
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
                  int oldY = y;
                  if (suit == 'D'){
                      y += 7;
                  } else if (suit == 'H'){
                     y += 7;
                  }
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 + 5, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 + 40, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 - 30, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 - 65, suit);
                  
                  if (suit == 'H'){
                    draw_symbol(x + card_width / 2, y + card_height / 2 - 13, suit);
                  } else {
                    draw_symbol(x + card_width / 2, y + card_height / 2 - 10, suit);
                  }
                  
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 + 5, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 + 40, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 - 30, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 - 65, suit);
                  
                  y = oldY;
            break;
            case 10:
                  oldY = y;
                  int Y1 = 3;
                  int Y2 = 38;
                  int Y3 = 32;
                  int Y4 = 67;
                  if (suit == 'H'){
                      y += 10;
                      
                      Y3 -= 2;
                      Y4 -=5;
                  } else if (suit == 'S'){
                      Y4-=5; 
                      Y3-=5; 
                      Y1+=5; 
                      Y2+=5; 
                  } else if (suit == 'C'){
                      Y4-=3; 
                      Y3-=3; 
                      Y1+=3; 
                      Y2+=3; 
                  } else if (suit == 'D'){
                      y += 8;
                  }
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 + Y1, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 + Y2, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 - Y3, suit);
                  draw_symbol(x - 22 + card_width / 2, y + card_height / 2 - Y4, suit);
                  
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 + Y1, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 + Y2, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 - Y3, suit);
                  draw_symbol(x + 22 + card_width / 2, y + card_height / 2 - Y4, suit);
                  
                  Y1 = 45;
                  Y2 = 25;
                  if (suit == 'H'){
                      y -= 5;
                      Y1 -= 3;
                  } else if (suit == 'S'){
                      Y1 -= 1;
                      Y2 += 1;
                  } else if (suit == 'D'){
                      y -= 3;
                  }
                  
                  draw_symbol(x + card_width / 2, y + card_height / 2 - Y1, suit);
                  draw_symbol(x + card_width / 2, y + card_height / 2 + Y2, suit);
                  y = oldY;
            break;
            default:
                 draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);
            break;
        }
      gfx_color(0, 0, 0);  
      gfx_rectangle(x, y, card_width, card_height);
      gfx_rectangle(x-1, y-1, card_width, card_height);
    }
    gfx_flush();
}

void clear_text(char* player){
  gfx_color(25,70,25);

  int i, j, x, y;
    
    
  if (strcmp("Person", player) == 0){
      x = 610;
      y = 640;
  } else if (strcmp("Dealer", player) == 0){
      x = 610;
      y = 95;
  }
  for (int i = x-14; i<= x+75; i++){
      for (int j = y; j>=y-40; j--){
          gfx_point(i, j);
      }
}
  gfx_flush();
}


void draw_button(int x, int y, char *text) {
    
    gfx_color(25, 80, 25);
    gfx_fillcircle(x, y, 100);

    gfx_color(0, 0, 0);
    gfx_circle(x, y, 100);
    gfx_circle(x, y, 120);

    
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

    
    saveDeckToFile("NewDeck.txt", deck);
}

void shuffleCards(Card deck[52]) {
    srand(time(NULL)); 
    
    
    
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    
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



bool hasEnoughCards(int topCardIndex) {
    return (52 - topCardIndex) >= 10;
}


void displayHands(Card playerHand[], int playerHandSize, Card dealerHand[], int dealerHandSize, int playerTotal, int dealerTotal) {
    
    
    bool playerDuality = false;
    bool dealerDuality = false;

    int maxHandSize = (playerHandSize > dealerHandSize) ? playerHandSize : dealerHandSize;

    printf("\nPlayers's Hand:         \t\tDealer's Hand      ");
    printf("\n---------------         \t\t-------------     ");
    printf("\n");
    int pIter = 0;
    int dIter = 0;
    for (int i = 0; i < maxHandSize; i++) {
        
        if (i < playerHandSize) {
              printf("%i: %s of %s", i + 1, playerHand[i].faceValue, playerHand[i].suit);
              int drawnValue = playerHand[i].cardValue;
              if (strcmp(playerHand[i].faceValue, "Jack") == 0){
                  drawnValue = 12;
              } else if (strcmp(playerHand[i].faceValue, "Queen") == 0){
                  drawnValue = 13;
              } else if (strcmp(playerHand[i].faceValue, "King") == 0){
                  drawnValue = 14;
              }
              gfx_flush();
              draw_card("Person", pIter, drawnValue, playerHand[i].suit[0]);
              
              pIter++;
            
            if (strcmp(playerHand[i].faceValue, "Ace") == 0 && playerHand[i].cardValue == 11) {
                playerDuality = true;
            }
        } else {
            printf("                   ");  
        }

        printf("    \t\t\t");

        
        if (i < dealerHandSize) {
            printf("%i: %s of %s", i + 1, dealerHand[i].faceValue, dealerHand[i].suit);
            int drawnValue = dealerHand[i].cardValue;
            if (strcmp(dealerHand[i].faceValue, "Jack") == 0){
                drawnValue = 12;
            } else if (strcmp(dealerHand[i].faceValue, "Queen") == 0){
                drawnValue = 13;
            } else if (strcmp(dealerHand[i].faceValue, "King") == 0){
                drawnValue = 14;
            }
            draw_card("Dealer", dIter, drawnValue, dealerHand[i].suit[0]);
            dIter++;
            if (strcmp(dealerHand[i].faceValue, "Ace") == 0 && dealerHand[i].cardValue == 11) {
                dealerDuality = true;
            }
        }

        printf("\n");  
    }

    if (playerDuality == true){
        printf("Total: %d or %d", playerTotal-10, playerTotal);
        int valX = (((1280/2)+(1280/2))/2)-25;
        if (playerTotal/10 == 2){
            valX -= 4; //- Offset;
        }
        draw_value("Person", playerTotal, valX, 1);
    } else {
        printf("Total: %d", playerTotal);
        draw_value("Person", playerTotal, ((1280/2)+(1280/2))/2, 0);
    }

    if (dealerDuality == true){
        int valX = (((1280/2)+(1280/2))/2)-25;
        if (dealerTotal/10 == 2){
            valX -= 4;
        }
        draw_value("Dealer", dealerTotal, valX, 1);
        printf("\t\t\t\tTotal: %d or %d", dealerTotal-10, dealerTotal);
    } else {
        draw_value("Dealer", dealerTotal, ((1280/2)+(1280/2))/2, 0);
        printf("\t\t\t\tTotal: %d", dealerTotal);
    }

    gfx_flush();

    

    printf("\n");
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


int determineWinner(int playerTotal, int dealerTotal, bool playerBlackjack, bool dealerBlackjack) {
    gfx_color(53, 101, 77);
    gfx_fillrectangle((1280/2)-300, (830/2)-250, 600, 125);
    gfx_color(0, 0, 0);
    gfx_rectangle((1280/2)-300, (830/2)-250, 600, 125);

    int midTextX, midTextY;
    midTextX = -125 + (((1280/2)-300)+((1280/2)+300))/2;
    midTextY = -130 + (((830/2)-250) + ((830/2)+180))/2;

    if (playerBlackjack && dealerBlackjack) {
        printf("Both player and dealer have Blackjack! It's a draw.\n");
        gfx_text("Both player and dealer have Blackjack!", midTextX-80, midTextY-40, 2);
    } else if (playerBlackjack) {
        printf("Player has Blackjack! Player wins.\n");
        gfx_text("Player has Blackjack! Player wins.", midTextX-80, midTextY-40, 2);
        return 0;
    } else if (dealerBlackjack) {
        printf("Dealer has Blackjack! Dealer wins.\n");
        gfx_text("Dealer has Blackjack! Dealer wins.", midTextX-80, midTextY-40, 2); 
        return 1;
    } else if (playerTotal > 21 && dealerTotal > 21) {
        printf("Both player and dealer bust! No one wins.\n");
        gfx_text("Both player and dealer bust! No one wins.", midTextX-120, midTextY-30, 2); 
    } else if (playerTotal > 21) {
        printf("Player busts! Dealer wins.\n");
        gfx_text("Player busts! Dealer wins.", midTextX-30, midTextY-30, 2);
        return 1;
    } else if (dealerTotal > 21) {
        printf("Dealer busts! Player wins.\n");
        gfx_text("Dealer busts! Player wins.", midTextX-30, midTextY-30, 2); 
        return 0;
    } else if (playerTotal > dealerTotal) {
        printf("Player wins with %d against dealer's %d.\n", playerTotal, dealerTotal);
        gfx_text("Player wins! Dealer loses.", midTextX-30, midTextY-30, 2);
        return 0;
    } else if (dealerTotal > playerTotal) {
        printf("Dealer wins with %d against player's %d.\n", dealerTotal, playerTotal);
        gfx_text("Dealer wins! Player loses.", midTextX-30, midTextY-30, 2);
        return 1;
    } else {
        printf("It's a draw with both having %d.\n", playerTotal);
        gfx_text("It's a draw.", midTextX+50, midTextY-30, 2);
    }
    gfx_flush();
    return 3;
}



int createHelpScreen(int x, int y){
    int oldx, oldy;
    oldx = x; oldy = y;

    gfx_clear_color(53, 101, 77);
    gfx_clear();

    gfx_color(137, 207, 240);
    gfx_fillrectangle((x/2)-500,(y/2)-400, 1000, 800);

    gfx_color(0, 0, 0);
    gfx_text("Blackjack", (x/2)-55, (y/2)-357, 2);

    gfx_text("How to Play Blackjack", (x/2)-105, (y/2)-275, 1);

    gfx_text("Blackjack is a popular card game played between the player and the dealer.", 300, (y/2)-245, 1);

    gfx_text("The goal is to have a hand value that is closer to 21 than the other player.", 300, (y/2)-215, 1);

    gfx_text("Card Values", 300, 250, 1);
    gfx_text("- Number Cards (2-10): Face value (e.g., 2 is worth 2 points)", 315, 280, 1);
    gfx_text("- Face Cards (J, Q, K): Worth 10 points each.", 315, 310, 1);
    gfx_text("- Aces: Can be worth either 1 point or 11 points.", 315, 340, 1);

    gfx_text("Game Setup", 300, 380, 1);
    gfx_text("1. Starting the Game: Click \"Start Game\" to begin.", 315, 410, 1);
    gfx_text("2. Dealing: You and the dealer will receive two cards. Both face-up.", 315, 440, 1);
    gfx_text("   Your cards and the dealers' are face-up.", 315, 457, 1);

    gfx_text("Player Actions", 300, 510, 1);
    gfx_text("- Hit: Click \"Hit\" to receive an additional card.", 315, 540, 1);
    gfx_text("- Stand: Click \"Stand\" when you want to end your turn.", 315, 570, 1);

    gfx_text("Dealer's Rules", 300, 640, 1);
    gfx_text("- The dealer must hit if their total is 16 or less.", 315, 670, 1);
    gfx_text("- The dealer must stand if their total is 17 or higher.", 315, 700, 1);

    gfx_line((x/2)-59, (y/2)-330, (x/2)+54, (y/2)-330);

    int card_width = 100;
    int card_height = 150;
    
    x = -150;
    y = 175;
    int value = 11;
    char suit = 'S';

    x = x + (MAX_CARDS / 2) * (card_width + 10);
    draw_card_outline(x, y, card_width, card_height);

    int r, g, b;
    r = 0; g = 0; b = 0;

    draw_large_A(x + 5, y + 3, r, g, b);
    draw_large_A(x + card_width - 12, y + card_height - 19, r, g, b);
    gfx_color(0, 0, 0);
    gfx_rectangle(x, y, card_width, card_height);
    gfx_rectangle(x-1, y-1, card_width, card_height);
    draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);

    x = -150;
    y = 375;
    value = 8;
    suit = 'H';

    
    x = x + (MAX_CARDS / 2) * (card_width + 10);
    draw_card_outline(x, y, card_width, card_height);

    r = 255; g = 0; b = 0;

    draw_number_or_letter(x + 5, y + 5, r, g, b, value);
    draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);

    gfx_color(0, 0, 0);
    gfx_rectangle(x, y, card_width, card_height);
    gfx_rectangle(x-1, y-1, card_width, card_height);

    draw_symbol(x - 20 + card_width / 2, y + card_height / 2 + 30, suit);
    draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 50, suit);
    draw_symbol(x - 20 + card_width / 2, y + card_height / 2 - 10, suit);
    
    draw_symbol(x + card_width / 2, y + card_height / 2 - 30, suit);
    draw_symbol(x + card_width / 2, y + card_height / 2 + 10, suit);
    
    draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 10, suit);
    draw_symbol(x + 20 + card_width / 2, y + card_height / 2 + 30, suit);
    draw_symbol(x + 20 + card_width / 2, y + card_height / 2 - 50, suit);

    x = -150;
    y = 575;

    x = x + (MAX_CARDS / 2) * (card_width + 10);
    draw_card_outline(x, y, card_width, card_height);
    
    r = 255; g = 0; b = 0;
    value = 14;
    suit = 'D';

    gfx_color(r, g, b);
    gfx_rectangle(x+10, y+20, card_width-20, card_height-40);
    
    draw_number_or_letter(x + 5 + 10, y + card_height - 15 - 20, r, g, b, value);
    draw_number_or_letter(x + card_width - 13 - 10, y + 5 + 20, r, g, b, value);
    
    draw_number_or_letter(x + 5, y + 5, r, g, b, value);
    draw_number_or_letter(x + card_width - 13, y + card_height - 15, r, g, b, value);
    draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);

    gfx_color(0, 0, 0);
    gfx_rectangle(x, y, card_width, card_height);
    gfx_rectangle(x-1, y-1, card_width, card_height);
    x = oldx; y = oldy;
    gfx_rectangle((x/2)-475,(y/2)-375, 120, 60);
    gfx_text("<- Back", (x/2)-460, (y/2)-357, 2);
    gfx_flush();
    
    while (1){
        int c = gfx_wait();
        if (c == 1){
            int xpos, ypos;

            xpos = gfx_xpos();
            ypos = gfx_ypos();
            if (xpos >= 165 && xpos <= 285){
                if (ypos >= 40 && ypos <= 100) {
                    gfx_clear_color(128, 128, 128);
                    gfx_clear();
                    return 1;
                }
            }
        }
    }
}


int createCreditsScreen(int x, int y){

    gfx_clear_color(53, 101, 77);
    gfx_clear();

    gfx_color(137, 207, 240);
    gfx_fillrectangle((x/2)-250,(y/2)-200, 500, 400);

    gfx_color(0, 0, 0);
    gfx_text("Credits", (x/2)-55, (y/2)-357/2, 2);

    int midX = 680;
    gfx_text("Game Developer    -    Mohammad Shebaro", midX-235, ((y/2)-245/2) + 25, 1);
    gfx_text("Game Designer     -    Mohammad Shebaro", midX-235, ((y/2)-215/2) + 55, 1);
    gfx_text("Graphic Artist    -    Mohammad Shebaro", midX-235, ((y/2)-185/2) + 85, 1);
    gfx_text("Quality Assurance -    Mohammad Shebaro", midX-235, ((y/2)-155/2) + 115, 1);
    gfx_text("Project Manager   -    Mohammad Shebaro", midX-235, ((y/2)-125/2) + 145, 1);
    gfx_text("     (Mohammad Shebaro - 24004149)     ", midX-235, ((y/2)-125/2) + 175, 1);

    gfx_rectangle((x/2)-475/2,(y/2)-375/2, 120, 60);
    gfx_text("<- Back", ((x/2)-460/2)+10, (y/2)-(357/2)+10, 2);
    gfx_flush();
    
    while (1){
        int c = gfx_wait();
        if (c == 1){
            int xpos, ypos;

            xpos = gfx_xpos();
            ypos = gfx_ypos();
            printf("%i %i \n", xpos, ypos);
            if (xpos >= 404 && xpos <= 523){
                if (ypos >= 230 && ypos <= 290) {
                    gfx_clear_color(128, 128, 128);
                    gfx_clear();
                    return 1;
                }
            }
        }
    }
}



typedef struct {
    int x, y;
} Point;

Point interpolate(Point start, Point end, float t) {
    Point p;
    p.x = (int)(start.x * (1 - t) + end.x * t); 
    p.y = (int)(start.y * (1 - t) + end.y * t); 
    return p;
}

Point bezier(Point p0, Point p1, Point p2, float t) {
    Point p;
    p.x = (int)((1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x);
    p.y = (int)((1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y);
    return p;
}

void drawCurve(Point start, Point control, Point end, int steps) {
    for (int i = 0; i <= steps; i++) {
        float t = (float)i / steps; 
        Point p = bezier(start, control, end, t); 
        gfx_line(p.x, p.y, p.x + 1, p.y + 1); 
    }
}

void characterDesign(char value){
    gfx_color(0, 0, 0);
    
    

    switch (value){
        case 'X':
            
            gfx_line((1280/2)-300+20, 275, (1280/2)-350+20, 250);
            gfx_line((1280/2)+300, 275, (1280/2)+350, 250);

            gfx_line(290+20, 250, 305+20, 285);
            gfx_line(990, 250, 980, 285);

            gfx_line(305+20, 285, 275+20, 290);
            gfx_line(980, 285, 1005, 290);

            gfx_line(275+20, 290, 320+20, 315);
            gfx_line(1005, 290, 960, 315);

            gfx_line(340+20, 275, 325+20, 280);
            gfx_line(325+20, 280, 315+20, 342);

            gfx_line(315+20, 343, 326+20, 346);
            gfx_line(326+20, 346, 346+20, 350);

            gfx_line(325+20, 280, 340+15, 285);
            gfx_line(340+20, 276, 338+20, 284);

            gfx_line(940, 275, 953, 279);

            gfx_line(953, 279, 941, 285);

            gfx_line(953, 279, 964, 344);
            
            gfx_line(940, 277, 941, 286);

            gfx_line(964, 345, 934, 349);

            Point s1 = {942, 285};
            Point c1 = {(942+357)/2, 325};
            Point e1 = {357, 285};
            drawCurve(s1, c1, e1, 100);

            Point s2 = {934, 350};
            Point c2 = {(934+366)/2, 377};
            Point e2 = {366, 351};
            drawCurve(s2, c2, e2, 100);
            break;
        case 'I':
            int x, y;
            x = 363; y = 303;
        
            gfx_line(x, y-5, x + 30, y);  
            
            
            gfx_line(378, 301, 371, 339);
            
            
            gfx_line(356, 338, 386, 343);
            break;
        case 'N':
            gfx_line(398, 347, 404, 304);

            gfx_line(405, 304, 419, 348);

            gfx_line(419, 348, 424, 309);

            gfx_line(570, 315, 570, 355);

            gfx_line(570, 355, 546, 315);

            gfx_line(545, 315, 545, 355);
            break;
        case 'S':
           int Scoordinates[7][2] = {
            {456, 310},
            {439, 307},
            {436, 331},
            {453, 332},
            {451, 351},
            {432, 349},
            {433, 347}
        };

            for (int i = 0; i < 5; i++) {
                gfx_line(Scoordinates[i][0], Scoordinates[i][1], Scoordinates[i+1][0], Scoordinates[i+1][1]);
            }

            gfx_line(750, 319, 733, 319);
            gfx_line(733, 319, 733, 338);
            gfx_line(733, 338, 751, 338);
            gfx_line(751, 338, 751, 356);
            gfx_line(751, 356, 733, 356);

            gfx_line(570, 0, 570, 87);
            gfx_line(570, 87, 638, 116);
            gfx_line(638, 116, 706, 87);
            gfx_line(706, 87, 706, 0);

            break;
        case 'U':
            gfx_line(467, 311, 462, 351);
            gfx_line(462, 351, 483, 353);
            gfx_line(483, 353, 486, 315);
            break;
        case 'R':

            gfx_line(490, 353, 494, 313);

            gfx_line(494, 313, 515, 316);
            gfx_line(515, 316, 514, 334);
            gfx_line(514, 334, 493, 331);

            gfx_line(494, 333, 510, 355);

            break;
        case 'A':
            gfx_line(515, 355, 530, 315);
            gfx_line(530, 315, 540, 355);
            gfx_line(540, 355, 535, 335);
            gfx_line(535, 335, 523, 335);

            gfx_line(686, 339, 696, 339);
            gfx_line(681, 357, 690, 316);
            gfx_line(690, 316, 701, 356);

        break;
        case 'C':
            gfx_line(605, 315, 580, 315);
            gfx_line(580, 315, 580, 355);
            gfx_line(580, 355, 605, 355);
        break;
        case 'E':
            gfx_line(635, 315, 615, 315);
            gfx_line(615, 315, 615, 355);
            gfx_line(615, 355, 635, 355);

            gfx_line(615, 335, 635, 335);
        break;
        case 'P':
            gfx_line(655, 357, 655, 315);
            gfx_line(655, 315, 674, 315);
            gfx_line(674, 315, 674, 335);
            gfx_line(674, 335, 655, 335);
            break;
        case 'Y':
            gfx_line(716, 337, 716, 355);
            gfx_line(716, 337, 706, 318);
            gfx_line(716, 335, 723, 317);
            break;
        case 'L':
            gfx_line(766, 318, 785, 318);
            gfx_line(785, 317, 785, 336);
            gfx_line(785, 337, 767, 337);
            gfx_line(768, 339, 768, 357);
            gfx_line(768, 357, 786, 355);

            gfx_line(795, 339, 817, 338);

            gfx_line(821, 317, 850, 315);
            gfx_line(835, 317, 836, 351);

            gfx_line(859, 315, 878, 313);
            gfx_line(879, 313, 882, 347);
            gfx_line(882, 347, 861, 350);
            gfx_line(861, 352, 859, 314);

            gfx_line(888, 334, 910, 329);

            gfx_line(918, 344, 946, 341);
            gfx_line(914, 319, 930, 307);
            gfx_line(930, 307, 932, 344);
            break;
    }

}


int createMenu(int x, int y){
    while (1){
        int scaleX = 200;
        int scaleY = 60;

        gfx_color(255, 255, 255);
        
        int buttonXAlignment = (x/2)-25;
        

        
        int middleYOffset = (y);
        for (int j=0; j<=10; j++){
            for (int i=0; i<=6; i++){
                gfx_rectangle(-50+125*j, -50-(50*j)+225*i, 100, 200);
            }
        }
        for (int i=0; i<6; i++){
        middleYOffset+=400;
        
        gfx_color(53, 101, 77);
        gfx_fillrectangle((x/2)-scaleX, (y/2)-scaleY-200, 400, 600);
        gfx_color(0, 0, 0);

        gfx_rectangle((x/2)-scaleX, (y/2)-scaleY-200, 400, 600);
        }
        

        
        gfx_color(0, 0, 0);      
        gfx_text("A Blackjack Experience", (x/2)-135, y-590, 2);

        gfx_color(0, 0, 0);
        gfx_rectangle((x/2)-scaleX/2, y-500, scaleX, scaleY);
        gfx_text("Start", buttonXAlignment, y-485, 2);
        gfx_rectangle((x/2)-scaleX/2, y-400, scaleX, scaleY);
        gfx_text("Help", buttonXAlignment+4, y-385, 2);
        gfx_rectangle((x/2)-scaleX/2, y-300, scaleX, scaleY);
        gfx_text("Credits", buttonXAlignment-15+2, y-285, 2);
        gfx_rectangle((x/2)-scaleX/2, y-200, scaleX, scaleY);
        gfx_text("Exit", buttonXAlignment-15+19, y-185, 2);
        gfx_color(255, 255, 255);

        while (1){
            int c = gfx_wait();
            if (c == 1){
                int xPos = gfx_xpos();
                int yPos = gfx_ypos();
                
                printf("X: %i; Y: %i\n", xPos, yPos);
                if (xPos >= 540 && xPos <= 740){
                    if(yPos >= 330 && yPos <= 390){
                        return 1;
                    } else if(yPos >= 440 && yPos <= 490){
                        int ret = createHelpScreen(x, y);
                        if (ret == 1){break;}
                    } else if(yPos >= 530 && yPos <= 590){
                        int ret = createCreditsScreen(x, y);
                        if (ret == 1){break;}
                    } else if(yPos >= 630 && yPos <= 690){
                        return 0;
                    }
                }
            }

        
        }
    }
}


int main(){
    int screenX = 1280;
    int screenY = 830;

    gfx_open(screenX, screenY, "A Blackjack Experience");

    while (1){

    int playerScore = 0;
    int dealerScore = 0;

    gfx_clear_color(128, 128, 128);
    gfx_clear();
    
    
    int ret = createMenu(screenX, screenY);
    if (ret != 1) {return 1;}

        Card deck[52];
        int topCardIndex = 0;

        
        createDeck(deck);
        shuffleCards(deck);

        
        readDeckFromFile("NewDeck.txt", deck);
        readDeckFromFile("ShuffledDeck.txt", deck);

        
        while (1) {
            draw_P = 0;
            draw_D = 0;

            gfx_clear_color(128, 128, 128);
            gfx_clear();
            gfx_flush();

            
            for (int x = 0; x < screenX; x++) {
                for (int y = 0; y < screenY; y++) {
                    if (((x / 20) % 2 == 0 && (y / 20) % 2 == 0) || ((x / 20) % 2 == 1 && (y / 20) % 2 == 1)) {
                        gfx_color(20, 85, 20);  
                    } else {
                        gfx_color(30, 100, 30);  
                    }
                    gfx_point(x, y);
                }
            }

            gfx_flush();

            
            int center_x = 650;
            int center_y = 375;
            int radius_x = 500;
            int radius_y = 350;

            int border_thickness = 30;
            int i = 29;
            gfx_color(0,0,0);
            printf("%i\n", i);


            radius_x += 5;
            radius_y += 5;

            for (int x = center_x - (radius_x + i); x <= center_x + (radius_x + i); x++) {
                for (int y = center_y; y <= center_y + (radius_y + i) * sqrt(1 - ((x - center_x) * (x - center_x)) / (double)((radius_x + i) * (radius_x + i))); y++) {
                    gfx_point(x, y);
                }
            }

            radius_x += 28;
            radius_y += 28;
            for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
                for (int y = 0; y <= center_y; y++) {
                    gfx_point(x, y);
                }
            }

            gfx_flush();

            radius_x = 500;
            radius_y = 350;

            gfx_color(81, 51, 17);

            for (int x = center_x - (radius_x + i); x <= center_x + (radius_x + i); x++) {
                for (int y = center_y; y <= center_y + (radius_y + i) * sqrt(1 - ((x - center_x) * (x - center_x)) / (double)((radius_x + i) * (radius_x + i))); y++) {
                    gfx_point(x, y);
                }
            }
            

            radius_x += 30;
            radius_y += 30;

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


            gfx_flush();

            radius_x = 500;
            radius_y = 350;

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

            gfx_flush();

            characterDesign('X');
            characterDesign('I');
            characterDesign('N'); // Double Case
            characterDesign('S');
            characterDesign('U');
            characterDesign('R');
            characterDesign('A');
            characterDesign('C');
            characterDesign('E');
            characterDesign('P');
            characterDesign('Y');
            characterDesign('L');

            gfx_color(255, 255, 0);
            for (int i = 0; i <= 80; i++){
                gfx_point(135, 5*i);
            }

            gfx_color(0, 0, 0);
            char DisplayedScore[30];
            sprintf(DisplayedScore, "(Player) %d - %d (Dealer)", playerScore, dealerScore);
            gfx_text(DisplayedScore, 800, 20, 2);
            gfx_flush();

            
            draw_button((screenX/2)-110, 600, "Stand");
            draw_button((screenX/2)+110, 600, "Hit");
            
            
            int x_between = ((screenX/2)+(screenX/2))/2;
            gfx_text("Total:", x_between-33, 570, 2);
            gfx_line(x_between-33, 595, x_between+37, 595);

            gfx_text("Total:", x_between-33, 20, 2);
            gfx_line(x_between-33, 45, x_between+37, 45);
        
            

            if (!hasEnoughCards(topCardIndex)) {
                printf("Not enough cards in the deck. Creating and shuffling a new deck.\n");
                createDeck(deck);
                shuffleCards(deck);
                topCardIndex = 0;
            }


            
            Card playerHand[52];
            Card dealerHand[52];
            int playerHandSize = 0;
            int dealerHandSize = 0;

            gfx_color(249, 199, 12);
            gfx_rectangle(510, 375, 110, 160);
            gfx_rectangle(510, 115, 110, 160);

            
            dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
            dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);
            dealCards(deck, &topCardIndex, playerHand, &playerHandSize);
            dealCards(deck, &topCardIndex, dealerHand, &dealerHandSize);

            
            int playerTotal = calculateTotalValue(playerHand, playerHandSize, true);
            int dealerTotal = calculateTotalValue(dealerHand, dealerHandSize, false);

            
            displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
            

            
            bool playerBlackjack = checkBlackjack(playerTotal);
            bool dealerBlackjack = checkBlackjack(dealerTotal);
            char choice;

            if (playerBlackjack || dealerBlackjack) {
                int Winner = determineWinner(playerTotal, dealerTotal, playerBlackjack, dealerBlackjack);
                if (Winner == 0){
                    playerScore += 1;
                } else if (Winner == 1){
                    dealerScore += 1;
                }
            } else {
                while (1) {
                    gfx_text("Turn: Player (YOU)", 250, 20, 2);
                    printf("\nDo you want to Hit or Stand? (h/s): ");
                    while (1) {
                        char c = gfx_wait();
                        if (c == 1) {
                            printf("%d %d\n", gfx_xpos(), gfx_ypos());
                            int xPos = gfx_xpos();
                            int yPos = gfx_ypos();
                            int standButtonX = (screenX / 2) - 110;
                            int hitButtonX = (screenX / 2) + 110;
                            int detectRad = 50;
                            
                            double standDist = sqrt((xPos - standButtonX) * (xPos - standButtonX) + (yPos - 600) * (yPos - 600));
                            double hitDist = sqrt((xPos - hitButtonX) * (xPos - hitButtonX) + (yPos - 600) * (yPos - 600));

                            if (standDist <= detectRad) {
                                
                                choice = 'S';
                                break;
                            } else if (hitDist <= detectRad) {
                                
                                choice = 'H';
                                break;
                            }
                        }
                    }
                    
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
                        gfx_color(25, 70, 25);
                        gfx_fillrectangle(250, 20, 300, 30);
                        gfx_flush();
                        gfx_color(0, 0, 0);
                        gfx_text("Turn: Dealer (BOT)", 250, 20, 2);
                        gfx_flush();
                        printf("Player stands.\n");
                        break;
                    } else {
                        printf("Invalid choice. Please enter 'h' to Hit or 's' to Stand.\n");
                    }
                }
                bool d_hasAceSave = false;

                    
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

                    
                    displayHands(playerHand, playerHandSize, dealerHand, dealerHandSize, playerTotal, dealerTotal);
                    gfx_flush();
                    
                    int Winner = determineWinner(playerTotal, dealerTotal, playerBlackjack, dealerBlackjack);
                    if (Winner == 0){
                        playerScore += 1;
                    } else if(Winner == 1){
                        dealerScore += 1;
                    }
                
            }
            
            
            printf("\nDo you want to start a new round? (y/n): ");
            
            gfx_color(53, 101, 77);
            gfx_fillrectangle((1280/2)-150, (830/2)-120, 300, 250);
            gfx_color(0, 0, 0);
            gfx_rectangle((1280/2)-150, (830/2)-120, 300, 250);

            gfx_text("Would you like to start", 505, 330, 2);
            gfx_text("a new game?", 580, 360, 2);

            gfx_text("YES", (515+40), 480, 2);
            gfx_rectangle(515, 465, 115, 50);
            
            


            gfx_text("NO", (575+120), 480, 2);
            gfx_rectangle(515+115+15, 465, 115, 50);
            
            

            gfx_flush();
            
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
            }*/
            int exitGame = 0;
            while(1){
                int c = gfx_wait();
                if (c==1){
                    int x, y;
                    x = gfx_xpos();
                    y = gfx_ypos();
                    if (y >= 465 && y<= 515){
                        if (x >= 515 && x <= 630){
                            break;
                        } else if (x >= 645 && x <= 760){
                            remove("NewDeck.txt");
                            remove("ShuffledDeck.txt");
                            exitGame = 1;
                            break;
                        }
                    }
                }
            };
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

        
        fgets(currentCommand, sizeof(currentCommand), stdin);

        
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
