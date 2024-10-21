#include "gfx.h"

void draw_card(int x, int y, char *number, char *suit, int suit_type) {
    // Draw the card background
    gfx_color(255, 255, 255); // White color
    gfx_fillrectangle(x, y, 100, 150); // Card dimensions

    // Draw the card border
    gfx_color(0, 0, 0); // Black color
    gfx_rectangle(x, y, 100, 150);

    // Draw top left number
    gfx_color(0, 0, 0); // Black color
    gfx_text(number, x + 5, y + 20, 1); // Top left corner
    gfx_text(suit, x + 5, y + 40, suit_type); // Suit shape under the number

    // Draw bottom right number
    gfx_text(number, x + 75, y + 130, 1); // Bottom right corner
    gfx_text(suit, x + 75, y + 110, suit_type); // Suit shape on top of the number
}

void draw_suit(int x, int y, int suit_type) {
    switch (suit_type) {
        case 0: // Hearts
            gfx_color(255, 0, 0); // Red color
            gfx_fillcircle(x, y - 10, 10); // Heart shape part 1
            gfx_fillcircle(x - 10, y, 10); // Heart shape part 2
            gfx_fillcircle(x + 10, y, 10); // Heart shape part 3
            gfx_fillrectangle(x - 5, y, 10, 20); // Heart shape stem
            break;
        case 1: // Diamonds
            gfx_color(255, 0, 0); // Red color
            gfx_fillrectangle(x, y - 20, 20, 40); // Diamond shape
            gfx_fillrectangle(x - 10, y - 10, 40, 20); // Diamond shape
            break;
        case 2: // Clubs
            gfx_color(0, 0, 0); // Black color
            gfx_fillcircle(x, y - 10, 10); // Club shape part 1
            gfx_fillcircle(x - 10, y, 10); // Club shape part 2
            gfx_fillcircle(x + 10, y, 10); // Club shape part 3
            gfx_fillrectangle(x - 5, y, 10, 20); // Club shape stem
            break;
        case 3: // Spades
            gfx_color(0, 0, 0); // Black color
            gfx_fillcircle(x, y - 10, 10); // Spade shape part 1
            gfx_fillcircle(x - 10, y, 10); // Spade shape part 2
            gfx_fillcircle(x + 10, y, 10); // Spade shape part 3
            gfx_fillrectangle(x - 5, y, 10, 20); // Spade shape stem
            break;
    }
}

int main() {
    gfx_open(800, 600, "Playing Cards");

    // Draw cards for each suit
    draw_card(100, 100, "A", "♥", 0); // Heart
    draw_card(250, 100, "A", "♦", 1); // Diamond
    draw_card(400, 100, "A", "♣", 2); // Club
    draw_card(550, 100, "A", "♠", 3); // Spade

    gfx_flush();
    gfx_wait(); // Wait for a key press before closing

    return 0;
}
