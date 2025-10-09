@echo off

REM Show C++ compiler version
cl /Bv

REM FLAGS Start
set compiler=               -nologo &:: Suppress Startup Banner
set compiler=%compiler%     -Od     &:: No Optimization
set compiler=%compiler%     /std:c++17 &:: Set C++ version to C++17
set compiler=%compiler%     -Oi     &:: Use assembly intrinsics where possible
set compiler=%compiler%     -Gm-    &:: Disable minimal rebuild
set compiler=%compiler%     -GR-    &:: Disable runtime type info (C++)
set compiler=%compiler%     -EHa-   &:: Disable exception handling (C++)
set compiler=%compiler%     -W4     &:: Display warnings up to level 4
@REM set compiler=%compiler%     -WXd     &:: Treat all warnings as errors
set compiler=%compiler%     -wd4201 &:: Nameless struct/union
set compiler=%compiler%     -wd4100 &:: Unused function parameter
set compiler=%compiler%     -wd4189                &:: Local variable not referenced
set compiler=%compiler%     -wd4505                &:: Unreferenced local function has been removed

set debug=        -FC &:: Produce the full path of the source code file
set debug=%debug% -Z7 &:: Produce debug information
set debug=%debug% /diagnostics:color &:: Colorize diagnostics

set win32_link= 			-incremental:no  	   &:: incremental build
set win32_link=%win32_link% -opt:ref               &:: Remove unused functions
REM FLAGS ends

set Definition= -DINTERNAL=1 -DWIN32=1 -DSAMPLE=1 &:: Define preprocessor macros

set CommonCompilerFlags= %compiler% -MTd %debug% 
set CommonLinkerFlags= %win32_link% user32.lib gdi32.lib winmm.lib


IF NOT EXIST build mkdir build > NUL 2 > NUL
pushd build 

echo The current directory is: %cd%

REM 32-bit build
REM cl %CommonCompilerFlags% ../src/main.cpp /link -subsystem:windows,5.1 %CommonLinkerFlags%

REM 64-bit build
del *.pdb > NUL 2> NUL
REM Optimization switches /O2 /Oi /fp:fast
cl %CommonCompilerFlags% ../src/main.cpp /link %CommonLinkerFlags% 
popd