// C_STATIC_H
// Only call (include) from "colour.c", not COLOUR_H

#ifndef DAVELIB_C_STATIC_H
#define DAVELIB_C_STATIC_H


extern char ansivt;

extern char FG_BLACK[8];
extern char FG_RED[8];
extern char FG_GREEN[8];
extern char FG_YELLOW[8];
extern char FG_BLUE[8];
extern char FG_MAGENTA[8];
extern char FG_CYAN[8];
extern char FG_WHITE[8];

extern char FG_BRIGHT_BLACK[8];
extern char FG_BRIGHT_RED[8];
extern char FG_BRIGHT_GREEN[8];
extern char FG_BRIGHT_YELLOW[8];
extern char FG_BRIGHT_BLUE[8];
extern char FG_BRIGHT_MAGENTA[8];
extern char FG_BRIGHT_CYAN[8];
extern char FG_BRIGHT_WHITE[8];

extern char BG_BLACK[8];
extern char BG_RED[8];
extern char BG_GREEN[8];
extern char BG_YELLOW[8];
extern char BG_BLUE[8];
extern char BG_MAGENTA[8];
extern char BG_CYAN[8];
extern char BG_WHITE[8];

extern char BG_BRIGHT_BLACK[8];
extern char BG_BRIGHT_RED[8];
extern char BG_BRIGHT_GREEN[8];
extern char BG_BRIGHT_YELLOW[8];
extern char BG_BRIGHT_BLUE[8];
extern char BG_BRIGHT_MAGENTA[8];
extern char BG_BRIGHT_CYAN[8];
extern char BG_BRIGHT_WHITE[8];

extern char NORMAL[8];





extern char BOLD[5]; // \e[1m
extern char UNDERLINE[5]; // \e[4m


// \eG "bell noise"
// \eI "tab"
// \eJ nextline (LF)
// \eM (CR) carraige return
// \eH "backspace" (moves the cursor back)


extern char CLS[5]; // \e[2J
extern char MOV_CRSR_TOPLEFT[4]; // \033[H , \e[H
extern char CLEAR_REST_OF_LINE[4]; // \e[K
extern char MOV_CRSR_DOWN_N[3+str_len_representing_num_lines]; // \e[<n>B
extern char MOV_CRSR_UP_N[3+str_len_representing_num_lines]; // \e[<n>A
extern char MOV_CRSR_LEFT_COLS[3+str_len_representing_num_cols]; // \e[<n>D
extern char MOV_CRSR_RIGHT_COLS[3+str_len_representing_num_cols]; // \e[<n>C



##endif

