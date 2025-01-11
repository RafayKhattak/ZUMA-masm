.386
.model flat, stdcall
.stack 4096

option casemap:none
include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc
include winmm.inc
include Irvine32.inc
include macros.inc
include filehandling.inc

.data
    ; Level layout

    walls BYTE " _____________________________________________________________________________ ", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                    ---                                      |", 0
          BYTE "|                                   |   |                                     |", 0
          BYTE "|                                   |   |                                     |", 0
          BYTE "|                                   |   |                                     |", 0
          BYTE "|                                    ---                                      |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|                                                                             |", 0
          BYTE "|_____________________________________________________________________________|", 0


    ; Player sprite
    player_right BYTE "   ", 0
                 BYTE " O-", 0
                 BYTE "   ", 0

    player_left BYTE "   ", 0
                BYTE "-O ", 0
                BYTE "   ", 0

    player_up BYTE " | ", 0
              BYTE " O ", 0
              BYTE "   ", 0

    player_down BYTE "   ", 0
                BYTE " O ", 0
                BYTE " | ", 0

    player_upright BYTE "  /", 0
                   BYTE " O ", 0
                   BYTE "   ", 0

    player_upleft BYTE "\  ", 0
                  BYTE " O ", 0
                  BYTE "   ", 0

    player_downright BYTE "   ", 0
                     BYTE " O ", 0
                     BYTE "  \", 0

    player_downleft BYTE "   ", 0
                    BYTE " O ", 0
                    BYTE "/  ", 0

    ; Player's starting position (center)
    xPos db 56      ; Column (X)
    yPos db 15      ; Row (Y)

    xDir db 0
    yDir db 0

    ; Default character (initial direction)
    inputChar db 0
    direction db "d"

    ; Colors for the emitter and player
    color_red db 4       ; Red
    color_green db 2     ; Green
    color_yellow db 14   ; Yellow (for fire symbol)

    current_color db 4   ; Default player color (red)

    emitter_color1 db 2  ; Green
    emitter_color2 db 4  ; Red

    fire_color db 14     ; Fire symbol color (Yellow)

    ; Emitter properties
    emitter_symbol db "#"
    emitter_row db 0    ; Two rows above player (fixed row for emitter)
    emitter_col db 1    ; Starting column of the emitter

    ; Fire symbol properties (fired from player)
    fire_symbol db "*", 0
    fire_row db 0        ; Fire will be fired from the player's position
    fire_col db 0        ; Initial fire column will be set in the update logic

    ; Interface variables
    score db 0          ; Player's score
    lives db 3          ; Player's lives
    levelInfo db 1
    
    ; Counter variables for loops
    counter1 db 0
    counter2 db 0

.code

FireBall PROC
    ; Fire a projectile from the player's current face direction

    mov dl, xPos      ; Fire column starts at the player's X position
    mov dh, yPos      ; Fire row starts at the player's Y position

    mov fire_col, dl  ; Save the fire column position
    mov fire_row, dh  ; Save the fire row position

    mov al, direction
    cmp al, "w"
    je fire_up

    cmp al, "x"
    je fire_down

    cmp al, "a"
    je fire_left

    cmp al, "d"
    je fire_right

    cmp al, "q"
    je fire_upleft

    cmp al, "e"
    je fire_upright

    cmp al, "z"
    je fire_downleft

    cmp al, "c"
    je fire_downright

    jmp end_fire

fire_up:
    mov fire_row, 14         ; Move fire position upwards
    mov fire_col, 57         ; Center fire position
    mov xDir, 0
    mov yDir, -1
    jmp fire_loop

fire_down:
    mov fire_row, 18         ; Move fire position downwards
    mov fire_col, 57         ; Center fire position
    mov xDir, 0
    mov yDir, 1
    jmp fire_loop

fire_left:
    mov fire_col, 55         ; Move fire position leftwards
    mov fire_row, 16         ; Center fire position
    mov xDir, -1
    mov yDir, 0
    jmp fire_loop

