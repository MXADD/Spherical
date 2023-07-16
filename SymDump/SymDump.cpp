#define  _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)
struct PEHead
{
	char  PEID[4];
	WORD  Machine;
    WORD  NumberOfSections;
	DWORD TimeDateStamp;
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;
	WORD  SizeOfOptionalHeader;
	WORD  Characteristics;
	WORD  Magic;
	BYTE  MajorLinkerVersion;
	BYTE  MinorLinkerVersion;
	DWORD SizeOfCode;
	DWORD SizeOfInitializedData;
	DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	DWORD BaseOfData;
	DWORD ImageBase;
	DWORD SectionAlignment;
	DWORD FileAlignment;
	WORD  MajorOperatingSystemVersion;
	WORD  MinorOperatingSystemVersion;
	WORD  MajorImageVersion;
	WORD  MinorImageVersion;
	WORD  MajorSubsystemVersion;
	WORD  MinorSubsystemVersion;
	DWORD Win32VersionValue;
	DWORD SizeOfImage;
	DWORD SizeOfHeaders;
	DWORD CheckSum;
	WORD  Subsystem;
	WORD  DllCharacteristics;
	DWORD SizeOfStackReserve;
	DWORD SizeOfStackCommit;
	DWORD SizeOfHeapReserve;
	DWORD SizeOfHeapCommit;
	DWORD LoaderFlags;
	DWORD NumberOfRvaAndSizes;

	bool IsValid() const
	{
		return (PEID[0] == 'P' && PEID[1] == 'E' && PEID[2] == 0 && PEID[3] == 0);
	}
};
#pragma pack()

void DumpHeader(const PEHead* h)
{
	printf("\n; PE Header sizeof(%i)\n\n", sizeof(PEHead));

	DWORD Offset = 0;

	printf("\tdb 0x%02X, 0x%02X, 0x%02X, 0x%02X\t\t; 0x%02X: Magic\n", DWORD(h->PEID[0]), DWORD(h->PEID[1]), DWORD(h->PEID[2]), DWORD(h->PEID[3]), Offset += 4);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: Machine\n", DWORD(h->Machine), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: NumberOfSections\n", DWORD(h->NumberOfSections), Offset += 2);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: TimeDateStamp\n", DWORD(h->TimeDateStamp), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: PointerToSymbolTable\n", DWORD(h->PointerToSymbolTable), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: NumberOfSymbols\n", DWORD(h->NumberOfSymbols), Offset += 4);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: SizeOfOptionalHeader\n", DWORD(h->SizeOfOptionalHeader), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: Characteristics\n", DWORD(h->Characteristics), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: Magic\n", DWORD(h->Magic), Offset += 2);
	printf("\tdb 0x%02X\t\t\t\t\t; 0x%02X: MajorLinkerVersion\n", DWORD(h->MajorLinkerVersion), Offset += 1);
	printf("\tdb 0x%02X\t\t\t\t\t; 0x%02X: MinorLinkerVersion\n", DWORD(h->MinorLinkerVersion), Offset += 1);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfCode\n", DWORD(h->SizeOfCode), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfInitializedData\n", DWORD(h->SizeOfInitializedData), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfUninitializedData\n", DWORD(h->SizeOfUninitializedData), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: AddressOfEntryPoint\n", DWORD(h->AddressOfEntryPoint), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: BaseOfCode\n", DWORD(h->BaseOfCode), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: BaseOfData\n", DWORD(h->BaseOfData), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: ImageBase\n", DWORD(h->ImageBase), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SectionAlignment\n", DWORD(h->SectionAlignment), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: FileAlignment\n", DWORD(h->FileAlignment), Offset += 4);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MajorOperatingSystemVersion\n", DWORD(h->MajorOperatingSystemVersion), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MinorOperatingSystemVersion\n", DWORD(h->MinorOperatingSystemVersion), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MajorImageVersion\n", DWORD(h->MajorImageVersion), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MinorImageVersion\n", DWORD(h->MinorImageVersion), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MajorSubsystemVersion\n", DWORD(h->MajorSubsystemVersion), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: MinorSubsystemVersion\n", DWORD(h->MinorSubsystemVersion), Offset += 2);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: Win32VersionValue\n", DWORD(h->Win32VersionValue), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfImage\n", DWORD(h->SizeOfImage), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfHeaders\n", DWORD(h->SizeOfHeaders), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: CheckSum\n", DWORD(h->CheckSum), Offset += 4);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: Subsystem\n", DWORD(h->Subsystem), Offset += 2);
	printf("\tdw 0x%04X\t\t\t\t; 0x%02X: DllCharacteristics\n", DWORD(h->DllCharacteristics), Offset += 2);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfStackReserve\n", DWORD(h->SizeOfStackReserve), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfStackCommit\n", DWORD(h->SizeOfStackCommit), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfHeapReserve\n", DWORD(h->SizeOfHeapReserve), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: SizeOfHeapCommit\n", DWORD(h->SizeOfHeapCommit), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: LoaderFlags\n", DWORD(h->LoaderFlags), Offset += 4);
	printf("\tdd 0x%08X\t\t\t\t; 0x%02X: NumberOfRvaAndSizes\n", DWORD(h->NumberOfRvaAndSizes), Offset += 4);

	return;
}

