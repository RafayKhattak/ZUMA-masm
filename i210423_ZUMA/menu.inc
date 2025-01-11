IFNDEF MENU_INC
MENU_INC		equ<1>
.data

next_menu_states	DWORD	ENTER_NAME,HIGH_SCORE,INSTRUCTION_SCREEN,EXIT_SCREEN
total_menu_states	DWORD	LENGTHOF next_menu_states

next_pause_states	DWORD	LEVEL_STATE,HIGH_SCORE,INSTRUCTION_SCREEN,MENU_SCREEN
total_pause_states	DWORD	LENGTHOF next_pause_states

next_states_index	DWORD	0
color_states_index	DWORD	0

record_counter		DWORD	0
stat_buff_counter	DWORD	0
user_stat_count		DWORD	3

.code

set_game_menu	proc

xor				eax,eax
mov				al,character

IF_BLOCK		eax,EQQ,'w',if2
dec				next_states_index
ENDIF_BLOCK		if2

IF_BLOCK		eax,EQQ,'s',if3
inc				next_states_index
ENDIF_BLOCK		if3

IF_BLOCK		eax,EQQ,' ',if4
mov				eax,4
mul				next_states_index
lea				esi,next_menu_states
add				esi,eax
mov				eax,DWORD PTR [esi]
push			gameState
mov				gameState,eax
pop				previousState
ENDIF_BLOCK		if4

IF_BLOCK		eax,EQQ,13,if5
mov				eax,4
mul				next_states_index
lea				esi,next_menu_states
add				esi,eax
mov				eax,DWORD PTR [esi]
push			gameState
mov				gameState,eax
pop				previousState
ENDIF_BLOCK		if5

push			total_menu_states
lea				esi,next_states_index
call			wrapAround

push			user_screens_length
lea				esi,main_menu_screen
push			esi
lea				esi,game_grid_buffer
push			esi
call			StringCopy

lea				esi,game_grid_buffer
mov				iteration_index_i,0
WHILE_BLOCK		iteration_index_i,LTT,user_screens_length,wh1

mov				al,BYTE PTR[esi]
cmp				al,'&'
jne				do_nothing

mov				BYTE PTR[esi],'B'
IF_BLOCK		color_states_index,EQQ,next_states_index,if1
mov				BYTE PTR[esi],'G'
ENDIF_BLOCK		if1
inc				color_states_index
do_nothing:
inc				esi
inc				iteration_index_i
ENDWHILE_BLOCK	wh1
mov				color_states_index,0

xor				eax,eax
mov				character,al

ret
set_game_menu	endp

set_pause_game	proc

xor				eax,eax
mov				al,character

IF_BLOCK		eax,EQQ,'w',if2
dec				next_states_index
ENDIF_BLOCK		if2

IF_BLOCK		eax,EQQ,'s',if3
inc				next_states_index
ENDIF_BLOCK		if3

IF_BLOCK		eax,EQQ,' ',if4
mov				eax,4
mul				next_states_index
lea				esi,next_pause_states
add				esi,eax
mov				eax,DWORD PTR [esi]
push			gameState
mov				gameState,eax
pop				previousState
ENDIF_BLOCK		if4

IF_BLOCK		eax,EQQ,13,if5
mov				eax,4
mul				next_states_index
lea				esi,next_pause_states
add				esi,eax
mov				eax,DWORD PTR [esi]
push			gameState
mov				gameState,eax
pop				previousState
ENDIF_BLOCK		if5

push			total_pause_states
lea				esi,next_states_index
call			wrapAround

push			user_screens_length
lea				esi,pause_game_screen
push			esi
lea				esi,game_grid_buffer
push			esi
call			StringCopy

lea				esi,game_grid_buffer
mov				iteration_index_i,0
WHILE_BLOCK		iteration_index_i,LTT,user_screens_length,wh1

mov				al,BYTE PTR[esi]
cmp				al,'&'
jne				do_nothing

