[org 0x0100]

jmp Start

;Alt+R to run
;Alt+Enter full screen

scoremessage            : db 'SCORE : ',0
timemessage             : db 'TIME : ',0
nextshapemessage        : db 'NEXT SHAPE :',0 
yourscoremessage        : db 'YOUR SCORE        : 0',0
highestscoremessage     : db 'HIGHEST SCORE     : 9990',0
youwonmessage           : db 'YOU WON CONGRATULATIONS!',0
yourscore               : db 0
generator: db 1

second1: 	dw 0
second2: 	dw 0
minutes:	dw 0
ldisr: 		dw 0
tickcount: 	dw 0
oldkb: 		dd 0

movement:	dw 3

randNum: 	db 0
randNum1:	db 0

oldisr: 	dd 0 		; space for saving old isr

columns:	dw 22
rows:		dw 2

colstart: dw 22
rowstart: dw 2

nextgo:		dw 0

menu1: db 'Press Escape to Exit!',0
menu2: db 'Press Space to Start!',0
menu3: db 'Exited Score: 0 :(',0


;------------------------------------------
rr: dw 2
rc: dw 2
remove: db 0
;---------------printing score--------------------------
printnumscore:
push bp
mov bp,sp
push es
push ax
push bx
push cx
push dx
push di

mov ax,0xb800
mov es, ax

mov ax,[bp+4]
mov bx,10
mov cx ,0

nextdigit12:
mov dx ,0
div bx
add dl, 0x30
push dx
inc cx
cmp ax, 0
jnz nextdigit12

mov di,[bp+6]

nextpos12:
pop dx
mov dh,0x07
mov [es: di],dx
add di,2
loop nextpos12

pop di
pop dx
pop cx
pop bx
pop ax
pop es
pop bp 
ret 4
;----------------------removing row code--------------------

;------finding row to be removed-------------------
get_row_remove:
lr1:
mov ax , 0xb800
mov es,ax

mov di,324
mov cx,44 ;width of each row of game block
jmp lr2

lr2:
cmp word [es:di],0x0720
je  lr4

lr3:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr2
;----------------------------------------------------------row2
lr4:
mov word [rr],4
mov di,644
mov cx,44
jmp lr5

lr5:
cmp word [es:di],0x0720
je  lr7

lr6:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr5
;-------------------------------------------------row3
lr7:
mov word [rr],6
mov di,964
mov cx,44
jmp lr8

lr8:
cmp word [es:di],0x0720
je  lr10

lr9:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr8
;-------------------------------------------------row4
lr10:
mov word [rr],8
mov di,1284
mov cx,44
jmp lr11

lr11:
cmp word [es:di],0x0720
je  lr13

lr12:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr11

;-------------------------------------------------row5
lr13:
mov word [rr],10
mov di,1604
mov cx,44
jmp lr14

lr14:
cmp word [es:di],0x0720
je  lr16

lr15:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr14

;-------------------------------------------------row6
lr16:
mov word [rr],12
mov di,1924
mov cx,44
jmp lr17

lr17:
cmp word [es:di],0x0720
je  lr19

lr18:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr17

;-------------------------------------------------row7
lr19:
mov word [rr],14
mov di,2244
mov cx,44
jmp lr20

lr20:
cmp word [es:di],0x0720
je  lr22

lr21:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr20

;-------------------------------------------------row8
lr22:
mov word [rr],16
mov di,2564
mov cx,44
jmp lr23

lr23:
cmp word [es:di],0x0720
je  lr25

lr24:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr23

;-------------------------------------------------row9
lr25:
mov word [rr],18
mov di,2884
mov cx,44
jmp lr26

lr26:
cmp word [es:di],0x0720
je  lr28

lr27:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr26

;-------------------------------------------------row10
lr28:
mov word [rr],20
mov di,3204
mov cx,44
jmp lr29

lr29:
cmp word [es:di],0x0720
je  lr31

lr30:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr29

;-------------------------------------------------row11
lr31:
mov word [rr],22
mov di,3524
mov cx,44
jmp lr32

lr32:
cmp word [es:di],0x0720
je  lr34

lr33:
sub cx,1
cmp cx,0
je lrexit
add di,2
jmp lr32




lrexit:
mov byte[remove],1  ; indicates row to be removed
ret

lr34:
lrexit2:
ret



;---------------------------removing founded row-----------------
remove_row:
push ax

mov ax, 0x0720
push ax
mov ax ,[rr]
push ax,
mov ax, [rc]
push ax
mov ax,[rr]
add ax,2
push ax
mov ax,[rc]
add ax,44
push ax
call drawrect

add byte [yourscore],10


mov dx,1892
push dx 
xor dx,dx
mov dx,0
mov dx,[yourscore]
sub dx,256
push dx
call printnumscore

mov ax,10
push ax
call TimeDelay

inc byte[rr]

mov ax,[rr]
push ax
call ScrollDown

inc byte[rr]

mov ax,[rr]
push ax
call ScrollDown

push cx
mov cx,2
call sound
pop cx

call Side
mov ax,1892
push ax 
mov ax,[yourscore]
sub ax,256
push ax
call printnumscore

mov byte [remove] , 0
	
pop ax	
ret

;--------------Scroll DOWN--------------------------
ScrollDown:
push bp
mov bp,sp

push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

mov ax,0xb800
mov es,ax
mov ds,ax

dec byte[bp+4]

mov ax,80
mul byte[bp+4] ;ypos (no of rows)
add ax,0;2
shl ax,1

mov si,ax

inc byte[bp+4]

mov ax,80
mul byte[bp+4] ;ypos (no of rows)
add ax,0;2
shl ax,1

mov cx,ax
mov di,ax

Down:

dec cx
mov ax,[ds:si]
mov word[es:di],ax

sub si,2
sub di,2
cmp cx,0

cmp si,322
jz ExitDown

jnz Down

ExitDown:

pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

pop bp

ret 2

;----------------SIDE-----------------------
Side:

