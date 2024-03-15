git add .

echo  %date%+%time%

git commit -m "update+%date%+%time%"

git push -f --set-upstream origin Second:Second

echo File upload successful
