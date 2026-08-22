@echo off
setlocal EnableExtensions

set "ROOT=%~1"
if "%ROOT%"=="" set "ROOT=%CD%"
if "%ROOT%"=="." set "ROOT=%CD%"

mkdir "%ROOT%\ToolLib\include\io" 2>nul
mkdir "%ROOT%\ToolLib\include\math" 2>nul
mkdir "%ROOT%\ToolLib\include\utils" 2>nul
mkdir "%ROOT%\ToolLib\src\io" 2>nul
mkdir "%ROOT%\ToolLib\src\math" 2>nul
mkdir "%ROOT%\ToolLib\src\memory" 2>nul
mkdir "%ROOT%\ToolLib\src\utils" 2>nul
mkdir "%ROOT%\output" 2>nul
mkdir "%ROOT%\.vscode" 2>nul

> "%ROOT%\Makefile" echo CC = gcc
>> "%ROOT%\Makefile" echo CFLAGS = -Wall -Wextra -g3 -IToolLib/include
>> "%ROOT%\Makefile" echo rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*^),$(call rwildcard,$d/,$2^))
>> "%ROOT%\Makefile" echo SRC = $(call rwildcard,ToolLib/,*.c^)
>> "%ROOT%\Makefile" echo OUT = output/main.exe
>> "%ROOT%\Makefile" echo.
>> "%ROOT%\Makefile" echo all: $(OUT)
>> "%ROOT%\Makefile" echo.
>> "%ROOT%\Makefile" echo $(OUT): $(SRC)
>> "%ROOT%\Makefile" echo 	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
>> "%ROOT%\Makefile" echo.
>> "%ROOT%\Makefile" echo clean:
>> "%ROOT%\Makefile" echo 	rm -f $(OUT)

> "%ROOT%\.vscode\c_cpp_properties.json" echo {
>> "%ROOT%\.vscode\c_cpp_properties.json" echo   "configurations": [
>> "%ROOT%\.vscode\c_cpp_properties.json" echo     {
>> "%ROOT%\.vscode\c_cpp_properties.json" echo       "name": "C Project",
>> "%ROOT%\.vscode\c_cpp_properties.json" echo       "includePath": [
>> "%ROOT%\.vscode\c_cpp_properties.json" echo         "${workspaceFolder}/ToolLib/include",
>> "%ROOT%\.vscode\c_cpp_properties.json" echo         "${workspaceFolder}/ToolLib/include/io",
>> "%ROOT%\.vscode\c_cpp_properties.json" echo         "${workspaceFolder}/ToolLib/include/math",
>> "%ROOT%\.vscode\c_cpp_properties.json" echo         "${workspaceFolder}/ToolLib/include/utils"
>> "%ROOT%\.vscode\c_cpp_properties.json" echo       ]
>> "%ROOT%\.vscode\c_cpp_properties.json" echo     }
>> "%ROOT%\.vscode\c_cpp_properties.json" echo   ],
>> "%ROOT%\.vscode\c_cpp_properties.json" echo   "version": 4
>> "%ROOT%\.vscode\c_cpp_properties.json" echo }

echo Project scaffold created in %ROOT%
echo Makefile now compiles every .c file found under ToolLib\ automatically (via recursive wildcard).
echo Use: make
