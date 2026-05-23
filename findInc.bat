@echo off
setlocal enabledelayedexpansion

echo Generating sources.cmake...

(
echo set(SOURCES
for /r src %%f in (*.cpp) do (
    set "file=%%f"
    set "file=!file:\=/!"
    set "file=!file:%cd%\=!"
    echo     !file!
)
echo )

echo(
echo set(HEADERS
for /r inc %%f in (*.h) do (
    set "file=%%f"
    set "file=!file:\=/!"
    set "file=!file:%cd%\=!"
    echo     !file!
)
echo )
) > sources.cmake

echo Done! sources.cmake created.
pause