push ax

		
		 ;------time  Block--------
    mov ax,2    ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,2    ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,7    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,7    ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
    ;------------Printing time
        mov  ax,57  ;   x horizontal
        push ax
        mov  ax, 5 ;   y  vertical
        push ax 
        mov  ax,4
        push ax
        mov  ax,timemessage
        push ax
        call write



 ;------next score Block--------
    mov ax,10    ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,10    ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,13   ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,13   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
	
	;----------LINE 1-----------
	mov ax,8    ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,8    ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,9   ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,9   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x3720   ;Format
    push ax
    call Block
    ;------------Printing score----------
        mov  ax,58  ;   x horizontal
        push ax
        mov  ax,11  ;   y  vertical
        push ax 
        mov  ax,2
        push ax
        mov  ax,scoremessage
        push ax
        call write
		
		mov ax,1892
		push ax 
		mov ax,[yourscore]
		sub ax,256
		push ax
		call printnumscore
    
 ;------next shape Block--------
    mov ax,16   ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,16   ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,23    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,23   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
	
	;-------------LINE2-------------
	
	mov ax,14   ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,14   ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,15    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,15   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x3720   ;Format
    push ax
    call Block
	
    ;------------Printing Next shape message----------
        mov  ax,51  ;   x horizontal
        push ax
        mov  ax,16  ;   y  vertical
        push ax 
        mov  ax,7
        push ax
        mov  ax,nextshapemessage
        push ax
        call write
   ;--------------------------------shape-------------
        mov ax,18   ;Y1
        push ax
        mov ax,60   ;X1
        push ax
        mov ax,18   ;Y2
        push ax
        mov ax,64   ;X2
        push ax
        mov ax,21    ;Y3
        push ax
        mov ax,60   ;X3
        push ax
        mov ax,21   ;Y4
        push ax
        mov ax,64   ;X4
        push ax
        mov ax,0x1720   ;Format
        push ax
        call Block

        mov ax,20   ;Y1
        push ax
        mov ax,64   ;X1
        push ax
        mov ax,20   ;Y2
        push ax
        mov ax,68   ;X2
        push ax
        mov ax,21    ;Y3
        push ax
        mov ax,64   ;X3
        push ax
        mov ax,21   ;Y4
        push ax
        mov ax,68   ;X4
        push ax
        mov ax,0x1720   ;Format
        push ax
        call Block


		mov ax,1892
		push ax 
		mov ax,[yourscore]
		sub ax,256
		push ax
		call printnumscore

pop ax
ret


;------------------------------------------------------------------------------------------------------------------------------------------------
ClearVariable:						; Clearing all the variables. In order to get rid of garbage values
	xor ax, ax				
	xor bx, bx				
	xor cx, cx				
	xor dx, dx				
	xor si, si				
	xor di, di				
ret

;--------------------------SHAPES SUBROUTINES-----------------------

	;-------------PRINTING L BLUE-----------------------------------
		printL:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x1720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		;right sq
		mov ax, 0x1720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

	;-------------PRINTING BS GREEN-----------------------------------
		printBS:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x2720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

	;-------------PRINTING S BLUE-----------------------------------
		printS:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x4720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		;right sq
		mov ax, 0x4720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,6
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4


		;-------------PRINTING I BLUE-----------------------------------
		printI:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x6720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

		;-------------PRINTING D BLUE-----------------------------------
		printD:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x7720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,2
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4


		;-------------PRINTING T BLUE-----------------------------------
		printT:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x5720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,2
		push ax
		mov ax, [bp+6]
		add ax,12
		push ax 
		call drawrect

		;right sq
		mov ax, 0x5720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4



;-------------------------TIME DELAY----------------------
TimeDelay:
push bp
mov bp,sp
push ax
push cx



mov cx,0xffff

TD1: mov ax,[bp+4]

        TD2:  dec ax
        jnz TD2

    dec cx
    jnz TD1
 



pop cx
pop ax
pop bp

ret 2

;-------------------------ClEAR SCREEN----------------------
ClearScreen:

push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es


mov ax,0xb800
mov es,ax

xor di,di
mov ax,0x0720
mov cx,2000

cld
rep stosw

pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret

;---------------------CALCULATE POSITION-----------------
CalculatePosition:
push bp

mov bp,sp
mov ax,0

mov al, 80  
mul byte [bp+6]     ;Y
add ax, [bp+4]      ;X
shl ax, 1

pop bp

ret 4


;---------------------------BLOCK------------------------
Block:
push bp
mov bp,sp
sub sp,10   ;4 local variable space

push ax
push bx
push cx
push dx
push si
push di
push ds
push es

;-----------TopLeft-------------
mov ax,[bp+20]   ;Y1
push ax
mov ax,[bp+18]   ;X1
push ax
call CalculatePosition  ;ax=pos
mov word[bp-2],ax

;-----------TopRight-------------
mov ax,[bp+16]   ;Y2
push ax
mov ax,[bp+14]   ;X2
push ax
call CalculatePosition  ;ax=pos
mov word[bp-4],ax

;-----------BottomLeft-------------
mov ax,[bp+12]   ;Y3
push ax
mov ax,[bp+10]   ;X3
push ax
call CalculatePosition  ;ax=pos
mov word[bp-6],ax

;-----------BottomRight-------------
mov ax,[bp+8]   ;Y4
push ax
mov ax,[bp+6]   ;X4
push ax
call CalculatePosition  ;ax=pos
mov word[bp-8],ax

;----------PRINTING----------
mov ax,0xb800
mov es,ax
xor di,di
xor si,si

mov di,[bp-2]
mov si,[bp-4]

shr word[bp-2],1   ;TopLeft
shr word[bp-4],1   ;TopRight

mov cx,[bp-4]
sub cx,[bp-2]
mov word[bp-10],cx
mov ax,[bp+4]

P1: mov cx,[bp-10]
    rep stosw

    cmp di,[bp-8]
    jz P2

    add si,160
       
    add word[bp+20],1   ;Y1
    mov ax,[bp+20]
    push ax
    mov ax,[bp+18]   ;X1
    push ax
    call CalculatePosition  ;ax=pos
   
    mov di,ax
    mov ax,[bp+4]

    jmp P1
P2:
pop es
pop ds
pop di
pop si
pop dx
pop cx
pop bx
pop ax

mov sp,bp
pop bp

ret 18


write:
push bp
mov  bp,sp

push es
push ax
push cx
push si
push di 

push ds 
pop  es

mov  di,[bp+4]
mov  cx, 0xffff
xor  al,al
repne scasb

mov  ax, 0xffff
sub  ax,cx
dec  ax

jz   exit

mov  cx,ax

mov  ax,0xb800
mov  es,ax

mov  al,80
mul  byte [bp+8]
add  ax, [bp+10]
shl  ax, 1

mov  di,ax

mov  si,[bp+4]
mov  ah,[bp+6]

cld

nextchar:
lodsb 
stosw
loop nextchar

exit:
pop di
pop si
pop cx
pop ax
pop es
pop bp
ret 8