void PrintHeader(const char* Filename)
{
	FILE *f = fopen(Filename, "rb");
	if (!f)
	{
		printf("Failed to open %s !\n", Filename);
		return;
	}

	DWORD Offset = 0;

	while (true)
	{
		PEHead Head;
		fseek(f, Offset, SEEK_SET);
		if (fread(&Head, sizeof(PEHead), 1, f) != 1)
			break;

		if (Head.IsValid())
		{
			DumpHeader(&Head);
			break;
		}
		else
		{
			Offset++;
		}
	}

	fclose(f);
	return;
}

inline unsigned short CRC16Asm(const char *Strz)
{
	/*
	unsigned short Res = 0;
	__asm
	{
		pushad
		mov		esi, Strz
		xor		edx, edx
CrcLoop:
		lodsb
		crc32	edx, al
		test	al, al
		jnz		CrcLoop

		mov     eax, edx
		shr     eax, 16
		xor     eax, edx

		mov		[Res], ax

		popad
	}

	return Res;
	*/

	unsigned short Res = 0;
	__asm
	{
		pushad
		mov		esi, Strz
		xor		edx, edx
CrcLoop:
		lodsb
		imul    edx, 83 // 113
		xor     dl, al
		test	al, al
		jnz		CrcLoop

		mov		[Res], dx

		popad
	}

	return Res;
}

void *FindFunctionByHash16(const char *FName, DWORD ModulePtr, WORD InHash)
{
	long tmp = *(long*)(*(long*)(ModulePtr + 0x3C) + ModulePtr + 0x78) + ModulePtr;
	int numImp = *(long*)(tmp + 0x18);
	while (--numImp >= 0)
	{
		WORD Hash = CRC16Asm((char*) (*(long*)(*(long*)(tmp + 0x20) + ModulePtr + numImp * 4) + ModulePtr));
		if (InHash == Hash)
		{
			WORD Ordinal = *(WORD*) (*(long*)((tmp + 0x24)) + ModulePtr + numImp * 2);

			printf("FindByCRC Fun: [%s] Ordinal: [0x%04X] (%s)\n", FName, Ordinal, (const char *)((char*) (*(long*)(*(long*)(tmp + 0x20) + ModulePtr + numImp * 4) + ModulePtr)));

			return (void *)(*(long*)(*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal)) + ModulePtr);
		}
	}

	return NULL;
}

