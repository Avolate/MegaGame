@echo off
chcp 65001 > nul
echo Компиляция Java проекта...

if not exist "bin" mkdir bin

javac -encoding UTF-8 -d bin *.java

if %errorlevel% equ 0 (
    echo Компиляция успешно завершена!
) else (
    echo Ошибка компиляции!
    pause
    exit /b 1
)

pause
