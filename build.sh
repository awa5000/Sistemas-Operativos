#!/bin/bash
echo "Compilando el proyecto..."

g++ -std=c++17 -Wall -Iinclude -o mi_shell src/main.cpp src/parser.cpp src/executor.cpp

if [ $? -eq 0 ]; then
    echo "mi-shell creado."
    echo "ejecuta con: ./mi_shell"
else
    echo "Error: La compilación falló."
fi
