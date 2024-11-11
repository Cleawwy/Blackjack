#include <stdio.h>
#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 6

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
        {{0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 4
        {{0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0, 0},
         {0, 0, 1, 0, 1, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 5
        {{1, 1, 1, 1, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
        // 6
        {{0, 0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 1, 0},
         {0, 1, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 1, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}},
          // 7
        {{1, 1, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
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
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1}
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


// Function to draw the card with value and suit
/*void draw_card(int x, int y, int width, int height, int value, char suit) {
    // Step 1: Draw the card outline
    draw_card_outline(x, y, width, height);

    // Step 2: Set color for value (red for hearts and diamonds, black for others)
    int r, g, b;
    if (suit == 'H' || suit == 'D') {
        r = 255; g = 0; b = 0;
    } else {
        r = 0; g = 0; b = 0;
    }

    // Step 3: Draw the value in the top-left and bottom-right corners
    if (value >= 2 && value < 10) {
        draw_number_or_letter(x + 5, y + 5, r, g, b, value);  // Top-left
        draw_number_or_letter(x + width - 12, y + height - 15, r, g, b, value);  // Bottom-right
    } else if (value == 1){
        draw_large_A(x + 5, y + 5, r, g, b);  // Top-left
        draw_large_A(x + width - 14, y + height - 19, r, g, b);  // Bottom-right
    } else if(value == 10){
        draw_number_or_letter(x + 5, y + 5, r, g, b, value);  // Top-left
        draw_number_or_letter(x + width - 22, y + height - 15, r, g, b, value);  // Bottom-right
    }

    // Step 4: Draw the suit symbol in the middle of the card
    draw_symbol(x + width / 2, y + height / 2 - 5, suit);
}*/



void draw_card(char *player, int card_number, int value, char suit) {
    int card_width = 100;
    int card_height = 150;
    int base_x;
    int y;

    if (strcmp(player, "Dealer") == 0) {
        base_x = 550;
        y = 100;
    } else if (strcmp(player, "Person") == 0) {
        base_x = 550;
        y = 300;
    } else {
        return;
    }

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
        if (value >= 2 && value <= 10) {
            draw_number_or_letter(x + 5, y + 5, r, g, b, value);
            draw_number_or_letter(x + card_width - 12, y + card_height - 15, r, g, b, value);
        } else if (value == 1) {
            draw_large_A(x + 5, y + 5, r, g, b);
            draw_large_A(x + card_width - 14, y + card_height - 19, r, g, b);
        }

        draw_symbol(x + card_width / 2, y + card_height / 2 - 5, suit);
    }
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
}


int main() {
    int screenX = 1280;
    int screenY = 830;

    gfx_open(screenX, screenY, "A Blackjack Experience");
    gfx_clear_color(128, 128, 128);
    gfx_clear();

    // Draw the casino floor background
    for (int x = 0; x < screenX; x++) {
        for (int y = 0; y < screenY; y++) {
            if (((x / 20) % 2 == 0 && (y / 20) % 2 == 0) || ((x / 20) % 2 == 1 && (y / 20) % 2 == 1)) {
                gfx_color(105, 10, 10);  // Darker red
            } else {
                gfx_color(165, 42, 42);  // Softer red
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

    gfx_color(0, 100, 0);
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

    draw_card("Person", 1, 1, 'H');
    draw_card("Person", 2, 1, 'S');
    draw_card("Person", 3, 1, 'S');
    draw_card("Person", 4, 1, 'S');
    draw_card("Person", 5, 1, 'S');
    
    draw_card("Dealer", 1, 7, 'H');

    while (1) {
        char c = gfx_wait();
        if (c == 1) {
            //printf("%d %d\n", gfx_xpos(), gfx_ypos());
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
            } else if (hitDist <= detectRad) {
                choice = 'H';
                printf("Hit button clicked!\n");
            }
        }
    }

    return 0;
}