fire_right:
    mov fire_col, 59         ; Move fire position rightwards
    mov fire_row, 16         ; Center fire position
    mov xDir, 1
    mov yDir, 0
    jmp fire_loop

fire_upleft:
    mov fire_row, 14         ; Move fire position upwards
    mov fire_col, 55         ; Move fire position leftwards
    mov xDir, -1
    mov yDir, -1
    jmp fire_loop

fire_upright:
    mov fire_row, 14         ; Move fire position upwards
    mov fire_col, 59         ; Move fire position rightwards
    mov xDir, 1
    mov yDir, -1
    jmp fire_loop

fire_downleft:
    mov fire_row, 18         ; Move fire position downwards
    mov fire_col, 55         ; Move fire position leftwards
    mov xDir, -1
    mov yDir, 1
    jmp fire_loop

fire_downright:
    mov fire_row, 18         ; Move fire position downwards
    mov fire_col, 59         ; Move fire position rightwards
    mov xDir, 1
    mov yDir, 1
    jmp fire_loop

fire_loop:
    ; Initialise fire position
    mov dl, fire_col
    mov dh, fire_row
    call Gotoxy

    ; Loop to move the fireball in the current direction
    L1:

        ; Ensure fire stays within the bounds of the emitter wall
        cmp dl, 20            ; Left wall boundary
        jle end_fire

        cmp dl, 96            ; Right wall boundary
        jge end_fire

        cmp dh, 5             ; Upper wall boundary
        jle end_fire

        cmp dh, 27            ; Lower wall boundary
        jge end_fire

        ; Print the fire symbol at the current position
        movzx eax, fire_color    ; Set fire color
        call SetTextColor

        add dl, xDir
        add dh, yDir
        call Gotoxy

        mWrite "*"

        ; Continue moving fire in the current direction (recursive)
        mov eax, 50
        call Delay

        ; erase the fire before redrawing it
        call Gotoxy
        mWrite " "

        jmp L1

    end_fire:
        mov dx, 0
        call Gotoxy

    ret
FireBall ENDP

DrawWall PROC
	call Clrscr

    mov dl,19
	mov dh,2
	call Gotoxy
	mWrite <"Score: ">
	mov eax, Blue + (black * 16)
	call SetTextColor
	mov al, score
	call WriteDec

    mov eax, White + (black * 16)
	call SetTextColor

	mov dl,90
	mov dh,2
	call Gotoxy
	mWrite <"Lives: ">
	mov eax, Red + (black * 16)
	call SetTextColor
	mov al, lives
	call WriteDec

	mov eax, white + (black * 16)
	call SetTextColor

	mov dl,55
	mov dh,2
	call Gotoxy

	mWrite "LEVEL " 
	mov al, levelInfo
	call WriteDec

	mov eax, gray + (black*16)
	call SetTextColor

	mov dl, 19
	mov dh, 4
	call Gotoxy

	mov esi, offset walls

	mov counter1, 50
	mov counter2, 80
	movzx ecx, counter1
	printcolumn:
		mov counter1, cl
		movzx ecx, counter2
		printrow:
			mov eax, [esi]
			call WriteChar
            
			inc esi
		loop printrow
		
        dec counter1
		movzx ecx, counter1

		mov dl, 19
		inc dh
		call Gotoxy
	loop printcolumn

	ret
DrawWall ENDP

PrintPlayer PROC
    mov eax, brown + (black * 16)
    call SetTextColor

    mov al, direction
    cmp al, "w"
    je print_up

    cmp al, "x"
    je print_down

    cmp al, "a"
    je print_left

    cmp al, "d"
    je print_right

    cmp al, "q"
    je print_upleft

    cmp al, "e"
    je print_upright

    cmp al, "z"
    je print_downleft

    cmp al, "c"
    je print_downright

    ret

    print_up:
        mov esi, offset player_up
        jmp print

    print_down:
        mov esi, offset player_down
        jmp print

    print_left:
        mov esi, offset player_left
        jmp print

    print_right:
        mov esi, offset player_right
        jmp print

    print_upleft:
        mov esi, offset player_upleft
        jmp print

    print_upright:
        mov esi, offset player_upright
        jmp print

    print_downleft:
        mov esi, offset player_downleft
        jmp print

    print_downright:
        mov esi, offset player_downright
        jmp print

    print:
    mov dl, xPos
    mov dh, yPos
    call Gotoxy

    mov counter1, 3
	mov counter2, 4
	movzx ecx, counter1
	printcolumn:
		mov counter1, cl
		movzx ecx, counter2
		printrow:
			mov eax, [esi]
			call WriteChar
            
			inc esi
		loop printrow

		movzx ecx, counter1

		mov dl, xPos
		inc dh
		call Gotoxy
	loop printcolumn
    
