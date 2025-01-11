IFNDEF GAME_PLAY_INC
GAME_PLAY_INC equ <1>

draw_ball	proto :DWORD,:DWORD,:DWORD

.data

calcX				DWORD	?
calcY				DWORD	?
result				DWORD	?
var1				DWORD	?
var2				DWORD	?
var3				DWORD	?

xShootPos			DWORD	?
yShootPos			DWORD	?

xShootPointArray	DWORD -7,-7,-7,-6,-4,-2, 0, 2, 4, 6, 7, 7, 7, 7, 7, 6, 4, 2, 0,-2,-4,-6,-7,-7
yShootPointArray	DWORD  0,-1,-2,-3,-3,-3,-3,-3,-3,-3,-2,-1, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 2, 1
xShootDirUpdate		DWORD -6,-6,-4,-5,-4,-2, 0, 2, 4, 5, 4, 6, 6, 6, 4, 5, 4, 2, 0,-2,-4,-5,-4,-6
yShootDirUpdate		DWORD  0,-1,-1,-2,-2,-3,-3,-3,-2,-2,-1,-1, 0, 1, 1, 2, 2, 3, 3, 3, 2, 2, 1, 1

shootIndex			DWORD	0

xShoot				DWORD	MAX_BALLS	DUP(-1)
yShoot				DWORD	MAX_BALLS	DUP(-1)
xShootUpdate		DWORD	MAX_BALLS	DUP(-1)
yShootUpdate		DWORD	MAX_BALLS	DUP(-1)
ballColor			DWORD	MAX_BALLS	DUP(-1)
ballShootIndex		DWORD	MAX_BALLS	DUP(-1)
ballUpdateSpeed		DWORD	MAX_BALLS	DUP(0h)
ballUpdateCount		DWORD	MAX_BALLS	DUP(0h)
ballCounter			DWORD	0h

ballUpdatePulse		DWORD	3

ballColorArray		DWORD	BLUE_COLOR,RED_COLOR,YELLOW_COLOR,GREEN_COLOR,WHITE_COLOR,ORANGE_COLOR
nextBallColor		DWORD	-1
currentBallColor	DWORD	-1

level_1_trailXpos	DWORD	106,100, 94, 88, 82, 76, 70, 64, 58, 52, 46, 40, 34, 28, 22, 16, 10, 10, 10, 10, 10, 10, 10, 10

level_1_trailYpos	DWORD	  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  6,  9, 12, 15, 18, 21, 24

level_1_trailType	DWORD	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

level_1_trailColor	DWORD	24 DUP(-1)

level_1_numTrailBalls	DWORD	25

level_1_trailSpeed	DWORD	60

level_2_trailXpos	DWORD	106,100, 94, 88, 82, 76, 70, 64, 58, 52, 46, 40, 34, 28, 22, 16, 10, 10, 10, 10, 10, 10, 10, 10, 10
					DWORD	 10, 10, 16, 22, 28, 34, 34, 34, 34, 34, 34, 34, 34, 34, 40, 46, 52, 58, 64, 70, 76, 82, 88, 94,100
					DWORD	106

level_2_trailYpos	DWORD	  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  6,  9, 12, 15, 18, 24, 21, 27
					DWORD	 30, 33, 33, 33, 33, 33, 30, 27, 24, 21, 18, 15, 12,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9
					DWORD	  9

level_2_trailType	DWORD	  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
					DWORD	  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  0
					DWORD	  0

level_2_trailColor	DWORD	51 DUP(-1)

level_2_numTrailBalls	DWORD	50

level_2_trailSpeed	DWORD	45


level_3_trailXpos	DWORD	106,106,106,106,106,106,106,106,106,106,100, 94, 88, 82, 76, 70, 64, 58, 52, 46, 40, 34, 28, 22, 16
					DWORD	 10,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 10, 16, 22, 28, 34, 40, 46, 52, 58, 64, 70, 76, 82
					DWORD	 88, 94, 94, 94, 94, 94, 94, 94, 94, 94, 88, 82, 76, 70, 64, 58, 52, 46, 40, 34, 28, 22, 16, 16, 16
					DWORD	 16, 16, 16, 16, 22, 28, 34, 40, 46, 52, 58, 64, 70, 76, 82, 82, 82, 82, 82

level_3_trailYpos	DWORD	  6,  9, 12, 15, 18, 21, 24, 27, 30, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33
					DWORD	 33, 33, 30, 27, 24, 21, 18, 15, 12,  9,  6,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3
					DWORD	  3,  3,  6,  9, 12, 15, 18, 21, 24, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 24, 21
					DWORD	 18, 15, 12,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 12, 15, 18, 21

level_3_trailType	DWORD	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
					DWORD	  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0
					DWORD	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,  0
					DWORD	  0,  0,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0

