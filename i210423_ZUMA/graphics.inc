IFNDEF	GRAPHICS_INC
GRAPHICS_INC		equ<1>

GAME_GRID_ROWS		equ<38>
GAME_GRID_COLS		equ<38*3>

.data

display_screen_grid	BYTE 38 DUP(10*38*5 + 1 DUP(0))

game_grid_buffer	BYTE GAME_GRID_ROWS DUP(GAME_GRID_COLS DUP(0h)),0

left_padding		DWORD 27
top_padding			DWORD 1
iteration_index_i	DWORD 0
iteration_index_j	DWORD 0
iteration_index_k	DWORD 0

scan_ansi_codes		DWORD	01h
colored_characters	BYTE	"#-*@O#-*@O#-*@O#-*@O#-*@O:/*$+",0
ansi_colors			BYTE	"WGYRBO",0
ansi_color_codes	BYTE	27,"[0m",0,27,"[32m",0,27,"[33m",0,27,"[31m",0,27,"[34m",0,27,"[38;5;208m",0
ansi_codes_length	DWORD	5,6,6,6,6,6

buff_pointer		DWORD	?
buff_index			DWORD	?

display_time		BYTE	" Time :: ",0
score_buffer		BYTE	"00000000",0
level_buffer		BYTE	"00000000",0
lives_buffer		BYTE	"00000000",0
time_buffer			BYTE	"00:00:00",0

lives_prompt		BYTE	" Lives :: "

power				BYTE	" Power :: ",0
power_buffer		BYTE	"NONE",0

.code

writeIntToBuffer	proc AddrBuff:DWORD, integer:DWORD

mov					esi,AddrBuff
mov					eax,integer
mov					ebx,10
mov					ecx,8

writeToBuffer:
dec					ecx
xor					edx,edx
div					ebx
	
add					edx,'0'

dec					esi
mov					BYTE PTR [esi],dl

cmp					ecx,0h
je					wroteToBuffer
jmp					writeToBuffer
wroteToBuffer:

ret
writeIntToBuffer	endp

writeTimeToBuffer	proc AddrBuff:DWORD, milliSeconds:DWORD
	
mov					esi,AddrBuff
add					esi,7

xor					edx,edx
mov					eax,milliSeconds
mov					ebx,1000
div					ebx

MOVE				iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,3,wh1

xor					edx,edx
mov					ebx,60
div					ebx

push				eax

mov					eax,edx
xor					edx,edx

mov					ebx,10
div					ebx

add					dl,'0'
add					al,'0'

mov					BYTE PTR [esi],dl
dec					esi
mov					BYTE PTR [esi],al

inc					iteration_index_i

IF_BLOCK			iteration_index_i,LTT,3,if1
mov					al,':'
dec					esi
mov					BYTE PTR [esi],al
dec					esi
ENDIF_BLOCK			if1

pop					eax

ENDWHILE_BLOCK		wh1

ret
writeTimeToBuffer	endp

map_buffer_to_screen	proc	buffer_size:DWORD

push					buffer_size
push					edx
push					esi
call					StringCopy
dec						buffer_size
add						esi,buffer_size

ret
map_buffer_to_screen	endp

display_screen	proc

lea					esi,display_screen_grid
mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,SIZEOF display_screen_grid,wh6
mov					BYTE PTR [esi],0
add					esi,SIZEOF BYTE
add					iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK		wh6

mov					dl,0
mov					dh,0
call				Gotoxy

push				total_elapsed_time
lea					esi,time_buffer
push				esi
call				writeTimeToBuffer

push				Score
lea					esi,score_buffer
add					esi,LENGTHOF score_buffer - 1
push				esi
call				writeIntToBuffer

push				Level
lea					esi,level_buffer
add					esi,LENGTHOF level_buffer - 1
push				esi
call				writeIntToBuffer

push				Lives
lea					esi,lives_buffer
add					esi,LENGTHOF lives_buffer - 1
push				esi
call				writeIntToBuffer

lea					esi,display_screen_grid

mov					al,'G'
call				set_ansi_color

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,left_padding,wh5

xor					eax,eax
mov					al,' '
mov					BYTE PTR [esi],al
inc					iteration_index_i
inc					esi