ret
PrintPlayer ENDP

MovePlayer PROC
    mov dx, 0
    call Gotoxy

    checkInput:

    mov eax, 5
    call Delay

    ; Check for key press
    mov eax, 0
    call ReadKey
    mov inputChar, al

    cmp inputChar, VK_SPACE
    je shoot

    cmp inputChar, VK_ESCAPE
    je paused

    cmp inputChar, "w"
    je move

    cmp inputChar, "a"
    je move

    cmp inputChar, "x"
    je move

    cmp inputChar, "d"
    je move

    cmp inputChar, "q"
    je move

    cmp inputChar, "e"
    je move

    cmp inputChar, "z"
    je move

    cmp inputChar, "c"
    je move

    ; if character is invalid, check for a new keypress
    jmp checkInput

    move:
        mov al, inputChar
        mov direction, al
        jmp chosen

    paused:
        ; call your pause menu here... once you make it. for now, this will exit the game.
        ret
        
    shoot:
        call FireBall

    chosen:
        call PrintPlayer
        call MovePlayer

    ret
MovePlayer ENDP

InitialiseScreen PROC
    ; Draw the level layout at the start
    call DrawWall

    ; Set the initial player cannon position
    call PrintPlayer

    ret
InitialiseScreen ENDP

main PROC
    ; Initialize screen and emitter
    call InitialiseScreen

    ; Call Player Cannon movement function(this function is recursive, and will repeat until the game is either won or lost)
    call MovePlayer
    invoke ExitProcess,0
main ENDP
.data
    ; Player's starting position (center)
    center_x db 40      ; Column (X)
    center_y db 12      ; Row (Y)

    ; Characters representing rotations
    up_char db '^'
    down_char db 'v'
    left_char db '<'
    right_char db '>'

    ; Default character (initial direction)
    current_char db '^'

.code
fire proc
    ; Fire a projectile from the player's current face direction
    push ax
    push dx

    mov dl, center_x      ; Fire column starts at the player's X position
    mov dh, center_y      ; Fire row starts at the player's Y position

    mov al, current_char
    cmp al, up_char
    je fire_up
    cmp al, down_char
    je fire_down
    cmp al, left_char
    je fire_left
    cmp al, right_char
    je fire_right
    jmp end_fire

fire_up:
    dec dh                ; Move fire position upwards
    jmp fire_loop

fire_down:
    inc dh                ; Move fire position downwards
    jmp fire_loop

fire_left:
    dec dl                ; Move fire position leftwards
    jmp fire_loop

fire_right:
    inc dl                ; Move fire position rightwards
    jmp fire_loop

fire_loop:
    ; Ensure fire stays within the bounds of the emitter wall
    cmp dl, 1             ; Left wall boundary
    jl end_fire
    cmp dl, 79            ; Right wall boundary
    jg end_fire
    cmp dh, 10            ; Upper wall boundary
    jl end_fire
    cmp dh, 12            ; Lower wall boundary
    jg end_fire

    ; Print the fire symbol at the current position
    mov al, fire_color    ; Set fire color
    call SetTextColor
    mov dl, fire_symbol   ; Set fire symbol
    call Gotoxy
    call WriteChar

    ; Continue moving fire in the current direction (recursive)
    call fire_loop

end_fire:
    pop dx
    pop ax
    ret
