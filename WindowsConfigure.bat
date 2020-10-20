@echo off
:AskEdition
set /p qqqqq=Would you like to specify the VS edition[Y/N]? 
IF "%qqqqq%"=="Y" goto :Edition
IF "%qqqqq%"=="N" goto :AskName
goto :AskEdition
:Edition
set /p qqqqqq=Please drive to 'C:\Program Files (x86)\Microsoft Visual Studio\2019' specify the VS edition[i.e., Enterprise]: 
setx AuroraWindowsVSEdition %qqqqqq%
echo[
:AskName
set /p qqqq=Would you like to specify the output name[Y/N]? 
IF "%qqqq%"=="Y" goto :Name
IF "%qqqq%"=="N" goto :AskConsole
goto :AskName
:Name
set /p a=Executable name[e.g, Aurora]: 
setx AuroraWindowsExeName %a%
echo[
:AskConsole
set /p Console=Specify if that is a console project[Y/N]: 
echo[
set aaaa="WINDOWS"
IF "%Console%"=="Y" set aaaa="CONSOLE"
setx AuroraWindowsSubsystem %aaaa%
set CArch=/D WIN32_LEAN_AND_MEAN
IF "%Console%"=="Y" set CArch=%CArch% /D AuroraConsole
IF "%Console%"=="Y" goto :Continue
IF "%Console%"=="N" goto :Continue
goto :AskConsole
:Continue
set /p qq=Would you like to change the MSVC version[Y/N]? 
IF "%qq%"=="Y" goto :ChangeMSVC
IF "%qq%"=="N" goto :AskKit
goto :Continue
:ChangeMSVC
set /p aa=Drive to C:\Program Files (x86)\Microsoft Visual Studio\2019\Edition\VC\Tools\MSVC and specify the MSVC version[e.g, 14.27.29110]: 
setx AuroraWindowsMSVC %aa%
echo[
:AskKit
set /p qqq=Would you like to change the Windows 10 Kit version[Y/N]? 
IF "%qqq%"=="Y" goto :Kit
IF "%qqq%"=="N" goto :Archg
goto :AskKit
:Kit
set /p aaa=Drive to C:\Program Files (x86)\Windows Kits\10\Lib and specify the Windows 10 Kit version[e.g, 10.0.19041.0]: 
setx AuroraWindows10Kit %aaa%
echo[
:Archg
set /p Arch=Architecture extensions[empty or separated by an space, e.g, avx avx2 sse3]: 
for /f "delims=" %%t in ("%Arch%") do (
    IF "%t%"=="xsave" set CArch=%CArch% /D AuroraXsave
    IF "%t%"=="waitpkg" set CArch=%CArch% /D AuroraWaitpkg
    IF "%t%"=="vpclmulqdq" set CArch=%CArch% /D AuroraVpclmulqdq
    IF "%t%"=="vaes" set CArch=%CArch% /D AuroraVaes
    IF "%t%"=="tsc" set CArch=%CArch% /D AuroraTsc
    IF "%t%"=="sha" set CArch=%CArch% /D AuroraSha
    IF "%t%"=="rtm" set CArch=%CArch% /D AuroraRtm
    IF "%t%"=="rdtscp" set CArch=%CArch% /D AuroraRdtscp
    IF "%t%"=="rdseed" set CArch=%CArch% /D AuroraRdseed
    IF "%t%"=="rdrand" set CArch=%CArch% /D AuroraRdrand
    IF "%t%"=="rdpid" set CArch=%CArch% /D AuroraRdpid
    IF "%t%"=="prefetchwt1" set CArch=%CArch% /D AuroraPrefetchwt1
    IF "%t%"=="popcnt" set CArch=%CArch% /D AuroraPopcnt
    IF "%t%"=="pclmulqdq" set CArch=%CArch% /D AuroraPclmulqdq
    IF "%t%"=="mpx" set CArch=%CArch% /D AuroraMpx
    IF "%t%"=="movdiri" set CArch=%CArch% /D AuroraMovdiri
    IF "%t%"=="movdir64b" set CArch=%CArch% /D AuroraMovdir64b
    IF "%t%"=="movbe" set CArch=%CArch% /D AuroraMovbe
    IF "%t%"=="lzcnt" set CArch=%CArch% /D AuroraLzcnt
    IF "%t%"=="gfni" set CArch=%CArch% /D AuroraGfni
    IF "%t%"=="fxsr" set CArch=%CArch% /D AuroraFxsr
    IF "%t%"=="fsgsbase" set CArch=%CArch% /D AuroraFsgsbase
    IF "%t%"=="fp16c" set CArch=%CArch% /D AuroraFp16c
    IF "%t%"=="clwb" set CArch=%CArch% /D AuroraClwb
    IF "%t%"=="clflushopt" set CArch=%CArch% /D AuroraClflushopt
    IF "%t%"=="cldemote" set CArch=%CArch% /D AuroraCldemote
    IF "%t%"=="bmi" set CArch=%CArch% /D AuroraBmi
    IF "%t%"=="bmi2" set CArch=%CArch% /D AuroraBmi2
    IF "%t%"=="aes" set CArch=%CArch% /D AuroraAes
    IF "%t%"=="adx" set CArch=%CArch% /D AuroraAdx
    IF "%t%"=="knc" set CArch=%CArch% /D AuroraKnc
    IF "%t%"=="avx512f" set CArch=%CArch% /D AuroraAvx512f
    IF "%t%"=="avx512bw" set CArch=%CArch% /D AuroraAvx512bw
    IF "%t%"=="avx512cd" set CArch=%CArch% /D AuroraAvx512cd
    IF "%t%"=="avx512dq" set CArch=%CArch% /D AuroraAvx512dq
    IF "%t%"=="avx512er" set CArch=%CArch% /D AuroraAvx512er
    IF "%t%"=="avx512ifma52" set CArch=%CArch% /D AuroraAvx512ifma52
    IF "%t%"=="avx512pf" set CArch=%CArch% /D AuroraAvx512pf
    IF "%t%"=="avx512vl" set CArch=%CArch% /D AuroraAvx512vl
    IF "%t%"=="avx512vpopcntdq" set CArch=%CArch% /D AuroraAvx512vpopcntdq
    IF "%t%"=="avx5124fmaps" set CArch=%CArch% /D AuroraAvx5124fmaps
    IF "%t%"=="avx5124vnniw" set CArch=%CArch% /D AuroraAvx5124vnniw
    IF "%t%"=="avx512bf16" set CArch=%CArch% /D AuroraAvx512bf16
    IF "%t%"=="avx512bitalg" set CArch=%CArch% /D AuroraAvx512bitalg
    IF "%t%"=="avx512vbmi" set CArch=%CArch% /D AuroraAvx512vbmi
    IF "%t%"=="avx512vbmi2" set CArch=%CArch% /D AuroraAvx512vbmi2
    IF "%t%"=="avx512vnni" set CArch=%CArch% /D AuroraAvx512vnni
    IF "%t%"=="avx512vp2intersect" set CArch=%CArch% /D AuroraAvx512vp2intersect
    IF "%t%"=="fma" set CArc=%CArch% /D AuroraFma
    IF "%t%"=="avx2" set CArch=%CArch% /D AuroraAvx2
    IF "%t%"=="avx" set CArch=%CArch% /D AuroraAvx
    IF "%t%"=="sse42" set CArch=%CArch% /D AuroraSse42
    IF "%t%"=="sse41" set CArch=%CArch% /D AuroraSse41
    IF "%t%"=="ssse3" set CArch=%CArch% /D AuroraSsse3
    IF "%t%"=="sse3" set CArch=%CArch% /D AuroraSse3
)
setx AuroraWindowsExtensions "%CArch%"