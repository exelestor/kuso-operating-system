#include <framebuffer.h>

static unsigned int current_cursor_pos = 0;

static inline void new_line()
{
    current_cursor_pos +=
            (current_cursor_pos / (SCREEN_WIDTH * 2) * SCREEN_WIDTH * 2 + SCREEN_WIDTH * 2) - current_cursor_pos;
}

unsigned int str_to_start_framebuffer(const char* str)
{
    current_cursor_pos = 0;
    unsigned int j = 0;

    volatile string vidptr = (volatile string) VIDEO_START;

    while(str[current_cursor_pos] != '\0') {
        vidptr[current_cursor_pos] = str[j];
        vidptr[current_cursor_pos + 1] = 0x07;
        ++j;
        current_cursor_pos += 2;
    }
    return j;
}

unsigned int str_to_framebuffer(const char* str)
{
    unsigned int j = 0;

    volatile string vidptr = (volatile string) VIDEO_START;

    while(str[j] != '\0') {
        if (str[j] == '\n') {
            new_line();
        } else {
            vidptr[current_cursor_pos] = str[j];
            vidptr[current_cursor_pos + 1] = 0x07;
            current_cursor_pos += 2;
        }
        ++j;
    }

    return j;
}

void clear_screen(void)
{
    volatile string vidptr = (volatile string) VIDEO_START;
    unsigned int j = 0;

    while(j < SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;
        j += 2;
    }
}

void printfb(string str)
{
    str_to_framebuffer(str);
}

void printlnfb(string str)
{
    str_to_framebuffer(str);
    str_to_framebuffer("\n");
}

void printnumfb(int i)
{
    _Bool negative;

    if (i < 0) {
        negative = 1;
        i = -i;
    }

    int c = 0;
    char buffer[25];

    if (i == 0) {
        buffer[0] = 48;
    }

    while (i > 0) {
        buffer[c] = (char) (i % 10 + 48);
        i /= 10;
        c++;
    }

    if (negative) {
        buffer[c] = '-';
        c++;
    }

    char temp;
    for (int j = 0; j < c / 2; j++) {
        temp = buffer[c - j - 1];
        buffer[c - j - 1] = buffer[j];
        buffer[j] = temp;
    }
    str_to_framebuffer(buffer);
}

void printlnnumfb(int i)
{
    printnumfb(i);
    str_to_framebuffer("\n");
}

void printcolorfb(string str, int color)
{
    unsigned int j = 0;

    volatile string vidptr = (volatile string) VIDEO_START;

    while(str[j] != '\0') {
        if (str[j] == '\n') {
            new_line();
        } else {
            vidptr[current_cursor_pos] = str[j];
            vidptr[current_cursor_pos + 1] = color;
            current_cursor_pos += 2;
        }
        ++j;
    }
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}