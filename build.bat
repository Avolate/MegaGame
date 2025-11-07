@echo off
echo Building Flying Danger Java...
if exist bin rmdir /s /q bin
mkdir bin
javac -d bin src/*.java
if %errorlevel% equ 0 (
    echo Сборка завершена успешно!
    dir bin
) else (
    echo Ошибка сборки!
)
echo.