;----------------------drawing rectangle------------------
		drawrect:
		push bp  
		mov bp,sp
		mov cx, [bp + 6]
		sub cx, [bp + 10]  ; cx is counter of rows
		mov bx, [bp+12]
		l1:
		mov dx,[bp+4]
		sub dx,[bp+8]  ; no of columns in dx
		mov ax, 0
		mov al,80 
		mul byte[bp+10]
		add ax,[bp+8]
		shl ax,1
		mov di,ax
		l2:
		mov word[es:di],bx
		add di,2
		sub dx,1
		jnz l2
		add word [bp+10],1
		sub cx,1
		jnz l1
		pop bp 
		ret 10


;----------------------RANDOM-------------------
RandomGen:
        push bp
        mov bp, sp
        push cx
        push dx
        push ax

        rdtsc                   ;getting a random number in ax dx
        xor dx, dx               ;making dx 0
        mov cx, 6
        div cx                  ;dividing by 'Paramter' to get numbers from 0 - Parameter
		add dl, 1
        mov [randNum], dl      ;moving the random number in variable

        pop ax
        pop dx
        pop cx
        pop bp
ret

;----------------------------RANDOM SHAPE-------------------
Print_Random_Shape:
push ax

	mov ax, 0
	mov word [rowstart], 2
	mov word [colstart], 22
	mov word [rows], 2
	mov word [columns], 22
	
	mov al, [randNum1]
	cmp byte al, 6
	je its6r

	mov al, [randNum1]
	cmp byte al, 5
	je its5r
	
	mov al, [randNum1]
	cmp byte al, 4
	je its4r
	
	mov al, [randNum1]
	cmp byte al, 3
	je its3r

	mov al, [randNum1]
	cmp byte al, 2
	je its2r
	jmp its1r

its6r:
	mov ax, [columns]	;ax=22
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printT
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	
	call CheckDownT
	
	cmp word [nextgo], 1
	jne move6
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printTcover
	
	add word [rowstart], 1
	add word [rows], 1
	jmp its6r
move6:
	pop ax
	ret
	
its5r:
	mov ax, [columns]	;ax=22
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printD
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	
	call CheckDownD
	
	cmp word [nextgo], 1
	jne move5
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printDcover
	
	add word [rowstart], 1
	add word [rows], 1
	jmp its5r
move5:
	pop ax
	ret
	
its4r:
	mov ax, [columns]	;ax=22
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printI
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	
	call CheckDownI
	
	cmp word [nextgo], 1
	jne move4
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printIcover
	
	add word [rowstart], 1
	add word [rows], 1
	jmp its4r
move4:
	pop ax
	ret

its3r:
	mov ax, [columns]
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printS
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call CheckDownS
	
	cmp word [nextgo], 1
	jne move3
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printScover
	
	add word [rowstart], 1
	add word [rows], 1
	
	jmp its3r
move3:
	mov byte[generator],1
	pop ax
	ret
	
its2r:
	mov ax, [columns]	;ax=22
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printBS
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	
	call CheckDownBS
	
	cmp word [nextgo], 1
	jne move2
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printBScover
	
	add word [rowstart], 1
	add word [rows], 1
	jmp its2r
move2:
	pop ax
	ret
	
its1r:
	mov ax, [columns]	;ax=22
	mov [colstart], ax
	
	mov ax, [rows]
	mov [rowstart], ax
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printL
	
	mov ax,5
	push ax
	call TimeDelay
	
	add word [rowstart], 1
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	
	call CheckDownL
	
	cmp word [nextgo], 1
	jne move1
	
	sub word [rowstart], 1
	
	mov ax, [columns]
	mov [colstart], ax
	mov ax, [rows]
	mov [rowstart], ax	
	
	mov ax, [colstart]		; Cols
	push ax
	mov ax, [rowstart]		; Rows
	push ax
	call printLcover
	
	add word [rowstart], 1
	add word [rows], 1
	jmp its1r
move1:
	pop ax
	ret
	
;----------------------------------------CHECK NEXT DOWN-----------------------------------------------
CheckDown:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],5
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	
	mov di,ax
		
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgo
	mov word [nextgo], 1
	jmp exit_check_next

cannotgo:
	mov word [nextgo], 0

exit_check_next:
	pop cx
	pop di
	pop es
	pop bp
ret 4


CheckDownS:

	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],5
	add byte[bp+6],7
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgosd2
			
	sub byte[bp+4],2
	sub byte[bp+6],7
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720	
	jne cannotgoSd
	
	mov word [nextgo], 1
	jmp exit_check_nextSd
	
cannotgosd2:
    mov word [nextgo], 0
cannotgoSd:
	mov word [nextgo], 0

exit_check_nextSd:
	pop cx
	pop di
	pop es
	pop bp
ret 4
	

CheckDownL:


push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],3
	add byte[bp+6],7
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgold1
	
	sub byte [bp+6],7
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgold

	mov word [nextgo], 1
	jmp exit_check_nextld
	
cannotgold1:
	mov word [nextgo], 0
cannotgold:
	mov word [nextgo], 0

exit_check_nextld:
	pop cx
	pop di
	pop es
	pop bp
ret 4


CheckDownBS:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	
	add byte[bp+4],3
	add byte[bp+6],7
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgobsd1
	
	
	sub byte [bp+6],7
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgobsd
	
	mov word [nextgo], 1
	jmp exit_check_nextbsd

cannotgobsd1:
    mov word [nextgo], 0
cannotgobsd:
	mov word [nextgo], 0

exit_check_nextbsd:
	pop cx
	pop di
	pop es
	pop bp
ret 4

CheckDownI:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],3
	add byte[bp+6],3
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoId
	
	mov word [nextgo], 1
	
	jmp exit_check_nextId

cannotgoId:
	mov word [nextgo], 0

exit_check_nextId:
	pop cx
	pop di
	pop es
	pop bp
ret 4

CheckDownD:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],1
	add byte[bp+6],1
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgodd
	
	mov word [nextgo], 1
	jmp exit_check_nextdd

cannotgodd:
	mov word [nextgo], 0

exit_check_nextdd:
	pop cx
	pop di
	pop es
	pop bp
ret 4


CheckDownT:

	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di

	mov ax, 0xb800
	mov es, ax
	
	add byte[bp+4],3
	add byte[bp+6],7
	
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgotd2
			
	sub byte[bp+4],2
	sub byte[bp+6],7
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720	
	jne cannotgotd
	
	add byte[bp+6],11
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax	
	mov word ax, [es:di]
	cmp ax, 0x0720	
	jne cannotgotd3
	
	mov word [nextgo], 1
	jmp exit_check_nexttd
	
cannotgotd2:
    mov word [nextgo], 0
cannotgotd:
	mov word [nextgo], 0