DWORD GetFunctionOrdinal(const char *Name, HMODULE _ModulePtr, bool ReverseBytes)
{
	DWORD ModulePtr((DWORD)_ModulePtr);

	long tmp   = *(long*)(*(long*)(ModulePtr + 0x3C) + ModulePtr + 0x78) + ModulePtr;
	int numImp = *(long*)(tmp + 0x18);

	while (--numImp >= 0)
	{
		if (strcmp(Name, ((char*) (*(long*)(*(long*)(tmp + 0x20) + ModulePtr + numImp * 4) + ModulePtr))) == 0)
		{
			WORD Ordinal = *(WORD*) (*(long*)((tmp + 0x24)) + ModulePtr + numImp * 2);
			if (ReverseBytes)
			{
				const WORD PartA = (Ordinal >> 0) & 0xFF;
				const WORD PartB = (Ordinal >> 8) & 0xFF;

				Ordinal = (PartA << 8) | PartB;
			}
			return Ordinal;
		}
	}

	return 0xFFFF;
}

void *FindFunctionByHash16ASM(DWORD ModulePtr, DWORD Hash)
{
	DWORD Result = 0;

	__asm
	{
		pushad

		mov		esi, ModulePtr
		mov		ecx, Hash

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mov		edi, [esi + 0x3C]			// Offset to PE
		mov     edi, [esi + edi + 0x78]		// Offset of imports dir
		add		edi, esi					// uint32 tmp = *(uint32*)(*(uint32*)(ModulePtr + 0x3C) + ModulePtr + 0x78) + ModulePtr;
		mov     eax, [edi + 0x18]			// uint32 NumberOfImports = *(uint32*)(tmp + 0x18);

ImportsScan:

		// esi == ModulePtr
		// edi == Temp
		// ebp == _DO NOT USE_
		// eax == NumberOfImports
		// ebx == Functions addresses index
		// ecx == Hash of function (lower 16 bit)
		// edx == ?

		dec		eax
		js		OutputJunk					// Symbol not found (eax is negative after dec, will result in 0xFFFFFFFF)

		push	eax
		push	esi

		// stack: eax, esi

		lea		eax, [esi + (eax * 4)]
		add		eax, [edi + 0x20]			// Offset of names table
		add		esi, [eax]					// const char *Export = *(uint32*)(*(uint32*)(tmp + 0x20) + ModulePtr + (NumberOfImports * 4) - 4) + ModulePtr;

		// esi - Function name
		// esi == Function name string, Make hash of it in dx
		xor		edx, edx

CrcLoop:

		lodsb
		imul	edx, 83
		xor     dl, al
		test	al, al
		jnz		CrcLoop

		// dx - Hash of function name
		// cx - Hash of what we are searchin' for 

		pop		esi
		pop		eax

		// cx = Hash to find, dx - our hash, Compare hashes

		cmp		cx, dx
		jne		ImportsScan

		// eax == ImportIndex, Get Ordinal

		lea     eax, [esi + (eax * 2)]
		add		eax, [edi + 0x24]		
		movzx   eax, word ptr [eax]			// uint16 Ordinal = *(uint16*)(*(uint32*)((tmp + 0x24)) + ModulePtr + (NumberOfImports * 2) - 2);

		// eax == Ordinal, Get function address

		lea		eax, [esi + eax * 4] 
		add		eax, [edi + 0x1C]
		mov		eax, [eax]		
		add		eax, esi					// void FunctionAddress = *(long*)(*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal)) + ModulePtr;

OutputJunk:									// Used for fake hashes

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mov Result, eax
		popad
	}

	return (void *)Result;
}

void TestFindFunctionByHash16ASM(HMODULE mod, const char* FName, void* Addr)
{
	void *R = FindFunctionByHash16ASM((DWORD)mod, CRC16Asm(FName));

	if (R != Addr)
		printf("ERROR: [0x%08X != 0x%08X] for [0x%08X:%s] !\n", R, Addr, mod, FName);
	else
		printf("OK: [0x%08X == 0x%08X] for [0x%08X:%s] !\n", R, Addr, mod, FName);

	return;
}