level_3_trailColor	DWORD	94 DUP(-1)

level_3_numTrailBalls	DWORD	80

level_3_trailSpeed	DWORD	30

trailXposPtr		DWORD	?
trailYposPtr		DWORD	?
trailColorPtr		DWORD	?
trailTypePtr		DWORD	?
trailLength			DWORD	?

numTrailBalls		DWORD	?
numTrailBallsCount	DWORD	0

trailSpeed			DWORD	?
trailSpeedCount		DWORD	0

isBallInserted		DWORD	0

drawBallTypes		DWORD	DRAW_OPEN_SPACE,DRAW_BALL_TUNNEL,DRAW_UNDERGROUND_TUNNEL

missionFailed		DWORD	0
missionPassed		DWORD	0

chainReactionX		DWORD	-1
chainReactionY		DWORD	-1
chainThreshold		DWORD	+2
chainCombos			DWORD	+0
chainCount			DWORD	+0
chainReactionColor	DWORD	-1

power_up_none		BYTE	"NONE",0
power_up_bomb		BYTE	"BOMB",0
power_up_rail		BYTE	"RAIL",0

collisionDirRange	DWORD	3
chainComboMultiplier	DWORD	10
ballDestroyScore	DWORD	5
bombRange			DWORD	3

bombsCounter		DWORD	120
speedCounter		DWORD	360
slowsCounter		DWORD	0

bombsCounterInit	DWORD	240
speedCounterInit	DWORD	360
slowsCounterInit	DWORD	720

speedCounterSpeed	DWORD	20
slowsCounterSpeed	DWORD	120

comboRewardThreshold	DWORD	2

.code

MAX_SHOOT_INDEX		equ<LENGTHOF xShootPointArray>

handlePlayState		proc

IF_BLOCK			gameState,EQQ,LEVEL_STATE,if2 
WHILE_BLOCK			elapsed_time,GTE,TIME_PULSE_MILLISEC,wh1

xor					eax,eax
call				ReadKey
mov					character,al

cmp					al,'p'
jne					continue_with_level_state
push				PAUSE_GAME
push				gameState
pop					previousState
pop					gameState

call				reset_player_game_state

ret
continue_with_level_state:

mov					eax,Level
call				load_game_level

call				generate_effects
call				special_effects

call				getNextBall
call				levelInit
call				shoot_ball
call				update_ball

call				addBallToTrail

push				0
call				moveTrail

call				chainReaction
call				generate_rewards

call				ball_collision

IF_BLOCK			missionFailed,EQQ,1,if4
IF_BLOCK			Lives,EQQ,0,if6
mov					gameState,OVER_SCREEN
mov					previousState,-1
call				reset_player_game_state
ret
ENDIF_BLOCK			if6
call				reset_player_game_state
mov					missionFailed,0
dec					Lives
ENDIF_BLOCK			if4

IF_BLOCK			missionPassed,EQQ,1,if5

IF_BLOCK			Level,EQQ,3,if7
mov					gameState,STAT_SCREEN
mov					previousState,-1
call				reset_player_game_state
ret
ENDIF_BLOCK			if7

inc					Level
mov					missionPassed,0
call				reset_player_game_state
ENDIF_BLOCK			if5

sub					elapsed_time,TIME_PULSE_MILLISEC
add					total_elapsed_time,TIME_PULSE_MILLISEC

IF_BLOCK			elapsed_time,LTT,0,if3
mov					eax,elapsed_time
add					total_elapsed_time,eax
ENDIF_BLOCK			if3

xor					eax,eax
mov					character,al

call				display_screen

ENDWHILE_BLOCK		wh1
ENDIF_BLOCK			if2

ret
handlePlayState		endp

getNextBall			proc

IF_BLOCK			currentBallColor,EQQ,-1,if1

IF_BLOCK			nextBallColor,EQQ,-1,if3

mov					eax,LENGTHOF ballColorArray
call				RandomRange
lea					esi,ballColorArray
mov					var1,4
mul					eax

add					esi,eax
mov					eax,DWORD PTR [esi]
mov					nextBallColor,eax
ENDIF_BLOCK			if3

mov					eax,nextBallColor
mov					currentBallColor,eax
mov					nextBallColor,-1
ENDIF_BLOCK			if1

IF_BLOCK			nextBallColor,EQQ,-1,if2

mov					eax,LENGTHOF ballColorArray
call				RandomRange
lea					esi,ballColorArray
mov					var1,4
mul					var1

add					esi,eax
mov					eax,DWORD PTR [esi]
mov					nextBallColor,eax
ENDIF_BLOCK			if2
ret
getNextBall			endp

wrapAround			proc	upper_limit:DWORD

