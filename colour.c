
// COLOUR_C

// A lightweight colourization subroutine set.
// Utilizes ANSI/VT100 control-codes.
// See function 'char ResetAnsiVtCodes(char f)' below to see how simple the implementation is.

// PLATFORM TARGETS
#ifdef _WIN32_
#include <windows.h>
#endif

// STDLIB INC'S
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// DAVELIB INC'S
#include "../davelib/lib.h"
#include "../stringy/stringy.h"
#include "./colour.h"

//-----------------------

char ansivt;

char FG_BLACK[8];
char FG_RED[8];
char FG_GREEN[8];
char FG_YELLOW[8];
char FG_BLUE[8];
char FG_MAGENTA[8];
char FG_CYAN[8];
char FG_WHITE[8];

char FG_BRIGHT_BLACK[8];
char FG_BRIGHT_RED[8];
char FG_BRIGHT_GREEN[8];
char FG_BRIGHT_YELLOW[8];
char FG_BRIGHT_BLUE[8];
char FG_BRIGHT_MAGENTA[8];
char FG_BRIGHT_CYAN[8];
char FG_BRIGHT_WHITE[8];

char BG_BLACK[8];
char BG_RED[8];
char BG_GREEN[8];
char BG_YELLOW[8];
char BG_BLUE[8];
char BG_MAGENTA[8];
char BG_CYAN[8];
char BG_WHITE[8];

char BG_BRIGHT_BLACK[8];
char BG_BRIGHT_RED[8];
char BG_BRIGHT_GREEN[8];
char BG_BRIGHT_YELLOW[8];
char BG_BRIGHT_BLUE[8];
char BG_BRIGHT_MAGENTA[8];
char BG_BRIGHT_CYAN[8];
char BG_BRIGHT_WHITE[8];

char NORMAL[8];

char BOLD[8];
char UNDERLINE[8]; 
char TAB[8]; 
char LINEFEED[8]; 
char CARRAIGERETURN[8]; 
char CRSRBACKSPACE[8]; 
char BELL[8]; 

char CLS[8]; 
char MOV_CRSR_TOPLEFT[8]; 
char CLEAR_REST_OF_LINE[8]; 
char MOV_CRSR_DOWN_N[8];
char MOV_CRSR_UP_N[8];
char MOV_CRSR_LEFT_COLS[8];
char MOV_CRSR_RIGHT_COLS[8];


char* ANSIVT( char* str, char cc[], LARGE offsets[], int _frees )	{
		
	LARGE str_width = strlen(str);
	LARGE width = str_width + (strlen(cc)*VTCODEWIDTH);
	char* _ = mem( width );
	char* bucket = mem( width );
	char* vtcodestr;

	LARGE q=0;
	LARGE t=0;
	while( t<str_width ){

		LARGE p;
		for( p=0; p<offsets[q]; p++ ) // offsets are relative.
			bucket[p] = str[t++];
		bucket[p] = '\0';

		safecat( _,bucket );
		vtcodestr = getVTCodeString( *cc );
		safecat( _,vtcodestr );

		free( vtcodestr );

		++cc;
		++q;

		if( *cc == '\0' ){

			LARGE y = strlen(_);
			for( LARGE x=t;x<str_width; x++ )
				_[y++]=str[x];
			_[y] = '\0';			
			break;}}

	return _;
}


// ANSI/VT Global Refs.
char* ANSIVT_FG;
char* ANSIVT_BG;
struct _ANSI_* ANSI;

