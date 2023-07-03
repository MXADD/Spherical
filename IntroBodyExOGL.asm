;
; (c) MX^Addict 2023 (mxadd@mxadd.org)
;

;
; Bits
;
bits 32
org  0x11000
%include "SymbolOffsetsOGL.inc"

;
; Defs
;
WIDTH	equ	  1280
HEIGHT	equ	   720

CompressedCode:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Entry point

;
; eax - 1
; ebx - Some non-zero value
; ecx - Some non-zero value
; edx - Some non-zero value
; esi - Some non-zero value
; edi - Some non-zero value
; ebp - points at start SymbolsTable

;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Window & OpenGL init & program loop

;
; Prepare stack & create window
;
push	ShaderCodeOffset
push	eax ; 1
dec		eax ; 0
push	0x8B30
push	glCreateShaderProgramv
push	pfd
push	pfd
push	eax
push	eax
push	eax
push	eax
push	HEIGHT
push	WIDTH
push	eax
push	eax
push	0x90000000
push	eax
push	0x0000c018
push	eax
call    dword [ebp + API_CreateWindowEx] 

;
; Get DC
;
push	eax
call    dword [ebp + API_GetDC]
mov		edi, eax ; edi == hDC

;
; Choose pixel format
;
push	eax
call    dword [ebp + API_ChoosePixelFormat]

;
; Set pixel format
;
push	eax
push	edi
call    dword [ebp + API_SetPixelFormat]

;
; Create context
;
push	edi
call    dword [ebp + API_wglCreateContext]

;
; Make current
;
push	eax
push	edi
call    dword [ebp + API_wglMakeCurrent]

;
; Get proc address & create shader
;
call    dword [ebp + API_wglGetProcAddress]
call	eax	; glCreateShaderProgramv

;
; Get proc address & use shader
;
push	eax
push	glUseProgram
call    dword [ebp + API_wglGetProcAddress]
call	eax ; glUseProgram

;
; Main loop
;
.Mainloop:           
%if NO_PEEK_MSG == 0
    ;
	; Peek message
	;
	push	1
	push	0
	push	0
	push	0
	push	0
	call    dword [ebp + API_PeekMessage]
%endif
	;
	; Draw rect
	;
	push	 1
	push	 1
	push	-1
	push	-1
	call    dword [ebp + API_glRects]

	;
	; Swap buffers
	;
	push	edi
	call    dword [ebp + API_SwapBuffers]
	call	dword [ebp + API_GetTickCount]

	;
	; Bind timer (we should cut the upper byte to not overload float, so & 0xFFFFFF)
	;
	push	eax
	push	eax
	push	eax
	call    dword [ebp + API_glColor3i]

	;
	; Wait for escape
	;
	push	27
	call	dword [ebp + API_GetAsyncKeyState]
	jz		.Mainloop

;
; Exit process
;
call	dword [ebp + API_ExitProcess]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Shader code
;

ShaderCode:						db '#version 130', 10, ''
								db 'out vec4 r;'
								db 'void main()'
								db '{'
								db   'for(++r.g;++r.a<130;)'
								db     'r+=vec4(1,gl_FragCoord.rg/1300,0)*(length(sin(r+gl_Color*1e6).rgb)-.3);'
								db   'r/=130;'
								db '}', 0

;
; Additional strings for wglGetProcAddress
;
glUseProgram:					db "glUseProgram", 0
glCreateShaderProgramv:			db "glCreateShaderProgramv", 0

;
; Shader code offset
;
ShaderCodeOffset:				dd ShaderCode

;
; Pixel format descriptor
;
pfd:							dw  0x0028
								dw	0x0001
								dd	0x00000025
								db	0
								db	0x20
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0x08
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0x20
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0
								db	0

; Note that trailing zeros are always cut by packer, so no need to take care of them

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
