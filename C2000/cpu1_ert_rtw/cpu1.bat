
cd .

if "%1"=="" ("D:\matlab\bin\win64\gmake"  DEPRULES=1 -j7  -f cpu1.mk all) else ("D:\matlab\bin\win64\gmake"  DEPRULES=1 -j7  -f cpu1.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1