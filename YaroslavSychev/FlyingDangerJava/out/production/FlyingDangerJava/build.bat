@echo off
echo [Windows] Building Java Application...

:: Создаем выходную директорию если её нет
if not exist "bin" mkdir bin

:: Компилируем Java классы
javac -d bin -sourcepath src src/game/*.java

echo [Windows] Build completed!
echo.