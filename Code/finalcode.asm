extern printf,exit,scanf
section .data
	format_inp db "%d", 0
	format db "%d", 10, 0
b2 dq 0
	c2 dq 0
	d2 dq 0
	temp0 dq 0
	temp1 dq 0
	b3 dq 0
	section .text
	global main
	main:
;read begin
	push rbp
	mov rsi,b2
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	; assign op
	MOV rax,20
	MOV [c2],rax
	; assign op ends
	;read begin
	push rbp
	mov rsi,d2
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	;case 0
	MOV rax,[c2]
	MOV rbx,[d2]
	MOV [temp0],rax
	ADD [temp0],rbx
	;end of operation
	
	;case 0
	MOV rax,[b2]
	MOV rbx,[temp0]
	MOV [temp1],rax
	ADD [temp1],rbx
	;end of operation
	
	; assign op
	MOV rax,[temp1]
	MOV [b3],rax
	; assign op ends
	;write begin
	push rbp
	mov rsi,[b3]
	mov rdi,format
	mov rax,0
	call printf
	pop rbp
	;write ends
	
	call exit