// FUNCTIONS
char ResetAnsiVtCodes(char f)	{

	int t=0;
	if(f == 0)	{

		repeat:

		strcpy((char *)FG_BLACK, "");
		strcpy((char *)FG_RED, "");
		strcpy((char *)FG_GREEN, "");
		strcpy((char *)FG_YELLOW, "");
		strcpy((char *)FG_BLUE, "");
		strcpy((char *)FG_MAGENTA, "");
		strcpy((char *)FG_CYAN, "");
		strcpy((char *)FG_WHITE, "");

		strcpy((char *)FG_BRIGHT_BLACK, "");
		strcpy((char *)FG_BRIGHT_RED, "");
		strcpy((char *)FG_BRIGHT_GREEN, "");
		strcpy((char *)FG_BRIGHT_YELLOW, "");
		strcpy((char *)FG_BRIGHT_BLUE, "");
		strcpy((char *)FG_BRIGHT_MAGENTA, "");
		strcpy((char *)FG_BRIGHT_CYAN, "");
		strcpy((char *)FG_BRIGHT_WHITE, "");

		strcpy((char *)BG_BLACK, "");
		strcpy((char *)BG_RED, "");
		strcpy((char *)BG_GREEN, "");
		strcpy((char *)BG_YELLOW, "");
		strcpy((char *)BG_BLUE, "");
		strcpy((char *)BG_MAGENTA, "");
		strcpy((char *)BG_CYAN, "");
		strcpy((char *)BG_WHITE, "");

		strcpy((char *)BG_BRIGHT_BLACK, "");
		strcpy((char *)BG_BRIGHT_RED, "");
		strcpy((char *)BG_BRIGHT_GREEN, "");
		strcpy((char *)BG_BRIGHT_YELLOW, "");
		strcpy((char *)BG_BRIGHT_BLUE, "");
		strcpy((char *)BG_BRIGHT_MAGENTA, "");
		strcpy((char *)BG_BRIGHT_CYAN, "");
		strcpy((char *)BG_BRIGHT_WHITE, "");

		strcpy((char *)NORMAL, "");

		strcpy((char *)BOLD, ""); // 
		strcpy((char *)UNDERLINE, ""); // 
		strcpy((char *)TAB, ""); // 
		strcpy((char *)LINEFEED, ""); // 
		strcpy((char *)CARRAIGERETURN, ""); // 
		strcpy((char *)CRSRBACKSPACE, ""); // 
		strcpy((char *)BELL, ""); // 

		strcpy((char *)CLS, ""); // 
		strcpy((char *)MOV_CRSR_TOPLEFT, ""); // \033[H , 
		strcpy((char *)CLEAR_REST_OF_LINE, ""); // 
		strcpy((char *)MOV_CRSR_DOWN_N, ""); // \e[<n>B
		strcpy((char *)MOV_CRSR_UP_N, ""); // \e[<n>A
		strcpy((char *)MOV_CRSR_LEFT_COLS, ""); // \e[<n>D
		strcpy((char *)MOV_CRSR_RIGHT_COLS, ""); // \e[<n>C


		if( t==1 )
			goto ret_stmt;
	}

	else if(f == 1)	{

		#ifndef cm0
		// Visibility determined by cmd-line compile switch -Dcm0
		// See Makefile target 'nocolour' for a clue.
		strcpy((char *)FG_BLACK, "\e[30m");
		strcpy((char *)FG_RED, "\e[31m");
		strcpy((char *)FG_GREEN, "\e[32m");
		strcpy((char *)FG_YELLOW, "\e[33m");
		strcpy((char *)FG_BLUE, "\e[34m");
		strcpy((char *)FG_MAGENTA, "\e[35m");
		strcpy((char *)FG_CYAN, "\e[36m");
		strcpy((char *)FG_WHITE, "\e[37m");

		strcpy((char *)FG_BRIGHT_BLACK, "\e[90m");
		strcpy((char *)FG_BRIGHT_RED, "\e[91m");
		strcpy((char *)FG_BRIGHT_GREEN, "\e[92m");
		strcpy((char *)FG_BRIGHT_YELLOW, "\e[93m");
		strcpy((char *)FG_BRIGHT_BLUE, "\e[94m");
		strcpy((char *)FG_BRIGHT_MAGENTA, "\e[95m");
		strcpy((char *)FG_BRIGHT_CYAN, "\e[96m");
		strcpy((char *)FG_BRIGHT_WHITE, "\e[97m");

		strcpy((char *)BG_BLACK, "\e[40m");
		strcpy((char *)BG_RED, "\e[41m");
		strcpy((char *)BG_GREEN, "\e[42m");
		strcpy((char *)BG_YELLOW, "\e[43m");
		strcpy((char *)BG_BLUE, "\e[44m");
		strcpy((char *)BG_MAGENTA, "\e[45m");
		strcpy((char *)BG_CYAN, "\e[46m");
		strcpy((char *)BG_WHITE, "\e[47m");

		strcpy((char *)BG_BRIGHT_BLACK, "\e[100m");
		strcpy((char *)BG_BRIGHT_RED, "\e[101m");
		strcpy((char *)BG_BRIGHT_GREEN, "\e[102m");
		strcpy((char *)BG_BRIGHT_YELLOW, "\e[103m");
		strcpy((char *)BG_BRIGHT_BLUE, "\e[104m");
		strcpy((char *)BG_BRIGHT_MAGENTA, "\e[105m");
		strcpy((char *)BG_BRIGHT_CYAN, "\e[106m");
		strcpy((char *)BG_BRIGHT_WHITE, "\e[107m");

		strcpy((char *)NORMAL, "\e[0m");
		
		
		strcpy((char *)BOLD, "\e[1m"); // 
		strcpy((char *)UNDERLINE, "\e[4m"); // 
		strcpy((char *)TAB, "\eI"); // 
		strcpy((char *)LINEFEED, "\eJ"); // 
		strcpy((char *)CARRAIGERETURN, "\eM"); // 
		strcpy((char *)CRSRBACKSPACE, "\eH"); // 
		strcpy((char *)BELL, "\eG"); // 

		strcpy((char *)CLS, "\e[2J"); // 
		strcpy((char *)MOV_CRSR_TOPLEFT, "\e[H"); // \033[H , 
		strcpy((char *)CLEAR_REST_OF_LINE, "\e[K"); // 
		strcpy((char *)MOV_CRSR_DOWN_N, " "); // \e[<n>B
		strcpy((char *)MOV_CRSR_UP_N, " "); // \e[<n>A
		strcpy((char *)MOV_CRSR_LEFT_COLS, " "); // \e[<n>D
		strcpy((char *)MOV_CRSR_RIGHT_COLS, " "); // \e[<n>C
		
		
		#else
		f=0;
		t=1;
		goto repeat;
		#endif
	}

	ret_stmt:
	return (ansivt = f);
}




