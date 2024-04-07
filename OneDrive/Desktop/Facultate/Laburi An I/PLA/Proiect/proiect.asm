.386
.model flat, stdcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;includem biblioteci, si declaram ce functii vrem sa importam
includelib msvcrt.lib
extern exit: proc
extern malloc: proc
extern memset: proc
extern printf:proc
includelib canvas.lib
extern BeginDrawing: proc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;declaram simbolul start ca public - de acolo incepe executia
public start
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;sectiunile programului, date, respectiv cod
.data
;aici declaram date
include digits.inc
include letters.inc
include Pieces.inc
include Chesslogic.inc

chessboard_green EQU 769656h
chessboard_white EQU 0EEEED2h
selected_color EQU 0BBCB2Bh
potential_move EQU 0F6F682h
capturable_piece EQU 0E4313Ch
window_title DB "Proiect PLA Deaconescu Nicolae-Daniel",0
area_width EQU 650
area_height EQU 660
area DD 0
piece_width equ 50
piece_height equ 50
counter DD 0 ; numara evenimentele de tip timer
first_click db 0 ; contorizeaza daca s-a dat click macar o data sau nu
arg1 EQU 8
arg2 EQU 12
arg3 EQU 16
arg4 EQU 20
sq dd ?
symbol_width EQU 10
symbol_height EQU 20
pieceoffset equ 4
statusoffset equ 24

square struct
	color dd ? ; 0=verde 1=alb
	piece dd ? ; piese de la 0-12
	piecex dd ? ; la acest x se deseneaza piesele
	piecey dd ? ; la acest y se deseneaza piesele
	sqrx dd ? ; la acest x se deseneaza patratele
	sqry dd ? ; la acest y se deseneaza patratele
	status dd ? ; patrat liber, patrat selectat, mutare posibila, piesa inamica de capturat, sah sau sah mat. Folosit pentru deciderea culorii de sub piesa
square ends
Table square 64 dup(<>)
Selected_square square <>
Target_square square <>
selsquareoffset dd ?
tarsquareoffset dd ?
turn db 0
has_select db 0
.code

eval_square macro sqr
local color,white,piece,piece_0,piece_1,piece_2,piece_3,piece_4,piece_5,piece_6,piece_7,piece_8,piece_9,piece_10,piece_11,piece_12,skip_piece_check,potentialmove
pusha
cmp dword ptr[sqr+statusoffset],1
jne potentialmove
	draw_square selected_color,dword ptr[sqr+16],dword ptr[sqr+20]
	jmp piece
potentialmove:
cmp dword ptr[sqr+statusoffset],2
jne color
	draw_square potential_move,dword ptr[sqr+16],dword ptr[sqr+20]
	jmp piece
	
color:
cmp dword ptr [sqr],0
	je white
	draw_square chessboard_green,dword ptr[sqr+16],dword ptr[sqr+20]
	jmp piece
	white:
	draw_square chessboard_white,dword ptr [sqr+16],dword ptr [sqr+20]
piece:
	mov eax,dword ptr[sqr+pieceoffset]
	cmp eax, 0
	je skip_piece_check
	cmp eax, 1
	je piece_1 
	cmp eax, 2 
	je piece_2 
	cmp eax, 3 
	je piece_3
	cmp eax,4
	je piece_4
	cmp eax, 5
	je piece_5
	cmp eax, 6
	je piece_6
	cmp eax, 7
	je piece_7
	cmp eax, 8 
	je piece_8
	cmp eax, 9 
	je piece_9
	cmp eax, 10 
	je piece_10
	cmp eax, 11 
	je piece_11
	cmp eax, 12 
	je piece_12
  jmp skip_piece_check
