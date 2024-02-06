@echo off
for /r %%f in (*) do (
    if "%%~xf"==".bat" (
        if "%%~nf"=="keilkill" (
            echo 正在运行： %%f
            call "%%f"
        )
    )
)
pause
