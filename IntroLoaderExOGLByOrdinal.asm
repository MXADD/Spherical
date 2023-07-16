;
; (c) MX^Addict 2023 (mxadd@mxadd.org)
;

;
; Bits
;
bits 32
org  0x10000

%include "SymbolOffsetsOGL.inc"

%ifdef OWN_ORDINALS_SUPPORT
	%include "Ordinals.inc"
%else
	%ifdef WIN11_SUPPORT
		%include "OrdinalsWin11.inc"
	%else	
		%include "OrdinalsWin10.inc"
	%endif	
%endif	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; DOS & PE header mockery ...
;

	dw 0x5A4D
	jmp		short BootStrapA			; 0x00: e_cblp

    db 0x50, 0x45, 0x00, 0x00           ; 0x04: Magic
    dw 0x014C                           ; 0x06: Machine
    dw 0x0000                           ; 0x08: NumberOfSections
BootStrapA:
	mov		edx, 0x11000	            ; Address of depack target
										; 0x0C: TimeDateStamp
	mov		edi, SymbolsTable			; Symbols table start
										; 0x10: PointerToSymbolTable
 	jmp		short BootStrapB			; 0x14: NumberOfSymbols

    dw 0x0008                           ; 0x16: SizeOfOptionalHeader
    dw 0x010F                           ; 0x18: Characteristics
    dw 0x010B                           ; 0x1A: Magic
BootStrapB:
	mov     eax, [ebx + 0x0C]			; At start ebx == Pointer to PEB ([fs:0x30])
	mov     eax, [eax + 0x14]			; Pointer to InMemoryOrderModuleList
	mov     eax, [eax]					; This program's module
	mov     ecx, [eax]					; NTDLL module (use ecx, to set it to non-zero value needed later)
	lea     ebp, [edx - 127]			; Output symbols table address
    mov     ebx, 0x00000000				; We need 4x 0x00 at 002C - AddressOfEntryPoint, we need ebx later to be 0
	lea		esi, [edi + (PakInputSizeOff -  SymbolsTable)]
	push	edx							; Return address for payload for ret at end.
	push	ebx							; 0
	lodsd								; Load from esi
    jmp     short BootStrapC			; Jump to continuation

    dd 0x00010000                       ; 0x38: ImageBase
    dd 0x00000004                       ; 0x3C: SectionAlignment
    dd 0x00000004                       ; 0x40: FileAlignment
PakInputSizeOff:						; 0x42: MajorOperatingSystemVersion
    dd PakInputSize						; 0x44: MinorOperatingSystemVersion
PakOutputSizeOff:						; 0x46: MajorImageVersion
    dd PakOutputSize					; 0x48: MinorImageVersion
    dw 0x0004                           ; 0x4A: MajorSubsystemVersion
    dw 0x0000                 ; *useme* ; 0x4C: MinorSubsystemVersion
CompressedPayloadOff:
    dd CompressedPayload				; 0x50: Win32VersionValue
CabinetFlags:
    dd 0x20000002                       ; 0x54: SizeOfImage --> COMPRESS_ALGORITHM_MSZIP | COMPRESS_RAW 
    dd 0x0000002C                       ; 0x58: SizeOfHeaders
BootStrapC:
	push	eax							; PakInputSizeOff
	push	edx							; PakTargetOff
	jmp     short BootStrapD			; Jump to continuation
										; 0x5C: CheckSum

    dw 0x0002                           ; 0x5E: Subsystem
    dw 0x0000                           ; 0x60: DllCharacteristics

