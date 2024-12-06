#ifndef BYPASS_ANSIVT_GUARD
#define BYPASS_ANSIVT_GUARD 1

extern char ansivt;
extern int colorMode();
#define colouriser colorMode
#define colourizer colouriser

// The Current Active Colour Selections.
extern char* ANSIVT_FG;
extern char* ANSIVT_BG;

// These are constant def's, the number of colours available in VT100 Emulation.
#define MAX_FG_COLORS 16
#define MAX_BG_COLORS 16

extern char* getVTCodeString( char );
extern char ResetAnsiVtCodes(char);
extern char* SetVT( char*, char* ); //fg and bg colour.
extern char* f( int sc ); // eg, +i, +b, -i, -b, and so on.
extern char* fg( char* );
extern char* bg( char* );


typedef struct {	

	char ansivt;
	char* ANSIVT_FG;
	char* ANSIVT_BG;
	
	char (*RVC)(char);
	char* (*SetVT)( char*, char* ); //fg and bg colour.

	char* (*fg)( char* );
	char* (*bg)( char* );
	char* (*f)( char* ); // eg, +i, +b, -i, -b, and so on.

	char** ANSIVT_CTABLE;

} _ANSI_;

extern _ANSI_* ANSI;

// generates the ansivt-formatted output string.
extern char* ANSIVT( char* str, char cc[], long long int offsets[], int _frees );
extern struct AVTC* ActivateColorConsole();
extern void Init_ANSIVT_CTABLE();
extern char resetAnsiVtCodes(char);
#define VTCODEWIDTH 8


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

extern char BOLD[8]; // \e[1m
extern char UNDERLINE[8]; // \e[4m
extern char TAB[8]; // \eI
extern char LINEFEED[8]; // \eJ
extern char CARRAIGERETURN[8]; // \eM
extern char CRSRBACKSPACE[8]; // \eH
extern char BELL[8]; // \eG

#define str_len_representing_num_cols 2
#define str_len_representing_num_lines 3
extern char CLS[8]; // \e[2J
extern char MOV_CRSR_TOPLEFT[8]; // \033[H , \e[H
extern char CLEAR_REST_OF_LINE[8]; // \e[K
extern char MOV_CRSR_DOWN_N[3+str_len_representing_num_lines]; // \e[<n>B
extern char MOV_CRSR_UP_N[3+str_len_representing_num_lines]; // \e[<n>A
extern char MOV_CRSR_LEFT_COLS[3+str_len_representing_num_cols]; // \e[<n>D
extern char MOV_CRSR_RIGHT_COLS[3+str_len_representing_num_cols]; // \e[<n>C

#endif

