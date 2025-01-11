IFNDEF	FILEHANDLING_INC
FILEHANDLING_INC	equ<1 >
MAX_RECORDS			equ<50>
BUFFER_SIZE			equ<200>

OPEN_FILE_RW macro
push			esi
push			eax
mov				esi,OFFSET FILE_NAME
invoke CreateFile, esi, GENERIC_WRITE + GENERIC_READ, \
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
mov FILE_HANDLE, eax
pop				eax
pop				esi
endm

OPEN_FILE_TR macro
push			esi
push			eax
mov				esi,OFFSET	FILE_NAME
invoke CreateFile, esi, GENERIC_WRITE + GENERIC_READ, \
		FILE_SHARE_READ, NULL,TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
mov FILE_HANDLE, eax
pop				eax
pop				esi
endm

CLOSE_FILE	macro
push			eax
mov				eax,FILE_HANDLE
call			CloseFile
xor				eax,eax
mov				FILE_HANDLE,eax
pop				eax				
endm

PUT_CHAR_BUFFER	macro
push			esi
push			eax
mov				esi, bufferPointer
add				esi, OFFSET buffer
inc				bufferPointer
mov				al,character
mov				BYTE PTR [esi], al
pop				eax
pop				esi
endm

CLEAR_BUFFER		macro
mov				esi,OFFSET buffer
push			esi
push			ecx
push			eax
mov				ecx,BUFFER_SIZE	-	1
xor				eax,eax
bufferClearLoop:
mov				BYTE PTR [esi + ecx],al
loop			bufferClearLoop
mov				BYTE PTR [esi + ecx],al
mov				bufferPointer,eax
pop				eax
pop				ecx
pop				esi
endm

READ_FILE_CHAR		macro
push			ecx
push			eax
mov				eax,FILE_HANDLE
mov				ecx,01h
lea				edx,character
call			ReadFromFile
cmp				eax,0h
jne				noEofFileHit
mov				al,01Ah
mov				character,al
noEofFileHit:
je				ExitReadFileChar
push			FILE_CURRENT
push			0
push			0
push			FILE_HANDLE
call			SetFilePointer
ExitReadFileChar:
pop				eax
pop				ecx
endm

FILE_NAME	equ	<filename>
FILE_HANDLE	equ	<filehandle>

StringCopy			proto	target:DWORD,source:DWORD,bytes:DWORD

.data

FILE_NAME		BYTE	"highScore.txt",0
FILE_HANDLE		DWORD	0h

bufferPointer	DWORD	0h
buffer			BYTE	BUFFER_SIZE	DUP(0h)
character		BYTE	0h

totalRecords	DWORD	0h
playRecords		BYTE	MAX_RECORDS	DUP(BUFFER_SIZE DUP (0h))

levelPrompt		BYTE	" Level :: ",0
scorePrompt		BYTE	" Score :: ",0
namesPrompt		BYTE	"  Name :: ",0

.code
	
outputRecord	proc

push			eax
push			esi
push			edx

mov				esi,OFFSET	buffer
mov				eax,DWORD PTR [esi]
call			WriteDec
call			Crlf

add				esi,4
mov				eax,DWORD PTR [esi]
call			WriteDec
call			Crlf

add				esi,4
mov				edx,esi
call			WriteString

pop				edx
pop				eax
pop				esi
ret
outputRecord	endp

loadRecord	proc
push			eax
push			edx
push			ecx
xor				eax,eax
mov				totalRecords,eax
mov				esi,OFFSET FILE_NAME
OPEN_FILE_RW

loadFileRecord:

readFileLine:
READ_FILE_CHAR
cmp				character,01Ah
je				exitLoadFileRecord
PUT_CHAR_BUFFER
cmp				character,0Ah
je				exitReadFileLine
jmp				readFileLine
exitReadFileLine:
mov				esi,OFFSET playRecords
mov				eax,BUFFER_SIZE
mul				totalRecords
add				esi,eax
invoke			StringCopy,esi,ADDR buffer,BUFFER_SIZE
sub				esi,eax
CLEAR_BUFFER
inc				totalRecords
jmp				loadFileRecord
exitLoadFileRecord:

CLOSE_FILE

pop				ecx
pop				edx
pop				eax
ret
loadRecord	endp

writeRecord	proc

OPEN_FILE_TR
CLOSE_FILE

mov				ecx,totalRecords
writeToFileLoop:
dec				ecx
mov				esi,OFFSET	playRecords
mov				eax,BUFFER_SIZE
mul				ecx
add				esi,eax
invoke			StringCopy,ADDR buffer,esi,BUFFER_SIZE
call			appendToFile
cmp				ecx,0h
je				exitWriteToFileLoop
jmp				writeToFileLoop
exitWriteToFileLoop:
ret
writeRecord	endp

