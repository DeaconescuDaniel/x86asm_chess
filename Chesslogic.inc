ROWS equ 8
COLS equ 8

; pieces:0-nimic 1-B_Bishop 2-B_King 3-B_Knight 4-B_Pawn 5-B_Queen 6-B_Rook 7-W_Bishop 8-W_King 9-W_Knight 10-W_Pawn 11-W_Queen 12-W_Rook
board_init macro
init_square Table,1,12,25,600,10,580,0
init_square [Table+28],0,9,105,600,90,580,0
init_square [Table+2*28],1,7,185,600,170,580,0
init_square [Table+3*28],0,11,265,600,250,580,0
init_square [Table+4*28],1,8,345,600,330,580,0
init_square [Table+5*28],0,7,425,600,410,580,0
init_square [Table+6*28],1,9,505,600,490,580,0
init_square [Table+7*28],0,12,585,600,570,580,0

init_square [Table+8*28],0,10,25,520,10,500,0
init_square [Table+9*28],1,10,105,520,90,500,0
init_square [Table+10*28],0,10,185,520,170,500,0
init_square [Table+11*28],1,10,265,520,250,500,0
init_square [Table+12*28],0,10,345,520,330,500,0
init_square [Table+13*28],1,10,425,520,410,500,0
init_square [Table+14*28],0,10,505,520,490,500,0
init_square [Table+15*28],1,10,585,520,570,500,0

init_square [Table+16*28],1,0,25,440,10,420,0
init_square [Table+17*28],0,0,105,440,90,420,0
init_square [Table+18*28],1,0,185,440,170,420,0
init_square [Table+19*28],0,0,265,440,250,420,0
init_square [Table+20*28],1,0,345,440,330,420,0
init_square [Table+21*28],0,0,425,440,410,420,0
init_square [Table+22*28],1,0,505,440,490,420,0
init_square [Table+23*28],0,0,585,440,570,420,0

init_square [Table+24*28],0,0,25,360,10,340,0
init_square [Table+25*28],1,0,105,360,90,340,0
init_square [Table+26*28],0,0,185,360,170,340,0
init_square [Table+27*28],1,0,265,360,250,340,0
init_square [Table+28*28],0,0,345,360,330,340,0
init_square [Table+29*28],1,0,425,360,410,340,0
init_square [Table+30*28],0,0,505,360,490,340,0
init_square [Table+31*28],1,0,585,360,570,340,0

init_square [Table+32*28],1,0,25,280,10,260,0
init_square [Table+33*28],0,0,105,280,90,260,0
init_square [Table+34*28],1,0,185,280,170,260,0
init_square [Table+35*28],0,0,265,280,250,260,0
init_square [Table+36*28],1,0,345,280,330,260,0
init_square [Table+37*28],0,0,425,280,410,260,0
init_square [Table+38*28],1,0,505,280,490,260,0
init_square [Table+39*28],0,0,585,280,570,260,0

init_square [Table+40*28],0,0,25,200,10,180,0
init_square [Table+41*28],1,0,105,200,90,180,0
init_square [Table+42*28],0,0,185,200,170,180,0
init_square [Table+43*28],1,0,265,200,250,180,0
init_square [Table+44*28],0,0,345,200,330,180,0
init_square [Table+45*28],1,0,425,200,410,180,0
init_square [Table+46*28],0,0,505,200,490,180,0
init_square [Table+47*28],1,0,585,200,570,180,0

init_square [Table+48*28],1,4,25,120,10,100,0
init_square [Table+49*28],0,4,105,120,90,100,0
init_square [Table+50*28],1,4,185,120,170,100,0
init_square [Table+51*28],0,4,265,120,250,100,0
init_square [Table+52*28],1,4,345,120,330,100,0
init_square [Table+53*28],0,4,425,120,410,100,0
init_square [Table+54*28],1,4,505,120,490,100,0
init_square [Table+55*28],0,4,585,120,570,100,0

init_square [Table+56*28],0,6,25,40,10,20,0
init_square [Table+57*28],1,3,105,40,90,20,0
init_square [Table+58*28],0,1,185,40,170,20,0
init_square [Table+59*28],1,5,265,40,250,20,0
init_square [Table+60*28],0,2,345,40,330,20,0
init_square [Table+61*28],1,1,425,40,410,20,0
init_square [Table+62*28],0,3,505,40,490,20,0
init_square [Table+63*28],1,6,585,40,570,20,0
endm

Init_square macro sqr,color,piece,piecex,piecey,sqrx,sqry,status
	pusha
	mov dword ptr [sqr], color
    mov dword ptr [sqr+4], piece
    mov dword ptr [sqr+8], piecex
    mov dword ptr [sqr+12], piecey
    mov dword ptr [sqr+16], sqrx
    mov dword ptr [sqr+20], sqry
    mov dword ptr [sqr+24], status
	popa
endm




eval_board macro
eval_square Table
eval_square [Table+28]
eval_square [Table+2*28]
eval_square [Table+3*28]
eval_square [Table+4*28]
eval_square [Table+5*28]
eval_square [Table+6*28]
eval_square [Table+7*28]

eval_square [Table+8*28]
eval_square [Table+9*28]
eval_square [Table+10*28]
eval_square [Table+11*28]
eval_square [Table+12*28]
eval_square [Table+13*28]
eval_square [Table+14*28]
eval_square [Table+15*28]

eval_square [Table+16*28]
eval_square [Table+17*28]
eval_square [Table+18*28]
eval_square [Table+19*28]
eval_square [Table+20*28]
eval_square [Table+21*28]
eval_square [Table+22*28]
eval_square [Table+23*28]