mov				BYTE PTR[esi],'B'
IF_BLOCK		color_states_index,EQQ,next_states_index,if1
mov				BYTE PTR[esi],'G'
ENDIF_BLOCK		if1
inc				color_states_index
do_nothing:
inc				esi
inc				iteration_index_i
ENDWHILE_BLOCK	wh1
mov				color_states_index,0

xor				eax,eax
mov				character,al
ret
set_pause_game	endp

set_start_state	proc

push			user_screens_length
lea				esi,start_game_screen
push			esi
lea				esi,game_grid_buffer
push			esi
call			StringCopy

ret
set_start_state	endp

set_exit_game_screen	proc

push			user_screens_length
lea				esi,exit_game_screen
push			esi
lea				esi,game_grid_buffer
push			esi
call			StringCopy

ret
set_exit_game_screen	endp

set_name_state	proc
push			user_screens_length
lea				esi,enter_name_screen
push			esi
lea				esi,game_grid_buffer
push			esi
call			StringCopy

xor				eax,eax
mov				al,character

IF_BLOCK		eax,EQQ,01Bh,if10
push			gameState
push			previousState
pop				gameState
pop				previousState
ENDIF_BLOCK		if10

IF_BLOCK		eax,GTE,32,if1
IF_BLOCK		eax,LTE,123,if2

lea				esi,player_name
add				esi,player_name_length

mov				BYTE PTR[esi],al

inc				player_name_length
ENDIF_BLOCK		if2
ENDIF_BLOCK		if1

IF_BLOCK		eax,EQQ,8,if4
IF_BLOCK		player_name_length,GTT,0,if9
dec				player_name_length
ENDIF_BLOCK		if9
ENDIF_BLOCK		if4

IF_BLOCK		eax,EQQ,13,if3
mov				gameState,LEVEL_STATE
ENDIF_BLOCK		if3

mov				iteration_index_i,0
WHILE_BLOCK		iteration_index_i,LTT,user_screens_length, wh1

mov				al,BYTE PTR [esi]
cmp				al,'!'
jne				skip_buffer_draw

IF_BLOCK		player_name_length,GTT,0,if5
push			player_name_length
lea				edx,player_name
push			edx
push			esi
call			StringCopy
ENDIF_BLOCK		if5

skip_buffer_draw:
inc				esi
inc				iteration_index_i
ENDWHILE_BLOCK	wh1

xor				eax,eax
mov				character,al

ret
set_name_state	endp

set_highscores_screen	proc

xor						eax,eax
mov						al,character

IF_BLOCK				eax,EQQ,01Bh,if1
push					gameState
push					previousState
pop						gameState
pop						previousState
ENDIF_BLOCK				if1

xor						eax,eax
mov						character,al

push					user_screens_length
lea						esi,leader_board_screen
push					esi
lea						esi,game_grid_buffer
push					esi
call					StringCopy

lea						esi,game_grid_buffer
mov						iteration_index_i,0

mov						eax,totalRecords
mov						record_counter,eax

mov						eax,BUFFER_SIZE
mul						record_counter
sub						eax,BUFFER_SIZE

lea						edx,playRecords
add						edx,eax

WHILE_BLOCK				iteration_index_i,LTT,user_screens_length, wh1
mov						al,BYTE PTR [esi]
cmp						al,'!'

jne						skip_buffer_write

IF_BLOCK				record_counter,NQQ,0,if2

IF_BLOCK				stat_buff_counter,EQQ,2,if5

push					edx
push					esi
push					DWORD PTR [edx + 4]
lea						ecx,level_buffer
add						ecx,LENGTHOF level_buffer - 1
push					ecx
call					writeIntToBuffer
pop						esi
pop						edx

push					edx
lea						edx,level_buffer
push					LENGTHOF level_buffer
call					map_buffer_to_screen
pop						edx
inc						stat_buff_counter
ENDIF_BLOCK				if5

IF_BLOCK				stat_buff_counter,EQQ,1,if4

push					edx
push					esi
push					DWORD PTR [edx]
lea						ecx,score_buffer
add						ecx,LENGTHOF score_buffer - 1
push					ecx
call					writeIntToBuffer
pop						esi
pop						edx