fire endp
check_for_key_press proc
    ; Check if a key has been pressed and update player position or shape
    call ReadKey         ; Wait for a key press

    cmp ah, 48h          ; Up arrow key
    je up_arrow
    cmp ah, 50h          ; Down arrow key
    je down_arrow
    cmp ah, 4Dh          ; Right arrow key
    je right_arrow
    cmp ah, 4Bh          ; Left arrow key
    je left_arrow

    ret                  ; If no key matches, return to main loop

up_arrow:
    cmp center_y, 10     ; Prevent moving above the emitter wall
    jle no_move
    mov al, up_char      ; Set the character to '^'
    mov current_char, al
    dec byte ptr center_y; Move up
    ; Print the updated player character
    mov dl, current_char
    call SetTextColor
    call Gotoxy
    call WriteChar
    ret

down_arrow:
    cmp center_y, 12     ; Prevent moving below the emitter wall
    jge no_move
    mov al, down_char    ; Set the character to 'v'
    mov current_char, al
    inc byte ptr center_y; Move down
    ; Print the updated player character
    mov dl, current_char
    call SetTextColor
    call Gotoxy
    call WriteChar
    ret

right_arrow:
    cmp center_x, 79     ; Prevent moving beyond the right wall
    jge no_move
    mov al, right_char   ; Set the character to '>'
    mov current_char, al
    inc byte ptr center_x; Move right
    ; Print the updated player character
    mov dl, current_char
    call SetTextColor
    call Gotoxy
    call WriteChar
    ret

left_arrow:
    cmp center_x, 1      ; Prevent moving beyond the left wall
    jle no_move
    mov al, left_char    ; Set the character to '<'
    mov current_char, al
    dec byte ptr center_x; Move left
    ; Print the updated player character
    mov dl, current_char
    call SetTextColor
    call Gotoxy
    call WriteChar
    ret

no_move:
    ret

check_for_key_press endp
; This segment was written inside the main procedure in the original skeleton code. i do not know what these functions do, as i did not understand the "emitter" variable.
Temp PROC
    ; Main loop for player movement and updates
    main_loop:
        call check_for_key_press
        call update_emitter
        call fire    ; Call the fire procedure
        jmp main_loop

    ret
Temp ENDP

; ---------------------------------------------------------------------------------------------------------------------------------
; i have not called these functions. try to understand them before implementing them. these functions are untouched by me(i think).
update_emitter PROC
    ; Update the emitter symbols to animate the line
    push ax
    push cx
    push dx

    mov cx, 80           ; Number of columns (console width)
    mov dl, emitter_col
    mov dh, emitter_row

    ; Redraw emitter with updated colors
emitter_update_loop:
    ; Alternate emitter colors between green and red
    cmp al, emitter_color1
    jne set_green_color
    mov al, emitter_color2
    jmp draw_symbol

set_green_color:
    mov al, emitter_color1

draw_symbol:
    mov al, emitter_symbol
    call Gotoxy
    call WriteChar

    inc dl               ; Move to the next column
    cmp dl, 80           ; Wrap around at the end of the row
    jne emitter_update_loop
    mov dl, emitter_col  ; Reset column

    pop dx
    pop cx
    pop ax
    ret
update_emitter ENDP

; i have not called this function
draw_emitter PROC
    ; Draw the emitter with alternating colors
    push ax
    push cx
    push dx

    mov cx, 119          ; Number of columns (console width)
    mov dl, emitter_col
    mov dh, emitter_row

emitter_loop:
    ; Alternate emitter colors between green and red
    mov al, emitter_color1
    call SetTextColor

    mov al, emitter_symbol
    call Gotoxy
    call WriteChar

    ; Toggle color for the next symbol
    cmp al, emitter_color1
    jne set_green
    mov al, emitter_color2
    jmp next_symbol

set_green:
    mov al, emitter_color1

next_symbol:
    inc dl               ; Move to the next column
    cmp dl, 119          ; Wrap around at the end of the row
    jne emitter_loop
    mov dl, emitter_col  ; Reset column

    pop dx
    pop cx
    pop ax
    ret
draw_emitter ENDP

END main