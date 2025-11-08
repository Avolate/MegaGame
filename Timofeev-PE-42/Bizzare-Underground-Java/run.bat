@echo off
chcp 65001 > nul
echo Запуск...

if not exist "bin" (
    echo Файлы не скомпилированы. Запустите compile.bat сначала!
    pause
    exit /b 1
)

java -Dfile.encoding=UTF-8 -cp bin Main

pause
