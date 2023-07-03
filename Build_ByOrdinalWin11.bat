@echo off

rem Compile body
nasm.exe -f bin IntroBodyExOGL.asm -o IntroBodyExOGL.bin -s -O9 -DNO_PEEK_MSG=1 -DLOAD_BY_ORDINAL=1
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Compress body into header
512Packer.exe IntroBodyExOGL.bin IntroBodyExOGL.inc
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Compile final intro (win11) 
nasm.exe -f bin IntroLoaderExOGL.asm -o add512_byOrdinalWin11.exe -s -O9 -DNO_PEEK_MSG=1 -DWIN11_SUPPORT -DLOAD_BY_ORDINAL=1
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Dump PE for debugging (win11)
call SymDump.exe --dump add512_byOrdinalWin11.exe

echo All done!
GOTO BUILDSUCC
:BUILDFAIL
echo Something is fucked!
:BUILDSUCC
