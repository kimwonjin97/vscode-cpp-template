@REM @Author: wonjin
@REM @Date:   2025-11-12 01:42:08
@REM @Last Modified by:   wonjin
@REM Modified time: 2026-01-08 00:29:01
@echo off

REM 
REM To run this at startup, use following command:
REM cmd.exe /k <path to this shell.bat file>
REM 

set VSDEVCMD="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

if EXIST %VSDEVCMD% call %VSDEVCMD%

set path="%~dp0";%path%