push					edx
lea						edx,score_buffer
push					LENGTHOF score_buffer
call					map_buffer_to_screen
pop						edx
inc						stat_buff_counter
ENDIF_BLOCK				if4

IF_BLOCK				stat_buff_counter,EQQ,0,if3

add						edx,8
mov						iteration_index_j,0
WHILE_BLOCK				DWORD PTR [edx],NQQ,0Ah,wh2

add						edx,SIZEOF BYTE
add						iteration_index_j,SIZEOF BYTE
ENDWHILE_BLOCK			wh2
sub						edx,iteration_index_j

push					edx
push					iteration_index_j
call					map_buffer_to_screen
pop						edx
sub						edx,8

inc						stat_buff_counter
ENDIF_BLOCK				if3

ENDIF_BLOCK				if2

skip_buffer_write:

IF_BLOCK				stat_buff_counter,GTE,user_stat_count,if6
sub						edx,BUFFER_SIZE
dec						record_counter
mov						stat_buff_counter,0
ENDIF_BLOCK				if6

add						esi,SIZEOF	BYTE
add						iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK			wh1

ret
set_highscores_screen	endp

set_instructions_screen	proc

xor						eax,eax
mov						al,character

IF_BLOCK				eax,EQQ,01Bh,if1
push					gameState
push					previousState
pop						gameState
pop						previousState
ENDIF_BLOCK				if1

xor						eax,eax
mov						character,al

push					user_screens_length
lea						esi,instructions_screen
push					esi
lea						esi,game_grid_buffer
push					esi
call					StringCopy

ret
set_instructions_screen	endp

level_to_menu_state		proc
mov						gameState,MENU_SCREEN
mov						previousState,-1
call					store_game_scores
mov						player_name_length,0
mov						Score,0
mov						Lives,3
mov						Level,1
ret
level_to_menu_state		endp

set_game_over_screen	proc

xor						eax,eax
mov						al,character

IF_BLOCK				eax,EQQ,01Bh,if1
call					level_to_menu_state
ENDIF_BLOCK				if1

IF_BLOCK				eax,EQQ,0Dh,if2
call					level_to_menu_state
ENDIF_BLOCK				if2

xor						eax,eax
mov						character,al

push					user_screens_length
lea						esi,game_over_screen
push					esi
lea						esi,game_grid_buffer
push					esi
call					StringCopy

lea						esi,game_grid_buffer
mov						iteration_index_i,0
WHILE_BLOCK				iteration_index_i,LTT,user_screens_length, wh1
mov						al,BYTE PTR [esi]
cmp						al,'!'

jne						skip_buffer_write

IF_BLOCK				stat_buff_counter,EQQ,2,if5

push					esi
push					Level
lea						edx,level_buffer
add						edx,LENGTHOF level_buffer - 1
push					edx
call					writeIntToBuffer
pop						esi

lea						edx,level_buffer
push					LENGTHOF level_buffer
call					map_buffer_to_screen

inc						stat_buff_counter
ENDIF_BLOCK				if5

IF_BLOCK				stat_buff_counter,EQQ,1,if4

push					esi
push					Score
lea						edx,score_buffer
add						edx,LENGTHOF score_buffer - 1
push					edx
call					writeIntToBuffer
pop						esi

lea						edx,score_buffer
push					LENGTHOF score_buffer
call					map_buffer_to_screen

inc						stat_buff_counter
ENDIF_BLOCK				if4

IF_BLOCK				stat_buff_counter,EQQ,0,if3

IF_BLOCK				player_name_length,NQQ,0,if7
lea						edx,player_name
inc						player_name_length
push					player_name_length
dec						player_name_length
call					map_buffer_to_screen
ENDIF_BLOCK				if7

inc						stat_buff_counter
ENDIF_BLOCK				if3

skip_buffer_write:

IF_BLOCK				stat_buff_counter,GTE,user_stat_count,if6
mov						stat_buff_counter,0
ENDIF_BLOCK				if6

