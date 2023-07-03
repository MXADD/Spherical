@echo off

rem Compile body
nasm.exe -f bin IntroBodyExOGL.asm -o IntroBodyExOGL.bin -s -O9 -DNO_PEEK_MSG=1 -DLOAD_BY_ORDINAL=1
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Compress body into header
512Packer.exe IntroBodyExOGL.bin IntroBodyExOGL.inc
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Export current ordinals
call SymDump.exe --ordinals

rem Compile final intro
nasm.exe -f bin IntroLoaderExOGL.asm -o add512_byOrdinalOwnSys.exe -s -O9 -DNO_PEEK_MSG=1 -DOWN_ORDINALS_SUPPORT -DLOAD_BY_ORDINAL=1
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Dump PE for debugging
call SymDump.exe --dump add512_byOrdinalOwnSys.exe

echo All done!
GOTO BUILDSUCC
:BUILDFAIL
echo Something is fucked!
:BUILDSUCC
