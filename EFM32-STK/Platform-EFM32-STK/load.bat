@echo off
setlocal

SET MCU=%1
set BIN=%2
set CMDS=jlink.cmds
set JLINK=%~dp0/jlink/JLink.exe

echo device %MCU%> %CMDS%
echo h>> %CMDS%
echo loadbin %BIN% 0x00 >> %CMDS%
echo r>> %CMDS%
echo g>> %CMDS%
echo q>> %CMDS%

"%JLINK%" %CMDS% 1> NUL
del %CMDS%

endlocal