cannotgotd3:
	mov word [nextgo], 0

exit_check_nexttd:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;-------------------------NEXT SHAPE-------------------
Print_Random_NextShape:
push ax

	mov ax, 0
	mov al, [randNum]
	
	cmp byte al, 6
	je shapen6
	
	mov al, [randNum]
	cmp byte al, 5
	je shapen5
	
	mov al, [randNum]
	cmp byte al, 4
	je shapen4

	mov al, [randNum]
	cmp byte al, 3
	je shapen3

	mov al, [randNum]
	cmp byte al, 2
	je shapen2
	
	jmp shapen1
	
shapen6:

	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printT
	
pop ax
ret

shapen5:
	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printD
	
pop ax
ret

shapen4:
	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printI
	
pop ax
ret
	
shapen3:
	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printS
	
pop ax
ret

shapen2:
	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printBS
	
pop ax
ret

shapen1:
	mov ax, 60		;Cols
	push ax
	mov ax, 18		;Rows
	push ax
	call printL
	
pop ax
ret


;--------------------------SCREEN 1----------------------

Screen1:
push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

;------CYAN BLOCK-----
mov ax,0    ;Y1
push ax
mov ax,0    ;X1
push ax
mov ax,0   ;Y2
push ax
mov ax,80   ;X2
push ax
mov ax,25   ;Y3
push ax
mov ax,0   ;X3
push ax
mov ax,25   ;Y4
push ax
mov ax,80   ;X4
push ax
mov ax,0x3720   ;Format
push ax
call Block

;-----BLUE BLOCK---
mov ax,7    ;Y1
push ax
mov ax,7    ;X1
push ax
mov ax,7   ;Y2
push ax
mov ax,73   ;X2
push ax
mov ax,17   ;Y3
push ax
mov ax,7   ;X3
push ax
mov ax,17   ;Y4
push ax
mov ax,73  ;X4
push ax
mov ax,0x1720   ;Format
push ax
call Block

;-----BLACK BLOCK---
mov ax,9    ;Y1
push ax
mov ax,10    ;X1
push ax
mov ax,9   ;Y2
push ax
mov ax,70   ;X2
push ax
mov ax,15   ;Y3
push ax
mov ax,10   ;X3
push ax
mov ax,15   ;Y4
push ax
mov ax,70   ;X4
push ax
mov ax,0x0720   ;Format
push ax
call Block

;-----PRINTING UFO---

	mov ax,5
	push ax
	call TimeDelay

    ;-----printing U-----
    mov ax,10   ;Y1
    push ax          ;top left
    mov ax,27   ;X1
    push ax
    mov ax,10   ;Y2
    push ax          ;top right
    mov ax,34   ;X2
    push ax
    mov ax,14   ;Y3
    push ax          ;bottom left
    mov ax,27   ;X3
    push ax
    mov ax,14   ;Y4
    push ax          ;bottom right
    mov ax,34   ;X4
    push ax
    mov ax,0x2720   ;Format
    push ax
    call Block

    mov ax,10   ;Y1
    push ax          ;top left
    mov ax,29   ;X1
    push ax
    mov ax,10   ;Y2
    push ax          ;top right
    mov ax,32   ;X2
    push ax
    mov ax,13   ;Y3
    push ax          ;bottom left
    mov ax,29   ;X3
    push ax
    mov ax,13   ;Y4
    push ax          ;bottom right
    mov ax,32   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
	
	mov ax,5
	push ax
	call TimeDelay
   
    ;-----Print F------
    mov ax,10   ;Y1
    push ax          ;top left
    mov ax,37   ;X1
    push ax
    mov ax,10   ;Y2
    push ax          ;top right
    mov ax,43   ;X2
    push ax
    mov ax,14   ;Y3
    push ax          ;bottom left
    mov ax,37   ;X3
    push ax
    mov ax,14   ;Y4
    push ax          ;bottom right
    mov ax,43   ;X4
    push ax
    mov ax,0x5720   ;Format
    push ax
    call Block

    mov ax,11   ;Y1
    push ax          ;top left
    mov ax,39   ;X1
    push ax
    mov ax,11   ;Y2
    push ax          ;top right
    mov ax,43   ;X2
    push ax
    mov ax,11   ;Y3
    push ax          ;bottom left
    mov ax,39   ;X3
    push ax
    mov ax,11   ;Y4
    push ax          ;bottom right
    mov ax,43   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block

    mov ax,13   ;Y1
    push ax          ;top left
    mov ax,39   ;X1
    push ax
    mov ax,13   ;Y2
    push ax          ;top right
    mov ax,43   ;X2
    push ax
    mov ax,14   ;Y3
    push ax          ;bottom left
    mov ax,39   ;X3
    push ax
    mov ax,14   ;Y4
    push ax          ;bottom right
    mov ax,43   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
	
	mov ax,5
	push ax
	call TimeDelay

    ;-----Printing O---
    mov ax,10   ;Y1
    push ax          ;top left
    mov ax,46   ;X1
    push ax
    mov ax,10   ;Y2
    push ax          ;top right
    mov ax,53   ;X2
    push ax
    mov ax,14   ;Y3
    push ax          ;bottom left
    mov ax,46   ;X3
    push ax
    mov ax,14   ;Y4
    push ax          ;bottom right
    mov ax,53   ;X4
    push ax
    mov ax,0x4720   ;Format
    push ax
    call Block
   
    mov ax,11   ;Y1
    push ax          ;top left
    mov ax,48   ;X1
    push ax
    mov ax,11   ;Y2
    push ax          ;top right
    mov ax,51   ;X2
    push ax
    mov ax,13   ;Y3
    push ax          ;bottom left
    mov ax,48   ;X3
    push ax
    mov ax,13   ;Y4
    push ax          ;bottom right
    mov ax,51   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block

	mov ax,20
	push ax
	call TimeDelay

pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret

;-------------------------Screen2-----------------------
Screen2:
push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

