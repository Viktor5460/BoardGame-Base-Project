@echo off
echo ===================================================
echo Компиляция...
echo ===================================================

g++ -O2 -std=c++11 main.cpp BoardGame.cpp Player.cpp Match.cpp RatingFilter.cpp FeatureFilter.cpp SimilarGamesFilter.cpp GameDatabase.cpp -o board_game_test.exe

if %errorlevel% equ 0 (
    echo.
    echo ===================================================
    echo Компиляция успешна!
    echo ===================================================
    echo Запуск программы:
    echo.
    board_game_test.exe
) else (
    echo.
    echo ===================================================
    echo Ошибка компиляции!
    echo ===================================================
)

pause