piece_1:
	make_piece_macro B_Bishop,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_2:
	make_piece_macro B_King,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_3:
   	make_piece_macro B_Knight,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
 piece_4:
	make_piece_macro B_Pawn,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_5:
	make_piece_macro B_Queen,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_6:
   	make_piece_macro B_Rook,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
  piece_7:
	make_piece_macro W_Bishop,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_8:
	make_piece_macro W_King,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_9:
   	make_piece_macro W_Knight,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_10:
	make_piece_macro W_Pawn,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_11:
	make_piece_macro W_Queen,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
piece_12:
   	make_piece_macro W_Rook,area,dword ptr[sqr+8],dword ptr[sqr+12]
	jmp skip_piece_check
skip_piece_check:
	popa
endm

;init_square square,color,piece,piecex,piecey,sqrx,sqry,status
; pieces: 0-B_Bishop 1-B_King 2-B_Knight 3-B_Pawn 4-B_Queen 5-B_Rook 6-W_Bishop 7-W_King 8-W_Knight 9-W_Pawn 10-W_Queen 11-W_Rook




; procedura make_text afiseaza o litera sau o cifra la coordonatele date
; arg1 - simbolul de afisat (litera sau cifra)
; arg2 - pointer la vectorul de pixeli
; arg3 - pos_x
; arg4 - pos_y
make_text proc
	push ebp
	mov ebp, esp
	pusha
	
	mov eax, [ebp+arg1] ; citim simbolul de afisat
	cmp eax, 'A'
	jl make_digit
	cmp eax, 'Z'
	jg make_digit
	sub eax, 'A'
	lea esi, letters
	jmp draw_text
make_digit:
	cmp eax, '0'
	jl make_space
	cmp eax, '9'
	jg make_space
	sub eax, '0'
	lea esi, digits
	jmp draw_text
make_space:	
	mov eax, 26 ; de la 0 pana la 25 sunt litere, 26 e space
	lea esi, letters
	
draw_text:
	mov ebx, symbol_width
	mul ebx
	mov ebx, symbol_height
	mul ebx
	add esi, eax
	mov ecx, symbol_height
bucla_simbol_linii:
	mov edi, [ebp+arg2] ; pointer la matricea de pixeli
	mov eax, [ebp+arg4] ; pointer la coord y
	add eax, symbol_height
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] ; pointer la coord x
	shl eax, 2 ; inmultim cu 4, avem un DWORD per pixel
	add edi, eax
	push ecx
	mov ecx, symbol_width
bucla_simbol_coloane:
	cmp byte ptr [esi], 0
	je simbol_pixel_alb
	mov dword ptr [edi], 0
	jmp simbol_pixel_next
simbol_pixel_alb:
	mov dword ptr [edi], 0FFFFFFh
simbol_pixel_next:
	inc esi
	add edi, 4
	loop bucla_simbol_coloane
	pop ecx
	loop bucla_simbol_linii
	popa
	mov esp, ebp
	pop ebp
	ret
make_text endp


make_piece proc
	push ebp
	mov ebp, esp
	pusha
	jmp draw_piece
	
draw_piece:
	mov ebx, piece_width
	mul ebx
	mov ebx, piece_height
	mul ebx
	mov ecx, piece_height
bucla_simbol_linii:
	mov edi, [ebp+arg2] ; pointer la matricea de pixeli
	mov eax, [ebp+arg4] ; pointer la coord y
	add eax, piece_height
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] ; pointer la coord x
	shl eax, 2 ; inmultim cu 4, avem un DWORD per pixel
	add edi, eax
	push ecx
	mov ecx, piece_width
bucla_simbol_coloane:
	cmp dword ptr [esi], 0ff00h
	je green
	movs dword ptr [edi],dword ptr [esi]
	jmp piece_pixel_next
	green:
	add edi,4
	add esi,4
piece_pixel_next:
	loop bucla_simbol_coloane
	pop ecx
	loop bucla_simbol_linii
	popa
	mov esp, ebp
	pop ebp
	ret
make_piece endp