;----------entire rectangle---------

    ;------CYAN BLOCK-----
    mov ax,0    ;Y1
    push ax
    mov ax,0    ;X1
    push ax
    mov ax,0    ;Y2
    push ax
    mov ax,80   ;X2
    push ax
    mov ax,25   ;Y3
    push ax
    mov ax,0    ;X3
    push ax
    mov ax,25   ;Y4
    push ax
    mov ax,80   ;X4
    push ax
    mov ax,0x3720   ;Format
    push ax
    call Block
    ;--------black block-----
    mov ax, 2   ;Y1
    push ax
    mov ax,2    ;X1    
    push ax
    mov ax,2    ;Y2
    push ax
    mov ax,46   ;X2
    push ax
    mov ax,23   ;Y3
    push ax
    mov ax,2    ;X3
    push ax
    mov ax,23   ;Y4
    push ax
    mov ax,46   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block

    ;--------black line separation-----
    mov ax, 0   ;Y1
    push ax
    mov ax,47   ;X1    
    push ax
    mov ax,0    ;Y2
    push ax
    mov ax,49   ;X2
    push ax
    mov ax,25   ;Y3
    push ax
    mov ax,47   ;X3
    push ax
    mov ax,25   ;Y4
    push ax
    mov ax,49   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block

 ;------time  Block--------
    mov ax,2    ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,2    ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,7    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,7    ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
    ;------------Printing time
        mov  ax,57  ;   x horizontal
        push ax
        mov  ax, 5 ;   y  vertical
        push ax 
        mov  ax,4
        push ax
        mov  ax,timemessage
        push ax
        call write

;------next score Block--------
    mov ax,10    ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,10    ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,13   ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,13   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
    ;------------Printing score----------
        mov  ax,58  ;   x horizontal
        push ax
        mov  ax,11  ;   y  vertical
        push ax 
        mov  ax,2
        push ax
        mov  ax,scoremessage
        push ax
        call write
    
 ;------next shape Block--------
    mov ax,16   ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,16   ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,23    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,23   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
    ;------------Printing Next shape message----------
        mov  ax,51  ;   x horizontal
        push ax
        mov  ax,16  ;   y  vertical
        push ax 
        mov  ax,7
        push ax
        mov  ax,nextshapemessage
        push ax
        call write
  

pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret
;-----------------------------------------------------------------------------------------
NextShape_Block:

push ax

	mov ax,16   ;Y1
    push ax
    mov ax,50   ;X1
    push ax
    mov ax,16   ;Y2
    push ax
    mov ax,78   ;X2
    push ax
    mov ax,23    ;Y3
    push ax
    mov ax,50   ;X3
    push ax
    mov ax,23   ;Y4
    push ax
    mov ax,78   ;X4
    push ax
    mov ax,0x0720   ;Format
    push ax
    call Block
    ;------------Printing Next shape message----------
	mov  ax,51  ;   x horizontal
	push ax
	mov  ax,16  ;   y  vertical
	push ax 
	mov  ax,7
	push ax
	mov  ax,nextshapemessage
	push ax
	call write
		
pop ax
ret

;--------------------------SCREEN 3----------------------

Screen3:
push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

mov ax,20
push ax
call TimeDelay

call ClearScreen

;------CYAN BLOCK-----
mov ax,0    ;Y1
push ax
mov ax,0    ;X1
push ax
mov ax,0   ;Y2
push ax
mov ax,80   ;X2
push ax
mov ax,25   ;Y3
push ax
mov ax,0   ;X3
push ax
mov ax,25   ;Y4
push ax
mov ax,80   ;X4
push ax
mov ax,0x3720   ;Format
push ax
call Block

;-----BLUE BLOCK---
mov ax,7    ;Y1
push ax
mov ax,7    ;X1
push ax
mov ax,7   ;Y2
push ax
mov ax,73   ;X2
push ax
mov ax,17   ;Y3
push ax
mov ax,7   ;X3
push ax
mov ax,17   ;Y4
push ax
mov ax,73  ;X4
push ax
mov ax,0x1720   ;Format
push ax
call Block

;-----BLACK BLOCK---
mov ax,9    ;Y1
push ax
mov ax,10    ;X1
push ax
mov ax,9   ;Y2
push ax
mov ax,70   ;X2
push ax
mov ax,15   ;Y3
push ax
mov ax,10   ;X3
push ax
mov ax,15   ;Y4
push ax
mov ax,70   ;X4
push ax
mov ax,0x0720   ;Format
push ax
call Block


;-----------printing your score-----------
    mov  ax,28  ;   x horizontal
    push ax
    mov  ax,12  ;   y  vertical
    push ax 
    mov  ax,7
    push ax
    mov  ax,yourscoremessage
    push ax
    call write
	
	mov ax,2016
	push ax 
	mov ax,[yourscore]
	push ax
	call printnumscore

;-----------printing highest score--------
    ;mov  ax,28  ;   x horizontal
    ;push ax
    ;mov  ax,10  ;   y  vertical
    ;push ax 
    ;mov  ax,7
    ;push ax
    ;mov  ax,highestscoremessage
   ; push ax
    ;call write

;-----------printing you won--------------
    mov  ax,28  ;   x horizontal
    push ax
    mov  ax,12  ;   y  vertical
    push ax 
    mov  ax,7
    push ax
    mov  ax, youwonmessage
    push ax
    ;call write


mov ax,100
push ax
call TimeDelay


pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret

;-------------------TIMER-------------------
printnum1: 
	push bp 
 	mov bp, sp 
 	push es 
 	push ax 
 	push bx 
 	push cx 
 	push dx 
 	push di 
 
	mov ax, 0xb800 
 	mov es, ax			; point es to video base 
 	mov ax, [bp+4] 			; load number in ax 
 	mov bx, 10 			; use base 10 for division 
 	mov cx, 0 			; initialize count of digits 

nextdigit: 
	mov dx, 0 			; zero upper half of dividend 
 	div bx 				; divide by 10 
 	add dl, 0x30 			; convert digit into ascii value 
 	push dx 			; save ascii value on stack 
 	inc cx 				; increment count of values 
 	cmp ax, 0 			; is the quotient zero 
 	jnz nextdigit 			; if no divide it again 
 	mov di, [bp+6] 			; point di to 70th column 
nextpos: 
	pop dx 				; remove a digit from the stack 
 	mov dh, 0x04 			; use normal attribute 
 	mov [es:di], dx	 		; print char on screen 
 	add di, 2 			; move to next screen location 
 	loop nextpos 			; repeat for all digits on stack 
 
	pop di 
 	pop dx 
 	pop cx 
 	pop bx 
 	pop ax
 	pop es 
 	pop bp 
 ret 4

;------------------------------------------------------------------------------------------------------------------------------------------------
timer:
	jmp started

ended:
	jmp Screen3

started:
	cmp word[cs:minutes], 5
	je ended
	cmp byte[generator],0
	je ended
 	push ax
	inc word [cs:tickcount]		; increment tick count
	cmp word[cs:tickcount], 18
	je update
	cmp word[cs:tickcount], 18
	jne kk

