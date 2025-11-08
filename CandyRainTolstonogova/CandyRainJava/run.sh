#!/bin/bash

echo "Запуск игры..."

if [ ! -d "bin" ]; then
    echo "Файлы не скомпилированы. Запустите compile.sh сначала!"
    exit 1
fi

java -Dfile.encoding=UTF-8 -cp bin Main

read -p "Нажмите Enter для продолжения..."