SymbolsTable:

	dw  ORD_LoadLibraryA				; kernel32::LoadLibraryA ordinal
	dw  ORD_ExitProcess					; kernel32::ExitProcess ordinal
										; 0x64: SizeOfStackReserve

	dw  ORD_GetTickCount				; kernel32::GetTickCount ordinal
	dw	0x0069							; kernel32::Fake!!! ordinal (we need something small)
										; 0x68: SizeOfStackCommit

	db  "GDI32", 0
	dw  ORD_SwapBuffers					; gdi32::SwapBuffers ordinal
										; 0x6C: SizeOfHeapReserve
										; 0x70: SizeOfHeapCommit
										
	dw  ORD_ChoosePixelFormat			; gdi32::ChoosePixelFormat ordinal
	dw  ORD_SetPixelFormat				; gdi32::SetPixelFormat ordinal
										; 0x74: LoaderFlags

	dw  0x0000							; gdi32:::Fake!!! ordinal (we need 0 here)
	dw  0x0000							; gdi32:::Fake!!! ordinal (we need 0 here)
										; 0x78: NumberOfRvaAndSizes

	db  "cabinet", 0						
	dw  ORD_CreateDecompressor			; cabinet::CreateDecompressor ordinal
	dw  ORD_Decompress					; cabinet::Decompress ordinal

	db  "opengl32", 0
	dw  ORD_wglCreateContext			; opengl32::wglCreateContext ordinal
	dw  ORD_wglMakeCurrent				; opengl32::wglMakeCurrent ordinal
	dw  ORD_wglGetProcAddress			; opengl32::wglGetProcAddress ordinal
	dw  ORD_glRects						; opengl32::glRects ordinal
	dw  ORD_glColor3i					; opengl32::glColor3i ordinal

	db  "user32", 0				
	dw  ORD_CreateWindowExA				; user32::CreateWindowExA ordinal
	dw  ORD_GetAsyncKeyState			; user32::GetAsyncKeyState ordinal
	dw  ORD_GetDC						; user32::GetDC ordinal
%if NO_PEEK_MSG == 0
	dw  ORD_PeekMessageA				; user32::PeekMessageA ordinal
%endif

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

BootStrapD:

	;
	; Push arguments for Decompress (continues from BootStrapB & BootStrapC)
	;
	lodsd
	push	eax							; PakOutputSizeOff
	lodsd								; Gap in params ...
	lodsd
	push	eax							; CompressedPayloadOff
	
	;
	; Push arguments for CreateDecompressor
	;
	push	ebp							; &HDecompressor (we use LoadLibraryA ptr, as we don't need it anymore)
	push	ebx							; 0
	lodsd
	push	eax							; CabinetFlags

	;
	; Prepare Kernel32 DllBase
	;
	mov     esi, [ecx -0x08 + 0x18]		; Kernel32 DllBase

    ;
    ; Load by Ordinal from symbols table
    ;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;
	; ebp - Start of symbols table (output)
	; esi - Kernel32 DllBase
	; edi - Start of symbols table (input)
	; eax - non-zero & rather big (> 0xFFFF)
	; ebx - 0
	; ecx - non-zero & rather big (> 0xFFFF)
	; edx - ?
	;

	jmp		LoaderOrdinals			

LoaderMain:

	inc		edi						
	inc		edi						
	push	edi							; Push DLL name
	call	[ebp]						; Call LoadLibraryA
	test    eax, eax				
	jz      LoaderOrdinals			
	mov		esi, eax					; al must be 0 after this (all modules addreses have lower word 0)
										; esi == ModulePtr
	repne   scasb						; Move to the end of string

LoaderOrdinals:

	; uint32 Tmp = *(uint32*)(*(uint32*)(ModulePtr + 0x3C) + ModulePtr + 0x78) + ModulePtr;
	; void FunctionAddress = *(long*)(*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal)) + ModulePtr;

	movzx	eax, word [edi]				; Ordinal			
	lea		eax, [esi + eax * 4]		; ModulePtr + 4 * DWORD(Ordinal)

	mov		edx, [esi + 0x3C]			; *(uint32*)(ModulePtr + 0x3C)
	mov     edx, [esi + edx + 0x78]		; *(uint32*)(*(uint32*)(ModulePtr + 0x3C) + ModulePtr + 0x78)
	add		eax, [esi + edx + 0x1C]		; (*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal))
	mov		eax, [eax]		
	add		eax, esi					; *(long*)(*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal)) + ModulePtr
										; eax == FunctionAddress
	mov		[ebp+ebx*4], eax
	inc		ebx
	cmp		ebx, NUM_Symbols			; Check if we are done with all the exports
	jne		LoaderMain

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	; CreateDecompressor(0x20000002, 0, &HDecompressor)

	call	[ebp + API_CreateDecompressor]																				
																														
	; Decompress(HDecompressor, CompressedPayload, PakOutputSize, 0x11000, PakInputSize, 0)								
																														
	push	dword [ebp] 																								
	call	[ebp + API_Decompress]																						
	ret

	;
	; ebp - Points at start of symbols table
	;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Compressed code at start have
;

; NOTE: Payload always starts with 0x43 (inc ebx) 0x4b (dec ebx) [MS-Zip header]

%include "IntroBodyExOGL.inc"