update:
    	mov word[cs:tickcount], 0
	inc word[cs:second2]
    	cmp word[cs:second2], 10
	jl kk
	
	mov word[cs:second2], 0
	inc word[cs:second1]
	cmp word[cs:second1], 6	
	jne kk
	
	inc word [cs:minutes] 
	mov word [cs:second1], 0
	cmp word [cs:minutes], 5
	je ended

kk:
    mov ax, 850+78
	push ax
	push word [cs:minutes]
	call printnum1 
	
	mov ax, 0xb800
	mov es, ax
	mov ah, 0x04
	mov al, ':'
	mov word[es:852+78], ax
		
    	mov ax, 854+78
	push ax
	push word [cs:second1]
	call printnum1 
	
	mov ax, 856+78
	push ax
	push word [cs:second2]
	call printnum1 
	
kl:
	mov al, 0x20
	out 0x20, al 		; end of interrupt
	pop ax
iret 				; return from interrupt

;------------------------------COVERS--------------------------------
printLcover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		;right sq
		mov ax, 0x0720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

	;-------------PRINTING BS GREEN-----------------------------------
printBScover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

	;-------------PRINTING S BLUE-----------------------------------
printScover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		;right sq
		mov ax, 0x0720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,6
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4


		;-------------PRINTING I BLUE-----------------------------------
printIcover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

		;-------------PRINTING D BLUE-----------------------------------
printDcover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,2
		push ax
		mov ax, [bp+6]
		add ax,4
		push ax 
		call drawrect

		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4

printTcover:
		push bp
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push ds
		push es
		mov ax,0xb800
		mov es,ax

		;left rect
		mov ax, 0x0720  ;attribute;;;;;;;;;;;;;;;;;;;;;
		push ax
		mov ax,[bp+4]  ; ycoordinate
		push ax
		mov ax,[bp+6]  ; xcordinate
		push ax, 
		mov ax, [bp+4]
		add ax,2
		push ax
		mov ax, [bp+6]
		add ax,12
		push ax 
		call drawrect

		;right sq
		mov ax, 0x0720  ;attribute
		push ax
		mov ax,[bp+4]  ; ycoordinate
		add ax,2
		push ax
		mov ax,[bp+6]  ; xcordinate
		add ax,4
		push ax, 
		mov ax, [bp+4]
		add ax,4
		push ax
		mov ax, [bp+6]
		add ax,8
		push ax 
		call drawrect
		pop es
		pop ds
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 4
;---------------------------------------------------------------------		
;-----------------------------CHECKS----------------------------------
;---------------------------------------------------------------------

;------------------CheckRights-------------------------------
CheckRightS:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax

    add byte[bp+6],8  ;x
	add byte[bp+4],2  ;y
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoS
	
	add byte[bp+4],1  ;y
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSr1
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSr2
	
	sub byte[bp+6],4
	sub byte[bp+4],5
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSr3
	
	mov word [nextgo], 1
	jmp exit_check_nextS

cannotgoS:
	mov word [nextgo], 0
cannotgoSr1:
	mov word [nextgo], 0
cannotgoSr2:
	mov word [nextgo], 0
cannotgoSr3:
	mov word [nextgo], 0

exit_check_nextS:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckLefts-------------------------------
CheckLeftS:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSl1
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSl2
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSl3
	
	add byte[bp+4],2
	add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]    
	add ax, [bp+6]      
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoSl4
	
	mov word [nextgo], 1
	jmp exit_check_nextSl

cannotgoSl1:
	mov word [nextgo], 0
cannotgoSl2:
	mov word [nextgo], 0	
cannotgoSl3:
	mov word [nextgo], 0
cannotgoSl4:
	mov word [nextgo], 0
	
exit_check_nextSl:
	pop cx
	pop di
	pop es
	pop bp
ret 4
;------------------CheckRightT-------------------------------
CheckRightT:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax


    add byte[bp+6],12
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTr1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTr2
	
	add byte[bp+4],2
	sub byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTr3
	
	mov word [nextgo], 1
	jmp exit_check_nextTr

    cannotgoTr1:
	mov word [nextgo], 0	
    cannotgoTr2:
	mov word [nextgo], 0
    cannotgoTr3:
	mov word [nextgo], 0
	
exit_check_nextTr:
	pop cx
	pop di
	pop es
	pop bp
ret 4


;------------------CheckLeftT--------------------------------
CheckLeftT:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTl1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTl2
	
	add byte[bp+4],2
	add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoTl3
	
	mov word [nextgo], 1
	jmp exit_check_nextTl

    cannotgoTl1:
		mov word [nextgo], 0	
    cannotgoTl2:
		mov word [nextgo], 0
    cannotgoTl3:
		mov word [nextgo], 0
	
exit_check_nextTl:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckRightBS-------------------------------
CheckRightBS:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax


    add byte[bp+6],8
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSr1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSr2
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSr3
	
	mov word [nextgo], 1
	jmp exit_check_nextBSr

    cannotgoBSr1:
	mov word [nextgo], 0	
    cannotgoBSr2:
	mov word [nextgo], 0
    cannotgoBSr3:
	mov word [nextgo], 0
	
exit_check_nextBSr:
	pop cx
	pop di
	pop es
	pop bp
ret 4


;------------------CheckLeftBS--------------------------------
CheckLeftBS:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSl1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSl2
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoBSl3
	
	mov word [nextgo], 1
	jmp exit_check_nextBSl

    cannotgoBSl1:
		mov word [nextgo], 0	
    cannotgoBSl2:
		mov word [nextgo], 0
    cannotgoBSl3:
		mov word [nextgo], 0
	
exit_check_nextBSl:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckRightL-------------------------------
CheckRightL:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax


    add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLr1
	
	add byte[bp+4],2
	add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLr2
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLr3
	
	mov word [nextgo], 1
	jmp exit_check_nextLr

    cannotgoLr1:
	mov word [nextgo], 0	
    cannotgoLr2:
	mov word [nextgo], 0
    cannotgoLr3:
	mov word [nextgo], 0
	
exit_check_nextLr:
	pop cx
	pop di
	pop es
	pop bp
ret 4


;------------------CheckLeftL--------------------------------
CheckLeftL:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLl1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLl2
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoLl3
	
	mov word [nextgo], 1
	jmp exit_check_nextLl

    cannotgoLl1:
		mov word [nextgo], 0	
    cannotgoLl2:
		mov word [nextgo], 0
    cannotgoLl3:
		mov word [nextgo], 0
	
