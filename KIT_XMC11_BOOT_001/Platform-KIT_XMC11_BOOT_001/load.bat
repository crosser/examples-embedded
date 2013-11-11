@echo off
setlocal

set BIN=%1
set CMDS=jlink.cmds
set JLINK=%~dp0/Jlink/JLink.exe

echo device XMC1100-T038F0064> %CMDS%
echo h>> %CMDS%
echo loadbin %BIN% 0x10001000>> %CMDS%
echo r>> %CMDS%
echo g>> %CMDS%
echo q>> %CMDS%

"%JLINK%" %CMDS%
del %CMDS%

endlocal