IF_BLOCK			[esi],EQQ,upper_limit,if1
mov					ecx,0
mov					[esi],ecx
ENDIF_BLOCK			if1

IF_BLOCK			[esi],EQQ,-1,if2
mov					ecx,upper_limit
dec					ecx
mov					[esi],ecx
ENDIF_BLOCK			if2

ret
wrapAround			endp

shoot_ball			proc

xor					eax,eax
mov					al,character

lea					esi,shootIndex

IF_BLOCK			eax,EQQ,'z',if1
dec					DWORD PTR [esi]
push				MAX_SHOOT_INDEX
call				wrapAround
ENDIF_BLOCK			if1

IF_BLOCK			eax,EQQ,'x',if2
inc					DWORD PTR [esi]
push				MAX_SHOOT_INDEX
call				wrapAround
ENDIF_BLOCK			if2

IF_BLOCK			eax,EQQ,'c',if6
push				currentBallColor
push				nextBallColor
pop					currentBallColor
pop					nextBallColor
ENDIF_BLOCK			if6

lea					esi,game_grid_buffer

MULTIPLY			result,yShootPos,GAME_GRID_COLS
add					esi,result
add					esi,xShootPos

push				iteration_index_i
MOVE				iteration_index_i,MAX_SHOOT_INDEX - 1
WHILE_BLOCK			iteration_index_i,GTE,0,wh3
push				eax
push				ebx
push				ecx
push				esi
push				edx

lea					ebx,xShootPointArray
lea					ecx,yShootPointArray
mov					eax,4
mul					iteration_index_i

add					ebx,eax
add					ecx,eax

mov					eax,GAME_GRID_COLS

mul					DWORD PTR [ecx]
add					eax,[ebx]

add					esi,eax

IF_BLOCK			iteration_index_i,EQQ,shootIndex, if5
mov					BYTE PTR[esi],ORANGE_COLOR + 4
jmp					ball_shoot_index_updated
ENDIF_BLOCK			if5
mov					BYTE PTR[esi],RED_COLOR + 2
ball_shoot_index_updated:

pop					edx
pop					esi
pop					ecx
pop					ebx
pop					eax
dec					iteration_index_i
ENDWHILE_BLOCK		wh3
pop					iteration_index_i

IF_BLOCK			eax,EQQ,32,if3

mov					eax,4
mul					shootIndex
mov					var1,eax

lea					esi,ballShootIndex
add					esi,ballCounter
mov					eax,shootIndex
mov					DWORD PTR [esi],eax

lea					esi,xShoot
add					esi,ballCounter

mov					ebx,xShootPos
mov					DWORD PTR[esi],ebx

lea					ebx,xShootPointArray
add					ebx,var1
mov					ebx,DWORD PTR [ebx]
add					DWORD PTR[esi],ebx

lea					esi,yShoot
add					esi,ballCounter

mov					ebx,yShootPos
mov					DWORD PTR [esi],ebx

lea					ebx,yShootPointArray
add					ebx,var1
mov					ebx,DWORD PTR [ebx]
add					DWORD PTR [esi],ebx

lea					esi,xShootUpdate
add					esi,ballCounter

lea					ebx,xShootDirUpdate
add					ebx,var1
mov					ebx,[ebx]
mov					DWORD PTR [esi],ebx

lea					esi,yShootUpdate
add					esi,ballCounter

lea					ebx,yShootDirUpdate
add					ebx,var1
mov					ebx,[ebx]
mov					DWORD PTR [esi],ebx

lea					esi,ballColor
add					esi,ballCounter
mov					ebx,currentBallColor
mov					DWORD PTR [esi],ebx

lea					esi,ballUpdateSpeed
add					esi,ballCounter
mov					ebx,ballUpdatePulse
mov					DWORD PTR[esi],ebx

lea					esi,ballUpdateCount
add					esi,ballCounter
mov					DWORD PTR[esi],0

add					ballCounter,4
IF_BLOCK			ballCounter,GTE,MAX_BALLS*4,if4
xor					eax,eax
mov					ballCounter,eax
ENDIF_BLOCK			if4

mov					ebx,-1
mov					currentBallColor,ebx

ENDIF_BLOCK			if3

ret
shoot_ball			endp

update_ball			proc

push				iteration_index_i

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,MAX_BALLS*(SIZEOF DWORD),wh1

lea					esi,ballColor
add					esi,iteration_index_i

IF_BLOCK			DWORD PTR [esi],EQQ,-1,if1
jmp					go_to_next_ball
ENDIF_BLOCK			if1

lea					esi,ballUpdateCount
add					esi,iteration_index_i
inc					DWORD PTR [esi]
mov					ebx,DWORD PTR [esi]
mov					var1,ebx

