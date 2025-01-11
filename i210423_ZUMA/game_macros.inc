IFNDEF GAME_MACROS_INC
GAME_MACROS_INC		equ<1>

MULTIPLY MACRO dest, src1, src2

push				eax
push				edx

mov                 eax, src1
imul                eax, src2
mov                 dest, eax

pop					edx
pop					eax

ENDM

DIVIDE MACRO dest, src1, src2

push				ebx
push                eax
push				edx

mov                 eax, src1
xor                 edx, edx
mov                 ebx, src2
div                 ebx
mov                 dest, eax

pop					edx
pop                 eax
pop					ebx

ENDM

MODULUS	 MACRO dest, src1, src2

push				eax
push				edx
mov                 eax, src1
xor                 edx, edx
div                 src2
mov                 dest, edx
pop					edx
pop					eax

ENDM

_ADD MACRO dest, src1, src2

push				eax
mov                 eax, src1
add                 eax, src2
mov                 dest, eax
pop					eax

ENDM

SUBTRACT MACRO dest, src1, src2

push				eax
mov                 eax, src1
sub                 eax, src2
mov                 dest, eax
pop					eax

ENDM

COMPARE MACRO dword1,dword2

push                eax
push				ebx

push				dword1
push				dword2

pop					ebx
pop					eax

cmp					eax,ebx

pop					ebx
pop					eax

ENDM

MOVE	MACRO mem1,mem2

push				eax
mov					eax,mem2
mov					mem1,eax
pop					eax

ENDM

SWAP	MACRO mem1,mem2

push				mem1
push				mem2

pop					mem1
pop					mem2

ENDM

LTT					equ <0>		; Less than
LTE					equ <1>		; Less than equal to
GTT					equ <2>		; Greater than
GTE					equ <3>		; Greater than equal to
EQQ					equ <4>		; Equal to
NQQ					equ <5>		; Not equal to

IF_BLOCK MACRO		num1, operator, num2, tag

COMPARE				operator, LTT
je					jump_to_less_than_block_&tag

COMPARE				operator, LTE
je					jump_to_less_than_equalto_block_&tag

COMPARE				operator, GTT
je					jump_to_greater_than_block_&tag

COMPARE				operator, GTE
je					jump_to_greater_than_equalto_block_&tag

COMPARE				operator, EQQ
je					jump_to_equal_to_block_&tag

COMPARE				operator, NQQ
je					jump_to_not_equal_to_block_&tag

jmp					skip_conditional_block_checking_&tag

jump_to_not_equal_to_block_&tag:
COMPARE				num1,num2
je					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

jump_to_less_than_block_&tag:
COMPARE				num1, num2
jge					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

jump_to_less_than_equalto_block_&tag:
COMPARE				num1, num2
jg					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

jump_to_greater_than_block_&tag:
COMPARE				num1, num2
jle					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

jump_to_greater_than_equalto_block_&tag:
COMPARE				num1, num2
jl					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

jump_to_equal_to_block_&tag:
COMPARE				num1, num2
jne					skip_statements_under_conditional_block_&tag
jmp					skip_conditional_block_checking_&tag

skip_statements_under_conditional_block_&tag:
jmp					near_if_block_jump_&tag
skip_conditional_block_checking_&tag:

ENDM

ENDIF_BLOCK MACRO           tag

near_if_block_jump_&tag:

ENDM

WHILE_BLOCK MACRO           num1, operator, num2, tag

continue_with_next_loop_iteration_&tag:
IF_BLOCK			num1,operator,num2,tag
jmp					continue_with_loop_&tag
ENDIF_BLOCK			tag
jmp					exit_the_loop_&tag
run_next_loop_iteration_&tag:
jmp					continue_with_next_loop_iteration_&tag
exit_the_loop_&tag:
jmp					terminate_the_current_loop_&tag
continue_with_loop_&tag:
ENDM

ENDWHILE_BLOCK MACRO tag
jmp					run_next_loop_iteration_&tag
terminate_the_current_loop_&tag:
ENDM

ORANGE_COLOR		equ<25>
BLUE_COLOR			equ<20>
RED_COLOR			equ<15>
YELLOW_COLOR		equ<10>
GREEN_COLOR			equ<5>
WHITE_COLOR			equ<0>

TIME_PULSE_MILLISEC	equ<16>
MAX_BALLS			equ<50>

LEVEL_STATE			equ<4>
ENTER_NAME			equ<3>
PAUSE_GAME			equ<5>
HIGH_SCORE			equ<2>
EXIT_SCREEN			equ<1>
LOGO_SCREEN			equ<0>
MENU_SCREEN			equ<6>
STAT_SCREEN			equ<7>
OVER_SCREEN			equ<9>
INSTRUCTION_SCREEN	equ<8>

OPEN_SPACE			equ<0>
BALL_TUNNEL			equ<1>
UNDERGROUND_TUNNEL	equ<2>

DRAW_OPEN_SPACE		equ<ORANGE_COLOR + 1>
DRAW_BALL_TUNNEL	equ<ORANGE_COLOR + 4>
DRAW_UNDERGROUND_TUNNEL	equ<ORANGE_COLOR + 3>

ELSE 
echo warning game_macros.inc redeclared
echo warning game_macros.inc redeclared
echo warning game_macros.inc redeclared
ENDIF