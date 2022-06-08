@echo off

echo Copying Files...

copy /Y %1 %3 
copy /Y %2 %3
copy /Y %4 %3
copy /Y %5 %3

echo Completed copy