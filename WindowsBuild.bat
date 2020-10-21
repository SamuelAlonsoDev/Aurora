@echo off
:Compile
cls
set CArch="%AuroraWindowsExtensions%"
IF "%AuroraUseConsole%"=="Y" set CArch=%CArch% /D AuroraConsole
"C:\Program Files (x86)\Microsoft Visual Studio\2019\%AuroraWindowsVSEdition%\VC\Tools\MSVC\%AuroraWindowsMSVC%\bin\Hostx64\x64\cl.exe" Aurora.cpp /Bt+ /WX /W4 /EHsc /GR- /MT /Ox /std:c++latest /D _HAS_EXCEPTIONS=0 /D AuroraWindows %CArch% /I"C:\Program Files (x86)\Windows Kits\10\Include\%AuroraWindows10Kit%\ucrt" /I"C:\Program Files (x86)\Windows Kits\10\Include\%AuroraWindows10Kit%\shared" /I"C:\Program Files (x86)\Windows Kits\10\Include\%AuroraWindows10Kit%\um" /I"C:\Program Files (x86)\Microsoft Visual Studio\2019\%AuroraWindowsVSEdition%\VC\Tools\MSVC\%AuroraWindowsMSVC%\include" /I%~dp0 /link /LIBPATH "C:\Program Files (x86)\Microsoft Visual Studio\2019\%AuroraWindowsVSEdition%\VC\Tools\MSVC\%AuroraWindowsMSVC%\lib\x64\*.lib" /LIBPATH "C:\Program Files (x86)\Windows Kits\10\Lib\%AuroraWindows10Kit%\um\x64\*.lib" /LIBPATH "C:\Program Files (x86)\Windows Kits\10\Lib\%AuroraWindows10Kit%\ucrt\x64\*.lib" /SUBSYSTEM:"%AuroraWindowsSubsystem%" /out:"%AuroraWindowsExeName%.exe"
IF EXIST Aurora.obj DEL /F Aurora.obj
pause
cls
:Execute
%AuroraWindowsExeName%.exe
echo[
echo[
set /p Recompile=Press 'r' to recompile, 'e' to execute again, or any other key to exit...
echo[
IF "%Recompile%"=="r" goto :Compile
IF "%Recompile%"=="e" goto :Execute