lea					esi,ballUpdateSpeed
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
mov					var2,ebx

lea					esi,ballColor
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
mov					var3,ebx

IF_BLOCK			var1,EQQ,var2,if2

lea					esi,ballShootIndex
add					esi,iteration_index_i
mov					eax,4
mul					DWORD PTR [esi]

lea					esi,xShootDirUpdate
add					esi,eax
mov					ebx,DWORD PTR [esi]
mov					var1,ebx

lea					esi,yShootDirUpdate
add					esi,eax
mov					ebx,DWORD PTR [esi]
mov					var2,ebx

lea					esi,xShoot
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
add					ebx,var1
mov					var1,ebx
mov					DWORD PTR [esi],ebx

lea					esi,yShoot
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
add					ebx,var2
mov					var2,ebx
mov					DWORD PTR [esi],ebx

lea					esi,ballUpdateCount
add					esi,iteration_index_i
mov					DWORD PTR[esi],0

jmp					go_update_ball
ENDIF_BLOCK			if2

lea					esi,xShoot
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
mov					var1,ebx

lea					esi,yShoot
add					esi,iteration_index_i
mov					ebx,DWORD PTR [esi]
mov					var2,ebx

go_update_ball:
IF_BLOCK			var1,GTE,2,if3
IF_BLOCK			var1,LTE,GAME_GRID_COLS - 2,if4
IF_BLOCK			var2,GTE,2,if5
IF_BLOCK			var2,LTE,GAME_GRID_ROWS - 2,if6

push				var3
push				var2
push				var1
call				draw_ball

jmp					ballDrawnSuccessfully
ENDIF_BLOCK			if3
ENDIF_BLOCK			if4
ENDIF_BLOCK			if5
ENDIF_BLOCK			if6

push				iteration_index_i
call				delete_ball

ballDrawnSuccessfully:
go_to_next_ball:
skip_ball_drawing:

add					iteration_index_i,4
ENDWHILE_BLOCK		wh1

pop					iteration_index_i

ret
update_ball			endp

delete_ball			proc index:DWORD

lea					esi,xShoot
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,yShoot
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,xShootUpdate
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,yShootUpdate
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,ballColor
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,ballShootIndex
add					esi,index
mov					DWORD PTR[esi],-1

lea					esi,ballUpdateCount
add					esi,index
mov					DWORD PTR [esi],0

lea					esi,ballUpdateSpeed
add					esi,index
mov					DWORD PTR [esi],0

ret
delete_ball			endp

levelInit			proc

mov					iteration_index_i,1
WHILE_BLOCK			iteration_index_i,LTT,GAME_GRID_ROWS - 1,wh1

mov					iteration_index_j,1
WHILE_BLOCK			iteration_index_j,LTT,GAME_GRID_COLS - 1,wh2

MULTIPLY			result,iteration_index_i,GAME_GRID_COLS
_ADD				result,result,iteration_index_j

lea					esi,game_grid_buffer
add					esi,result

xor					eax,eax
mov					al,BYTE PTR[esi]

IF_BLOCK			eax,EQQ,'Z',if3
mov					BYTE PTR[esi],ORANGE_COLOR
mov					BYTE PTR[esi + 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS + 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS + 1],ORANGE_COLOR + 4
ENDIF_BLOCK			if3

IF_BLOCK			eax,EQQ,'X',if4
mov					BYTE PTR[esi],ORANGE_COLOR + 3
mov					BYTE PTR[esi + 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS + 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi + GAME_GRID_COLS - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS - 1],ORANGE_COLOR + 4
mov					BYTE PTR[esi - GAME_GRID_COLS + 1],ORANGE_COLOR + 4
ENDIF_BLOCK			if4

IF_BLOCK			eax,EQQ,'S',if2

MOVE				xShootPos,iteration_index_j
MOVE				yShootPos,iteration_index_i

push				esi
invoke				draw_ball,iteration_index_j,iteration_index_i,currentBallColor
pop					esi

ENDIF_BLOCK			if2

IF_BLOCK			eax,EQQ,'N',if5

push				esi
invoke				draw_ball,iteration_index_j,iteration_index_i,nextBallColor
pop					esi

ENDIF_BLOCK			if5

inc					iteration_index_j
ENDWHILE_BLOCK		wh2

inc					iteration_index_i
ENDWHILE_BLOCK		wh1

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,trailLength,wh3

mov					edx,trailColorPtr
add					edx,iteration_index_i

COMMENT	!
IF_BLOCK			DWORD PTR [edx],EQQ,-1,if8
push				'*'
jmp					skip_ball_colouring
ENDIF_BLOCK			if8
!

push				DWORD PTR [edx]
skip_ball_colouring:

mov					edx,trailYposPtr
add					edx,iteration_index_i
push				DWORD PTR [edx]