eval_square [Table+24*28]
eval_square [Table+25*28]
eval_square [Table+26*28]
eval_square [Table+27*28]
eval_square [Table+28*28]
eval_square [Table+29*28]
eval_square [Table+30*28]
eval_square [Table+31*28]

eval_square [Table+32*28]
eval_square [Table+33*28]
eval_square [Table+34*28]
eval_square [Table+35*28]
eval_square [Table+36*28]
eval_square [Table+37*28]
eval_square [Table+38*28]
eval_square [Table+39*28]

eval_square [Table+40*28]
eval_square [Table+41*28]
eval_square [Table+42*28]
eval_square [Table+43*28]
eval_square [Table+44*28]
eval_square [Table+45*28]
eval_square [Table+46*28]
eval_square [Table+47*28]

eval_square [Table+48*28]
eval_square [Table+49*28]
eval_square [Table+50*28]
eval_square [Table+51*28]
eval_square [Table+52*28]
eval_square [Table+53*28]
eval_square [Table+54*28]
eval_square [Table+55*28]

eval_square [Table+56*28]
eval_square [Table+57*28]
eval_square [Table+58*28]
eval_square [Table+59*28]
eval_square [Table+60*28]
eval_square [Table+61*28]
eval_square [Table+62*28]
eval_square [Table+63*28]

endm


draw_title macro
	make_text_macro 'S', area, 310, 270
	make_text_macro 'A', area, 320, 270
	make_text_macro 'H', area, 330, 270
	                                
	make_text_macro 'I', area, 315, 290
	make_text_macro 'N', area, 325, 290
	                                
	make_text_macro 'A', area, 290, 310
	make_text_macro 'S', area, 300, 310
	make_text_macro 'S', area, 310, 310
	make_text_macro 'E', area, 320, 310
	make_text_macro 'M', area, 330, 310
	make_text_macro 'B', area, 340, 310
	make_text_macro 'L', area, 350, 310
	make_text_macro 'Y', area, 360, 310
	                                
	make_text_macro 'C', area, 255, 340
	make_text_macro 'L', area, 265, 340
	make_text_macro 'I', area, 275, 340
	make_text_macro 'C', area, 285, 340
	make_text_macro 'K', area, 295, 340
	                                
	make_text_macro 'T', area, 315, 340
	make_text_macro 'O', area, 325, 340
	                                
	make_text_macro 'C', area, 345, 340
	make_text_macro 'O', area, 355, 340
	make_text_macro 'N', area, 365, 340
	make_text_macro 'T', area, 375, 340
	make_text_macro 'I', area, 385, 340
	make_text_macro 'N', area, 395, 340
	make_text_macro 'U', area, 405, 340
	make_text_macro 'E', area, 415, 340
endm

select_square macro outoffset,sqr,x,y
local col,select_end,row1,row2,row3,row4,row5,row6,row7,row8,col1,col2,col3,col4,col5,col6,col7,col8,calculate
	push eax
	push ebx
	cmp y,20
	jl select_end
	cmp y,100
	jl row1
	cmp y,180
	jl row2
	cmp y,260
	jl row3
	cmp y,340
	jl row4
	cmp y,420
	jl row5
	cmp y,500
	jl row6
	cmp y,580
	jl row7
	cmp y,660
	jl row8
	row1:
	mov eax,56
	jmp col
	row2:
	mov eax,48
	jmp col
	row3:
	mov eax,40
	jmp col
	row4:
	mov eax,32
	jmp col
	row5:
	mov eax,24
	jmp col
	row6:
	mov eax,16
	jmp col
	row7:
	mov eax,8
	jmp col
	row8:
	mov eax,0
col:
	cmp x,10
	jl select_end
	cmp x,100
	jl col1
	cmp x,180
	jl col2
	cmp x,260
	jl col3
	cmp x,340
	jl col4
	cmp x,420
	jl col5
	cmp x,500
	jl col6
	cmp x,580
	jl col7
	cmp x,660
	jl col8
	col1:
	add eax,0
	jmp calculate
	col2:
	add eax,1
	jmp calculate
	col3:
	add eax,2
	jmp calculate
	col4:
	add eax,3
	jmp calculate
	col5:
	add eax,4
	jmp calculate
	col6:
	add eax,5
	jmp calculate
	col7:
	add eax,6
	jmp calculate
	col8:
	add eax,7
calculate:
	mov ebx,28
	mul ebx
	mov outoffset,eax
	add eax,offset Table
	mov ebx,[eax]
	mov dword ptr [sqr],ebx
	mov ebx,[eax+4]
    mov dword ptr [sqr+4], ebx
	mov ebx,[eax+8]
    mov dword ptr [sqr+8], ebx
	mov ebx,[eax+12]
    mov dword ptr [sqr+12], ebx
	mov ebx,[eax+16]
    mov dword ptr [sqr+16], ebx
	mov ebx,[eax+20]
    mov dword ptr [sqr+20], ebx
	mov ebx,[eax+24]
    mov dword ptr [sqr+24], ebx
	select_end:
	pop ebx
	pop eax
endm

drawpawnmoves macro sqr,color
local whitepawn,end_pawnmove
pusha
	mov ebx,color
	cmp ebx,0
	jg whitepawn
	mov ebx,2
	mov dword ptr[sqr-8*28+statusoffset],ebx
	eval_square [sqr-8*28]
	jmp end_pawnmove
	whitepawn:
	mov ebx,2
	mov dword ptr[sqr+8*28+statusoffset],ebx
	eval_square [sqr+8*28]
	end_pawnmove:
popa
endm

