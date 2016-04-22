extern printf,exit,scanf
section .data
	format_inp db "%d", 0
	format db "%d", 10, 0
b5 dq 0
	d5cb34567 dq 0
	d4.maths dq 0
	d4.physics dq 0
	d4.chemistry dq 0
	b3c2.maths dq 0
	b3c2.physics dq 0
	b3c2.chemistry dq 0
	temp0 dq 0
	temp1 dq 0
	temp2 dq 0
	temp3 dq 0
	section .text
	global main
	main:
; assign op
	MOV rax,1
	MOV [b5],rax
	; assign op ends
	;read begin
	push rbp
	mov rsi,d5cb34567
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	; assign op
	MOV rax,0
	MOV [d4.maths],rax
	; assign op ends
	; assign op
	MOV rax,0
	MOV [d4.physics],rax
	; assign op ends
	; assign op
	MOV rax,0
	MOV [d4.chemistry],rax
	; assign op ends
	label0:
	mov rax,[b5]
	mov rbx,[d5cb34567]
	cmp rax,rbx
	JLE label1
	JMP label2
	label1:
	;read begin
	push rbp
	mov rsi,b3c2.maths
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	;read begin
	push rbp
	mov rsi,b3c2.physics
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	;read begin
	push rbp
	mov rsi,b3c2.chemistry
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	;case 0
	MOV rax,[b3c2.maths]
	MOV rbx,[d4.maths]
	MOV [temp0],rax
	ADD [temp0],rbx
	;end of operation
	
	;case 0
	MOV rax,[b3c2.physics]
	MOV rbx,[d4.physics]
	MOV [temp1],rax
	ADD [temp1],rbx
	;end of operation
	
	;case 0
	MOV rax,[b3c2.chemistry]
	MOV rbx,[d4.chemistry]
	MOV [temp2],rax
	ADD [temp2],rbx
	;end of operation
	
	; assign op
	MOV rax,[temp0]
	MOV [d4.maths],rax
	; assign op ends
	; assign op
	MOV rax,[temp1]
	MOV [d4.physics],rax
	; assign op ends
	; assign op
	MOV rax,[temp2]
	MOV [d4.chemistry],rax
	; assign op ends
	;case 1
	MOV rax,[b5]
	MOV rbx,1
	MOV [temp3],rax
	ADD [temp3],rbx
	;end of operation
	
	; assign op
	MOV rax,[temp3]
	MOV [b5],rax
	; assign op ends
	JMP label0
	label2:
	;write begin
	push rbp
	mov rsi,[d4.maths]
	mov rdi,format
	mov rax,0
	call printf
	pop rbp
	;write ends
	
	;write begin
	push rbp
	mov rsi,[d4.physics]
	mov rdi,format
	mov rax,0
	call printf
	pop rbp
	;write ends
	
	;write begin
	push rbp
	mov rsi,[d4.chemistry]
	mov rdi,format
	mov rax,0
	call printf
	pop rbp
	;write ends
	
	call exit
