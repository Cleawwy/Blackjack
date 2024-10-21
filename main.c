mido@mido-VirtualBox:~/Desktop/Blackjack-main$ gcc main.c gfx.c -o main.o -lX11 -lm
main.c: In function ‘drawCard’:
main.c:161:16: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  161 |     gfx_text(x + 5, y + 15, card.faceValue);
      |              ~~^~~
      |                |
      |                int
In file included from main.c:7:
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:161:33: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  161 |     gfx_text(x + 5, y + 15, card.faceValue);
      |                             ~~~~^~~~~~~~~~
      |                                 |
      |                                 char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:161:5: error: too few arguments to function ‘gfx_text’
  161 |     gfx_text(x + 5, y + 15, card.faceValue);
      |     ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c:162:16: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  162 |     gfx_text(x + 5, y + 30, card.suit);
      |              ~~^~~
      |                |
      |                int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:162:33: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  162 |     gfx_text(x + 5, y + 30, card.suit);
      |                             ~~~~^~~~~
      |                                 |
      |                                 char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:162:5: error: too few arguments to function ‘gfx_text’
  162 |     gfx_text(x + 5, y + 30, card.suit);
      |     ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c: In function ‘drawButton’:
main.c:169:16: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  169 |     gfx_text(x + 20, y + 30, label);
      |              ~~^~~~
      |                |
      |                int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:169:30: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  169 |     gfx_text(x + 20, y + 30, label);
      |                              ^~~~~
      |                              |
      |                              const char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘const char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:169:5: error: too few arguments to function ‘gfx_text’
  169 |     gfx_text(x + 20, y + 30, label);
      |     ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c: In function ‘determineWinner’:
main.c:178:18: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  178 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player busts! Dealer wins.");
      |                  ^~
      |                  |
      |                  int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:178:41: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  178 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player busts! Dealer wins.");
      |                                         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
      |                                         |
      |                                         char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:178:9: error: too few arguments to function ‘gfx_text’
  178 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player busts! Dealer wins.");
      |         ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c:180:18: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  180 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer busts! Player wins.");
      |                  ^~
      |                  |
      |                  int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:180:41: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  180 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer busts! Player wins.");
      |                                         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
      |                                         |
      |                                         char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:180:9: error: too few arguments to function ‘gfx_text’
  180 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer busts! Player wins.");
      |         ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c:182:18: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  182 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player wins!");
      |                  ^~
      |                  |
      |                  int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:182:41: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  182 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player wins!");
      |                                         ^~~~~~~~~~~~~~
      |                                         |
      |                                         char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:182:9: error: too few arguments to function ‘gfx_text’
  182 |         gfx_text(50, WINDOW_HEIGHT / 2, "Player wins!");
      |         ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c:184:18: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  184 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer wins!");
      |                  ^~
      |                  |
      |                  int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:184:41: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  184 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer wins!");
      |                                         ^~~~~~~~~~~~~~
      |                                         |
      |                                         char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:184:9: error: too few arguments to function ‘gfx_text’
  184 |         gfx_text(50, WINDOW_HEIGHT / 2, "Dealer wins!");
      |         ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
main.c:186:18: warning: passing argument 1 of ‘gfx_text’ makes pointer from integer without a cast [-Wint-conversion]
  186 |         gfx_text(50, WINDOW_HEIGHT / 2, "It's a draw!");
      |                  ^~
      |                  |
      |                  int
gfx.h:57:21: note: expected ‘char *’ but argument is of type ‘int’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |               ~~~~~~^~~~~
main.c:186:41: warning: passing argument 3 of ‘gfx_text’ makes integer from pointer without a cast [-Wint-conversion]
  186 |         gfx_text(50, WINDOW_HEIGHT / 2, "It's a draw!");
      |                                         ^~~~~~~~~~~~~~
      |                                         |
      |                                         char *
gfx.h:57:39: note: expected ‘int’ but argument is of type ‘char *’
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |                                   ~~~~^
main.c:186:9: error: too few arguments to function ‘gfx_text’
  186 |         gfx_text(50, WINDOW_HEIGHT / 2, "It's a draw!");
      |         ^~~~~~~~
gfx.h:57:6: note: declared here
   57 | void gfx_text(char *test2, int x, int y,int sel);
      |      ^~~~~~~~
mido@mido-VirtualBox:~/Desktop/Blackjack-main$ 
