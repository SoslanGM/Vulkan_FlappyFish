@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

glslangValidator -V ..\code\background.vert -o background_vert.spv
glslangValidator -V ..\code\background.frag -o background_frag.spv

glslangValidator -V ..\code\player.vert -o player_vert.spv
glslangValidator -V ..\code\player.frag -o player_frag.spv

glslangValidator -V ..\code\level.vert -o level_vert.spv
glslangValidator -V ..\code\level.frag -o level_frag.spv

glslangValidator -V ..\code\overlay.vert -o overlay_vert.spv
glslangValidator -V ..\code\overlay.frag -o overlay_frag.spv


set vulkanInclude=%vulkan_sdk%\Include

set NAME=source
cl -I %vulkanInclude% -nologo -Zi "..\code\%NAME%.cpp" /link shlwapi.lib user32.lib gdi32.lib winmm.lib

popd