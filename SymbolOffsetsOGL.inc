%if LOAD_BY_ORDINAL
;
; Symbol offsets - Load by Ordinal
;
%if NO_PEEK_MSG == 0
NUM_Symbols                     equ  (17+3)
%else
NUM_Symbols                     equ  (16+3)
%endif

API_LoadLibraryA				equ   0				; Invalid after loader
API_ExitProcess					equ   4
API_GetTickCount				equ   8
API_Padding0					equ  12
API_SwapBuffers					equ	 16
API_ChoosePixelFormat			equ  20
API_SetPixelFormat				equ  24
API_Padding1					equ  28
API_Padding2					equ  32
API_CreateDecompressor			equ	 36
API_Decompress					equ	 40
API_wglCreateContext			equ	 44
API_wglMakeCurrent				equ	 48
API_wglGetProcAddress			equ	 52
API_glRects						equ  56
API_glColor3i					equ	 60
API_CreateWindowEx				equ	 64
API_GetAsyncKeyState			equ	 68
API_GetDC						equ	 72
%if NO_PEEK_MSG == 0
API_PeekMessage					equ	 76
%endif

%else
;
; Symbol offsets - Load by Hash
;
%if NO_PEEK_MSG == 0
NUM_Symbols                     equ  (17+5)	; +5 --> padding
%else
NUM_Symbols                     equ  (16+5) ; +5 --> padding
%endif

API_LoadLibraryA				equ   0
API_Padding0					equ   4
API_ExitProcess					equ   8
API_Padding1					equ  12
API_GetTickCount				equ  16
API_Padding2					equ  20
API_SwapBuffers					equ	 24
API_Padding3					equ  28
API_Padding4					equ  32
API_ChoosePixelFormat			equ  36
API_SetPixelFormat				equ  40
API_CreateDecompressor			equ	 44
API_Decompress					equ	 48
API_glRects						equ  52
API_glColor3i					equ	 56
API_wglCreateContext			equ	 60
API_wglMakeCurrent				equ	 64
API_wglGetProcAddress			equ	 68
API_CreateWindowEx				equ	 72
API_GetAsyncKeyState			equ	 76
API_GetDC						equ	 80
%if NO_PEEK_MSG == 0
API_PeekMessage					equ	 84
%endif
%endif
