cd zsummerX
call make.bat

xcopy depends\* ..\..\depends\include\  /S /Y /F
xcopy include\* ..\..\depends\include\  /S /Y /F
xcopy lib\* ..\..\depends_win\lib\  /S /Y /F

cd ..