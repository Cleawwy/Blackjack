#include <stdio.h>
#include "gfx.h"
#include <math.h>
#include <stdlib.h>

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
void draw_card(int x, int y, int width, int height, char value, char suit) {
    // Step 1: Draw the card outline
    draw_card_outline(x, y, width, height);

    // Step 2: Set color for 'A'
    int r, g, b;
    if (suit == 'H' || suit == 'D') {
        r = 255; g = 0; b = 0;
    } else {
        r = 0; g = 0; b = 0;
    }

    // Step 3: Draw the value 'A' in the top-left and bottom-right corners
    if (value == 'A') {
        draw_large_A(x + 5, y + 5, r, g, b);  // Top-left, closer to edge
        draw_large_A(x + width - 14, y + height - 19, r, g, b);  // Bottom-right, closer to edge
    }

    // Step 4: Draw the suit symbol in the middle of the card
    draw_symbol(x + width / 2, y + height / 2 - 5, suit);
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

    // Draw four cards: Ace of Hearts, Ace of Spades, Ace of Clubs, Ace of Diamonds
    int card_width = 100;
    int card_height = 150;
    draw_card(250, 100, card_width, card_height, 'A', 'H');  // Ace of Hearts
    draw_card(400, 100, card_width, card_height, 'A', 'S');  // Ace of Spades
    draw_card(550, 100, card_width, card_height, 'A', 'C');  // Ace of Clubs
    draw_card(700, 100, card_width, card_height, 'A', 'D');  // Ace of Diamonds

    while (1) {
        char c = gfx_wait();
        if (c == 1) {
            printf("%d %d\n", gfx_xpos(), gfx_ypos());
        }
    }

    return 0;
}