mov					edx,trailXposPtr
add					edx,iteration_index_i
push				DWORD PTR [edx]

mov					edx,trailTypePtr
add					edx,iteration_index_i

IF_BLOCK			DWORD PTR [edx],EQQ,OPEN_SPACE,if8
mov					edx,trailColorPtr
add					edx,iteration_index_i

IF_BLOCK			DWORD PTR [edx],NQQ,-1,if7

jmp					draw_ball_with_color

ENDIF_BLOCK			if7

ENDIF_BLOCK			if8

pop					var3
pop					var2
pop					var1

mov					eax,4

mov					edx,trailTypePtr
add					edx,iteration_index_i
mul					DWORD PTR [edx]

lea					esi,drawBallTypes
add					esi,eax

push				DWORD PTR [esi]
push				var2
push				var3

jmp					draw_ball_tunnel

mov					edx,trailColorPtr
add					edx,iteration_index_i

draw_ball_with_color:
call				draw_ball
jmp					ball_drawn_with_colour

draw_ball_tunnel:
call				put_character

ball_drawn_with_colour:

add					iteration_index_i,4
ENDWHILE_BLOCK		wh3

push				LENGTHOF power_up_none
lea					edx,power_up_none
push				edx
lea					edx,power_buffer
push				edx
call				StringCopy

IF_BLOCK			currentBallColor,EQQ,WHITE_COLOR,if9
push				LENGTHOF power_up_bomb
lea					edx,power_up_bomb
push				edx
lea					edx,power_buffer
push				edx
call				StringCopy
ENDIF_BLOCK			if9

IF_BLOCK			currentBallColor,EQQ,ORANGE_COLOR,if10
push				LENGTHOF power_up_rail
lea					edx,power_up_rail
push				edx
lea					edx,power_buffer
push				edx
call				StringCopy
ENDIF_BLOCK			if10

ret
levelInit			endp

put_character		proc x:DWORD,y:DWORD,value:DWORD

lea					esi,game_grid_buffer
MULTIPLY			y,y,GAME_GRID_COLS

add					esi,y
add					esi,x

mov					eax,value
mov					BYTE PTR[esi],al

ret
put_character		endp

draw_ball	proc x:DWORD,y:DWORD,color:DWORD

_ADD				color,color,4
invoke				put_character,x,y,color

inc					x

invoke				put_character,x,y,color

SUBTRACT			x,x,2

invoke				put_character,x,y,color

inc					x
inc					y

SUBTRACT			color,color,3

invoke				put_character,x,y,color

SUBTRACT			y,y,2

invoke				put_character,x,y,color

ret
draw_ball			endp

load_game_level	proc

IF_BLOCK			eax,EQQ,1,if1

lea					edx,level_1_trailXpos
mov					trailXposPtr,edx

lea					edx,level_1_trailYpos
mov					trailYposPtr,edx

lea					edx,level_1_trailColor
mov					trailColorPtr,edx

lea					edx,level_1_trailType
mov					trailTypePtr,edx

mov					trailLength,SIZEOF level_1_trailColor

mov					eax,level_1_numTrailBalls
mov					numTrailBalls,eax

mov					eax,level_1_trailSpeed
mov					trailSpeed,eax

push				GAME_GRID_COLS*GAME_GRID_ROWS + 1
lea					edx,game_level_1_grid
push				edx
lea					edx,game_grid_buffer
push				edx
call				StringCopy

ENDIF_BLOCK			if1

IF_BLOCK			eax,EQQ,2,if2

lea					edx,level_2_trailXpos
mov					trailXposPtr,edx

lea					edx,level_2_trailYpos
mov					trailYposPtr,edx

lea					edx,level_2_trailType
mov					trailTypePtr,edx

lea					edx,level_2_trailColor
mov					trailColorPtr,edx

mov					trailLength,SIZEOF level_2_trailColor

mov					eax,level_2_numTrailBalls
mov					numTrailBalls,eax

mov					eax,level_2_trailSpeed
mov					trailSpeed,eax

push				GAME_GRID_COLS*GAME_GRID_ROWS + 1
lea					edx,game_level_2_grid
push				edx
lea					edx,game_grid_buffer
push				edx
call				StringCopy
ENDIF_BLOCK			if2

IF_BLOCK			eax,EQQ,3,if3

lea					edx,level_3_trailXpos
mov					trailXposPtr,edx

lea					edx,level_3_trailYpos
mov					trailYposPtr,edx

lea					edx,level_3_trailType
mov					trailTypePtr,edx

lea					edx,level_3_trailColor
mov					trailColorPtr,edx

mov					trailLength,SIZEOF level_3_trailColor

mov					eax,level_3_numTrailBalls
mov					numTrailBalls,eax