exit_check_nextLl:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckRightI-------------------------------
CheckRightI:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax


    add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIr1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIr2
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIr3
	
	mov word [nextgo], 1
	jmp exit_check_nextIr

    cannotgoIr1:
	mov word [nextgo], 0	
    cannotgoIr2:
	mov word [nextgo], 0
    cannotgoIr3:
	mov word [nextgo], 0
	
exit_check_nextIr:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckLeftI--------------------------------
CheckLeftI:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIl1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIl2
	
	add byte[bp+4],2
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoIl3
	
	mov word [nextgo], 1
	jmp exit_check_nextIl

    cannotgoIl1:
		mov word [nextgo], 0	
    cannotgoIl2:
		mov word [nextgo], 0
    cannotgoIl3:
		mov word [nextgo], 0
	
exit_check_nextIl:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckRightD-------------------------------
CheckRightD:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax


    add byte[bp+6],4
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoDr1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoDr2
	
	
	mov word [nextgo], 1
	jmp exit_check_nextDr

    cannotgoDr1:
	mov word [nextgo], 0	
    cannotgoDr2:
	mov word [nextgo], 0
	
exit_check_nextDr:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;------------------CheckLeftD--------------------------------
CheckLeftD:
	push bp				; Pushing so that previous value can be safe
	mov bp, sp
	push es				
	push di				
	push cx
	
	xor di,di
	mov ax, 0xb800
	mov es, ax
	
	dec byte[bp+6]
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoDl1
	
	add byte[bp+4],1
	mov al, 80  
	mul byte [bp+4]   ;y   
	add ax, [bp+6]    ;x  
	shl ax, 1
	mov di,ax
	mov word ax, [es:di]
	cmp ax, 0x0720
	jne cannotgoDl2
	
	mov word [nextgo], 1
	jmp exit_check_nextDl

    cannotgoDl1:
		mov word [nextgo], 0	
    cannotgoDl2:
		mov word [nextgo], 0
	
exit_check_nextDl:
	pop cx
	pop di
	pop es
	pop bp
ret 4

;-----------------------------MOVEMENT--------------------------------
kbisr:

		push ax
		push es
		
		mov ax,0

		mov al, [randNum1]
		cmp byte al, 6
		jz movement6

		mov al, [randNum1]
		cmp byte al, 5
		jz movement5

		mov al, [randNum1]
		cmp byte al, 4
		jz movement4
		
		mov al, [randNum1]
		cmp byte al, 3
		jz movement3
		
		mov al, [randNum1]
		cmp byte al, 2
		jz movement2
		
		jmp movement1

;-----------------------------------------------movement 6----T---------------------------------------
movement6:
		in al, 0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp6  		; no, try next comparison

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		call CheckLeftT
		
		cmp byte[nextgo],1
		jne nomatch6

		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printTcover
		
		sub word [columns],4	;columns=20


		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printT

		jmp nomatch6     	; leave interrupt routine
	 
	nextcmp6: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch6 		; no, leave interrupt routine
		
		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		call CheckRightT
		
		cmp byte[nextgo],1
		jne nomatch6

		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printTcover
		
		add word [columns],4	;columns=23

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printT

	nomatch6:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR

;----------------------------------------------movement 5---D-----------------------------------------------------

movement5:
		in al,  0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp5  		; no, try next comparison

        mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckLeftD
		cmp byte[nextgo],1
		jne nomatch5


		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printDcover
		
		sub word [columns],4	;columns=20

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printD

		jmp nomatch5     	; leave interrupt routine
	 
	nextcmp5: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch5 		; no, leave interrupt routine

        mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckRightD
		cmp byte[nextgo],1
		jne nomatch5
		

		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printDcover
		
		add word [columns],4;columns=23

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printD

	nomatch5:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR

;-----------------------------------------------movement 4-------I-----------------------------------------------		
movement4:
		in al, 0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp4  		; no, try next comparison
	 
		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckLeftI
		cmp byte[nextgo],1
		jne nomatch4
	 
	 
		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printIcover
		
		sub word [columns],4	;columns=20

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printI

		jmp nomatch4     	; leave interrupt routine
	 
	nextcmp4: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch4 		; no, leave interrupt routine

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckRightI
		cmp byte[nextgo],1
		jne nomatch4


		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printIcover
		
		add word [columns],4	;columns=23

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printI

	nomatch4:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR

;----------------------------------------------movement 3-----------S---------------------------------------------
movement3:
		in al, 0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp3  		; no, try next comparison
		
		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckLeftS
		cmp byte[nextgo],1
		jne nomatch3

		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printScover
		
		sub word [columns],4	;columns=20   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printS

		jmp nomatch3     	; leave interrupt routine
	 
	nextcmp3: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch3 		; no, leave interrupt routine
		
		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckRightS
		
		cmp byte[nextgo],1
		jne nomatch3

		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printScover
		
		add word [columns],4	;columns=23;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printS

	nomatch3:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR
;----------------------------------------------movement 2---------BS----------------------------------------------
movement2:
		in al, 0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp2  		; no, try next comparison

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckLeftBS
		cmp byte[nextgo],1
		jne nomatch2


		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printBScover
		
		sub word [columns],4	;columns=20

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printBS

		jmp nomatch2     	; leave interrupt routine
	 
	nextcmp2: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch2 		; no, leave interrupt routine

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckRightBS
		cmp byte[nextgo],1
		jne nomatch2


		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printBScover
		
		add word [columns],4	;columns=23

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printBS

	nomatch2:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR
;----------------------------------------------movement 1------------L--------------------------------------------
movement1:
		in al, 0x60  		; read a char from keyboard port
		cmp al, 0x4b 		; is the key left
		jne nextcmp1  		; no, try next comparison

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckLeftL
		cmp byte[nextgo],1
		jne nomatch1


		mov ax,[colstart]
		mov word [columns], ax	;columns=22
		
		mov ax,[rowstart]
		mov word [rows], ax	;rows=2

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printLcover
		
		sub word [columns],4	;columns=20

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printL

		jmp nomatch1     	; leave interrupt routine
	 
	nextcmp1: 
		cmp al, 0x4d 		; is the key right shift
		jne nomatch1 		; no, leave interrupt routine

		mov ax,[colstart]
		push ax
		mov ax,[rowstart]
		push ax
		
		call CheckRightL
		cmp byte[nextgo],1
		jne nomatch1

		mov ax,[colstart]
		mov word [columns], ax
		
		mov ax,[rowstart]
		mov word [rows], ax
		
		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printLcover
		
		add word [columns],4	;columns=23

		mov ax, [columns]		; Cols
		push ax
		mov ax, [rows]			; Rows
		push ax
		call printL

	nomatch1:
		mov ax,[columns]
		mov word[colstart],ax
		mov ax,[rows]
		mov word[rowstart],ax 
		pop es
		pop ax
		jmp far [cs:oldisr] 	; call the original ISR
		