ENDWHILE_BLOCK		wh5

lea					edx,namesPrompt
push				LENGTHOF namesPrompt
call				map_buffer_to_screen

lea					edx,player_name
inc					player_name_length
push				player_name_length
dec					player_name_length
call				map_buffer_to_screen

lea					edx,display_time
push				LENGTHOF display_time
call				map_buffer_to_screen

lea					edx,time_buffer
push				LENGTHOF time_buffer
call				map_buffer_to_screen

lea					edx,levelPrompt
push				LENGTHOF levelPrompt
call				map_buffer_to_screen

lea					edx,level_buffer
push				LENGTHOF level_buffer
call				map_buffer_to_screen

lea					edx,scorePrompt
push				LENGTHOF scorePrompt
call				map_buffer_to_screen

lea					edx,score_buffer
push				LENGTHOF score_buffer
call				map_buffer_to_screen

lea					edx,lives_prompt
push				LENGTHOF lives_prompt
call				map_buffer_to_screen

lea					edx,lives_buffer
push				LENGTHOF lives_buffer
call				map_buffer_to_screen

lea					edx,power
push				LENGTHOF power
call				map_buffer_to_screen

lea					edx,power_buffer
push				LENGTHOF power_buffer
call				map_buffer_to_screen

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,top_padding,wh4

xor					eax,eax
mov					al,0ah
mov					BYTE PTR [esi],al
inc					iteration_index_i
inc					esi

ENDWHILE_BLOCK		wh4

mov					al,'W'
call				set_ansi_color

lea					edx,game_grid_buffer
mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,GAME_GRID_ROWS,wh1

mov					iteration_index_j,0
WHILE_BLOCK			iteration_index_j,LTT,left_padding,wh3

xor					eax,eax
mov					al,' '
mov					BYTE PTR [esi],al
inc					iteration_index_j
inc					esi

ENDWHILE_BLOCK		wh3

mov					iteration_index_j,0
WHILE_BLOCK			iteration_index_j,LTT,GAME_GRID_COLS,wh2

xor					eax,eax
mov					al,BYTE PTR [edx]

call				map_characters_to_display_screen

inc					edx
inc					iteration_index_j
ENDWHILE_BLOCK		wh2
mov					al,0ah
mov					BYTE PTR [esi],al
inc					esi

inc					iteration_index_i
ENDWHILE_BLOCK		wh1
xor					eax,eax
mov					BYTE PTR [esi],al

lea					edx,display_screen_grid
call				WriteString

ret
display_screen		endp

map_characters_to_display_screen	proc

mov					BYTE PTR [esi],al

IF_BLOCK			eax,LTE,ORANGE_COLOR + 4,if1
IF_BLOCK			eax,GTE,0,iff1
push				eax
push				esi

lea					esi,ansi_codes_length
DIVIDE				buff_index,eax,GREEN_COLOR - WHITE_COLOR

push				iteration_index_i
mov					iteration_index_i,0
xor					eax,eax
WHILE_BLOCK			iteration_index_i,LTT,buff_index,wh1

add					eax,DWORD PTR [esi]

add					esi,SIZEOF DWORD
inc					iteration_index_i
ENDWHILE_BLOCK		wh1
pop					iteration_index_i

lea					esi,ansi_color_codes
add					esi,eax
mov					buff_pointer,esi

pop					esi
push				edx

push				iteration_index_i
mov					edx,buff_pointer

mov					eax,[edx]
and					eax,000000FFh
WHILE_BLOCK			eax,NQQ,0,wh2

mov					BYTE PTR [esi],al

inc					edx		
inc					esi

mov					eax,[edx]
and					eax,000000FFh
ENDWHILE_BLOCK		wh2

pop					iteration_index_i
pop					edx
pop					eax
push				eax
push				edx

lea					edx,colored_characters
add					edx,eax
mov					eax,[edx]
mov					BYTE PTR[esi],al

inc					esi

lea					edx,ansi_color_codes
mov					eax,[edx]
and					eax,000000FFh
WHILE_BLOCK			eax,NQQ,0,wh3

mov					BYTE PTR [esi],al

