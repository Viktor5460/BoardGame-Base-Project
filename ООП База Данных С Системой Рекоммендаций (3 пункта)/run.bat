@echo off

if not exist "board_game_test.exe" (
    echo Исполняемый файл не найден!
    pause
    exit /b 1
)
board_game_test.exe
echo Программа завершена.
pause
