#!/bin/bash
echo "[Linux] Building Java Application..."

# Создаем выходную директорию если её нет
mkdir -p bin

# Компилируем Java классы
javac -d bin -sourcepath src src/game/*.java

echo "[Linux] Build completed!"
echo