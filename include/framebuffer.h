#pragma once

#define VIDEO_START     0xb8000
#define SCREEN_WIDTH    80
#define SCREEN_HEIGHT   25

typedef char* string;

typedef struct {
    int     id;
    string  text;
    int     cursor_pos;
} Terminal;

unsigned int str_to_start_framebuffer(const char* str);
unsigned int str_to_framebuffer(const char* str);

void printfb(string str);
void printlnfb(string str);

void printnumfb(int i);
void printlnnumfb(int i);

void printcolorfb(string str, int color);

void clear_screen(void);