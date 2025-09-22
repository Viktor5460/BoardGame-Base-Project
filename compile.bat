@echo off

g++ -O2 main.cpp BoardGame.cpp -o board_game_test.exe

if %errorlevel% equ 0 (
    echo Компиляция успешна!
    echo Запуск программы:
    board_game_test.exe
) else (
    echo Ошибка компиляции!
)

pause
