@echo off

if not exist bin mkdir bin

set cc=clang
set flags=--std=c99 -Wall -Wextra
set libs=-lgdi32 -lopengl32

%cc% %flags% src/main.c %libs% -o bin/program

if %errorlevel% equ 0 bin\program