mov					eax,level_3_trailSpeed
mov					trailSpeed,eax

push				GAME_GRID_COLS*GAME_GRID_ROWS + 1
lea					edx,game_level_3_grid
push				edx
lea					edx,game_grid_buffer
push				edx
call				StringCopy
ENDIF_BLOCK			if3

ret
load_game_level	endp

insertBall			proc xPos:DWORD,yPos:DWORD,ball_Color:DWORD

IF_BLOCK			ball_Color,EQQ,-1,if8
ret
ENDIF_BLOCK			if8

mov					esi,trailXposPtr
mov					edx,trailYposPtr
mov					iteration_index_i,0

WHILE_BLOCK			iteration_index_i,LTT,trailLength,wh1

IF_BLOCK			DWORD PTR [esi],EQQ,xPos,if1
IF_BLOCK			DWORD PTR [edx],EQQ,yPos,if2

jmp					exit_ball_find_loop

ENDIF_BLOCK			if2
ENDIF_BLOCK			if1

add					esi,4
add					edx,4
add					iteration_index_i,4

ENDWHILE_BLOCK		wh1
ret
exit_ball_find_loop:

mov					eax,trailTypePtr
add					eax,iteration_index_i

IF_BLOCK			DWORD PTR [eax],NQQ,OPEN_SPACE,if17

IF_BLOCK			DWORD PTR [eax],EQQ,BALL_TUNNEL,if18
mov					isBallInserted,1
ret
ENDIF_BLOCK			if18

IF_BLOCK			DWORD PTR [eax],EQQ,UNDERGROUND_TUNNEL,if19
mov					isBallInserted,0
ret
ENDIF_BLOCK			if19

ENDIF_BLOCK			if17

mov					esi,trailColorPtr
add					esi,iteration_index_i

IF_BLOCK			DWORD PTR [esi],NQQ,-1,if3
IF_BLOCK			ball_Color,NQQ,ORANGE_COLOR,if11
IF_BLOCK			ball_Color,NQQ,WHITE_COLOR,if12

mov					eax,trailSpeed
dec					eax
mov					trailSpeedCount,eax

push				iteration_index_i
push				iteration_index_i
call				moveTrail
pop					iteration_index_i

jmp					insert_ball

ENDIF_BLOCK			if12
ENDIF_BLOCK			if11
ENDIF_BLOCK			if3


mov					iteration_index_j,0
WHILE_BLOCK			iteration_index_j,LTT,bombRange,wh2

IF_BLOCK			ball_Color,EQQ,WHITE_COLOR,if10

mov					eax,SIZEOF DWORD
mul					iteration_index_j

push				iteration_index_i
sub					iteration_index_i,eax

IF_BLOCK			iteration_index_i,GTE,0,if13

sub					esi,eax

cmp					DWORD PTR [esi],-1
je					no_ball_blast_1
mov					edx,3
add					Score,edx

cmp					iteration_index_j,1
jne					no_collision_1
mov					isBallInserted,1
no_collision_1:

no_ball_blast_1:

mov					DWORD PTR [esi],-1
add					esi,eax
ENDIF_BLOCK			if13

pop					iteration_index_i

push				iteration_index_i
add					iteration_index_i,eax

IF_BLOCK			iteration_index_i,LTT,trailLength,if14
add					esi,eax

cmp					DWORD PTR [esi],-1
je					no_ball_blast_2
mov					edx,3
add					Score,edx

cmp					iteration_index_j,1
jne					no_collision_2
mov					isBallInserted,1
no_collision_2:

no_ball_blast_2:

mov					DWORD PTR [esi],-1
sub					esi,eax
ENDIF_BLOCK			if14

pop					iteration_index_i

ENDIF_BLOCK			if10

inc					iteration_index_j
ENDWHILE_BLOCK		wh2

cmp					isBallInserted,1
jne					noBomb
ret
noBomb:

sub					iteration_index_i,4
mov					esi,trailColorPtr
add					esi,iteration_index_i

IF_BLOCK			iteration_index_i,GTE,0,if4
IF_BLOCK			DWORD PTR [esi],NQQ,-1,if5

add					iteration_index_i,4
jmp					insert_ball

ENDIF_BLOCK			if5
ENDIF_BLOCK			if4

add					iteration_index_i,8
mov					esi,trailColorPtr
add					esi,iteration_index_i

IF_BLOCK			iteration_index_i,LTT,trailLength,if6
IF_BLOCK			DWORD PTR [esi],NQQ,-1,if7

sub					iteration_index_i,4

jmp					insert_ball

ENDIF_BLOCK			if7
ENDIF_BLOCK			if6
ret

insert_ball:

mov					eax,ball_Color
mov					chainReactionColor,eax