void PrintAddress(const char *FName, HMODULE mod, void *addr)
{
	char Buffer[24+1];
	Buffer[24] = 0;
	memset(Buffer, '-', 24);
	Buffer[max(0, 24 - strlen(FName))] = 0;
	printf("Fun: [%s] --%s> MOD:[0x%08X] ADR:[0x%08X] CRC16:[0x%04X]\n", FName, Buffer, DWORD(mod), DWORD(addr), DWORD(CRC16Asm(FName)));

	void *FindAs16 = FindFunctionByHash16(FName, (DWORD)mod, CRC16Asm(FName));

	if (FindAs16 == addr)
		printf("Found as CRC16 - OK\n");
	else
		printf("Found as CRC16 - FAIL [0x%08X] != [0x%08X]\n", (DWORD)addr, (DWORD)FindAs16);
	
	return;
}

void ListAllFunctions(HMODULE HModule)
{
	const DWORD ModulePtr = DWORD(HModule);
	const long tmp = *(long*)(*(long*)(ModulePtr + 0x3C) + ModulePtr + 0x78) + ModulePtr;
	int numImp = *(long*)(tmp + 0x18);
	while (--numImp >= 0)
	{
		const char *ExportName = ((char*) (*(long*)(*(long*)(tmp + 0x20) + ModulePtr + numImp * 4) + ModulePtr));
		const WORD  Ordinal    = *(WORD*) (*(long*)((tmp + 0x24)) + ModulePtr + numImp * 2);
		const void *FPtr       = (void *)(*(long*)(*(long*)(tmp + 0x1C) + ModulePtr + 4 * DWORD(Ordinal)) + ModulePtr);

		if (DWORD(CRC16Asm(ExportName)) <= 0x8FF)
			printf("Fun: [0x%08X][%s] Ordinal: [0x%04X] CRC16: [0x%04X] (********)\n", DWORD(FPtr), ExportName, DWORD(Ordinal), DWORD(CRC16Asm(ExportName)));
		else
			printf("Fun: [0x%08X][%s] Ordinal: [0x%04X] CRC16: [0x%04X]\n", DWORD(FPtr), ExportName, DWORD(Ordinal), DWORD(CRC16Asm(ExportName)));
	}

	return;
}

