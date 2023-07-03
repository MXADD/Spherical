@echo off

rem Compile body
nasm.exe -f bin IntroBodyExOGL.asm -o IntroBodyExOGL.bin -s -O9 -DNO_PEEK_MSG=1 -DLOAD_BY_ORDINAL=0
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Compress body into header
512Packer.exe IntroBodyExOGL.bin IntroBodyExOGL.inc
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Compile final intro
nasm.exe -f bin IntroLoaderExOGL.asm -o add512_byHash.exe -s -O9 -DNO_PEEK_MSG=1 -DLOAD_BY_ORDINAL=0
IF ERRORLEVEL 1 GOTO BUILDFAIL

rem Dump PE (win10)
call SymDump.exe --dump add512_byHash.exe

echo All done!
GOTO BUILDSUCC
:BUILDFAIL
echo Something is fucked!
:BUILDSUCC
