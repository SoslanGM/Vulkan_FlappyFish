
// Windows includes
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// Vulkan includes
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"
#include "vulkan/vk_platform.h"


// lib includes
#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb_truetype.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"


// My includes
#include <stdint.h>
#include "source.h"



LRESULT CALLBACK MainWindowCallback(HWND Window,
                                    UINT Message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    switch(Message)
    {
        case WM_CLOSE:
        {
            app.running = false;
        } break;
        
        case WM_DESTROY:
        {
            app.running = false;
        } break;
        
        case WM_KEYDOWN:
        {
            u32 virtual_key = wParam;
            u32 key_state = lParam;
            bool was_down = ((key_state & (1 << 30)) != 0);
            bool is_down  = ((key_state & (1 << 31)) == 0);
            
            if(was_down != is_down)
            {
                if(virtual_key == VK_ESCAPE)
                {
                    if(is_down)
                    {
                        ODS("Quitting the program");
                        PostQuitMessage(0);
                    }
                }
                
                if(virtual_key == VK_RETURN)
                {
                    if(is_down)
                    {
                        if(!game.collided)
                            GamePause();
                        else
                            GameReset();
                    }
                }
                if(virtual_key == VK_SPACE)
                {
                    if(!game.pause)
                    {
                        if(is_down)
                            PlayerJump();
                    }
                }
            }
        }
        
        default:
        {
            
        } break;
    }
    
    return DefWindowProc(Window, Message, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE Instance,
                     HINSTANCE PrevInstance,
                     LPSTR CommandLine,
                     int ShowMode)
{
    TimerSetup();
    TimerStart();
    
    u32 vk_dir_len = 100;
    app.vk_sdk_path = (char *)calloc(vk_dir_len, sizeof(char));
    GetEnvironmentVariable("vulkan_sdk", app.vk_sdk_path, vk_dir_len);
    ODS("Found Vulkan SDK path: %.*s\n", vk_dir_len, app.vk_sdk_path);
    
    app.instance = Instance;
    COLORREF color = 0x00000000;  // black;
    WindowClassRegister(MainWindowCallback, Instance,
                        color, app.class_name);
    WindowCreate(app.class_name, app.window_name, Instance);
    
    
    // --- Vulkan preparations ---
    LoadEnums();
    LoadInfos();
    
    VulkanPrepare();
    // ---
    
    
    
    // --- Data preparations ---
    DataPrepare();
    
    data.target_fps = 60.0f;
    
    data.target_frametime = 1.0f / data.target_fps;  // target_render_time
    
    r64 us_per_s = 1000000.0;
    r64 ms_per_s = 1000.0;
    
    data.time_framestart = TimerRead();
    data.time_active = TimerRead();
    data.time_warmup = TimerElapsedFrom_ms(data.time_start);
    
    //data.record_frames = 300;
    
    // --- Message Pump ---
    MSG msg;
    while(app.running)
    {
        PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
        if(msg.message == WM_QUIT)
            app.running = false;
        else
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        
        // ---
        Process();
        
        Render();
        
        Present();
        if(!game.pause)
            data.frame_counter++;
        
        // ---
        
        // wait here
        r64 frame_elapsed = TimerElapsedFrom_s(data.time_framestart);
        r64 sleep_time = frame_elapsed;
        if(sleep_time < data.target_frametime)
        {
            // if sleep is granular, then sleep
            if(data.ms_granular)
            {
                u32 sleep_for_ms = (u32)(ms_per_s * (data.target_frametime - frame_elapsed));
                if(sleep_for_ms > 0)
                    Sleep(sleep_for_ms);
            }
            
            // if not, then spinlock with no shame
            while(sleep_time < data.target_frametime)
                sleep_time = TimerElapsedFrom_s(data.time_framestart);
        }
        // ---
        
        data.dt = TimerElapsedFrom_s(data.time_framestart);
        
        data.time_framestart = TimerRead();
    }
    
    u32 debug_padsize = 20;
    PadDebugOutput(debug_padsize);
    
    TimerShutdown();
    
    return 0;
    // ---
}