#ifndef LED_H
#define LED_H

void moveLEDup (char led[][220], int time, int color);
void moveLEDdown (char led[][220], int time, int clolr);
void moveLEDleft (char led[][220], char col[][1], int len, int time, int color);
void moveLEDright (char led[][220], char col[][1], int len, int time, int color);

#endif
