#!/bin/bash

echo "Компиляция Java проекта..."

mkdir -p bin

javac -encoding UTF-8 -d bin *.java

if [ $? -eq 0 ]; then
  echo "Компиляция успешно завершена!"
else
  echo "Ошибка компиляции!"
  read -p "Нажмите Enter для выхода..." 
  exit 1
fi

read -p "Нажмите Enter для выхода..." 
exit 0