add						esi,SIZEOF	BYTE
add						iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK			wh1

ret
set_game_over_screen	endp

set_user_stats_screen	proc

xor						eax,eax
mov						al,character

IF_BLOCK				eax,EQQ,01Bh,if1
call					level_to_menu_state
ENDIF_BLOCK				if1

IF_BLOCK				eax,EQQ,0Dh,if2
call					level_to_menu_state
ENDIF_BLOCK				if2

xor						eax,eax
mov						character,al

push					user_screens_length
lea						esi,game_stats_screen
push					esi
lea						esi,game_grid_buffer
push					esi
call					StringCopy

lea						esi,game_grid_buffer
mov						iteration_index_i,0
WHILE_BLOCK				iteration_index_i,LTT,user_screens_length, wh1
mov						al,BYTE PTR [esi]
cmp						al,'!'

jne						skip_buffer_write

IF_BLOCK				stat_buff_counter,EQQ,2,if5

push					esi
push					Level
lea						edx,level_buffer
add						edx,LENGTHOF level_buffer - 1
push					edx
call					writeIntToBuffer
pop						esi

lea						edx,level_buffer
push					LENGTHOF level_buffer
call					map_buffer_to_screen

inc						stat_buff_counter
ENDIF_BLOCK				if5

IF_BLOCK				stat_buff_counter,EQQ,1,if4

push					esi
push					Score
lea						edx,score_buffer
add						edx,LENGTHOF score_buffer - 1
push					edx
call					writeIntToBuffer
pop						esi

lea						edx,score_buffer
push					LENGTHOF score_buffer
call					map_buffer_to_screen

inc						stat_buff_counter
ENDIF_BLOCK				if4

IF_BLOCK				stat_buff_counter,EQQ,0,if3

IF_BLOCK				player_name_length,NQQ,0,if7
lea						edx,player_name
inc						player_name_length
push					player_name_length
dec						player_name_length
call					map_buffer_to_screen
ENDIF_BLOCK				if7

inc						stat_buff_counter
ENDIF_BLOCK				if3

skip_buffer_write:

IF_BLOCK				stat_buff_counter,GTE,user_stat_count,if6
mov						stat_buff_counter,0
ENDIF_BLOCK				if6

add						esi,SIZEOF	BYTE
add						iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK			wh1

ret
set_user_stats_screen	endp

reset_player_game_state	proc

mov						iteration_index_i,0
WHILE_BLOCK				iteration_index_i,LTT,MAX_BALLS*SIZEOF DWORD,wh1
push					iteration_index_i
call					delete_ball
add						iteration_index_i,SIZEOF DWORD

ENDWHILE_BLOCK			wh1
mov						edx,trailColorPtr
mov						iteration_index_i,0
WHILE_BLOCK				iteration_index_i,LTT,trailLength,wh4
mov						DWORD PTR [edx],-1
add						edx,SIZEOF DWORD
add						iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK			wh4

mov						missionFailed,0
mov						missionPassed,0
mov						numTrailBallsCount,0

mov						dl,0
mov						dh,0
call					Gotoxy

lea						esi,display_screen_grid

mov						iteration_index_i,0
WHILE_BLOCK				iteration_index_i,LTT,GAME_GRID_ROWS +  1,wh3

mov						iteration_index_j,0
WHILE_BLOCK				iteration_index_j,LTT,GAME_GRID_COLS + 27,wh2
mov						BYTE PTR [esi],' '
add						esi,SIZEOF BYTE
add						iteration_index_j,SIZEOF BYTE
ENDWHILE_BLOCK			wh2

mov						BYTE PTR [esi],0Ah
add						esi,SIZEOF BYTE
add						iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK			wh3

mov						BYTE PTR [esi],0
lea						edx,display_screen_grid
call					WriteString
ret
reset_player_game_state	endp

ELSE	
echo warning menu.inc redeclared
echo warning menu.inc redeclared
echo warning menu.inc redeclared
ENDIF
