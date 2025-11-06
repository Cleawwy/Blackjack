Project Title: A Blackjack Game – Created in C<br>
Author: [Cleaver](https://github.com/Cleawwy)<br>
Copyright © 2024. All rights reserved.

---

Overview:
This project is a full-featured implementation of the popular casino game Blackjack, written entirely in C. <br>
It demonstrates practical use of graphics handling, event-driven logic, and structured programming concepts. <br>
The program includes a minimal graphical interface powered by the X11 library, providing a simple yet interactive gaming experience.<br>

---

### 🧠 Skills Demonstrated

- **C Programming:** Applied core C concepts including functions, structures, loops, and conditional statements.<br>
- **Graphics Programming:** Utilized the **X11** library to handle drawing and display rendering through `gfx.c`.<br>
- **Algorithm Design:** Implemented shuffling, randomization, and decision-making algorithms.<br>
- **Memory Management:** Managed data flow efficiently between player, dealer, and deck objects.<br>
- **Game Logic & State Handling:** Clean game loop with win/loss evaluation, card value calculation, and round resets.<br>
- **Modular Programming:** Separated graphical, logical, and structural code into components.<br>
- **Event-driven Programming:** Integrated real-time player interactions.<br>

---

Compilation & Execution:<br>
Before running, ensure the X11 and math libraries are installed on your system.<br>

To compile:<br>
`gcc blackjack.c gfx.c -o blackjack.o -lX11 -lm`<br>

To execute:<br>
`./blackjack.o`<br>

---

File Structure:<br>
• blackjack.c – Main game logic and control flow. <br>
• gfx.c – Graphics utility functions for rendering and input. <br>
• gfx.h – Header file containing prototypes and constants.<br> 

---
