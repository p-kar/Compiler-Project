extern printf,exit,scanf
section .data
	format_inp db "%d", 0
	format db "%d", 10, 0
d3 dq 0
	b5b567 dq 0
	c3bd dq 0
	temp0 dq 0
	temp1 dq 0
	section .text
	global main
	main:
; assign op
	MOV rax,1
	MOV [b5b567],rax
	; assign op ends
	; assign op
	MOV rax,0
	MOV [d3],rax
	; assign op ends
	label0:
	mov rax,[b5b567]
	mov rbx,7
	cmp rax,rbx
	JLE label1
	JMP label2
	label1:
	;read begin
	push rbp
	mov rsi,c3bd
	mov rdi,format_inp
	mov rax,0
	call scanf
	pop rbp
	;read over
	
	;case 0
	MOV rax,[d3]
	MOV rbx,[c3bd]
	MOV [temp0],rax
	ADD [temp0],rbx
	;end of operation
	
	; assign op
	MOV rax,[temp0]
	MOV [d3],rax
	; assign op ends
	;case 1
	MOV rax,[b5b567]
	MOV rbx,1
	MOV [temp1],rax
	ADD [temp1],rbx
	;end of operation
	
	; assign op
	MOV rax,[temp1]
	MOV [b5b567],rax
	; assign op ends
	JMP label0
	label2:
	;write begin
	push rbp
	mov rsi,[d3]
	mov rdi,format
	mov rax,0
	call printf
	pop rbp
	;write ends
	
	call exit