mov					esi,trailColorPtr
add					esi,iteration_index_i
mov					eax,ball_Color

IF_BLOCK			eax,NQQ,WHITE_COLOR,if15
IF_BLOCK			eax,NQQ,ORANGE_COLOR,if16

mov					DWORD PTR [esi],eax

mov					esi,trailXposPtr
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
mov					chainReactionX,eax

mov					esi,trailYposPtr
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
mov					chainReactionY,eax

mov					isBallInserted,1
ret
ENDIF_BLOCK			if16
ENDIF_BLOCK			if15

IF_BLOCK			ball_Color,EQQ,ORANGE_COLOR,if9

cmp					DWORD PTR [esi],-1
je					no_ball_deleted

mov					eax,2
add					Score,eax

no_ball_deleted:

mov					DWORD PTR [esi],-1
mov					isBallInserted,0
ret
ENDIF_BLOCK			if9

mov					isBallInserted,1

ret
insertBall			endp

chainReaction		proc

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,trailLength,wh1

mov					esi,trailXposPtr
add					esi,iteration_index_i
IF_BLOCK			DWORD PTR [esi],EQQ,chainReactionX,if2
mov					esi,trailYposPtr
add					esi,iteration_index_i
IF_BLOCK			DWORD PTR [esi],EQQ,chainReactionY,if3
jmp					chainReactionPhase
ENDIF_BLOCK			if3
ENDIF_BLOCK			if2

add					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh1
ret

chainReactionPhase:

WHILE_BLOCK			iteration_index_i,LTT,trailLength,wh2
mov					esi,trailColorPtr
add					esi,iteration_index_i
IF_BLOCK			DWORD PTR[esi],NQQ,chainReactionColor,if4
jmp					exit_chain_top_loop
ENDIF_BLOCK			if4

add					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh2
exit_chain_top_loop:

mov					chainCount,0

sub					iteration_index_i,SIZEOF DWORD
WHILE_BLOCK			iteration_index_i,GTE,0,wh3
mov					esi,trailColorPtr
add					esi,iteration_index_i
IF_BLOCK			DWORD PTR[esi],NQQ,chainReactionColor,if5
jmp					exit_chain_count_loop
ENDIF_BLOCK			if5
inc					chainCount
sub					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh3
exit_chain_count_loop:

IF_BLOCK			chainCount,GTE,chainThreshold,if8

inc					chainCombos

mov					eax,chainComboMultiplier
mul					chainCombos
add					Score,eax

mov					eax,ballDestroyScore
mul					chainCount
add					Score,eax


skip_combo_rewards:

add					iteration_index_i,SIZEOF DWORD
WHILE_BLOCK			iteration_index_i,LTT,trailLength,wh4
mov					esi,trailColorPtr
add					esi,iteration_index_i
IF_BLOCK			DWORD PTR[esi],NQQ,chainReactionColor,if7
jmp					exit_chain_reactor_loop
ENDIF_BLOCK			if7
IF_BLOCK			DWORD PTR[esi],EQQ,chainReactionColor,if6
mov					DWORD PTR[esi],-1
ENDIF_BLOCK			if6
add					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh4

ENDIF_BLOCK			if8

exit_chain_reactor_loop:

mov					chainReactionColor,-1
mov					chainReactionX,-1
mov					chainReactionY,-1
ret
chainReaction		endp

moveTrail			proc index:DWORD

inc					trailSpeedCount
IF_BLOCK			trailSpeedCount,GTE,trailSpeed,if5
mov					trailSpeedCount,0

mov					eax,index
mov					iteration_index_i,eax
mov					esi,trailColorPtr
add					esi,iteration_index_i
WHILE_BLOCK			DWORD PTR [esi],EQQ,-1,wh1

add					esi,SIZEOF DWORD
add					iteration_index_i,SIZEOF DWORD

IF_BLOCK			iteration_index_i,EQQ,trailLength,if4
mov					missionPassed,1
ret
ENDIF_BLOCK			if4

ENDWHILE_BLOCK		wh1

WHILE_BLOCK			DWORD PTR[esi],NQQ,-1,wh2

add					esi,SIZEOF DWORD
add					iteration_index_i,SIZEOF DWORD

IF_BLOCK			iteration_index_i,EQQ,trailLength,if1
mov					missionFailed,1
ret
ENDIF_BLOCK			if1

ENDWHILE_BLOCK		wh2

add					iteration_index_i,SIZEOF DWORD
IF_BLOCK			iteration_index_i,NQQ,trailLength,if2
IF_BLOCK			DWORD PTR[esi + SIZEOF DWORD],NQQ,-1,if3
mov					eax,DWORD PTR[esi + SIZEOF DWORD]
mov					chainReactionColor,eax
push				esi
mov					esi,trailXposPtr
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
mov					chainReactionX,eax