make_piece_macro macro piece, drawArea,x,y
	lea esi, [piece]
	push y
	push x
	push drawArea
	push esi
	call make_piece
	add esp, 16
endm



draw_square macro color,x,y

local bucla_line,column
	pusha
	push x
	push y
	mov ecx,80
column:
	push ecx
	mov eax,y
	mov ebx,area_width
	mul ebx
	add eax,x
	shl eax,2
	add eax,area
	
	mov ecx,80
bucla_line:
	mov dword ptr[eax],color
	add eax,4
loop bucla_line
pop ecx
add dword ptr[y],1
loop column
pop y
pop x
popa
endm

; un macro ca sa apelam mai usor desenarea simbolului
make_text_macro macro symbol, drawArea, x, y
	push y
	push x
	push drawArea
	push symbol
	call make_text
	add esp, 16
endm

; functia de desenare - se apeleaza la fiecare click
; sau la fiecare interval de 200ms in care nu s-a dat click
; arg1 - evt (0 - initializare, 1 - click, 2 - s-a scurs intervalul fara click)
; arg2 - x
; arg3 - y
draw proc
	push ebp
	mov ebp, esp
	pusha
	
	mov eax, [ebp+arg1]
	cmp eax, 1
	jz evt_click
	cmp eax, 2
	jz evt_timer ; nu s-a efectuat click pe nimic
	;mai jos e codul care intializeaza fereastra cu pixeli albi
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	push 255
	push area
	call memset
	add esp, 12
	jmp afisare_litere
	
evt_click:				;pos = (y*area_width+x)<<2
	cmp first_click,0 
	je first
	cmp has_select,1
	je selected
	select_square selsquareoffset,Selected_square,dword ptr [ebp+arg2],dword ptr[ebp+arg3]
	cmp dword ptr[Selected_square+pieceoffset],0
	je final_draw
	cmp turn,0
	jg blackturn
	cmp dword ptr[Selected_square+pieceoffset],6
	jle evt_timer
	cmp dword ptr[Selected_square+pieceoffset],10
	jne not_pawn
	mov edi,selsquareoffset
	add edi,offset Table
	drawpawnmoves edi,1
	not_pawn:
	mov dword ptr[Selected_square+statusoffset],1
	eval_square Selected_square
	inc has_select
	inc turn
	jmp evt_timer
blackturn:
	cmp dword ptr[Selected_square+pieceoffset],6
	jg evt_timer
	cmp dword ptr[Selected_square+pieceoffset],4
	jne not_pawn2
	mov edi,selsquareoffset
	add edi,offset Table
	drawpawnmoves edi,0
not_pawn2:
	mov dword ptr[Selected_square+statusoffset],1
	eval_square Selected_square
	inc has_select
	dec turn
	jmp evt_timer
selected:
	dec dword ptr[Selected_square+statusoffset]
	select_square tarsquareoffset,Target_square,dword ptr [ebp+arg2],dword ptr[ebp+arg3]
	;cmp dword ptr[Target_square+statusoffset],2
	;jne evt_timer
	cmp dword ptr[Selected_square+pieceoffset],6
	jg selectedwhite
	

	
skip1:	
	mov dword ptr[Target_square+statusoffset],1
	mov eax,selsquareoffset
	mov edx,tarsquareoffset
	cmp eax,edx
	je evt_timer
	
	add eax,offset Table
	add edx,offset Table
	mov ebx,dword ptr[Selected_square+pieceoffset]
	mov dword ptr[edx+pieceoffset],ebx
	mov dword ptr[eax+pieceoffset],0
	mov dword ptr[eax+statusoffset],0
	dec has_select
	
	mov ebx,dword ptr[Selected_square+pieceoffset]
	mov dword ptr[Selected_square+pieceoffset],0
	mov dword ptr[Target_square+pieceoffset],ebx
	mov dword ptr[Target_square+statusoffset],0
	eval_square Selected_square
	eval_square Target_square
	
	jmp evt_timer
