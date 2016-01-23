@echo off
SET lv="C:\Program Files (x86)\National Instruments\LabVIEW 2015\LabVIEW.exe"
SET lvc="C:\Program Files (x86)\National Instruments\Shared\LabVIEW Compare\LVCompare.exe"
echo This is the LabVIEW Compare script made by Kerry.&echo To use, drag the vis into the window when prompted.
SET /p vi1=First vi to be compared:
SET /p vi2=Second vi to be compared:
IF NOT EXIST %lv% (
echo Error: LabVIEW 2015 is not installed.
pause
exit
)
IF NOT EXIST %lvc% (
echo Error: LabVIEW Compare is not installed.
pause
exit
)
cd /
mkdir asdf
copy %vi1% C:\asdf\1.vi
copy %vi2% C:\asdf\2.vi
%lvc% C:\asdf\1.vi C:\asdf\2.vi -lvpath %lv%
rd /s /q C:\asdf