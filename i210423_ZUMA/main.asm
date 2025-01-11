.386
.model flat, stdcall
.stack 4096

option casemap:none

includelib kernel32.lib
include kernel32.inc
includelib winmm.lib
include winmm.inc
include windows.inc
includelib irvine32.lib
include Irvine32.inc
include macros.inc

include game_macros.inc
include filehandling.inc
include graphics.inc
include game_screens.inc
include game_play.inc
include menu_screens.inc
include	menu.inc

.data

current_time		DWORD	?
previous_time		DWORD	?
elapsed_time		DWORD	?
total_elapsed_time	DWORD	?

Score				DWORD	0
Level				DWORD	3
Lives				DWORD	3

player_name			BYTE	BUFFER_SIZE DUP(0)
player_name_length	DWORD	?

gameState			DWORD	LOGO_SCREEN
previousState		DWORD	?

.code

main PROC

call				GetTickCount
mov					current_time,eax
call				Randomize

main_game_loop:

IF_BLOCK			gameState,EQQ,LOGO_SCREEN,if3

call				set_start_state
push				5
push				35
call				display_menu_screen

push				1000
call				Sleep
mov					gameState,MENU_SCREEN
ENDIF_BLOCK			if3

IF_BLOCK			gameState,EQQ,MENU_SCREEN,if4

xor					eax,eax
call				ReadKey
mov					character,al

call				set_game_menu
push				5
push				35
call				display_menu_screen
ENDIF_BLOCK			if4

IF_BLOCK			gameState,EQQ,ENTER_NAME,if5

xor					eax,eax
call				ReadKey
mov					character,al

call				set_name_state
push				5
push				35
call				display_menu_screen
ENDIF_BLOCK			if5

IF_BLOCK			gameState,EQQ,EXIT_SCREEN,if6

call				set_exit_game_screen
push				5
push				35
call				display_menu_screen
push				1000
call				Sleep
jmp					exit_main_loop
ENDIF_BLOCK			if6

IF_BLOCK			gameState,EQQ,HIGH_SCORE,if7
call				loadRecord
call				sortRecord
xor					eax,eax
call				ReadKey
mov					character,al

call				set_highscores_screen
push				5
push				35
call				display_menu_screen

ENDIF_BLOCK			if7

IF_BLOCK			gameState,EQQ,INSTRUCTION_SCREEN,if8

xor					eax,eax
call				ReadKey
mov					character,al

call				set_instructions_screen
push				5
push				35
call				display_menu_screen

ENDIF_BLOCK			if8

IF_BLOCK			gameState,EQQ,PAUSE_GAME,if9

xor					eax,eax
call				ReadKey
mov					character,al

call				set_pause_game
push				5
push				35
call				display_menu_screen
ENDIF_BLOCK			if9

IF_BLOCK			gameState,EQQ,STAT_SCREEN,if10
xor					eax,eax
call				ReadKey
mov					character,al

call				set_user_stats_screen
push				5
push				35
call				display_menu_screen
ENDIF_BLOCK			if10

IF_BLOCK			gameState,EQQ,OVER_SCREEN,if11
xor					eax,eax
call				ReadKey
mov					character,al

call				set_game_over_screen
push				5
push				35
call				display_menu_screen
ENDIF_BLOCK			if11

mov					eax,current_time
mov					previous_time,eax

call				handlePlayState

call				GetTickCount

mov					current_time,eax
sub					eax,previous_time

IF_BLOCK			gameState,EQQ,LEVEL_STATE,if1
add					elapsed_time,eax
ENDIF_BLOCK			if1

push				TIME_PULSE_MILLISEC
call				Sleep

jmp					main_game_loop
exit_main_loop:

invoke				ExitProcess,0
main ENDP

END main