char* fg( char* c )	{

	if(c!=0)
		ANSI->SetVT( c,(char*)0 );

	return ANSI->ANSIVT_FG;
}

char* bg( char* c )	{

	if(c!=0)
		ANSI->SetVT( (char*)0,c );

	return ANSI->ANSIVT_BG;
}

char* SetVT( char* fg, char* bg )	{

	char* fg_ = 0;
	char* bg_ = 0;

	int i;

	//FG:
	if( fg==(char*)0 )
		goto BG;

	for( i=0; i<16; i++ ){

		if( streq( fg, ANSI->c->ANSIVT_CTABLE[i*4] ) ){

			fg_ = getstring( *(ANSI->c->ANSIVT_CTABLE + (i*4) + 4) );
			printf( "%s", fg_ );
			ANSI->ANSIVT_FG = fg;
			ANSI->c->fg( fg_ );
			break;
		}
	}

	BG:
	if( bg==(char*)0 )
		goto NEXT;

	for( i=16; i<(16*2); i++ ){

		if( streq( bg, ANSI->c->ANSIVT_CTABLE[i*4] ) ){

			bg_ = getstring( ANSI->c->ANSIVT_CTABLE[(i*4)+4] );
			printf( "%s", bg_ );
			ANSI->ANSIVT_BG = bg;
			ANSI->c->bg( bg_ );
			break;
		}
	}

	NEXT:
	char* _ = mem( strlen(ANSIVT_FG)+strlen(ANSIVT_BG) + strlen("//") );
	_[0] = '\0';

	if( strlen(ANSI->ANSIVT_FG) )	
	safecat( _, ANSI->ANSIVT_FG );
	else
	safecat( _,"Default" );

	safecat(  _,"//" );	

	if( strlen(ANSI->ANSIVT_BG) ) 
	safecat( _,ANSI->ANSIVT_BG );
	else
	safecat( _,"Default" );	

	return _;
}

