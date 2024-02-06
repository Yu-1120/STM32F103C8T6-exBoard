git add .

echo  %date%+%time%

git commit -m "update+%date%+%time%"

git push -f --set-upstream origin master:master

echo File upload successful

choice /t 5 /d y /n >nul


exit