mov					esi,trailYposPtr
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
mov					chainReactionY,eax

pop					esi
ENDIF_BLOCK			if3
ENDIF_BLOCK			if2
sub					iteration_index_i,SIZEOF DWORD

WHILE_BLOCK			iteration_index_i,NQQ,index,wh3
mov					eax,DWORD PTR [esi - SIZEOF DWORD]
mov					DWORD PTR [esi],eax
sub					esi,SIZEOF DWORD
sub					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh3
mov					DWORD PTR [esi],-1

ENDIF_BLOCK			if5
ret
moveTrail			endp

addBallToTrail		proc
IF_BLOCK			numTrailBallsCount,LTE,numTrailBalls,if2

push				edx
push				esi

mov					edx,trailColorPtr
IF_BLOCK			DWORD PTR [edx],EQQ,-1,if1

inc					numTrailBallsCount

mov					eax,LENGTHOF ballColorArray - 2
call				RandomRange
mov					var1,4
push				edx
mul					var1
pop					edx

lea					esi,ballColorArray
add					esi,eax

mov					eax,DWORD PTR [esi]
mov					DWORD PTR [edx],eax

ENDIF_BLOCK			if1

pop					esi
pop					edx

ENDIF_BLOCK			if2
ret
addBallToTrail		endp

ball_collision		proc

mov					iteration_index_i,0
WHILE_BLOCK			iteration_index_i,LTT,MAX_BALLS*SIZEOF DWORD,wh1

mov					eax,-1
mul					collisionDirRange
mov					iteration_index_j,eax

WHILE_BLOCK			iteration_index_j,LTT,collisionDirRange,wh2

mov					eax,-1
mul					collisionDirRange
mov					iteration_index_k,eax

WHILE_BLOCK			iteration_index_k,LTT,collisionDirRange,wh3

push				iteration_index_i
push				iteration_index_j
push				iteration_index_k

lea					esi,ballColor
add					esi,iteration_index_i
push				DWORD PTR [esi]

lea					esi,yShoot
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
add					eax,iteration_index_j
push				eax

lea					esi,xShoot
add					esi,iteration_index_i
mov					eax,DWORD PTR [esi]
add					eax,iteration_index_k
push				eax

call				insertBall

pop					iteration_index_k
pop					iteration_index_j
pop					iteration_index_i

IF_BLOCK			isBallInserted,EQQ,1,if1
mov					chainCombos,0
mov					isBallInserted,0
push				iteration_index_i
push				iteration_index_i
call				delete_ball
pop					iteration_index_i
jmp					go_to_next_iteration
ENDIF_BLOCK			if1

inc					iteration_index_k
ENDWHILE_BLOCK		wh3

inc					iteration_index_j
ENDWHILE_BLOCK		wh2
go_to_next_iteration:
mov					isBallInserted,0
add					iteration_index_i,SIZEOF DWORD
ENDWHILE_BLOCK		wh1

ret
ball_collision		endp

bomb_explosion		proc

ret
bomb_explosion		endp

special_effects		proc

IF_BLOCK			bombsCounter,GTT,0,if1
mov					nextBallColor,WHITE_COLOR
dec					bombsCounter
ENDIF_BLOCK			if1

IF_BLOCK			speedCounter,GTT,0,if3
mov					eax,speedCounterSpeed
mov					trailSpeed,eax
dec					speedCounter
ENDIF_BLOCK			if3

IF_BLOCK			slowsCounter,GTT,0,if2
mov					eax,slowsCounterSpeed
mov					trailSpeed,eax
dec					slowsCounter
ENDIF_BLOCK			if2

ret
special_effects		endp

generate_effects	proc

mov					eax,10
IF_BLOCK			eax,EQQ,5,if1
mov					eax,speedCounterInit
mov					speedCounter,eax
ENDIF_BLOCK			if1

ret
generate_effects	endp

generate_rewards	proc

IF_BLOCK			chainCombos,GTE,comboRewardThreshold,if12

mov					eax,3
call				RandomRange

IF_BLOCK			eax,EQQ,0,if9
inc					Lives
ENDIF_BLOCK			if9

IF_BLOCK			eax,EQQ,1,if10
mov					eax,360
call				RandomRange
mov					bombsCounter,eax
ENDIF_BLOCK			if10

IF_BLOCK			eax,EQQ,2,if11
mov					eax,slowsCounterInit
call				RandomRange
mov					slowsCounter,eax
ENDIF_BLOCK			if11
ENDIF_BLOCK			if12

ret
generate_rewards	endp

ELSE
echo warning game_play.inc redeclared
echo warning game_play.inc redeclared
echo warning game_play.inc redeclared
ENDIF