;------------Top Row Check-----------------
TopCheck:
push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

Qr1:
mov ax , 0xb800
mov es,ax

mov di,324
mov cx,44 ;width of each row of game block
jmp Qr2

Qr2:
cmp word [es:di],0x0720
jne  Qrexit

Qr3:
sub cx,1
cmp cx,0
je Qr7
add di,2
jmp Qr2
;----------------------------------------------------------row2
Qr4:
mov word [rr],4
mov di,644
mov cx,44
jmp Qr5

Qr5:
cmp word [es:di],0x0720
jne  Qrexit

Qr6:
sub cx,1
cmp cx,0
je Qr7
add di,2
jmp Qr5
;---------------------------------------------------------result
Qrexit:
mov byte [generator], 0
ret

Qr7:
mov byte [generator], 1



pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax
ret

;--------------------------MAIN BOARD-------------------
MainBoard:

push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es


start1:       
		 xor ax, ax 
		 mov es, ax ; point es to IVT base 
		 cli ; disable interrupts 
		 mov word [es:8*4], timer; store offset at n*4 
		 mov [es:8*4+2], cs ; store segment at n*4+2 
		 sti ; enable interrupts 
		 mov dx, start1 ; end of resident portion 
		 add dx, 15 ; round up to next para 
		 mov cl, 4 
 		shr dx, cl ; number of paras
		
		
	call Screen2
	
	xor ax, ax
	mov es, ax 			; point es to IVT base
	mov ax, [es:9*4]
	mov [oldisr], ax 		; save offset of old routine
	mov ax, [es:9*4+2]
	mov [oldisr+2], ax	 	; save segment of old routine

	cli 				; disable interrupts
	mov word [es:9*4], kbisr 	; store offset at n*4
	mov [es:9*4+2], cs 		; store segment at n*4+2
	sti 	
	
	call RandomGen
	call Print_Random_NextShape
	
	only:
		push cx
		mov cx,2
		call sound
		pop cx
		;-------------------------------------
		;funtion for coliision
		removeit:
		call get_row_remove
		cmp byte [remove],1
		jne dontremoveit
		call remove_row
		
		call get_row_remove
		cmp byte [remove],1
		jne dontremoveit
		call remove_row
		
		dontremoveit:
		
		;-------------------------------------
		
		mov byte al, [randNum]
		mov byte [randNum1], al
		call NextShape_Block
		call RandomGen
		call Print_Random_NextShape
		call Print_Random_Shape
		
		call TopCheck
		cmp byte[generator],1
		jz only
		jnz EndScreen

	leftorright:
		mov ah, 0 			; service 0 – get keystroke
 		int 0x16 			; call BIOS keyboard service
 		cmp al, 27 			; is the Esc key pressed
 		jne leftorright 		; if no, check for next key
 		mov ax, [oldisr]		; read old offset in ax
 		mov bx, [oldisr+2] 		; read old segment in bx
		cli 				; disable interrupts
 		mov [es:9*4], ax 		; restore old offset from ax
 		mov [es:9*4+2], bx 		; restore old segment from bx
 		sti				; enable interrupts

	EndScreen:
		jmp ended

		
pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret

;----------Sound------------
sound:
push ax
push bx
mov al, 182
out 43h, al
mov ax, 2711
out 42h, al
mov al, ah
out 42h, al
in al, 61h
or al, 00000011b
out 61h, al
mov bx, cx
.pause1:
mov cx, 65535
.pause2:
dec cx
jne .pause2
dec bx
jne .pause1
in al, 61h
and al, 11111100b
out 61h, al
pop bx
pop ax
ret

Screen4:
push ax
push bx
push cx
push dx
push si
push di
push bp
push ds
push es

push cx
mov cx,2
call sound
pop cx

call ClearScreen

;------CYAN BLOCK-----
mov ax,0    ;Y1
push ax
mov ax,0    ;X1
push ax
mov ax,0   ;Y2
push ax
mov ax,80   ;X2
push ax
mov ax,25   ;Y3
push ax
mov ax,0   ;X3
push ax
mov ax,25   ;Y4
push ax
mov ax,80   ;X4
push ax
mov ax,0x3720   ;Format
push ax
call Block

;-----BLUE BLOCK---
mov ax,7    ;Y1
push ax
mov ax,7    ;X1
push ax
mov ax,7   ;Y2
push ax
mov ax,73   ;X2
push ax
mov ax,17   ;Y3
push ax
mov ax,7   ;X3
push ax
mov ax,17   ;Y4
push ax
mov ax,73  ;X4
push ax
mov ax,0x1720   ;Format
push ax
call Block

;-----BLACK BLOCK---
mov ax,9    ;Y1
push ax
mov ax,10    ;X1
push ax
mov ax,9   ;Y2
push ax
mov ax,70   ;X2
push ax
mov ax,15   ;Y3
push ax
mov ax,10   ;X3
push ax
mov ax,15   ;Y4
push ax
mov ax,70   ;X4
push ax
mov ax,0x0720   ;Format
push ax
call Block


;-----------printing your score-----------
    mov  ax,30  ;   x horizontal
    push ax
    mov  ax,12  ;   y  vertical
    push ax 
    mov  ax,7
    push ax
    mov  ax,menu3
    push ax
    call write




mov ax,100
push ax
call TimeDelay


pop es
pop ds
pop bp
pop di
pop si
pop dx
pop cx
pop bx
pop ax

ret


;---------------------------START------------------------

Start:  
		call ClearVariable
		; mov ax,150
		; push ax
		; call TimeDelay
        call Screen1
		
		mov  ax,30  ;   x horizontal
        push ax
        mov  ax, 19 ;   y  vertical
        push ax 
        mov  ax,4
        push ax
        mov  ax,menu1
        push ax
        call write
		
		mov  ax,30  ;   x horizontal
        push ax
        mov  ax, 21 ;   y  vertical
        push ax 
        mov  ax,4
        push ax
        mov  ax,menu2
        push ax
        call write
		
		keypress:
		mov ah,0x00
		int 16h
		cmp al,32
		je StartGame
		
		cmp al,27
		je EndGame
		
		jne keypress
		
		
StartGame:
		push cx
		mov cx,2
		call sound
		pop cx
		
        call MainBoard
		
		
EndGame:
		push cx
		mov cx,2
		call sound
		pop cx
		
		call Screen4

mov ax, 0x3100
int 0x21