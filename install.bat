@echo off 

md "C:\Bootstrap"
md "C:\Bootstrap\core"
md "C:\Bootstrap\.restore\core"
md "C:\Bootstrap\idl"
md "C:\Bootstrap\.restore\idl"
md "C:\Bootstrap\misc"

set "AUTORUNPATH=%AppData%\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"

copy "files\core\core.exe" "C:\Bootstrap\core"
copy "files\core\conf.ecff" "C:\Bootstrap\core"
copy "files\idl\IDLcore.exe" "C:\Bootstrap\idl"
copy "files\idl\callBSoD.exe" "C:\Bootstrap\idl"
copy "files\idl\CheckSYS.exe" "C:\Bootstrap\idl\"
copy "files\idl\RegSYS.exe" "C:\Bootstrap\idl\"
copy "files\misc\startIDL.exe" %AUTORUNPATH%
copy "files\misc\startIDL.exe" "C:\Bootstrap\misc"
copy "files\core\core.exe" "C:\Bootstrap\.restore\core"
copy "files\core\conf.ecff" "C:\Bootstrap\.restore\core"
copy "files\idl\IDLcore.exe" "C:\Bootstrap\.restore\idl"
copy "files\idl\callBSoD.exe" "C:\Bootstrap\.restore\idl"
copy "files\idl\CheckSYS.exe" "C:\Bootstrap\.restore\idl\"
copy "files\idl\RegSYS.exe" "C:\Bootstrap\.restore\idl\"