int main(int argc, char *argv[])
{
	if (argc >= 2)
	{
		if (_stricmp(argv[1], "--dump") == 0)
		{
			printf("Header for %s\n\n", argv[2]);
			PrintHeader(argv[2]);
			return 0;
		}
	}

	HMODULE kernel32 = ::LoadLibraryA("kernel32");
	HMODULE user32	 = ::LoadLibraryA("user32");
	HMODULE gdi32	 = ::LoadLibraryA("gdi32");
	HMODULE opengl32 = ::LoadLibraryA("opengl32");
	HMODULE cabinet  = ::LoadLibraryA("cabinet");

	bool ExportOrdinals    = false;
	bool ExportOrdinalsRev = false;
	bool ExportHashes	   = false;

	if (argc == 1 || _stricmp(argv[1], "--ordinals") == 0)
		ExportOrdinals = true;

	if (argc == 1 || _stricmp(argv[1], "--ordinalsrev") == 0)
	{
		ExportOrdinals	  = true;
		ExportOrdinalsRev = true;
	}

	if (argc == 1 || _stricmp(argv[1], "--hashes") == 0)
		ExportHashes = true;

	if (!(ExportOrdinals || ExportHashes))
	{
		printf("kernel32 functions:\n");
		ListAllFunctions(kernel32);
		printf("\n");
		printf("user32 functions:\n");
		ListAllFunctions(user32);
		printf("\n");
		printf("gdi32 functions:\n");
		ListAllFunctions(gdi32);
		printf("\n");
		printf("cabinet functions:\n");
		ListAllFunctions(cabinet);
		printf("\n");
		printf("opengl32 functions:\n");
		ListAllFunctions(opengl32);
		printf("\n");
		printf("\n");
	}

	void *API_LoadLibraryA			= ::GetProcAddress(kernel32, "LoadLibraryA");		PrintAddress("LoadLibraryA", kernel32, API_LoadLibraryA);
	void *API_GetTickCount			= ::GetProcAddress(kernel32, "GetTickCount");		PrintAddress("GetTickCount", kernel32, API_GetTickCount);
	void *API_ExitProcess			= ::GetProcAddress(kernel32, "ExitProcess");		PrintAddress("ExitProcess", kernel32, API_ExitProcess);
																						
	printf("\n");																		
																						
	void *API_StretchDIBits			= ::GetProcAddress(gdi32, "StretchDIBits");			PrintAddress("StretchDIBits", gdi32, API_StretchDIBits);
	void *API_ChoosePixelFormat		= ::GetProcAddress(gdi32, "ChoosePixelFormat");		PrintAddress("ChoosePixelFormat", gdi32, API_ChoosePixelFormat);
	void *API_SetPixelFormat		= ::GetProcAddress(gdi32, "SetPixelFormat");		PrintAddress("SetPixelFormat", gdi32, API_SetPixelFormat);
	void *API_SwapBuffers			= ::GetProcAddress(gdi32, "SwapBuffers");			PrintAddress("SwapBuffers", gdi32, API_SwapBuffers);
																						
	printf("\n");																		
																						
	void *API_CreateDecompressor	= ::GetProcAddress(cabinet, "CreateDecompressor");	PrintAddress("CreateDecompressor", cabinet, API_CreateDecompressor);
	void *API_Decompress			= ::GetProcAddress(cabinet, "Decompress");			PrintAddress("Decompress", cabinet, API_Decompress);
																						
	printf("\n");																		
																						
	void *API_CreateWindowExA		= ::GetProcAddress(user32, "CreateWindowExA");		PrintAddress("CreateWindowExA", user32, API_CreateWindowExA);
	void *API_GetAsyncKeyState		= ::GetProcAddress(user32, "GetAsyncKeyState");		PrintAddress("GetAsyncKeyState", user32, API_GetAsyncKeyState);
	void *API_GetDC					= ::GetProcAddress(user32, "GetDC");				PrintAddress("GetDC", user32, API_GetDC);
	void *API_PeekMessageA			= ::GetProcAddress(user32, "PeekMessageA");			PrintAddress("PeekMessageA", user32, API_PeekMessageA);
																						
	printf("\n");																		
																						
	void *API_wglCreateContext		= ::GetProcAddress(opengl32, "wglCreateContext");	PrintAddress("wglCreateContext", opengl32, API_wglCreateContext);
	void *API_wglMakeCurrent		= ::GetProcAddress(opengl32, "wglMakeCurrent");		PrintAddress("wglMakeCurrent", opengl32, API_wglMakeCurrent);
	void *API_wglGetProcAddress		= ::GetProcAddress(opengl32, "wglGetProcAddress");	PrintAddress("wglGetProcAddress", opengl32, API_wglGetProcAddress);
	void *API_glRects				= ::GetProcAddress(opengl32, "glRects");			PrintAddress("glRects", opengl32, API_glRects);
	void *API_glColor3i				= ::GetProcAddress(opengl32, "glColor3i");			PrintAddress("glColor3i", opengl32, API_glColor3i);

	//
	// Export current ordinals
	//
	if (ExportOrdinals)
	{
		FILE *f = fopen(argc >= 3 ? argv[2] : "Ordinals.inc", "wb");
		if (f)
		{
			fprintf(f, "; Ordinals dump\n\n");

			fprintf(f, "ORD_LoadLibraryA       EQU 0x%04X\n", GetFunctionOrdinal("LoadLibraryA", kernel32, false));
			fprintf(f, "ORD_GetTickCount       EQU 0x%04X\n", GetFunctionOrdinal("GetTickCount", kernel32, ExportOrdinalsRev));
			fprintf(f, "ORD_ExitProcess        EQU 0x%04X\n", GetFunctionOrdinal("ExitProcess", kernel32, ExportOrdinalsRev));
			fprintf(f, "ORD_StretchDIBits      EQU 0x%04X\n", GetFunctionOrdinal("StretchDIBits", gdi32, ExportOrdinalsRev));
			fprintf(f, "ORD_ChoosePixelFormat  EQU 0x%04X\n", GetFunctionOrdinal("ChoosePixelFormat", gdi32, ExportOrdinalsRev));
			fprintf(f, "ORD_SetPixelFormat     EQU 0x%04X\n", GetFunctionOrdinal("SetPixelFormat", gdi32, ExportOrdinalsRev));
			fprintf(f, "ORD_SwapBuffers        EQU 0x%04X\n", GetFunctionOrdinal("SwapBuffers", gdi32, ExportOrdinalsRev));
			fprintf(f, "ORD_CreateDecompressor EQU 0x%04X\n", GetFunctionOrdinal("CreateDecompressor", cabinet, ExportOrdinalsRev));
			fprintf(f, "ORD_Decompress         EQU 0x%04X\n", GetFunctionOrdinal("Decompress", cabinet, ExportOrdinalsRev));
			fprintf(f, "ORD_CreateWindowExA    EQU 0x%04X\n", GetFunctionOrdinal("CreateWindowExA", user32, ExportOrdinalsRev));
			fprintf(f, "ORD_GetAsyncKeyState   EQU 0x%04X\n", GetFunctionOrdinal("GetAsyncKeyState", user32, ExportOrdinalsRev));
			fprintf(f, "ORD_GetDC              EQU 0x%04X\n", GetFunctionOrdinal("GetDC", user32, ExportOrdinalsRev));
			fprintf(f, "ORD_PeekMessageA       EQU 0x%04X\n", GetFunctionOrdinal("PeekMessageA", user32, ExportOrdinalsRev));
			fprintf(f, "ORD_wglCreateContext   EQU 0x%04X\n", GetFunctionOrdinal("wglCreateContext", opengl32, ExportOrdinalsRev));
			fprintf(f, "ORD_wglMakeCurrent     EQU 0x%04X\n", GetFunctionOrdinal("wglMakeCurrent", opengl32, ExportOrdinalsRev));
			fprintf(f, "ORD_wglGetProcAddress  EQU 0x%04X\n", GetFunctionOrdinal("wglGetProcAddress", opengl32, ExportOrdinalsRev));
			fprintf(f, "ORD_glRects            EQU 0x%04X\n", GetFunctionOrdinal("glRects", opengl32, ExportOrdinalsRev));
			fprintf(f, "ORD_glColor3i          EQU 0x%04X\n", GetFunctionOrdinal("glColor3i", opengl32, ExportOrdinalsRev));

			fclose(f);
		}
	}

	//
	// Export current ordinals
	//
	if (ExportHashes)
	{
		FILE *f = fopen(argc >= 3 ? argv[2] : "Hashes.inc", "wb");
		if (f)
		{
			fprintf(f, "; Hashes dump\n\n");

			fprintf(f, "HSH_LoadLibraryA       EQU 0x%04X\n", (DWORD)CRC16Asm("LoadLibraryA"));
			fprintf(f, "HSH_GetTickCount       EQU 0x%04X\n", (DWORD)CRC16Asm("GetTickCount"));
			fprintf(f, "HSH_ExitProcess        EQU 0x%04X\n", (DWORD)CRC16Asm("ExitProcess"));
			fprintf(f, "HSH_StretchDIBits      EQU 0x%04X\n", (DWORD)CRC16Asm("StretchDIBits"));
			fprintf(f, "HSH_ChoosePixelFormat  EQU 0x%04X\n", (DWORD)CRC16Asm("ChoosePixelFormat"));
			fprintf(f, "HSH_SetPixelFormat     EQU 0x%04X\n", (DWORD)CRC16Asm("SetPixelFormat"));
			fprintf(f, "HSH_SwapBuffers        EQU 0x%04X\n", (DWORD)CRC16Asm("SwapBuffers"));
			fprintf(f, "HSH_CreateDecompressor EQU 0x%04X\n", (DWORD)CRC16Asm("CreateDecompressor"));
			fprintf(f, "HSH_Decompress         EQU 0x%04X\n", (DWORD)CRC16Asm("Decompress"));
			fprintf(f, "HSH_CreateWindowExA    EQU 0x%04X\n", (DWORD)CRC16Asm("CreateWindowExA"));
			fprintf(f, "HSH_GetAsyncKeyState   EQU 0x%04X\n", (DWORD)CRC16Asm("GetAsyncKeyState"));
			fprintf(f, "HSH_GetDC              EQU 0x%04X\n", (DWORD)CRC16Asm("GetDC"));
			fprintf(f, "HSH_PeekMessageA       EQU 0x%04X\n", (DWORD)CRC16Asm("PeekMessageA"));
			fprintf(f, "HSH_wglCreateContext   EQU 0x%04X\n", (DWORD)CRC16Asm("wglCreateContext"));
			fprintf(f, "HSH_wglMakeCurrent     EQU 0x%04X\n", (DWORD)CRC16Asm("wglMakeCurrent"));
			fprintf(f, "HSH_wglGetProcAddress  EQU 0x%04X\n", (DWORD)CRC16Asm("wglGetProcAddress"));
			fprintf(f, "HSH_glRects            EQU 0x%04X\n", (DWORD)CRC16Asm("glRects"));
			fprintf(f, "HSH_glColor3i          EQU 0x%04X\n", (DWORD)CRC16Asm("glColor3i"));

			fclose(f);
		}
	}

	//
	// Tests
	//
	if (!ExportOrdinals)
	{
		printf("\n --------------------------------- TESTS BEGZ ---------------------------------\n\n");

		TestFindFunctionByHash16ASM(kernel32, "LoadLibraryA", API_LoadLibraryA);
		TestFindFunctionByHash16ASM(kernel32, "GetTickCount", API_GetTickCount);
		TestFindFunctionByHash16ASM(kernel32, "ExitProcess", API_ExitProcess);
	
		TestFindFunctionByHash16ASM(gdi32, "StretchDIBits", API_StretchDIBits);
		TestFindFunctionByHash16ASM(gdi32, "ChoosePixelFormat", API_ChoosePixelFormat);
		TestFindFunctionByHash16ASM(gdi32, "SetPixelFormat", API_SetPixelFormat);
		TestFindFunctionByHash16ASM(gdi32, "SwapBuffers", API_SwapBuffers);

		TestFindFunctionByHash16ASM(cabinet, "CreateDecompressor", API_CreateDecompressor);
		TestFindFunctionByHash16ASM(cabinet, "Decompress", API_Decompress);

		TestFindFunctionByHash16ASM(user32, "CreateWindowExA", API_CreateWindowExA);
		TestFindFunctionByHash16ASM(user32, "GetAsyncKeyState", API_GetAsyncKeyState);
		TestFindFunctionByHash16ASM(user32, "GetDC", API_GetDC);
		TestFindFunctionByHash16ASM(user32, "PeekMessageA", API_PeekMessageA);

		TestFindFunctionByHash16ASM(opengl32, "wglCreateContext", API_wglCreateContext);
		TestFindFunctionByHash16ASM(opengl32, "wglMakeCurrent", API_wglMakeCurrent);
		TestFindFunctionByHash16ASM(opengl32, "wglGetProcAddress", API_wglGetProcAddress);
		TestFindFunctionByHash16ASM(opengl32, "glRects", API_glRects);
		TestFindFunctionByHash16ASM(opengl32, "glColor3i", API_glColor3i);

		printf("\n --------------------------------- TESTS ENDS ---------------------------------\n\n");
	}

	return 0;
}