SR_LOCAL_i	equ	<DWORD	PTR	[ebp]>
SR_LOCAL_j	equ	<DWORD	PTR	[ebp + 4]>
SR_LOCAL_ic	equ	<DWORD	PTR [ebp + 8]>
SR_LOCAL_jc	equ	<DWORD	PTR	[ebp +12]>
SR_LOCAL_i1	equ	<DWORD	PTR	[ebp +16]>
SR_LOCAL_i2	equ	<DWORD	PTR	[ebp +20]>
sortRecord	proc

mov				eax,totalRecords
cmp				eax,01h
jg				continue
ret
continue:

push			ebp
sub				esp,24
mov				ebp,esp

mov				eax,totalRecords
mov				SR_LOCAL_ic,eax
dec				eax
mov				SR_LOCAL_jc,eax

xor				eax,eax
mov				SR_LOCAL_i,eax

outerLoop:
	
xor				eax,eax
mov				SR_LOCAL_j,eax
innerLoop:
mov				esi,	OFFSET	playRecords
mov				eax,BUFFER_SIZE
mul				SR_LOCAL_j

add				esi,eax
mov				SR_LOCAL_i1,esi
add				esi,BUFFER_SIZE
mov				SR_LOCAL_i2,esi

mov				eax,[esi]
mov				esi,SR_LOCAL_i1

cmp				[esi],eax

jl				nextInnerIteration
invoke			StringCopy,ADDR buffer,SR_LOCAL_i2,BUFFER_SIZE
invoke			StringCopy,SR_LOCAL_i2,SR_LOCAL_i1,BUFFER_SIZE
invoke			StringCopy,SR_LOCAL_i1,ADDR buffer,BUFFER_SIZE
nextInnerIteration:

inc				SR_LOCAL_j
mov				eax,SR_LOCAL_j
cmp				eax,SR_LOCAL_jc
je				exitInnerLoop
jmp				innerLoop
exitInnerLoop:

mov				eax,SR_LOCAL_i
inc				SR_LOCAL_i
mov				eax,SR_LOCAL_ic
cmp				SR_LOCAL_i,eax
je				exitOuterLoop
jmp				outerLoop
exitOuterLoop:

add				esp,24
mov				ebp,esp
pop				ebp
ret
sortRecord	endp

appendToFile	proc

push			eax
push			esi
push			ecx
push			edx

mov				esi,	OFFSET	FILE_NAME
OPEN_FILE_RW

push			FILE_END
push			0
push			0
push			FILE_HANDLE
call			SetFilePointer

mov				eax,FILE_HANDLE
mov				esi,OFFSET	buffer
call			getStringBytes
mov				edx,OFFSET	buffer
call			WriteToFile

mov				eax,FILE_HANDLE

CLOSE_FILE

pop			edx
pop			ecx
pop			esi
pop			eax

ret
appendToFile	endp

getStringBytes	proc
mov				ecx,0
push			eax
countCharacters:
mov				al,BYTE	PTR	[esi]
inc				ecx

inc				esi
cmp				al,0Ah
je				exitByteFunction
jmp				countCharacters
exitByteFunction:
pop				eax

ret
getStringBytes	endp

StringCopy		proc	target:DWORD,source:DWORD,bytes:DWORD

push			esi
push			eax
push			ecx

mov				ecx,bytes

StringCopyLoop:
dec				ecx
mov				esi,source
mov				al,BYTE PTR [esi + ecx]
mov				esi,target
mov				BYTE PTR [esi + ecx],al

cmp				ecx,0h
je				exitStringCopyLoop

jmp				StringCopyLoop
exitStringCopyLoop:

pop				ecx
pop				eax
pop				esi

ret
StringCopy		endp

store_game_scores	proc

CLEAR_BUFFER

lea					esi,buffer
MOVE				DWORD PTR [esi],Score
add					esi,4
MOVE				DWORD PTR [esi],Level
add					esi,4

push				player_name_length
lea					esi,player_name
push				esi

lea					esi,buffer
add					esi,8
push				esi
call				StringCopy

add					esi,player_name_length
xor					eax,eax
mov					al,0Ah
MOVE				DWORD PTR [esi],eax
call				appendToFile
ret
store_game_scores	endp

ELSE
echo warning filehandling.inc redeclared
echo warning filehandling.inc redeclared
echo warning filehandling.inc redeclared
ENDIF