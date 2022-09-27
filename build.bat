@echo off
setlocal

set FILES_TO_COMPILE="refps2_main_win64.c"

where /q cl || (
  echo MSVC not found. No debug build generated.
  exit /b 1
)

set COMPILER_FLAGS=/nologo /Z7 /W3 /Fe"build/refps2_win64_debug"
set LINKER_FLAGS=/incremental:no /opt:icf /opt:ref /subsystem:windows
call cl %COMPILER_FLAGS% %FILES_TO_COMPILE% /link %LINKER_FLAGS%

if %errorlevel% neq 0 (
  exit /b 1
)

where /q clang || (
  echo CLANG not found. No release build generated.
  exit /b 1
)
set COMPILER_FLAGS=-O3 -nostdlib++ -o "build/refps2_win64_release.exe"
set LINKER_FLAGS=-fuse-ld=lld -Wl,-subsystem:windows
call clang %COMPILER_FLAGS% %LINKER_FLAGS% %FILES_TO_COMPILE%