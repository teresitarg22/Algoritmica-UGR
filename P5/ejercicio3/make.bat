@echo off

rem Lógica principal del script
:main
@REM rem Verificar los argumentos pasados al script
@REM if "%1" == "clean" (
@REM     call :clean
@REM ) else (
@REM     call :build_run
@REM )

if exist juegoBolsasOro.exe (
    del /Q juegoBolsasOro.exe
    echo Archivos limpiados.
)
echo Compilando el programa...
g++ juegoBolsasOro.cpp -o juegoBolsasOro.exe
if %errorlevel% neq 0 (
    echo Error: Fallo en la compilación.
    exit /b %errorlevel%
)
echo Compilacion exitosa.

