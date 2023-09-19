@echo off 
if not exist "C:\Bootstrap\core\core.exe" copy "C:\Bootstrap\.restore\core\core.exe" "C:\Bootstrap\core\"
if not exist "C:\Bootstrap\core\conf.ecff" copy "C:\Bootstrap\.restore\core\conf.ecff" "C:\Bootstrap\core\"
if not exist "C:\Bootstrap\idl\IDLcore.exe" copy "C:\Bootstrap\.restore\idl\IDLcore.exe" "C:\Bootstrap\idl\"
if not exist "C:\Bootstrap\idl\callBSoD.exe" copy "C:\Bootstrap\.restore\idl\callBSoD.exe" "C:\Bootstrap\idl\"
if not exist "C:\Bootstrap\idl\CheckSYS.exe" copy "C:\Bootstrap\.restore\idl\CheckSYS.exe" "C:\Bootstrap\idl\"
if not exist "C:\Bootstrap\idl\RegSYS.exe" copy "C:\Bootstrap\.restore\idl\RegSYS.exe" "C:\Bootstrap\idl\"