selectedwhite:
	cmp dword ptr[Target_square+pieceoffset],6
	jg evt_timer
	mov dword ptr[Target_square+statusoffset],1
	mov eax,selsquareoffset
	mov edx,tarsquareoffset
	cmp eax,edx
	je evt_timer
	
	add eax,offset Table
	add edx,offset Table
	mov ebx,dword ptr[Selected_square+pieceoffset]
	mov dword ptr[edx+pieceoffset],ebx
	mov dword ptr[eax+pieceoffset],0
	mov dword ptr[eax+statusoffset],0
	dec has_select
	
	mov ebx,dword ptr[Selected_square+pieceoffset]
	mov dword ptr[Selected_square+pieceoffset],0
	mov dword ptr[Target_square+pieceoffset],ebx
	mov dword ptr[Selected_square+statusoffset],0
	mov dword ptr[Target_square+statusoffset],0
	eval_square Selected_square
	eval_square Target_square
	

	
	mov dword ptr[Target_square+statusoffset],0

	first:					; deseneaza tabla daca e primul click
	inc first_click
	jmp erase
evt_timer:
	cmp dword ptr[Target_square+statusoffset],1
	jne skip2
	mov dword ptr[Target_square+statusoffset],0
skip2:
	inc counter
	cmp first_click,0
	je afisare_litere
afisare_litere:
	;afisam valoarea counter-ului curent (sute, zeci si unitati)
	mov ebx, 10
	mov eax, counter
	;cifra unitatilor
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 20, 0
	;cifra zecilor
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 10, 0
	;cifra sutelor
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 0, 0
	
	cmp first_click,0
	jg	erase 
	
	draw_title
	
jmp final_draw
erase:
cmp first_click,1
jg final_draw
	make_text_macro '8', area, 0, 20
	make_text_macro '7', area, 0, 100
	make_text_macro '6', area, 0, 180
	make_text_macro '5', area, 0, 260
	make_text_macro '4', area, 0, 340
	make_text_macro '3', area, 0, 420
	make_text_macro '2', area, 0, 500
	make_text_macro '1', area, 0, 580

	make_text_macro 'A', area, 40,  0
	make_text_macro 'B', area, 120, 0
	make_text_macro 'C', area, 200, 0
	make_text_macro 'D', area, 280, 0
	make_text_macro 'E', area, 360, 0
	make_text_macro 'F', area, 440, 0
	make_text_macro 'G', area, 520, 0
	make_text_macro 'H', area, 600, 0
	
	mov ecx,[area_height-20]
	mov dword ptr[arg3+ebp],20
	mov dword ptr[arg2+ebp],10
line1:
	mov eax,[arg3+ebp]
	mov ebx,area_width
	mul ebx
	add eax,[arg2+ebp]
	shl eax,2
	add eax,area
	mov dword ptr [eax],000000h
	add dword ptr [arg3+ebp],1
loop line1
	mov ecx,[area_height-20]
	mov dword ptr[arg3+ebp],20
	mov dword ptr[arg2+ebp],10
line2:
	mov eax,[arg3+ebp]
	mov ebx,area_width
	mul ebx
	add eax,[arg2+ebp]
	shl eax,2
	add eax,area
	mov dword ptr [eax],000000h
	add dword ptr [arg2+ebp],1
loop line2

	board_init
	eval_board

final_draw:
	popa
	mov esp, ebp
	pop ebp
	ret
draw endp

start:
	;alocam memorie pentru zona de desenat
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov area, eax
	;apelam functia de desenare a ferestrei
	; typedef void (*DrawFunc)(int evt, int x, int y);
	; void __cdecl BeginDrawing(const char *title, int width, int height, unsigned int *area, DrawFunc draw);
	push offset draw
	push area
	push area_height
	push area_width
	push offset window_title
	call BeginDrawing
	add esp, 20
	
	;terminarea programului
	push 0
	call exit
end start
