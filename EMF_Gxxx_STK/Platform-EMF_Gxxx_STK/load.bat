@echo off
setlocal

set BIN=%1
set CMDS=jlink.cmds
set JLINK=%~dp0/jlink/JLink.exe

echo device EFM32G890F128> %CMDS%
echo h>> %CMDS%
echo loadbin %BIN% 0x00 >> %CMDS%
echo r>> %CMDS%
echo g>> %CMDS%
echo q>> %CMDS%

"%JLINK%" %CMDS% 1> NUL
del %CMDS%

endlocal