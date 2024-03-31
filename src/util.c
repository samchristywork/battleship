#include <stdio.h>

void alternate_screen() { printf("\e[?1049h"); }

void normal_screen() { printf("\e[?1049l"); }

void clear_screen() { printf("\e[1;1H\e[2J"); }

void reset_cursor() { printf("\e[1;1H"); }

void grey_text() { printf("\e[90m"); }

void reset_text() { printf("\e[0m"); }

void yellow_text() { printf("\e[93m"); }

void red_text() { printf("\e[91m"); }

void blue_text() { printf("\e[94m"); }

void invert_text() { printf("\e[7m"); }

void enable_mouse_tracking() { printf("\e[?1000h"); }

void disable_mouse_tracking() { printf("\e[?1000l"); }
