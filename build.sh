#!/bin/bash

mkdir -p build

cd build

cmake ../src

make

cd ..

cp build/SlotMachine .

echo "Сборка завершена. Бинарный файл находится в ./build."