void Init_ANSIVT_CTABLE(){

	char** ANSIVT_CTABLE/* 64 * (16+8) */ = (char**)malloc( (64*2) * sizeof(char*) );

	uint32_t i=0;
	uint32_t offset = sizeof( char* );

	//FG
	*(ANSIVT_CTABLE + i + 0)= getstring( "black" ); // BASE + i + (0*4)
	*(ANSIVT_CTABLE + i + offset)= FG_BLACK;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "red" );
	*(ANSIVT_CTABLE + i + offset)= FG_RED;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "green" );
	*(ANSIVT_CTABLE + i + offset)= FG_GREEN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "yellow" );
	*(ANSIVT_CTABLE + i + offset)= FG_YELLOW;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "blue" );
	*(ANSIVT_CTABLE + i + offset)= FG_BLUE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "magenta" );
	*(ANSIVT_CTABLE + i + offset)= FG_MAGENTA;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "cyan" );
	*(ANSIVT_CTABLE + i + offset)= FG_CYAN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "white" );
	*(ANSIVT_CTABLE + i + offset)= FG_WHITE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_black" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_BLACK;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_red" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_RED;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_green" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_GREEN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_yellow" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_YELLOW;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_blue" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_BLUE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_magenta" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_MAGENTA;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_cyan" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_CYAN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_white" );
	*(ANSIVT_CTABLE + i + offset)= FG_BRIGHT_WHITE;

	i += (offset*2);
	// BG
	*(ANSIVT_CTABLE + i + 0)= getstring( "black" );
	*(ANSIVT_CTABLE + i + offset)= BG_BLACK;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "red" );
	*(ANSIVT_CTABLE + i + offset)= BG_RED;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "green" );
	*(ANSIVT_CTABLE + i + offset)= BG_GREEN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "yellow" );
	*(ANSIVT_CTABLE + i + offset)= BG_YELLOW;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "blue" );
	*(ANSIVT_CTABLE + i + offset)= BG_BLUE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "magenta" );
	*(ANSIVT_CTABLE + i + offset)= BG_MAGENTA;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "cyan" );
	*(ANSIVT_CTABLE + i + offset)= BG_CYAN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "white" );
	*(ANSIVT_CTABLE + i + offset)= BG_WHITE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_black" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_BLACK;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_red" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_RED;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_green" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_GREEN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_yellow" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_YELLOW;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_blue" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_BLUE;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_magenta" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_MAGENTA;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_cyan" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_CYAN;

	i += (offset*2);
	*(ANSIVT_CTABLE + i + 0)= getstring( "bright_white" );
	*(ANSIVT_CTABLE + i + offset)= BG_BRIGHT_WHITE;

	i += (offset*2);
	// RESET
	*(ANSIVT_CTABLE + i + 0) = getstring( "default" );
	*(ANSIVT_CTABLE + i + 4) = NORMAL;

	i += (offset*2);
	// i contains a count of all the colour codes. Should be 33.
	ANSI->ANSIVT_CTABLE = ANSIVT_CTABLE;
	ANSI->fg( "white" );
	ANSI->bg( "black" );

	return; 
}

int colorMode()	{

	int color = 0;
	
	if( ansivt != 0 )	{
		
		#ifdef _WIN32_
			
			// Assumes the target OS is Windows.
			#include <windows.h>
			#define STD_OUTPUT_HANDLE ((DWORD)-11)
			#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
			HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			color = (int) SetConsoleMode(
				StdHandle,
				0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
			);
			
			#ifdef _WIN32_
LPDWORD resultCode;
#endif

		#else

			// Assumes the target OS is Linux.
			color = 1;	
		#endif
	}

	int x = ( color==0 ? 0 : 1 );
	#ifdef DAVELIB_VERBOSE
	if( x==0 )		
		printf( "ANSI/VT Support Not Available in this Win32-API console process.\n" );
	else
		printf( "%sCongratulations! ANSI/VT mode is functioning.%s\n", FG_BRIGHT_GREEN, NORMAL );
	#endif

	ResetAnsiVtCodes(x);

	return x;
}

_ANSI_ Init_ANSI(){

	
	ANSI->RVC = ResetAnsiVtCodes;
	ANSI->SetVT = SetVT;
	ANSI->fg = fg;	
	ANSI->bg = bg;

	ANSI->ANSIVT_FG = "default";
	ANSI->ANSIVT_FG = "default";
	
	ANSI->ANSIVT_CTABLE = (char**)malloc( (FG_COLORS+BG_COLORS)*2 * sizeof(char*) + 1 );	

	return ANSI;
}

char* getVTCodeString( char cc )	{

	return *(ANSI->c->ANSIVT_CTABLE + (cc*4) + 4);
}