inc					edx
inc					esi

mov					eax,[edx]
and					eax,000000FFh
ENDWHILE_BLOCK		wh3

pop					edx
pop					eax

ENDIF_BLOCK			iff1
ENDIF_BLOCK			if1

IF_BLOCK			eax,GTE,32,if2
inc					esi
ENDIF_BLOCK			if2

mov					buff_pointer,0
mov					buff_index,0
ret
map_characters_to_display_screen	endp

set_ansi_color	proc

IF_BLOCK			scan_ansi_codes,EQQ,1,if3
push				iteration_index_i
push				edx
push				esi

lea					edx,ansi_color_codes
mov					buff_pointer,edx

lea					edx,ansi_colors
lea					esi,ansi_codes_length

push				ebx

mov					iteration_index_i,0
mov					buff_index,0
mov					ebx,[edx]
and					ebx,000000FFh

WHILE_BLOCK			ebx,NQQ,eax,wh1
add					esi,SIZEOF DWORD
inc					edx

mov					ebx,[edx]
and					ebx,000000FFh
IF_BLOCK			ebx,EQQ,0,if1
pop					ebx
jmp					exit_function
ENDIF_BLOCK			if1

_ADD				buff_index,buff_index,[esi]
ENDWHILE_BLOCK		wh1

pop					ebx
pop					esi
push				ebx

mov					edx,buff_pointer

IF_BLOCK			buff_index,GTT,0,if2
dec					buff_index
ENDIF_BLOCK			if2

add					edx,buff_index

mov					ebx,[edx]
and					ebx,000000FFh
WHILE_BLOCK			ebx,NQQ,0,wh2

mov					al,BYTE PTR[edx]
mov					BYTE PTR[esi],al

inc					esi
inc					edx
mov					ebx,[edx]
and					ebx,000000FFh
ENDWHILE_BLOCK		wh2

pop					ebx
push				esi

exit_function:
pop					esi
pop					edx
pop					iteration_index_i
mov					buff_pointer,0
mov					buff_index,0
ENDIF_BLOCK			if3

ret
set_ansi_color	endp

display_menu_screen	proc	x:DWORD,y:DWORD

lea					esi,display_screen_grid
mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,SIZEOF display_screen_grid,wh5
mov					BYTE PTR [esi],0
add					esi,SIZEOF BYTE
add					iteration_index_i,SIZEOF BYTE
ENDWHILE_BLOCK		wh5

mov					dl,0
mov					dh,0
call				Gotoxy

lea					esi,display_screen_grid
mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,y,wh2
mov					BYTE PTR[esi],0ah
inc					esi
inc					iteration_index_i
ENDWHILE_BLOCK		wh2
mov					iteration_index_i,0

WHILE_BLOCK			iteration_index_i,LTT,x,wh4
mov					BYTE PTR[esi],' '
inc					iteration_index_i
inc					esi
ENDWHILE_BLOCK		wh4

lea					edx,game_grid_buffer

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,user_screens_length,wh1

xor					eax,eax
mov					al,BYTE PTR[edx]

mov					BYTE PTR[esi],al

call				set_ansi_color

mov					al,BYTE PTR [esi]
cmp					al,0
jne					skip_esi_update

mov					al,' '
mov					BYTE PTR[esi],al

skip_esi_update:
inc					esi
inc					edx
inc					iteration_index_i

IF_BLOCK			eax,EQQ,0Ah,if1

mov					iteration_index_j,0
WHILE_BLOCK			iteration_index_j,LTT,x,wh3
mov					BYTE PTR[esi],' '
inc					iteration_index_j
inc					esi
ENDWHILE_BLOCK		wh3

ENDIF_BLOCK			if1

IF_BLOCK			eax,EQQ,'$',if2
xor					scan_ansi_codes,01h
mov					BYTE PTR [esi - SIZEOF BYTE],' '
ENDIF_BLOCK			if2

ENDWHILE_BLOCK		wh1

lea					edx,display_screen_grid
call				WriteString

ret
display_menu_screen endp

ELSE
echo warning graphics.asm redeclared
echo warning graphics.asm redeclared
echo warning graphics.asm redeclared
ENDIF