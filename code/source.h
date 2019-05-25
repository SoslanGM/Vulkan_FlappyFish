
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                 DATA TYPES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// --- Standard type redefinitions ---

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  r32;
typedef double r64;

// ---



// --- Special characters ---

char terminator  = '\0';
char newline     = '\n';
char carriageret = '\r';
char space       = ' ';
char dot         = '.';
char underscore  = '_';
char equals      = '=';
char semicolon   = ';';

char braceopen   = '{';
char braceclose  = '}';

// ---





// --- geometry

typedef struct vertex
{
    float x, y, z, w;
} vertex;

typedef struct vertex_uv
{
    float x, y, z, w;
    float u, v;
} vertex_uv;


typedef struct quad
{
    vertex v0;
    vertex v1;
    vertex v2;
    vertex v3;
} quad;
typedef struct quad_uv
{
    vertex_uv v0;
    vertex_uv v1;
    vertex_uv v2;
    vertex_uv v3;
} quad_uv;

// ---


// --- text stuff

typedef struct
{
    char *text;
    int length;
} string;
string *String(char *s)
{
    string *result = (string *)malloc(sizeof(string));
    result->length = strlen(s);
    result->text = (char *)malloc(sizeof(char) * (result->length+1));
    result->text[result->length] = '\0';
    memcpy(result->text, s, result->length);
    return result;
}


typedef struct
{
    s32 width;
    s32 height;
    u32 sampler_binding;
    VkSampler sampler;
    VkImage image;
    VkImageView imageview;
    VkDeviceMemory memory;
    u32 *pixels;
    u32 pixels_datasize;
} image_data;

typedef struct font_data
{
    // stb parameters
    stbtt_fontinfo fontinfo;
    stbtt_bakedchar *baked_chardata;
    
    r32 font_size;
    r32 scale;
    
    r32 ascent;
    r32 descent;
    r32 linegap;
    r32 v_advance;
    
    s32 first_char;
    s32 char_count;
    
    image_data atlas_data;
} font_data;

// ---



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           DEBUG FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char ods_buf[2048];
#define ODS(...) \
_snprintf_s(ods_buf, sizeof(ods_buf), __VA_ARGS__); \
OutputDebugStringA(ods_buf);

void PadDebugOutput(u32 padsize)
{
    for(u32 i = 0; i < padsize; i++)
        OutputDebugStringA("\n");
}

void Assert(VkResult result, char *msg)
{
    if(result != VK_SUCCESS)
    {
        ODS("Result code: %d \n", result);
        ODS("ASSERT: %s \n", msg);
        
        int *base = 0;
        *base = 1;
    }
}
void Assert(bool flag, char *msg = "")
{
    if(!flag)
    {
        ODS("ASSERT: %s \n", msg);
        
        int *base = 0;
        *base = 1;
    }
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                    DEBUG FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                   VECTOR/MATRIX FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// VECTOR2
typedef r32 *vector2;
vector2 Vector2()
{
    vector2 result = (r32 *)malloc(sizeof(r32) * 2);
    return result;
}
vector2 Vector2(r32 v0, r32 v1)
{
    vector2 result = (r32 *)malloc(sizeof(r32) * 2);
    result[0] = v0;
    result[1] = v1;
    return result;
}

// VECTOR3
typedef r32 *vector3;
vector3 Vector3()
{
    vector3 result = (r32 *)malloc(sizeof(r32) * 3);
    return result;
}
vector3 Vector3(r32 v0, r32 v1, r32 v2)
{
    vector3 result = (r32 *)malloc(sizeof(r32) * 3);
    result[0] = v0;
    result[1] = v1;
    result[2] = v2;
    return result;
}
// ---

// VECTOR4
typedef r32 *vector4;
r32 *Vector4()
{
    r32 *result = (r32 *)malloc(sizeof(r32) * 4);
    return result;
}
void PrintVector(vector4 v)
{
    ODS("%7.3f %7.3f %7.3f %7.3f\n", v[0], v[1], v[2], v[3]);
}

typedef r32 *matrix4;
r32 *Matrix4()
{
    r32 *result = (r32 *)malloc(sizeof(r32) * 16);
    for(u32 i = 0; i < 16; i++)
    {
        if(i % 5 == 0)
            result[i] = 1.0f;
        else
            result[i] = 0.0f;
    }
    return result;
}

void PrintMatrix(matrix4 m)
{
    ODS("%7.3f %7.3f %7.3f %7.3f\n",   m[0],  m[1],  m[2],  m[3]);
    ODS("%7.3f %7.3f %7.3f %7.3f\n",   m[4],  m[5],  m[6],  m[7]);
    ODS("%7.3f %7.3f %7.3f %7.3f\n",   m[8],  m[9],  m[10], m[11]);
    ODS("%7.3f %7.3f %7.3f %7.3f\n\n", m[12], m[13], m[14], m[15]);
}

vector4 Vector4(r32 x, r32 y, r32 z, r32 w)
{
    vector4 result = (r32 *)malloc(sizeof(r32) * 4);
    result[0] = x;
    result[1] = y;
    result[2] = z;
    result[3] = w;
    return result;
}

vector4 MultMV(matrix4 m, vector4 v)
{
    vector4 result = Vector4();
    for(u32 i = 0; i < 4; i++)
    {
        r32 sum = 0.0f;
        for(u32 j = 0; j < 4; j++)
            sum += m[4*i+j] * v[j];
        result[i] = sum;
    }
    return result;
}
// ---

matrix4 Matrix4(r32 m0,  r32 m1,  r32 m2,  r32 m3,
                r32 m4,  r32 m5,  r32 m6,  r32 m7,
                r32 m8,  r32 m9,  r32 m10, r32 m11,
                r32 m12, r32 m13, r32 m14, r32 m15)
{
    matrix4 result = (r32 *)malloc(sizeof(r32) * 16);
    result[0]  = m0;
    result[1]  = m1;
    result[2]  = m2;
    result[3]  = m3;
    result[4]  = m4;
    result[5]  = m5;
    result[6]  = m6;
    result[7]  = m7;
    result[8]  = m8;
    result[9]  = m9;
    result[10] = m10;
    result[11] = m11;
    result[12] = m12;
    result[13] = m13;
    result[14] = m14;
    result[15] = m15;
    return result;
}
matrix4 Matrix4(r32 *m)
{
    matrix4 result = (r32 *)malloc(sizeof(r32) * 16);
    for(u32 i = 0; i < 16; i++)
        result[i] = m[i];
    return result;
}

matrix4 MultMM(matrix4 l, matrix4 r)
{
    matrix4 result = Matrix4();
    for(u32 i = 0; i < 4; i++)
    {
        u32 k;
        for(k = 0; k < 4; k++)
        {
            r32 sum = 0.0f;
            for(u32 j = 0; j < 4; j++)
                sum += l[4*i+j] * r[4*j+k];
            result[4*i+k] = sum;
        }
    }
    return result;
}

matrix4 MultMS(matrix4 m, r32 s)
{
    matrix4 result = (matrix4)malloc(sizeof(r32) * 16);
    for(u32 i = 0; i < 16; i++)
        result[i] = m[i] * s;
    return result;
}

matrix4 GenerateRotationMatrix(r32 angle_rad, vector4 axis)
{
    r32 *result = (r32 *)malloc(sizeof(r32) * 16);
    
    r32 PI = 3.14159265358f;
    r32 angle_deg = (angle_rad * PI) / 180.0f;
    
    r32 c = cos(angle_deg);
    r32 s = sin(angle_deg);
    
    r32 x = axis[0];
    r32 y = axis[1];
    r32 z = axis[2];
    
    result[0]  = x*x*(1.0f - c) + c;
    result[1]  = x*y*(1.0f - c) - z*s;
    result[2]  = x*z*(1.0f - c) + y*s;
    result[3]  = 0.0f;
    
    result[4]  = y*x*(1.0f - c) + z*s;
    result[5]  = y*y*(1.0f - c) + c;
    result[6]  = y*z*(1.0f - c) - x*s;
    result[7]  = 0.0f;
    
    result[8]  = z*x*(1.0f - c) - y*s;
    result[9]  = z*y*(1.0f - c) + x*s;
    result[10] = z*z*(1.0f - c) + c;
    result[11] = 0.0f;
    
    result[12] = 0.0f;
    result[13] = 0.0f;
    result[14] = 0.0f;
    result[15] = 1.0f;
    
    return result;
}

matrix4 GenerateTranslationMatrix(vector3 v)
{
    matrix4 result = Matrix4();
    
    result[3]  = v[0];
    result[7]  = v[1];
    result[11] = v[2];
    
    return result;
}

matrix4 TranslateMatrix(matrix4 m, vector3 v)
{
    matrix4 result = Matrix4();
    matrix4 translation_matrix = GenerateTranslationMatrix(v);
    
    result = MultMM(translation_matrix, result);
    
    free(translation_matrix);
    return result;
}

matrix4 GenerateOrthographicMatrix(u32 width, u32 height)
{
    r32 l = 0.0f;
    r32 r = (r32)width;
    r32 b = (r32)height;
    r32 t = 0.0f;
    r32 n = 1000.0f;
    r32 f = 0.0f;
    
    r32 o0  = 2.0f / (r-l);
    r32 o3  = - ((r+l) / (r-l));
    r32 o5  = 2.0f / (t-b);
    r32 o7  = - ((t+b) / (t-b));
    r32 o10 = -2.0f / (f-n);
    r32 o11 = - ((f+n) / (f-n));
    
    return Matrix4(o0,    0.0f,  0.0f,  o3,
                   0.0f,  o5,    0.0f,  o7,
                   0.0f,  0.0f,  o10,   o11,
                   0.0f,  0.0f,  0.0f,  1.0f);
}

matrix4 GenerateProjectiveMatrix(r32 l, r32 r, r32 b, r32 t, r32 n, r32 f)
{
    r32 p0  = (2.0f * n) / (r-l);
    r32 p2  = ((r+l) / (r-l));
    r32 p5  = (2.0f * n) / (t-b);
    r32 p6  = ((t+b) / (t-b));
    r32 p10 = - ((f+n) / (f-n));
    r32 p11 = - ((2.0f * f * n) / (f-n));
    
    matrix4 result = Matrix4(p0,    0.0f,  p2,    0.0f,
                             0.0f,  p5,    p6,    0.0f,
                             0.0f,  0.0f,  p10,   p11,
                             0.0f,  0.0f, -1.0f,  0.0f);
    
    return result;
}
matrix4 GenerateProjectiveMatrix(r32 fov, r32 ratio, r32 front, r32 back)
{
    r32 deg_to_rad = (fov * 180.0f) / 3.14159265358;
    r32 tangent = tanf(fov/2.0f * deg_to_rad);
    r32 height = front * tangent;
    r32 width = height * ratio;
    
    return GenerateProjectiveMatrix(-width, width, -height, height, front, back);
}

// What is this O_O
matrix4 GenerateScalingMatrix(r32 factor, r32 ratio)
{
    matrix4 result = Matrix4();
    
    result[0]  = factor;
    result[5]  = factor * ratio;
    result[10] = factor;
    
    return result;
}
matrix4 GenerateScalingMatrix(vector3 v)
{
    matrix4 result = Matrix4();
    
    result[0]  = v[0];
    result[5]  = v[1];
    result[10] = v[2];
    
    return result;
}

matrix4 GenerateViewportMatrix(u32 width, u32 height)
{
    matrix4 result = Matrix4();
    
    result[0]  = (r32)width  / 2.0f;
    result[5]  = (r32)height / 2.0f;
    result[10] = 1.0f;
    
    result[3]  = (r32)width  / 2.0f;
    result[7]  = (r32)height / 2.0f;
    result[11] = 0.0f;
    
    return result;
}

vector4 PerspectiveDivision(vector4 v)
{
    vector4 result = Vector4();
    
    result[0] = v[0] / v[3];
    result[1] = v[1] / v[3];
    result[2] = v[2] / v[3];
    result[3] = v[3] / v[3];
    
    return result;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////            VECTOR/MATRIX FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



//// //// --- --- Data structures --- ---

// Application side of things
struct
{
    HINSTANCE instance;
    WNDCLASS window_class = {};
    HWND window = {};
    
    char *class_name  = "Window class name";
    char *window_name = "Window name";
    
    u32 screen_width  = GetSystemMetrics(SM_CXSCREEN);
    u32 screen_height = GetSystemMetrics(SM_CYSCREEN);
    u32 window_width  = 1280;
    u32 window_height = 720;
    RECT rect_client_area;
    
    char *vk_sdk_path;
    
    bool running = true;
} app;

// vulkan side of things
struct
{
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkPhysicalDevice gpu;
    VkSurfaceKHR surface;
    u32 queue_family_index;
    VkDevice device;
    VkQueue queue;
    
    VkFormat format;
    VkColorSpaceKHR colorspace;
    VkPresentModeKHR present_mode;
    
    VkExtent2D extent_client_area;
    VkSwapchainKHR swapchain;
    VkImage *swapchain_images;
    VkImageView *swapchain_imageviews;
    
    VkCommandPool command_pool;
    VkCommandBuffer command_buffer;
    VkPhysicalDeviceMemoryProperties gpu_memprops;
    
    VkViewport viewport;
    VkRect2D scissor;
    VkFramebuffer *framebuffers;
    
    VkComponentMapping components;
    VkImageSubresourceRange color_sr;
    VkCommandBufferBeginInfo cb_bi;
    VkPipelineStageFlags stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo queue_si;
    VkFenceCreateInfo fence_ci;
    VkSemaphoreCreateInfo semaphore_ci;
} vk;

// our data
struct
{
    string *result_enum;
    string *format_enum;
    string *colorspace_enum;
    string *presentmode_enum;
    
    u32 image_count = 2;
    u32 acquired_index;
    
    matrix4 orthographic_matrix;
    matrix4 view_matrix;
    
    VkBuffer staging_buffer;
    VkDeviceMemory staging_memory;
    
    // ---
    u32 vertex_binding = 0;
    
    u32 matrix_binding;
    VkBuffer matrix_buffer;
    VkDeviceMemory matrix_memory;
    // ---
    
    VkBuffer obstacle_heightsbuf;
    VkDeviceMemory obstacle_heightsmemory;
    
    VkImage screenshot_image;
    VkDeviceMemory screenshot_memory;
    
    u32 frame_counter = 0;
    
    // --- program data ---
    // ---
    
    r32 distance = 0.0f;
    
    VkSemaphore semaphore_execution_complete;
    
    // --- time data ---
    bool ms_granular;
    u64 frequency;
    
    u32 record_frames;
    
    r64 target_fps;
    r64 target_frametime;
    
    u64 time_start;      // start of the application
    u64 time_active;
    u64 time_framestart;
    
    r64 frametime;
    r64 dt;
    r64 time_warmup;    // roughly from start of app to frame display
    // ---
} data;

//// //// --- ---   --- ---





// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                DYNAMIC FUNCTION LOADING(?) ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define DECLARE_FUNCTION_POINTER(Func) \
PFN_##Func Func = NULL;

#define LOAD_FUNCTION_POINTER_AND_ASSERT(Func) \
Func = (PFN_##Func) GetProcAddress (vulkanDLL, "" #Func ""); \
Assert(Func, "Unable to load function " #Func);

#define LOAD_EXTENSION_FUNCTION_POINTER_AND_ASSERT(Func, Inst) \
*(void **)&##Func = vkGetInstanceProcAddr(Inst, "" #Func); \
Assert(Func, "Unable to load extension function " #Func);


#define X(Func) DECLARE_FUNCTION_POINTER(Func)
#include "list_of_functions.h"
LIST_OF_FUNCTIONS
#include "list_of_ext_functions.h"
LIST_OF_EXT_FUNCTIONS
#undef X

// extraction of functions from the library and filling of function pointers
#define X(Func) LOAD_FUNCTION_POINTER_AND_ASSERT(Func)
void Vulkan_LoadInstanceFunctions()
{
    HMODULE vulkanDLL = LoadLibrary("vulkan-1.dll");
    Assert(vulkanDLL, "! Can't load Vulkan.");
    
    LIST_OF_FUNCTIONS
}
#undef LIST_OF_FUNCTIONS
#undef X

// loading of extension functions and filling of their pointers
#define X(Func) LOAD_EXTENSION_FUNCTION_POINTER_AND_ASSERT(Func, instance)
void Vulkan_LoadExtensionFunctions(VkInstance instance)
{
    LIST_OF_EXT_FUNCTIONS
}
#undef LIST_OF_EXT_FUNCTIONS
#undef X

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////            DYNAMIC FUNCTION LOADING ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                            TIME FUNCTIONS  ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define MS_GRANULARITY 1

void TimerSetup()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    data.frequency = freq.QuadPart;
    
    data.ms_granular = (timeBeginPeriod(MS_GRANULARITY) == TIMERR_NOERROR);
}

void TimerShutdown()
{
    if(data.ms_granular)
        timeEndPeriod(MS_GRANULARITY);
}

void TimerStart()
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    data.time_start = L.QuadPart;
}

u64 TimerRead()
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    
    u64 time = L.QuadPart;
    return time;
}

r64 TimerElapsedFrom(u64 prev, u64 mult)
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    
    u64 curr = L.QuadPart;
    u64 diff = curr - prev;
    r64 result = (r64)(diff * mult) / (r64)data.frequency;
    
    return result;
}
r64 TimerElapsedFrom_s(u64 prev)
{
    return TimerElapsedFrom(prev, 1.0);
}
r64 TimerElapsedFrom_ms(u64 prev)
{
    u64 ms_to_s = 1000.0;
    return TimerElapsedFrom(prev, ms_to_s);
}
r64 TimerElapsedFrom_us(u64 prev)
{
    u64 us_to_s = 1000000.0;
    return TimerElapsedFrom(prev, us_to_s);
}
r64 TimerElapsedFrom_ns(u64 prev)
{
    r64 ns_to_m = 1000000000.0;
    return TimerElapsedFrom(prev, ns_to_m);
}

string *TimerString(r64 t_us)
{
    r64 us_to_ms = 1000.0;
    r64 ms_to_s  = 1000.0;
    r64 s_to_m   = 60.0;
    r64 m_to_h   = 60.0;
    
    u32 m  = (u64)(t_us / (us_to_ms * ms_to_s * s_to_m));
    u32 s  = (u32)(t_us / (us_to_ms * ms_to_s)) % 60;
    u32 ms = (u32)((u32)(t_us / us_to_ms) % (u32)us_to_ms);
    
    char *format = "%02dm:%02ds.%03dms";
    u32 size = 100;
    char *buf = (char *)malloc(size);
    snprintf(buf, size, format, m, s, ms);
    
    return String(buf);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                      TIME FUNCTIONS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           WIN32 FUNCTIONS  ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void WindowClassRegister(WNDPROC callback, HINSTANCE instance,
                         COLORREF color, char *class_name)
{
    HBRUSH brush = CreateSolidBrush(color);
    
    app.window_class.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    app.window_class.lpfnWndProc   = callback;
    app.window_class.hInstance     = instance;
    app.window_class.lpszClassName = class_name;
    app.window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    app.window_class.hbrBackground = brush;
    
    if(!RegisterClassA(&app.window_class))
        OutputDebugStringA("! Register class failed");
    else
        OutputDebugStringA("> Window class registered");
}

void WindowCreate(char *class_name, char *window_name,
                  HINSTANCE instance)
{
    app.rect_client_area.left   = 0;
    app.rect_client_area.top    = 0;
    app.rect_client_area.right  = app.window_width  + 16;
    app.rect_client_area.bottom = app.window_height + 37;
    u32 style = WS_OVERLAPPEDWINDOW|WS_VISIBLE;
    
    u32 cx = (app.screen_width  - app.window_width)/2;
    u32 cy = (app.screen_height - app.window_height)/2;
    u32 width  = app.rect_client_area.right;
    u32 height = app.rect_client_area.bottom;
    
    app.window = CreateWindowExA(0,
                                 class_name,
                                 window_name,
                                 style,
                                 cx, cy,
                                 width, height,
                                 0,
                                 0,
                                 instance,
                                 0);
    
    if(!app.window)
        OutputDebugStringA("! Window creation failed");
    else
        OutputDebugStringA("> Window created");
    
    GetClientRect(app.window, &app.rect_client_area);
    
    vk.extent_client_area.width  = app.rect_client_area.right;
    vk.extent_client_area.height = app.rect_client_area.bottom;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                     WIN32 FUNCTIONS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                    FILE IO ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int strlen(char c) { return 1; }

char *OpenFile_v0(char *filename, int *size, bool removeslashr, bool debugprint)
{
    FILE *f = fopen(filename, "rb");
    if(!f)
    {
        printf("Couldn't open %s for reading\n", filename);
        exit(0);
    }
    
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    rewind(f);
    
    if(debugprint)
        printf("> OpenFile: ftell says length = %d\n", length);
    
    int alloc = length + strlen(terminator);
    char *buffer = (char *)malloc(sizeof(char) * alloc);
    fread(buffer, length, 1, f);
    buffer[length] = terminator;
    
    fclose(f);
    
    if(removeslashr)
    {
        int lengthsansr = 0;
        // count length without /r
        char *reader = buffer;
        while(reader[0] != terminator)
        {
            if(reader[0] != carriageret)
                lengthsansr++;
            reader++;
        }
        
        int allocsansr = lengthsansr + strlen(terminator);
        char *buffersansr = (char *)malloc(sizeof(char) * allocsansr);
        
        reader = buffer;
        char *writer = buffersansr;
        while(reader[0] != terminator)
        {
            if(reader[0] != carriageret)
                *writer++ = *reader;
            reader++;
        }
        buffersansr[lengthsansr] = terminator;
        
        free(buffer);
        
        if(size != NULL)
            *size = lengthsansr;
        return buffersansr;
    }
    
    if(size != NULL)
        *size = length;
    return buffer;
}
char *OpenFile_v0(char *filename, int *size)
{
    bool killslashrburnitdown = true;
    bool debugprint = false;
    
    return OpenFile_v0(filename, size, killslashrburnitdown, debugprint);
}
string *OpenFile(char *filename, int *size, bool removeslashr, bool debugprint)
{
    string *result = (string *)malloc(sizeof(string));
    
    result->text = OpenFile_v0(filename, size, removeslashr, debugprint);
    result->length = *size;
    
    return result;
}
string *OpenFile(char *filename, int *size)
{
    bool removeslashr = true;
    bool debugprint = false;
    
    string *result = (string *)malloc(sizeof(string));
    
    result->text = OpenFile_v0(filename, size, removeslashr, debugprint);
    result->length = *size;
    
    return result;
}
string *OpenFile(char *filename)
{
    bool removeslashr = true;
    bool debugprint = false;
    
    string *result = (string *)malloc(sizeof(string));
    
    int size = 0;
    result->text = OpenFile_v0(filename, &size, removeslashr, debugprint);
    result->length = size;
    
    return result;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                             FILE IO ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                  TOKENIZER ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct
{
    char *At;
} tokenizer;
tokenizer Tokenizer;

enum token_type
{
    token_Unknown,
    
    token_Pound,
    token_Dot,
    token_Comma,
    token_Equals,
    token_Colon,       token_SemiColon,
    token_BraceOpen,   token_BraceClose,
    token_ParensOpen,  token_ParensClose,
    token_BracketOpen, token_BracketClose,
    token_ChevronOpen, token_ChevronClose,
    token_Dash,
    token_Number,
    
    token_Identifier
};

typedef struct
{
    token_type type;
    
    int length;
    char *text;
} Token;

bool IsLetter(char c)
{
    if(('a' <= c && c <= 'z') ||
       ('A' <= c && c <= 'Z'))
        return true;
    
    return false;
}
bool IsNumber(char c)
{
    if('0' <= c && c <= '9')
        return true;
    return false;
}

bool IsNewline(char c)
{
    if(c == '\n' ||
       c == '\r')
        return true;
    return false;
}
bool IsGarbage(char c)
{
    if(c == ' ' ||
       c == '\t' ||
       IsNewline(c) ||
       c == '\0')
        return true;
    return false;
}

Token GetToken()
{
    while(IsGarbage(Tokenizer.At[0]))
        Tokenizer.At++;
    
    Token token;
    
    token.length = 1;
    token.text = Tokenizer.At;
    
    char c = *Tokenizer.At;
    switch(c)
    {
        case '#': { token.type = token_Pound; } break;
        case '.': { token.type = token_Dot;   } break;
        case ',': { token.type = token_Comma; } break;
        case ':': { token.type = token_Colon;     } break;
        case ';': { token.type = token_SemiColon; } break;
        case '=': { token.type = token_Equals; } break;
        
        case '{': { token.type = token_BraceOpen;  } break;
        case '}': { token.type = token_BraceClose; } break;
        case '(': { token.type = token_ParensOpen;  } break;
        case ')': { token.type = token_ParensClose; } break;
        case '[': { token.type = token_BracketOpen;  } break;
        case ']': { token.type = token_BracketClose; } break;
        case '<': { token.type = token_ChevronOpen;  } break;
        case '>': { token.type = token_ChevronClose; } break;
        
        default:
        {
            if(IsLetter(c) || (Tokenizer.At[0] == '*' && Tokenizer.At[1] != ' '))
            {
                token.type = token_Identifier;
                while(IsLetter(Tokenizer.At[0]) ||
                      IsNumber(Tokenizer.At[0]) ||
                      Tokenizer.At[0] == '_' ||
                      Tokenizer.At[0] == '*')
                {
                    Tokenizer.At++;
                }
                token.length = Tokenizer.At - token.text;
                Tokenizer.At--;
            } break;
            
            token.type = token_Unknown;
        } break;
    }
    
    return token;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                           TOKENIZER ------ ------
// //////////////////////////////////////////////////////////////////////////////




// --- Program functions ---

char *DecToBin(u64 n)
{
    u32 width = 64;
    
    char *binnum = (char *)malloc(width+1);
    binnum[width] = '\0';
    
    for(int i = 0; i < width; i++)
    {
        if(n >> i & 1)
            binnum[width-i-1] = '1';
        else
            binnum[width-i-1] = '0';
    }
    
    return binnum;
}

char *NumToString(int number, bool debugprint)
{
    int sign = (number < 0) ? -1 : 1;
    if(debugprint)
        printf("Is this %d value positive? %s\n", number, number >= 1 ? "YES" : "NO");
    
    number *= sign;
    int copynum = number;
    int length = 0;
    while(copynum >= 1)
    {
        copynum /= 10;
        length++;
    }
    
    u32 signlength;
    if(sign == 1)
        signlength = 0;
    else
        signlength = 1;
    
    if(length == 0)
        length = 1;
    char *str = (char *)malloc(sizeof(char) * (signlength + length + 1));
    str[length] = terminator;
    for(int i = 0; i < length; i++)
    {
        if(debugprint)
        {
            printf(" --- \n");
            printf("number: %d\n", number);
            printf("number %% 10: %d\n", number % 10);
            printf("symbol: %c\n", (number % 10) + '0');
            printf(" --- \n");
        }
        str[i] = number % 10 + '0';
        number /= 10;
    }
    
    // reverse value
    char *result = (char *)malloc(sizeof(char) * (signlength + length + 1));
    if(sign)
        result[0] = '-';
    
    for(int i = signlength, j = length-1; i < length+signlength; i++, j--)
        result[i] = str[j];
    
    result[length+signlength] = terminator;
    
    return result;
}

// ---



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                         ENUM INTROSPECTION ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *FindLine(char *buffer, int *length, char *searchterm)
{
    char *prelimstart = strstr(buffer, searchterm);
    
    if(prelimstart == NULL)
        return NULL;
    
    char *start;
    char *end;
    
    start = prelimstart;
    while(start != buffer)
    {
        start--;
        if(*start == newline)
        {
            start++;
            break;
        }
    }
    
    end = prelimstart;
    while(*end != terminator)
    {
        end++;
        if(*end == newline)
            break;
    }
    
    *length = (int)(end - start);
    return start;
}

string *RetrieveEnum(char *filename, char *enum_name)
{
    string *buffer = OpenFile(filename);
    
    char *enum_prefix = "typedef enum ";
    char *enum_searchterm = (char *)malloc(sizeof(char) * strlen(enum_prefix) + strlen(enum_name));
    strcpy(enum_searchterm, enum_prefix);
    strcat(enum_searchterm, enum_name);
    
    char *pos = strstr(buffer->text, enum_searchterm);
    if(pos == NULL)
    {
        ODS("Wrong enum name!\n");
        ODS("You were searching for this: %s\n", enum_name);
        exit(0);
    }
    
    
    char *begin = strchr(pos,   braceopen)  + 2;  // scroll forward a brace and a newline
    char *end   = strchr(begin, braceclose) - 1;  // scroll back a newline
    
    int length = (int)(end - begin);
    
    char *enumbuffer = (char *)malloc(sizeof(char) * length);
    strncpy(enumbuffer, begin, length);
    
    string *result = (string *)malloc(sizeof(string));
    result->text   = enumbuffer;
    result->length = length;
    
    return result;
}
char *RetrieveVkEnumString(string *vkenumbuffer, u32 enumvalue, bool debugprint)
{
    bool deb = false;
    
    char *valuestring = NumToString(enumvalue, debugprint);
    if(debugprint)
        printf("value: %s\n", valuestring);
    
    int length = 0;
    char *enumstring = FindLine(vkenumbuffer->text, &length, valuestring);
    
    Tokenizer.At = enumstring;
    Token token = GetToken();
    
    if(deb)
    {
        printf("token text:   %.*s\n", token.length, token.text);
        printf("token length: %d\n", token.length);
    }
    
    char *result = (char *)malloc(sizeof(char) * (token.length + 1));
    strncpy(result, token.text, token.length);
    result[token.length] = terminator;
    
    if(deb)
        printf("string length: %d\n", length);
    
    return result;
}
char *RevEnum(string *enum_buffer, s32 value, bool debugprint)
{
    return RetrieveVkEnumString(enum_buffer, value, debugprint);
}
char *RevEnum(string *enum_buffer, s32 value)
{
    bool debugprint = false;
    return RetrieveVkEnumString(enum_buffer, value, debugprint);
}

void LoadEnums()
{
    char *header_path = (char *)calloc(150, sizeof(char));
    strcpy(header_path, app.vk_sdk_path);
    strcat(header_path, "/Include/vulkan/vulkan_core.h");
    
    data.result_enum      = RetrieveEnum(header_path, "VkResult");
    data.format_enum      = RetrieveEnum(header_path, "VkFormat");
    data.colorspace_enum  = RetrieveEnum(header_path, "VkColorSpaceKHR");
    data.presentmode_enum = RetrieveEnum(header_path, "VkPresentModeKHR");
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                 ENUM INTROSPECTION  ------ ------
// //////////////////////////////////////////////////////////////////////////////



// -------------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                  RENDERSTATE MANAGEMENT(?) ------ ------ ------
//
// -----------------------\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// -------------------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct memory_pool
{
    u8 *start;
    u8 *write;  // reset each frame
    u32 size;
    u32 used;   // same
} memory_pool;

typedef struct renderstate
{
    VkPipeline pipeline;
    VkRenderPass renderpass;
    VkPipelineLayout pipeline_layout;
    VkDescriptorSetLayout ds_layout;
    VkDescriptorSet dset;
    u32 descset_count = 1;
    
    image_data texture_data;
    
    // if it's an overlay rs
    font_data *fd;
    
    // ---
    memory_pool *geometry;
    u32 quad_count;
    VkBuffer vertex_buffer;
    VkDeviceMemory vertex_memory;
    
    memory_pool *indexes;
    u32 index_count;
    VkBuffer index_buffer;
    VkDeviceMemory index_memory;
    // ---
} renderstate;
renderstate background_rs;
renderstate player_rs;
renderstate level_rs;
renderstate overlay_rs;


typedef struct render_init
{
    renderstate *rs;
    char *vert;
    char *frag;
} render_init;
render_init background_render_init;
render_init player_render_init;
render_init overlay_render_init;
render_init level_render_init;

typedef struct font_init
{
    char *fontfile;
    u32 font_size;
    u32 color;
} font_init;
font_init overlay_font_init;


#define KILOBYTE 1024
#define MEGABYTE 1024 * 1024
void MemoryAllocate(memory_pool *mp, u32 size)
{
    mp->start = (u8 *)malloc(size);
    mp->write = mp->start;
    mp->size = size;
    mp->used = 0;
}


void VertexesWrite(renderstate *rs, vertex *vertexes, u32 quad_count)
{
    u32 write_size = sizeof(vertex) * 4 * quad_count;  // 4 vertexes per quad
    memcpy(rs->geometry->write, vertexes, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    // I won't run out of memory now, but for the future
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Non-overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(vertexes);
}
void VertexesWrite_uv(renderstate *rs, vertex_uv *vertexes, u32 quad_count)
{
    u32 write_size = sizeof(vertex_uv) * 4 * quad_count;
    memcpy(rs->geometry->write, vertexes, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Non-overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(vertexes);
}


void IndexesWrite(renderstate *rs, u32 *indexes)
{
    u32 write_size = sizeof(u32) * rs->index_count;
    memcpy(rs->indexes->write, indexes, write_size);
    rs->indexes->write += write_size;
    rs->indexes->used += write_size;
    
    if(rs->indexes->used > rs->indexes->size)
    {
        ODS("Indexes pool's been blown out!\n");
        exit(0);
    }
    
    free(indexes);
}

u32 *GenerateQuadIndexes(renderstate *rs)
{
    u32 n = rs->quad_count;
    
    u32 indexes_per_polygon = 3;
    u32 polygons_per_quad = 2;
    u32 indexes_per_quad = indexes_per_polygon * polygons_per_quad;
    
    rs->index_count = indexes_per_quad * n;
    u32 *indexes = (u32 *)malloc(sizeof(u32) * rs->index_count);
    
    for(u32 i = 0; i < n; i++)
    {
        for(u32 j = 0; j < indexes_per_quad; j++)
        {
            u32 starting_index = 4*i;
            indexes[indexes_per_quad*i]   = starting_index;
            indexes[indexes_per_quad*i+1] = starting_index+1;
            indexes[indexes_per_quad*i+2] = starting_index+2;
            indexes[indexes_per_quad*i+3] = starting_index+1;
            indexes[indexes_per_quad*i+4] = starting_index+3;
            indexes[indexes_per_quad*i+5] = starting_index+2;
        }
    }
    
    u32 index_datasize = sizeof(u32) * rs->index_count;
    return indexes;
}

void WriteVertexMemory(renderstate *rs)
{
    void *level_geometry_mapptr;
    vkMapMemory(vk.device, rs->vertex_memory, 0, VK_WHOLE_SIZE, 0, &level_geometry_mapptr);
    memcpy(level_geometry_mapptr, rs->geometry->start, rs->geometry->used);
    vkUnmapMemory(vk.device, rs->vertex_memory);
}
void WriteIndexMemory(renderstate *rs)
{
    void *level_index_mapptr;
    vkMapMemory(vk.device, rs->index_memory, 0, VK_WHOLE_SIZE, 0, &level_index_mapptr);
    memcpy(level_index_mapptr, rs->indexes->start, rs->indexes->used);
    vkUnmapMemory(vk.device, rs->index_memory);
}

void WriteRenderstateMemory(renderstate *rs)
{
    WriteVertexMemory(rs);
    IndexesWrite(rs, GenerateQuadIndexes(rs));
    WriteIndexMemory(rs);
}


void QuadsWrite_uv(renderstate *rs, quad_uv *quads, u32 quad_count)
{
    u32 write_size = sizeof(quad_uv) * quad_count;
    memcpy(rs->geometry->write, quads, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(quads);
}
void QuadsWrite(renderstate *rs, quad *quads, u32 quad_count)
{
    u32 write_size = sizeof(quad) * quad_count;
    memcpy(rs->geometry->write, quads, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(quads);
}


void MemoryReset_geometry(renderstate *rs)
{
    rs->geometry->write = rs->geometry->start;
    rs->geometry->used = 0;
    rs->quad_count = 0;
}
void MemoryReset_indexes(renderstate *rs)
{
    rs->indexes->write = rs->indexes->start;
    rs->indexes->used = 0;
    rs->index_count = 0;
}



// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////              RENDERSTATE MANAGEMENT ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           STRING RENDERING ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum { left, h_center, right  } h_align;
typedef enum { top,  v_center, bottom } v_align;

u8 *ReadFontFile(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if(!f)
    {
        ODS("File '%s' not found\n", filename);
        exit(0);
    }
    
    fseek(f, 0, SEEK_END);
    
    u32 size = ftell(f);
    rewind(f);
    u8 *buffer = (u8 *)malloc(sizeof(u8) * size);
    
    fread(buffer, size, 1, f);
    fclose(f);
    
    return buffer;
}

quad_uv StringQuad(r32 l,    r32 r,    r32 t,    r32 b,
                   r32 uv_l, r32 uv_r, r32 uv_t, r32 uv_b)
{
    quad_uv result;
    
    result.v0.x = l;
    result.v0.y = b;
    result.v0.z = 0.0f;
    result.v0.w = 1.0f;
    result.v0.u = uv_l;
    result.v0.v = uv_b;
    
    result.v1.x = l;
    result.v1.y = t;
    result.v1.z = 0.0f;
    result.v1.w = 1.0f;
    result.v1.u = uv_l;
    result.v1.v = uv_t;
    
    result.v2.x = r;
    result.v2.y = b;
    result.v2.z = 0.0f;
    result.v2.w = 1.0f;
    result.v2.u = uv_r;
    result.v2.v = uv_b;
    
    result.v3.x = r;
    result.v3.y = t;
    result.v3.z = 0.0f;
    result.v3.w = 1.0f;
    result.v3.u = uv_r;
    result.v3.v = uv_t;
    
    return result;
}


vertex_uv *QuadGenerate_uv(r32 left, r32 top, r32 right, r32 bottom, bool flip)
{
    vertex_uv *result = (vertex_uv *)malloc(sizeof(vertex_uv) * 4);
    
    r32 uv_top;
    r32 uv_bot;
    if(!flip)
    {
        uv_top = 0.0f;
        uv_bot = 1.0f;
    }
    else
    {
        uv_top = 1.0f;
        uv_bot = 0.0f;
    }
    
    
    result[0].x = left;
    result[0].y = bottom;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    result[0].u = 0.0f;
    result[0].v = uv_bot;
    
    result[1].x = left;
    result[1].y = top;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    result[1].u = 0.0f;
    result[1].v = uv_top;
    
    result[2].x = right;
    result[2].y = bottom;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    result[2].u = 1.0f;
    result[2].v = uv_bot;
    
    result[3].x = right;
    result[3].y = top;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    result[3].u = 1.0f;
    result[3].v = uv_top;
    
    return result;
}
vertex_uv *QuadGenerate_uv_center(u32 w, u32 h, r32 cx, r32 cy)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    vertex_uv *result = (vertex_uv *)malloc(sizeof(vertex_uv) * 4);
    
    r32 left  = cx - width/2.0f;
    r32 right = cx + width/2.0f;
    r32 top    = cy - height/2.0f;
    r32 bottom = cy + height/2.0f;
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    result[0].u = 0.0f;
    result[0].v = 1.0f;  // 1
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    result[1].u = 0.0f;
    result[1].v = 0.0f;  // 0
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    result[2].u = 1.0f;
    result[2].v = 1.0f;  // 1
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    result[3].u = 1.0f;
    result[3].v = 0.0f;  // 0
    
    return result;
}
vertex_uv *QuadGenerate_centered_uv(u32 w, u32 h)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    r32 cx = app.window_width  / 2.0f;
    r32 cy = app.window_height / 2.0f;
    
    vertex_uv *result = QuadGenerate_uv_center(w, h, cx, cy);
    
    return result;
}

vertex *QuadGenerate(r32 left, r32 top, r32 right, r32 bottom)
{
    vertex *result = (vertex *)malloc(sizeof(vertex) * 4);
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    
    return result;
}
vertex *QuadGenerate_center(u32 w, u32 h, r32 cx, r32 cy)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    vertex *result = (vertex *)malloc(sizeof(vertex) * 4);
    
    r32 left  = cx - width/2.0f;
    r32 right = cx + width/2.0f;
    r32 top    = cy - height/2.0f;
    r32 bottom = cy + height/2.0f;
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    
    return result;
}
vertex *QuadGenerate_centered(u32 w, u32 h)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    r32 cx = app.window_width  / 2.0f;
    r32 cy = app.window_height / 2.0f;
    
    vertex *result = QuadGenerate(w, h, cx, cy);
    
    return result;
}


// --- strings
quad_uv *GenerateStringQuads_topleft(font_data *fdata, u32 font_index,
                                     string *str, r32 x_topleft, r32 y_topleft)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &x_topleft, &y_topleft, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate prospective coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}
quad_uv *GenerateStringQuads_centered(font_data *fdata, u32 font_index, string *str,
                                      r32 x_center, r32 y_center)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    r32 xcoord = 0.0f;
    r32 ycoord = 0.0f;
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &xcoord, &ycoord, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    r32 hcorr = x_center - str_width/2;
    r32 vcorr = y_center - str_height/2;
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate prospective coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        // --- Apply corrections ---
        // ---
        l += hcorr;
        r += hcorr;
        t -= vcorr;
        b -= vcorr;
        // ---
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}


quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h,     v_align v,
                             r32 h_padding, r32 v_padding)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    r32 xcoord = 0.0f;
    r32 ycoord = 0.0f;
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &xcoord, &ycoord, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    
    // --- calculate corrections ---
    // ---
    r32 hcorr = 0.0f;
    if(h == left)
        hcorr = h_padding;
    else if(h == h_center)
        hcorr = (app.window_width - str_width)/2.0f;
    else if(h == right)
        hcorr = app.window_width - str_width - h_padding;
    else { ODS("Whoops. Wrong enum value.\n"); exit(0); }
    
    r32 vcorr;
    if(v == top)
        vcorr = v_padding;
    else if(v == v_center)
        vcorr = (app.window_height - str_height)/2.0f;
    else if(v == bottom)
        vcorr = app.window_height - fdata[font_index].ascent - v_padding;
    else { ODS("Whoops. Wrong enum value.\n"); exit(0); }
    // ---
    
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        
        // --- Apply corrections ---
        // ---
        l += hcorr;
        r += hcorr;
        t -= vcorr;
        b -= vcorr;
        // ---
        
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}
quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h, v_align v,
                             r32 padding)
{
    return GenerateStringQuads(fdata, font_index, str,
                               h, v,
                               padding, padding);
}
quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h, v_align v)
{
    return GenerateStringQuads(fdata, font_index, str,
                               h, v,
                               0.0f, 0.0f);
}

// ------ ------ ------ divide between stb-facing and render-oriented functions ------ ------ ------

u32 *STB_WritePixels(u8 *bitmap, s32 width, s32 height, u32 color)
{
    u32 *pixels = (u32 *)malloc(sizeof(u32) * width * height);
    
    color = color & 0xFFFFFF;
    
    u32 *writer = pixels;
    u8 *linetracker = bitmap;
    for(u32 y = 0; y < height; y++)
    {
        u8 *reader = linetracker;
        for(u32 x = 0; x < width; x++)
        {
            u8 alpha = *reader++;
            u32 pixel;
            pixel = (alpha << 24) | color;
            
            *writer++ = pixel;
        }
        linetracker += width;
    }
    
    return pixels;
}

#define BUFSIZE 50
void Font_InitAndBake(renderstate *rs, char *fontfile, r32 font_size, u32 color)
{
    u8 *ttf_buffer = ReadFontFile(fontfile);
    stbtt_InitFont(&rs->fd->fontinfo, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
    
    rs->fd->font_size = font_size;
    rs->fd->scale = stbtt_ScaleForPixelHeight(&rs->fd->fontinfo, rs->fd->font_size);
    
    s32 s_ascent;
    s32 s_descent;
    s32 s_linegap;
    stbtt_GetFontVMetrics(&rs->fd->fontinfo, &s_ascent, &s_descent, &s_linegap);
    rs->fd->ascent  = (r32)s_ascent * rs->fd->scale;
    rs->fd->descent = (r32)s_descent * rs->fd->scale;
    rs->fd->linegap = (r32)s_linegap * rs->fd->scale;
    rs->fd->v_advance = rs->fd->ascent - rs->fd->descent + rs->fd->linegap;
    
    s32 char_count = 96;
    rs->fd->atlas_data.width  = 512;
    rs->fd->atlas_data.height = 512;
    
    u8 *bakedfont_bitmap = (u8 *)malloc(rs->fd->atlas_data.width * rs->fd->atlas_data.height);
    rs->fd->baked_chardata = (stbtt_bakedchar *)malloc(sizeof(stbtt_bakedchar) * rs->fd->char_count);
    
    stbtt_BakeFontBitmap(ttf_buffer, 0,
                         font_size,
                         bakedfont_bitmap, rs->fd->atlas_data.width, rs->fd->atlas_data.height,
                         rs->fd->first_char, rs->fd->char_count,
                         rs->fd->baked_chardata);
    
    rs->fd->atlas_data.pixels = STB_WritePixels(bakedfont_bitmap, rs->fd->atlas_data.width, rs->fd->atlas_data.height, color);
    rs->fd->atlas_data.pixels_datasize = rs->fd->atlas_data.width * rs->fd->atlas_data.height * 4;
    
    free(bakedfont_bitmap);
}

void RenderString_va(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 h_pad, u32 v_pad, char *format, va_list args)
{
    // --- format writing ---
    u32 size = BUFSIZE;
    char *buffer = (char *)malloc(size);
    u32 n = vsnprintf(buffer, size, format, args);
    if(size < n)
    {
        while(size < n)
            size *= 2;
        buffer = (char *)realloc(buffer, size);
        vsnprintf(buffer, size, format, args);
    }
    // ---
    
    // --- quad generating ---
    string *str = String(buffer);
    quad_uv *quads = GenerateStringQuads(rs->fd, font_index, str, ha, va, h_pad, v_pad);
    QuadsWrite_uv(rs, quads, str->length);
    // ---
    
    free(buffer);
}
void RenderString(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 h_pad, u32 v_pad, char *format, ...)
{
    va_list args;
    va_start(args, format);
    RenderString_va(rs, font_index, ha, va, h_pad, v_pad, format, args);
    va_end(args);
}
void RenderString(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 pad, char *format, ...)
{
    va_list args;
    va_start(args, format);
    RenderString_va(rs, font_index, ha, va, pad, pad, format, args);
    va_end(args);
}

// TODO: make a _va overload to pass varargs, like above
void RenderString_centered(renderstate *rs, u32 font_index, r32 x, r32 y, char *format, ...)
{
    // --- format writing ---
    u32 size = BUFSIZE;
    char *buffer = (char *)malloc(size);
    va_list args;
    va_start(args, format);
    u32 n = vsnprintf(buffer, size, format, args);
    if(size < n)
    {
        while(size < n)
            size *= 2;
        buffer = (char *)realloc(buffer, size);
        vsnprintf(buffer, size, format, args);
    }
    // ---
    
    // --- quad generating ---
    string *str = String(buffer);
    quad_uv *quads = GenerateStringQuads_centered(rs->fd, font_index, str, x, y);
    QuadsWrite_uv(rs, quads, str->length);
    // ---
    
    free(buffer);
}

void RenderMatrixStrings(renderstate *rs, u32 font_index, h_align ha, v_align va,
                         u32 h_pad, u32 v_pad, char *format, matrix4 m)
{
    r32 v_advance = rs->fd->v_advance;
    RenderString(rs, font_index, ha, va, h_pad, v_pad,
                 format, m[0],  m[1],  m[2],  m[3]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + v_advance,
                 format, m[4],  m[5],  m[6],  m[7]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + 2 * v_advance,
                 format, m[8],  m[9],  m[10], m[11]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + 3 * v_advance,
                 format, m[12], m[13], m[14], m[15]);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                    STRING RENDERING ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                  VULKAN FUNCTION(INTERACTION?) ABSTRACTION ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void LoadInfos()
{
    vk.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    
    vk.color_sr.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    vk.color_sr.baseMipLevel   = 0;
    vk.color_sr.levelCount     = 1;
    vk.color_sr.baseArrayLayer = 0;
    vk.color_sr.layerCount     = 1;
    
    vk.cb_bi.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vk.cb_bi.pNext            = NULL;
    vk.cb_bi.flags            = 0;
    vk.cb_bi.pInheritanceInfo = NULL;
    
    vk.queue_si.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    vk.queue_si.pNext                = NULL;
    vk.queue_si.pWaitDstStageMask    = &vk.stage_mask;
    vk.queue_si.commandBufferCount   = 1;
    vk.queue_si.pCommandBuffers      = &vk.command_buffer;
    
    vk.fence_ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vk.fence_ci.pNext = NULL;
    vk.fence_ci.flags = 0;
    
    vk.semaphore_ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    vk.semaphore_ci.pNext = NULL;
    vk.semaphore_ci.flags = 0;
}

// --- --- ---


VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
              VkDebugUtilsMessageTypeFlagsEXT types,
              const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
              void *user_data)
{
    ODS(">>> MessageIdName: %s\n", callback_data->pMessageIdName);
    ODS(">>> MessageIdNum:  %d\n", callback_data->messageIdNumber);
    ODS(">>> Message:       %s\n", callback_data->pMessage);
    ODS("\n");
    
    return VK_FALSE;
}

void Vulkan_SetupDebugging(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger)
{
    VkDebugUtilsMessengerCreateInfoEXT debug_messenger_ci = {};
    debug_messenger_ci.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_messenger_ci.pNext           = NULL;
    debug_messenger_ci.flags           = 0;
    debug_messenger_ci.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_messenger_ci.messageType     =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_messenger_ci.pfnUserCallback = DebugCallback;
    debug_messenger_ci.pUserData       = NULL;
    
    vkCreateDebugUtilsMessengerEXT(instance, &debug_messenger_ci, NULL, &debug_messenger);
}

void EnumerateGlobalExtensions()
{
    u32 global_propscount;
    vkEnumerateInstanceExtensionProperties(NULL, &global_propscount, NULL);
    VkExtensionProperties *global_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * global_propscount);
    vkEnumerateInstanceExtensionProperties(NULL, &global_propscount, global_props);
    
    ODS("\n> Instance-wide extensions: %d\n", global_propscount);
    for(u32 i = 0; i < global_propscount; i++)
    {
        u32 version = global_props[i].specVersion;
        u32 major = VK_VERSION_MAJOR(version);
        u32 minor = VK_VERSION_MINOR(version);
        u32 patch = VK_VERSION_PATCH(version);
        ODS("%2d - %-40s | %d.%d.%d\n", i, global_props[i].extensionName, major, minor, patch);
    }
    ODS("\n");
}

void EnumerateLayerExtensions()
{
    u32 layer_count = 0;
    vkEnumerateInstanceLayerProperties(&layer_count, NULL);
    VkLayerProperties *layer_props = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, layer_props);
    
    ODS("\n> Instance layers: %d\n", layer_count);
    for(u32 i = 0; i < layer_count; i++)
    {
        u32 spec_version = layer_props[i].specVersion;
        u32 spec_major = VK_VERSION_MAJOR(spec_version);
        u32 spec_minor = VK_VERSION_MINOR(spec_version);
        u32 spec_patch = VK_VERSION_PATCH(spec_version);
        
        u32 impl_version = layer_props[i].implementationVersion;
        u32 impl_major = VK_VERSION_MAJOR(impl_version);
        u32 impl_minor = VK_VERSION_MINOR(impl_version);
        u32 impl_patch = VK_VERSION_PATCH(impl_version);
        
        ODS("%2d - %-40s | %d.%d.%-3d | %d.%d.%d | %.50s\n",
            i,
            layer_props[i].layerName,
            spec_major, spec_minor, spec_patch,
            impl_major, impl_minor, impl_patch,
            layer_props[i].description);
        
        u32 ext_count = 0;
        vkEnumerateInstanceExtensionProperties(layer_props[i].layerName, &ext_count, NULL);
        if(ext_count)
        {
            ODS(">> its extensions: %d\n", ext_count);
            
            VkExtensionProperties *ext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * ext_count);
            vkEnumerateInstanceExtensionProperties(layer_props[i].layerName, &ext_count, ext_props);
            
            for(u32 i = 0; i < ext_count; i++)
            {
                u32 version = ext_props[i].specVersion;
                u32 major = VK_VERSION_MAJOR(version);
                u32 minor = VK_VERSION_MINOR(version);
                u32 patch = VK_VERSION_PATCH(version);
                ODS(" - %2d - %-37s | %d.%d.%d\n", i, ext_props[i].extensionName, major, minor, patch);
            }
        }
    }
    ODS("\n");
}

void GetGPU()
{
    u32 device_count;
    vkEnumeratePhysicalDevices(vk.instance, &device_count, NULL);
    VkPhysicalDevice *gpus = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * device_count);
    vkEnumeratePhysicalDevices(vk.instance, &device_count, gpus);
    
    vk.gpu = gpus[0];
}

void EnumerateDeviceExtensions()
{
    u32 devext_propcount;
    vkEnumerateDeviceExtensionProperties(vk.gpu, NULL, &devext_propcount, NULL);
    VkExtensionProperties *devext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * devext_propcount);
    vkEnumerateDeviceExtensionProperties(vk.gpu, NULL, &devext_propcount, devext_props);
    
    ODS("\n> Device extensions: %d\n", devext_propcount);
    for(u32 i = 0; i < devext_propcount; i++)
    {
        u32 version = devext_props[i].specVersion;
        u32 major = VK_VERSION_MAJOR(version);
        u32 minor = VK_VERSION_MINOR(version);
        u32 patch = VK_VERSION_PATCH(version);
        ODS("%2d - %-40s | %d.%d.%d\n", i, devext_props[i].extensionName, major, minor, patch);
    }
    ODS("\n");
}

void EnumerateDeviceLayers()
{
    u32 dev_layercount = 0;
    vkEnumerateDeviceLayerProperties(vk.gpu, &dev_layercount, NULL);
    VkLayerProperties *dev_layerprops = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * dev_layercount);
    vkEnumerateDeviceLayerProperties(vk.gpu, &dev_layercount, dev_layerprops);
    
    ODS("\n> Device layers: %d\n", dev_layercount);
    for(u32 i = 0; i < dev_layercount; i++)
    {
        u32 spec_version = dev_layerprops[i].specVersion;
        u32 spec_major = VK_VERSION_MAJOR(spec_version);
        u32 spec_minor = VK_VERSION_MINOR(spec_version);
        u32 spec_patch = VK_VERSION_PATCH(spec_version);
        
        u32 impl_version = dev_layerprops[i].implementationVersion;
        u32 impl_major = VK_VERSION_MAJOR(impl_version);
        u32 impl_minor = VK_VERSION_MINOR(impl_version);
        u32 impl_patch = VK_VERSION_PATCH(impl_version);
        
        ODS("%2d - %-40s | %d.%d.%-3d | %d.%d.%d | %.50s\n",
            i,
            dev_layerprops[i].layerName,
            spec_major, spec_minor, spec_patch,
            impl_major, impl_minor, impl_patch,
            dev_layerprops[i].description);
        
        u32 ext_count = 0;
        vkEnumerateDeviceExtensionProperties(vk.gpu, dev_layerprops[i].layerName, &ext_count, NULL);
        if(ext_count)
        {
            ODS(" > its extensions: %d\n", ext_count);
            
            VkExtensionProperties *ext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * ext_count);
            vkEnumerateDeviceExtensionProperties(vk.gpu, dev_layerprops[i].layerName, &ext_count, ext_props);
            
            for(u32 i = 0; i < ext_count; i++)
            {
                u32 version = ext_props[i].specVersion;
                u32 major = VK_VERSION_MAJOR(version);
                u32 minor = VK_VERSION_MINOR(version);
                u32 patch = VK_VERSION_PATCH(version);
                ODS(" - %2d - %-37s | %d.%d.%d\n", i, ext_props[i].extensionName, major, minor, patch);
            }
        }
    }
    ODS("\n");
}

void CheckGPUFeatures()
{
    VkPhysicalDeviceFeatures gpu_features;
    vkGetPhysicalDeviceFeatures(vk.gpu, &gpu_features);
    
    // This was previously generated with a metaprogramming utility.
    // To be showcased in a future portfolio entry :)
    ODS("- %-40s: %s\n", "robustBufferAccess", (gpu_features.robustBufferAccess & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fullDrawIndexUint32", (gpu_features.fullDrawIndexUint32 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "imageCubeArray", (gpu_features.imageCubeArray & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "independentBlend", (gpu_features.independentBlend & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "geometryShader", (gpu_features.geometryShader & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "tessellationShader", (gpu_features.tessellationShader & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sampleRateShading", (gpu_features.sampleRateShading & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "dualSrcBlend", (gpu_features.dualSrcBlend & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "logicOp", (gpu_features.logicOp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "multiDrawIndirect", (gpu_features.multiDrawIndirect & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "drawIndirectFirstInstance", (gpu_features.drawIndirectFirstInstance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthClamp", (gpu_features.depthClamp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthBiasClamp", (gpu_features.depthBiasClamp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fillModeNonSolid", (gpu_features.fillModeNonSolid & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthBounds", (gpu_features.depthBounds & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "wideLines", (gpu_features.wideLines & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "largePoints", (gpu_features.largePoints & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "alphaToOne", (gpu_features.alphaToOne & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "multiViewport", (gpu_features.multiViewport & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "samplerAnisotropy", (gpu_features.samplerAnisotropy & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionETC2", (gpu_features.textureCompressionETC2 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionASTC_LDR", (gpu_features.textureCompressionASTC_LDR & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionBC", (gpu_features.textureCompressionBC & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "occlusionQueryPrecise", (gpu_features.occlusionQueryPrecise & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "pipelineStatisticsQuery", (gpu_features.pipelineStatisticsQuery & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "vertexPipelineStoresAndAtomics", (gpu_features.vertexPipelineStoresAndAtomics & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fragmentStoresAndAtomics", (gpu_features.fragmentStoresAndAtomics & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderTessellationAndGeometryPointSize", (gpu_features.shaderTessellationAndGeometryPointSize & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderImageGatherExtended", (gpu_features.shaderImageGatherExtended & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageExtendedFormats", (gpu_features.shaderStorageImageExtendedFormats & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageMultisample", (gpu_features.shaderStorageImageMultisample & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageReadWithoutFormat", (gpu_features.shaderStorageImageReadWithoutFormat & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageWriteWithoutFormat", (gpu_features.shaderStorageImageWriteWithoutFormat & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderUniformBufferArrayDynamicIndexing", (gpu_features.shaderUniformBufferArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderSampledImageArrayDynamicIndexing", (gpu_features.shaderSampledImageArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageBufferArrayDynamicIndexing", (gpu_features.shaderStorageBufferArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageArrayDynamicIndexing", (gpu_features.shaderStorageImageArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderClipDistance", (gpu_features.shaderClipDistance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderCullDistance", (gpu_features.shaderCullDistance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderFloat64", (gpu_features.shaderFloat64 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderInt64", (gpu_features.shaderInt64 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderInt16", (gpu_features.shaderInt16 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderResourceResidency", (gpu_features.shaderResourceResidency & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderResourceMinLod", (gpu_features.shaderResourceMinLod & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseBinding", (gpu_features.sparseBinding & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyBuffer", (gpu_features.sparseResidencyBuffer & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyImage2D", (gpu_features.sparseResidencyImage2D & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyImage3D", (gpu_features.sparseResidencyImage3D & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency2Samples", (gpu_features.sparseResidency2Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency4Samples", (gpu_features.sparseResidency4Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency8Samples", (gpu_features.sparseResidency8Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency16Samples", (gpu_features.sparseResidency16Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyAliased", (gpu_features.sparseResidencyAliased & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "variableMultisampleRate", (gpu_features.variableMultisampleRate & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "inheritedQueries", (gpu_features.inheritedQueries & 1) ? "YES" : "NO");
    ODS("\n");
}

void GetFormatAndColorspace()
{
    u32 surface_formatcount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vk.gpu, vk.surface, &surface_formatcount, NULL);
    VkSurfaceFormatKHR *surface_formats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * surface_formatcount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(vk.gpu, vk.surface, &surface_formatcount, surface_formats);
    
    ODS("> Surface formats:\n");
    for(u32 i = 0; i < surface_formatcount; i++)
    {
        ODS("FormatKHR %d:\n", i);
        ODS("- format:      %s\n", RevEnum(data.format_enum,     surface_formats[i].format));
        ODS("- color space: %s\n", RevEnum(data.colorspace_enum, surface_formats[i].colorSpace));
    }
    ODS("\n");
    
    ODS("> Surface properties:\n");
    for(u32 i = 0; i < surface_formatcount; i++)
    {
        VkFormatProperties surface_props;
        vkGetPhysicalDeviceFormatProperties(vk.gpu, surface_formats[i].format, &surface_props);
        
        ODS("> Format %d:\n", i);
        ODS("Linear  tiling:  %s\n", DecToBin(surface_props.linearTilingFeatures));
        ODS("Optimal tiling:  %s\n", DecToBin(surface_props.optimalTilingFeatures));
        ODS("Buffer features: %s\n", DecToBin(surface_props.bufferFeatures));
        ODS("\n");
    }
    
    vk.format = surface_formats[0].format;
    vk.colorspace = surface_formats[0].colorSpace;
}

void CheckSurfaceCapabilities()
{
    VkSurfaceCapabilitiesKHR surface_caps;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk.gpu, vk.surface, &surface_caps);
    ODS("> Surface capabilities:\n");
    ODS("- min images: %d\n", surface_caps.minImageCount);
    ODS("- max images: %d\n", surface_caps.maxImageCount);
    ODS("- current extent: %-4d x %-4d\n", surface_caps.currentExtent.width,  surface_caps.currentExtent.height);
    ODS("- minimal extent: %-4d x %-4d\n", surface_caps.minImageExtent.width, surface_caps.minImageExtent.height);
    ODS("- maximal extent: %-4d x %-4d\n", surface_caps.maxImageExtent.width, surface_caps.maxImageExtent.height);
    ODS("- max image arrays: %d\n", surface_caps.maxImageArrayLayers);
    ODS("- Supported transforms:      %s\n", DecToBin(surface_caps.supportedTransforms));
    ODS("- Current transform:         %s\n", DecToBin(surface_caps.currentTransform));
    ODS("- Supported composite alpha: %s\n", DecToBin(surface_caps.supportedCompositeAlpha));
    ODS("- Supported usage flags:     %s\n", DecToBin(surface_caps.supportedUsageFlags));
    ODS("\n");
}

void SetPresentMode()
{
    u32 present_modecount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vk.gpu, vk.surface, &present_modecount, NULL);
    VkPresentModeKHR *present_modes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * present_modecount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(vk.gpu, vk.surface, &present_modecount, present_modes);
    
    ODS("> Present modes:\n");
    for(u32 i = 0; i < present_modecount; i++)
    {
        char *mode = RevEnum(data.presentmode_enum, present_modes[i]);
        ODS("Mode %d: %s\n", i, mode);
        
        if(strstr(mode, "MAILBOX"))
            vk.present_mode = present_modes[i];
    }
    ODS("Chosen present mode: %s\n", RevEnum(data.presentmode_enum, vk.present_mode));
    ODS("\n");
}

void CheckDeviceMemoryProperties()
{
    vkGetPhysicalDeviceMemoryProperties(vk.gpu, &vk.gpu_memprops);
    
    ODS("> Memory properties: \n");
    ODS("- memory heap count: %d\n", vk.gpu_memprops.memoryHeapCount);
    for(u32 i = 0; i < vk.gpu_memprops.memoryHeapCount; i++)
    {
        ODS("-- heap: %d: \n", i);
        ODS("size:  %zd MB\n", vk.gpu_memprops.memoryHeaps[i].size / (1024 * 1024));
        ODS("flags: %s  \n", DecToBin(vk.gpu_memprops.memoryHeaps[i].flags));
        ODS("\n");
    }
    ODS("- memory type count: %d\n", vk.gpu_memprops.memoryTypeCount);
    for(u32 i = 0; i < vk.gpu_memprops.memoryTypeCount; i++)
    {
        ODS("-- memory: %d: \n", i);
        ODS("heap index: %d \n", vk.gpu_memprops.memoryTypes[i].heapIndex);
        ODS("type:       %s \n", DecToBin(vk.gpu_memprops.memoryTypes[i].propertyFlags));
        ODS("\n");
    }
    ODS("\n");
}

// Finding a memory type index
u32 FindMemoryIndex(u32 possibleMemoryIndexes, u32 requiredProperties,
                    VkPhysicalDeviceMemoryProperties memoryProperties)
{
    ODS("Possible indexes:\n%.*s\n", 64,        DecToBin(possibleMemoryIndexes));
    ODS("Looking for these flags:\n%.*s\n", 64, DecToBin(requiredProperties));
    
    u32 memoryTypeCount = memoryProperties.memoryTypeCount;
    // iterate over all of the memory types,
    for(int i = 0; i < memoryTypeCount; i++)
    {
        // if we encountered a bit that's one of the returned from memoryreqs,
        if((possibleMemoryIndexes >> i) & 1)
        {
            // check if it has our required memory properties.
            u32 memoryTypePropertyFlags = memoryProperties.memoryTypes[i].propertyFlags;
            if((memoryTypePropertyFlags & requiredProperties) == requiredProperties)
            {
                ODS("selected index: %d\n", i);
                return i;
            }
        }
    }
    
    ODS("Couldn't find anything suitable\n");
    return -1;
}

// --- --- ---

void InstanceCreate(char **instance_layers, u32 layer_count,
                    char **instance_extensions, u32 extension_count)
{
    VkInstanceCreateInfo instance_ci = {};
    instance_ci.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_ci.pNext                   = NULL;
    instance_ci.flags                   = 0;
    instance_ci.pApplicationInfo        = NULL;
    instance_ci.enabledLayerCount       = layer_count;
    instance_ci.ppEnabledLayerNames     = instance_layers;
    instance_ci.enabledExtensionCount   = extension_count;
    instance_ci.ppEnabledExtensionNames = instance_extensions;
    
    VkResult result = vkCreateInstance(&instance_ci, NULL, &vk.instance);
    ODS("Vulkan instance creation: %s\n", RevEnum(data.result_enum, result));
}

void CreateSurface()
{
    VkWin32SurfaceCreateInfoKHR surface_ci = {};
    surface_ci.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_ci.pNext     = NULL;
    surface_ci.flags     = 0;
    surface_ci.hinstance = app.instance;
    surface_ci.hwnd      = app.window;
    
    vkCreateWin32SurfaceKHR(vk.instance, &surface_ci, NULL, &vk.surface);
}

void SetupQueue()
{
    // ---
    u32 queuefam_propcount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk.gpu, &queuefam_propcount, NULL);
    VkQueueFamilyProperties *queue_famprops = (VkQueueFamilyProperties *)malloc(sizeof(VkQueueFamilyProperties) * queuefam_propcount);
    vkGetPhysicalDeviceQueueFamilyProperties(vk.gpu, &queuefam_propcount, queue_famprops);
    
    ODS("> Queue family count: %d\n", queuefam_propcount);
    for(u32 i = 0; i < queuefam_propcount; i++)
    {
        ODS("Family %d:\n", i);
        ODS("%3d queues\n", queue_famprops[i].queueCount);
        ODS("Minimum gran: %-4d x %-4d\n", queue_famprops[i].minImageTransferGranularity.width, queue_famprops[i].minImageTransferGranularity.height);
        ODS("- graphics:  %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "YES" : "NO");
        ODS("- compute:   %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_COMPUTE_BIT)  ? "YES" : "NO");
        ODS("- transfer:  %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_TRANSFER_BIT) ? "YES" : "NO");
        ODS("- sparse:    %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? "YES" : "NO");
        ODS("- protected: %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_PROTECTED_BIT) ? "YES" : "NO");
        ODS("\n");
    }
    // ---
    
    // ---
    u32 queue_famindex = 0;
    
    for(u32 i = 0; i < queuefam_propcount; i++)
    {
        u32 can_graphics;
        u32 can_present;
        
        can_graphics = queue_famprops[i].queueFlags & VK_QUEUE_GRAPHICS_BIT;
        vkGetPhysicalDeviceSurfaceSupportKHR(vk.gpu, i, vk.surface, &can_present);
        
        if(can_graphics && can_present)
            queue_famindex = i;
    }
    
    vk.queue_family_index = queue_famindex;
    // ---
}
void DeviceCreate(char **device_extensions, u32 device_extension_count, VkPhysicalDeviceFeatures features)
{
    r32 queue_priority = 1.0f;
    
    VkDeviceQueueCreateInfo queue_ci = {};
    queue_ci.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_ci.pNext            = NULL;
    queue_ci.flags            = 0;
    queue_ci.queueFamilyIndex = vk.queue_family_index;
    queue_ci.queueCount       = 1;
    queue_ci.pQueuePriorities = &queue_priority;
    
    VkDeviceCreateInfo device_ci = {};
    device_ci.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_ci.pNext                   = NULL;
    device_ci.flags                   = 0;
    device_ci.queueCreateInfoCount    = 1;
    device_ci.pQueueCreateInfos       = &queue_ci;
    device_ci.enabledLayerCount       = 0;
    device_ci.ppEnabledLayerNames     = NULL;
    device_ci.enabledExtensionCount   = device_extension_count;
    device_ci.ppEnabledExtensionNames = device_extensions;
    device_ci.pEnabledFeatures        = &features;
    
    vkCreateDevice(vk.gpu, &device_ci, NULL, &vk.device);
}

void SwapchainCreate()
{
    VkSwapchainCreateInfoKHR swapchain_ci = {};
    swapchain_ci.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.pNext                 = NULL;
    swapchain_ci.flags                 = 0;
    swapchain_ci.surface               = vk.surface;
    swapchain_ci.minImageCount         = data.image_count;
    swapchain_ci.imageFormat           = vk.format;
    swapchain_ci.imageColorSpace       = vk.colorspace;
    swapchain_ci.imageExtent           = vk.extent_client_area;
    swapchain_ci.imageArrayLayers      = 1;
    swapchain_ci.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    swapchain_ci.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_ci.queueFamilyIndexCount = 0;
    swapchain_ci.pQueueFamilyIndices   = NULL;
    swapchain_ci.preTransform          = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchain_ci.compositeAlpha        = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_ci.presentMode           = vk.present_mode;
    swapchain_ci.clipped               = VK_TRUE;
    swapchain_ci.oldSwapchain          = NULL;
    
    vkCreateSwapchainKHR(vk.device, &swapchain_ci, NULL, &vk.swapchain);
}
void GetSwapchainImages()
{
    u32 swapchain_imagecount = 0;
    vkGetSwapchainImagesKHR(vk.device, vk.swapchain, &swapchain_imagecount, NULL);
    vk.swapchain_images = (VkImage *)malloc(sizeof(VkImage) * swapchain_imagecount);
    vkGetSwapchainImagesKHR(vk.device, vk.swapchain, &swapchain_imagecount, vk.swapchain_images);
}

void CreateSwapchainImageViews()
{
    VkImageViewCreateInfo imageview_ci = {};
    imageview_ci.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageview_ci.pNext            = NULL;
    imageview_ci.flags            = 0;
    imageview_ci.viewType         = VK_IMAGE_VIEW_TYPE_2D;
    imageview_ci.format           = vk.format;
    imageview_ci.components       = vk.components;
    imageview_ci.subresourceRange = vk.color_sr;
    
    vk.swapchain_imageviews = (VkImageView *)malloc(sizeof(VkImageView) * data.image_count);
    for(u32 i = 0; i < data.image_count; i++)
    {
        imageview_ci.image = vk.swapchain_images[i];
        vkCreateImageView(vk.device, &imageview_ci, NULL, &vk.swapchain_imageviews[i]);
    }
}

void CreateCommandPool()
{
    VkCommandPoolCreateInfo commandpool_ci = {};
    commandpool_ci.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandpool_ci.pNext            = NULL;
    commandpool_ci.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandpool_ci.queueFamilyIndex = vk.queue_family_index;
    
    vkCreateCommandPool(vk.device, &commandpool_ci, NULL, &vk.command_pool);
}

void AllocateCommandBuffer()
{
    VkCommandBufferAllocateInfo cb_ai = {};
    cb_ai.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cb_ai.pNext              = NULL;
    cb_ai.commandPool        = vk.command_pool;
    cb_ai.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cb_ai.commandBufferCount = 1;
    
    vkAllocateCommandBuffers(vk.device, &cb_ai, &vk.command_buffer);
}

VkBuffer CreateBuffer(u32 size, u32 usage, u32 required_memprops,
                      VkDevice device, VkPhysicalDeviceMemoryProperties gpu_memprops, VkDeviceMemory *memory)
{
    // ---
    VkBufferCreateInfo buffer_ci = {};
    buffer_ci.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_ci.pNext                 = NULL;
    buffer_ci.flags                 = 0;
    buffer_ci.size                  = size;
    buffer_ci.usage                 = usage;
    buffer_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    
    VkBuffer buffer;
    vkCreateBuffer(device, &buffer_ci, NULL, &buffer);
    // ---
    
    // ---
    VkMemoryRequirements mem_reqs;
    vkGetBufferMemoryRequirements(device, buffer, &mem_reqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = mem_reqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(mem_reqs.memoryTypeBits,
                                             required_memprops,
                                             gpu_memprops);
    
    vkAllocateMemory(device, &mem_ai, NULL, memory);
    // ---
    
    vkBindBufferMemory(device, buffer, *memory, 0);
    
    return buffer;
}

VkShaderModule RetrieveShaderModule(char *filepath, VkDevice GPUinterface)
{
    u32 shaderCodeSize;
    int maxShaderSize = 10000;
    char *shaderCode = (char *)malloc(sizeof(char) * maxShaderSize);
    
    HANDLE fileHandle = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if(fileHandle == INVALID_HANDLE_VALUE)
    {
        ODS("Couldn't load shader file %s\n", filepath);
        exit(1);
    }
    ReadFile((HANDLE)fileHandle, shaderCode, maxShaderSize, (LPDWORD)&shaderCodeSize, 0);
    CloseHandle(fileHandle);
    
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.pNext    = NULL;
    shaderModuleCreateInfo.flags    = 0;
    shaderModuleCreateInfo.codeSize = shaderCodeSize;
    shaderModuleCreateInfo.pCode    = (u32 *)shaderCode;
    
    VkShaderModule shaderModule = {};
    VkResult result = vkCreateShaderModule(GPUinterface, &shaderModuleCreateInfo, NULL, &shaderModule);
    ODS("Here's yo shader module!\n");
    
    return shaderModule;
}

void CreateViewport()
{
    vk.viewport.x        = 0;
    vk.viewport.y        = 0;
    vk.viewport.width    = app.window_width;
    vk.viewport.height   = app.window_height;
    vk.viewport.minDepth = 0.0;
    vk.viewport.maxDepth = 1.0;
}

void CreateScissor()
{
    vk.scissor.offset.x = 0;
    vk.scissor.offset.y = 0;
    vk.scissor.extent.width  = app.window_width;
    vk.scissor.extent.height = app.window_height;
}


// --- --- --- These are special. --- --- ---
void CreateRenderpass(renderstate *rs, bool keep_contents, bool last_renderpass)
{
    VkAttachmentDescription att_desc = {};
    att_desc.flags           = 0;
    att_desc.format          = vk.format;
    att_desc.samples         = VK_SAMPLE_COUNT_1_BIT;
    if(keep_contents)
        att_desc.loadOp      = VK_ATTACHMENT_LOAD_OP_LOAD;
    else
        att_desc.loadOp      = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att_desc.storeOp         = VK_ATTACHMENT_STORE_OP_STORE;
    att_desc.stencilLoadOp   = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att_desc.stencilStoreOp  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att_desc.initialLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    if(last_renderpass)
        att_desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    else
        att_desc.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    VkAttachmentReference color_attachment = {};
    color_attachment.attachment = 0;
    color_attachment.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    VkSubpassDescription subpass = {};
    subpass.flags                   = 0;
    subpass.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.inputAttachmentCount    = 0;
    subpass.pInputAttachments       = NULL;
    subpass.colorAttachmentCount    = 1;
    subpass.pColorAttachments       = &color_attachment;
    subpass.pResolveAttachments     = NULL;
    subpass.pDepthStencilAttachment = NULL;
    subpass.preserveAttachmentCount = 0;
    subpass.pPreserveAttachments    = NULL;
    
    VkRenderPassCreateInfo renderpass_ci = {};
    renderpass_ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpass_ci.pNext           = NULL;
    renderpass_ci.flags           = 0;
    renderpass_ci.attachmentCount = 1;
    renderpass_ci.pAttachments    = &att_desc;
    renderpass_ci.subpassCount    = 1;
    renderpass_ci.pSubpasses      = &subpass;
    renderpass_ci.dependencyCount = 0;
    renderpass_ci.pDependencies   = NULL;
    
    vkCreateRenderPass(vk.device, &renderpass_ci, NULL, &rs->renderpass);
}

void CreatePipeline_background(render_init *ri)
{
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    
    
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    
    
    // ---
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    // ---
    
    
    // ---
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    // ---
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    
    
    
    // ---
    VkDescriptorPoolSize matrixpool_size = {};
    matrixpool_size.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrixpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize dpool_sizes[] = { matrixpool_size, samplerpool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = 1;
    dpool_ci.poolSizeCount = 2;
    dpool_ci.pPoolSizes    = dpool_sizes;
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    VkDescriptorSetLayoutBinding ortho_matrix_binding = {};
    ortho_matrix_binding.binding            = data.matrix_binding;
    ortho_matrix_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ortho_matrix_binding.descriptorCount    = 1;
    ortho_matrix_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    ortho_matrix_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_binding = {};
    sampler_binding.binding            = 1;
    sampler_binding.descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    sampler_binding.descriptorCount    = 1;
    sampler_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dset_bindings[] = { ortho_matrix_binding, sampler_binding };
    
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = NULL;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = 2;
    dsl_ci.pBindings    = dset_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = NULL;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = 1;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    
    
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    
    
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
}

void CreatePipeline_player(render_init *ri)
{
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    
    
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    
    
    // ---
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    // ---
    
    
    // ---
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    // ---
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    
    
    
    // ---
    VkDescriptorPoolSize matrixpool_size = {};
    matrixpool_size.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrixpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize dpool_sizes[] = { matrixpool_size, samplerpool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = 1;
    dpool_ci.poolSizeCount = 2;
    dpool_ci.pPoolSizes    = dpool_sizes;
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    VkDescriptorSetLayoutBinding ortho_matrix_binding = {};
    ortho_matrix_binding.binding            = 0;
    ortho_matrix_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ortho_matrix_binding.descriptorCount    = 1;
    ortho_matrix_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    ortho_matrix_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_binding = {};
    sampler_binding.binding            = 1;
    sampler_binding.descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    sampler_binding.descriptorCount    = 1;
    sampler_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dset_bindings[] = { ortho_matrix_binding, sampler_binding };
    
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = NULL;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = 2;
    dsl_ci.pBindings    = dset_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = NULL;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = 1;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    
    
    VkPushConstantRange fish_offset_range = {};
    fish_offset_range.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    fish_offset_range.offset     = 0;
    fish_offset_range.size       = sizeof(r32);
    
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    pipeline_lci.pushConstantRangeCount = 1;
    pipeline_lci.pPushConstantRanges    = &fish_offset_range;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    
    
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
}
void CreatePipeline_level(render_init *ri)
{
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    
    
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    
    
    // ---
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    // ---
    
    
    // ---
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    // ---
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    
    
    
    // ---
    VkDescriptorPoolSize matrixpool_size = {};
    matrixpool_size.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrixpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize heightpool_size = {};
    heightpool_size.type            = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    heightpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize dpool_sizes[] = { matrixpool_size, samplerpool_size, heightpool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = 1;
    dpool_ci.poolSizeCount = 3;
    dpool_ci.pPoolSizes    = dpool_sizes;
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    VkDescriptorSetLayoutBinding ortho_matrix_binding = {};
    ortho_matrix_binding.binding            = 0;
    ortho_matrix_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ortho_matrix_binding.descriptorCount    = 1;
    ortho_matrix_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    ortho_matrix_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_binding = {};
    sampler_binding.binding            = 1;
    sampler_binding.descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    sampler_binding.descriptorCount    = 1;
    sampler_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding heights_binding = {};
    heights_binding.binding            = 2;
    heights_binding.descriptorType     = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    heights_binding.descriptorCount    = 1;
    heights_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    heights_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dset_bindings[] = { ortho_matrix_binding, sampler_binding, heights_binding };
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = NULL;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = 3;
    dsl_ci.pBindings    = dset_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = NULL;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = 1;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    
    
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    pipeline_lci.pushConstantRangeCount = 0;
    pipeline_lci.pPushConstantRanges    = NULL;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    
    
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
}
void CreatePipeline_overlay(render_init *ri)
{
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    
    
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    
    
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    
    
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    
    
    
    // ---
    u32 binding_index = 0;
    data.matrix_binding = binding_index++;
    ri->rs->fd->atlas_data.sampler_binding = binding_index++;
    
    VkDescriptorSetLayoutBinding matrix_binding = {};
    matrix_binding.binding            = data.matrix_binding;
    matrix_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrix_binding.descriptorCount    = 1;
    matrix_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    matrix_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_binding = {};
    sampler_binding.binding            = ri->rs->fd->atlas_data.sampler_binding;
    sampler_binding.descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    sampler_binding.descriptorCount    = 1;
    sampler_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dsl_bindings[] = { matrix_binding, sampler_binding};
    
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = NULL;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = 2;
    dsl_ci.pBindings    = dsl_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    
    VkDescriptorPoolSize matrixpool_size = {};
    matrixpool_size.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrixpool_size.descriptorCount = ri->rs->descset_count;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerpool_size.descriptorCount = ri->rs->descset_count;
    
    VkDescriptorPoolSize dpool_sizes[] = { matrixpool_size, samplerpool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = ri->rs->descset_count;
    dpool_ci.poolSizeCount = 2;
    dpool_ci.pPoolSizes    = dpool_sizes;
    
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = NULL;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = ri->rs->descset_count;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    // ---
    
    
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    
    
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
}


void InitRenderstateMemory(renderstate *rs, u32 geometry_size, u32 indexes_size)
{
    rs->geometry = (memory_pool *)malloc(sizeof(memory_pool));
    MemoryAllocate(rs->geometry, geometry_size);
    
    rs->indexes = (memory_pool *)malloc(sizeof(memory_pool));
    MemoryAllocate(rs->indexes, indexes_size);
    
    rs->vertex_buffer = CreateBuffer(rs->geometry->size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                     vk.device, vk.gpu_memprops, &rs->vertex_memory);
    
    rs->index_buffer = CreateBuffer(rs->indexes->size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                    vk.device, vk.gpu_memprops, &rs->index_memory);
}


void CreateRenderstate_background(render_init *ri)
{
    //// --- --- --- Render init --- --- ---
    // --- Renderstate memory
    InitRenderstateMemory(ri->rs, KILOBYTE, KILOBYTE);
    
    // --- Pipeline
    CreateRenderpass(ri->rs, false, false);
    CreatePipeline_background(ri);
}
void CreateRenderstate_player(render_init *ri)
{
    //// --- --- --- Render init --- --- ---
    // --- Renderstate memory
    InitRenderstateMemory(ri->rs, KILOBYTE, KILOBYTE);
    
    // --- Pipeline
    CreateRenderpass(ri->rs, true, false);
    CreatePipeline_player(ri);
}
void CreateRenderstate_level(render_init *ri)
{
    //// --- --- --- Render init --- --- ---
    // --- Renderstate memory
    InitRenderstateMemory(ri->rs, MEGABYTE, 240 * KILOBYTE);
    
    // --- Pipeline
    CreateRenderpass(ri->rs, true, false);
    CreatePipeline_level(ri);
}
void CreateRenderstate_overlay(render_init *ri, font_init *ti)
{
    // --- --- --- Text init --- --- ---
    ri->rs->fd = (font_data *)malloc(sizeof(font_data));
    ri->rs->fd->first_char = 32;
    ri->rs->fd->char_count = 96;
    
    Font_InitAndBake(ri->rs, ti->fontfile, ti->font_size, ti->color);
    // ---
    
    
    // --- --- --- Render init --- --- ---
    // --- Renderstate memory
    InitRenderstateMemory(ri->rs, MEGABYTE, 240 * KILOBYTE);
    
    // --- Pipeline
    CreateRenderpass(ri->rs, true, true);
    CreatePipeline_overlay(ri);
}
// ------------------------------------------



VkFramebuffer *CreateFramebuffers(renderstate *rs, VkImageView *imageviews, u32 image_count)
{
    VkFramebufferCreateInfo framebuffer_ci = {};
    framebuffer_ci.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_ci.pNext           = NULL;
    framebuffer_ci.flags           = 0;
    framebuffer_ci.renderPass      = rs->renderpass;
    framebuffer_ci.attachmentCount = 1;
    framebuffer_ci.width           = app.window_width;
    framebuffer_ci.height          = app.window_height;
    framebuffer_ci.layers          = 1;
    
    VkFramebuffer *framebuffers = (VkFramebuffer *)malloc(sizeof(VkFramebuffer) * image_count);
    for(u32 i = 0; i < data.image_count; i++)
    {
        framebuffer_ci.pAttachments = &imageviews[i];
        vkCreateFramebuffer(vk.device, &framebuffer_ci, NULL, &framebuffers[i]);
    }
    return framebuffers;
}

void CreateSamplerImage(u32 width, u32 height, VkImage *image, VkDeviceMemory *memory)
{
    // ---
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkImageCreateInfo image_ci = {};
    image_ci.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_ci.pNext                 = NULL;
    image_ci.flags                 = 0;
    image_ci.imageType             = VK_IMAGE_TYPE_2D;
    image_ci.format                = vk.format;
    image_ci.extent                = extent;
    image_ci.mipLevels             = 1;
    image_ci.arrayLayers           = 1;
    image_ci.samples               = VK_SAMPLE_COUNT_1_BIT;
    image_ci.tiling                = VK_IMAGE_TILING_OPTIMAL;
    image_ci.usage                 = VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    image_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_ci.queueFamilyIndexCount = 0;
    image_ci.pQueueFamilyIndices   = NULL;
    image_ci.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
    
    vkCreateImage(vk.device, &image_ci, NULL, image);
    // ---
    
    // ---
    VkMemoryRequirements memreqs;
    vkGetImageMemoryRequirements(vk.device, *image, &memreqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = memreqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(memreqs.memoryTypeBits,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                             vk.gpu_memprops);
    
    vkAllocateMemory(vk.device, &mem_ai, NULL, memory);
    
    vkBindImageMemory(vk.device, *image, *memory, 0);
    // ---
}
void CreateImage(VkImage *image, VkDeviceMemory *memory,
                 s32 width, s32 height,
                 VkImageTiling tiling, u32 usage,
                 VkImageLayout layout, VkMemoryPropertyFlags memory_properties)
{
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    // ---
    VkImageCreateInfo image_ci = {};
    image_ci.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_ci.pNext                 = NULL;
    image_ci.flags                 = 0;
    image_ci.imageType             = VK_IMAGE_TYPE_2D;
    image_ci.format                = vk.format;
    image_ci.extent                = extent;
    image_ci.mipLevels             = 1;
    image_ci.arrayLayers           = 1;
    image_ci.samples               = VK_SAMPLE_COUNT_1_BIT;
    image_ci.tiling                = tiling;
    image_ci.usage                 = usage;
    image_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_ci.queueFamilyIndexCount = 0;
    image_ci.pQueueFamilyIndices   = NULL;
    image_ci.initialLayout         = layout;
    
    vkCreateImage(vk.device, &image_ci, NULL, image);
    // ---
    
    // ---
    VkMemoryRequirements memreqs;
    vkGetImageMemoryRequirements(vk.device, *image, &memreqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = memreqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(memreqs.memoryTypeBits,
                                             memory_properties,
                                             vk.gpu_memprops);
    
    vkAllocateMemory(vk.device, &mem_ai, NULL, memory);
    
    vkBindImageMemory(vk.device, *image, *memory, 0);
    // ---
}

void CreateImageView(VkImage *image, VkImageView *imageview)
{
    VkComponentMapping components = {};
    components.r = VK_COMPONENT_SWIZZLE_B;
    components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    components.b = VK_COMPONENT_SWIZZLE_R;
    components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    
    VkImageViewCreateInfo imageview_ci = {};
    imageview_ci.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageview_ci.pNext            = NULL;
    imageview_ci.flags            = 0;
    imageview_ci.image            = *image;
    imageview_ci.viewType         = VK_IMAGE_VIEW_TYPE_2D;
    imageview_ci.format           = vk.format;
    imageview_ci.components       = components;
    imageview_ci.subresourceRange = vk.color_sr;
    
    vkCreateImageView(vk.device, &imageview_ci, NULL, imageview);
}

void CreateSampler(VkSampler *sampler)
{
    VkSamplerCreateInfo sampler_ci = {};
    sampler_ci.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_ci.pNext                   = NULL;
    sampler_ci.flags                   = 0;
    sampler_ci.magFilter               = VK_FILTER_LINEAR;
    sampler_ci.minFilter               = VK_FILTER_LINEAR;
    sampler_ci.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sampler_ci.addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.mipLodBias              = 0.0f;
    sampler_ci.anisotropyEnable        = VK_FALSE;
    sampler_ci.compareEnable           = VK_FALSE;
    sampler_ci.minLod                  = 1.0f;
    sampler_ci.maxLod                  = 1.0f;
    sampler_ci.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    
    vkCreateSampler(vk.device, &sampler_ci, NULL, sampler);
}
void CreateSampler_tile(VkSampler *sampler)
{
    VkSamplerCreateInfo sampler_ci = {};
    sampler_ci.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_ci.pNext                   = NULL;
    sampler_ci.flags                   = 0;
    sampler_ci.magFilter               = VK_FILTER_LINEAR;
    sampler_ci.minFilter               = VK_FILTER_LINEAR;
    sampler_ci.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sampler_ci.addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.mipLodBias              = 0.0f;
    sampler_ci.anisotropyEnable        = VK_FALSE;
    sampler_ci.compareEnable           = VK_FALSE;
    sampler_ci.minLod                  = 1.0f;
    sampler_ci.maxLod                  = 1.0f;
    sampler_ci.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    
    vkCreateSampler(vk.device, &sampler_ci, NULL, sampler);
}

// --- --- ---

void TransitImageLayout(VkImageLayout old_layout, VkImageLayout new_layout,
                        VkImage image, VkImageSubresourceRange sr,
                        VkCommandBuffer command_buffer, VkCommandBufferBeginInfo cb_bi,
                        VkDevice device, VkQueue queue, VkSubmitInfo queue_si)
{
    VkImageMemoryBarrier barrier = {};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext               = NULL;
    barrier.srcAccessMask       = VK_ACCESS_HOST_READ_BIT;
    barrier.dstAccessMask       = VK_ACCESS_HOST_WRITE_BIT;
    barrier.oldLayout           = old_layout;
    barrier.newLayout           = new_layout;
    barrier.image               = image;
    barrier.subresourceRange    = sr;
    
    vkBeginCommandBuffer(command_buffer, &cb_bi);
    vkCmdPipelineBarrier(command_buffer,
                         VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT,
                         0,
                         0, NULL,
                         0, NULL,
                         1, &barrier);
    vkEndCommandBuffer(command_buffer);
    
    VkFence fence;
    vkCreateFence(device, &vk.fence_ci, NULL, &fence);
    
    vkQueueSubmit(queue, 1, &queue_si, fence);
    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
    
    vkDestroyFence(device, fence, NULL);
}
void TransitImageLayout(VkImageLayout old_layout, VkImageLayout new_layout,
                        VkImage image)
{
    TransitImageLayout(old_layout, new_layout,
                       image, vk.color_sr,
                       vk.command_buffer, vk.cb_bi,
                       vk.device, vk.queue, vk.queue_si);
}

void TransitSwapchainImageLayouts()
{
    for(u32 i = 0; i < data.image_count; i++)
    {
        TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                           vk.swapchain_images[i]);
    }
}

void StageImage(u32 width, u32 height, VkImage image)
{
    VkImageSubresourceLayers subresource_layers = {};
    subresource_layers.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource_layers.mipLevel       = 0;
    subresource_layers.baseArrayLayer = 0;
    subresource_layers.layerCount     = 1;
    
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkBufferImageCopy regions = {};
    regions.bufferOffset      = 0;
    regions.bufferRowLength   = 0;
    regions.bufferImageHeight = 0;
    regions.imageSubresource  = subresource_layers;
    regions.imageExtent       = extent;
    regions.imageOffset.x = 0;
    regions.imageOffset.y = 0;
    regions.imageOffset.z = 0;
    // ---
    
    VkImageMemoryBarrier barrier = {};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext               = NULL;
    barrier.srcAccessMask       = VK_ACCESS_HOST_READ_BIT;
    barrier.dstAccessMask       = VK_ACCESS_HOST_WRITE_BIT;
    barrier.oldLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout           = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.image               = image;
    barrier.subresourceRange    = vk.color_sr;
    
    vkBeginCommandBuffer(vk.command_buffer, &vk.cb_bi);
    vkCmdCopyBufferToImage(vk.command_buffer, data.staging_buffer, image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &regions);
    vkCmdPipelineBarrier(vk.command_buffer,
                         VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT,
                         0,
                         0, NULL,
                         0, NULL,
                         1, &barrier);
    vkEndCommandBuffer(vk.command_buffer);
    
    VkPipelineStageFlags staging_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    
    VkSubmitInfo staging_si = {};
    staging_si.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    staging_si.pNext                = NULL;
    staging_si.waitSemaphoreCount   = 0;
    staging_si.pWaitSemaphores      = NULL;
    staging_si.pWaitDstStageMask    = &staging_mask;
    staging_si.commandBufferCount   = 1;
    staging_si.pCommandBuffers      = &vk.command_buffer;
    staging_si.signalSemaphoreCount = 0;
    staging_si.pSignalSemaphores    = NULL;
    
    VkFence fence;
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &fence);
    
    vkQueueSubmit(vk.queue, 1, &staging_si, fence);
    vkWaitForFences(vk.device, 1, &fence, VK_TRUE, UINT64_MAX);
}

void CopySwapchainImageToScreenshotImage(u32 width, u32 height,
                                         VkImage dst_image, VkImageLayout layout_of_dst,
                                         VkImage src_image, VkImageLayout layout_of_src)
{
    VkImageSubresourceLayers subresource_layers = {};
    subresource_layers.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource_layers.mipLevel       = 0;
    subresource_layers.baseArrayLayer = 0;
    subresource_layers.layerCount     = 1;
    
    VkOffset3D offset = {};
    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkImageCopy region = {};
    region.srcSubresource = subresource_layers;
    region.srcOffset      = offset;
    region.dstSubresource = subresource_layers;
    region.dstOffset      = offset;
    region.extent         = extent;
    
    vkBeginCommandBuffer(vk.command_buffer, &vk.cb_bi);
    vkCmdCopyImage(vk.command_buffer,
                   dst_image, layout_of_dst,
                   src_image, layout_of_src,
                   1,
                   &region);
    vkEndCommandBuffer(vk.command_buffer);
    
    VkFence fence;
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &fence);
    
    vkQueueSubmit(vk.queue, 1, &vk.queue_si, fence);
    vkWaitForFences(vk.device, 1, &fence, VK_TRUE, UINT64_MAX);
    
    vkDestroyFence(vk.device, fence, NULL);
}

// --- --- ---

void VulkanPrepare()
{
    Vulkan_LoadInstanceFunctions();
    EnumerateGlobalExtensions();
    EnumerateLayerExtensions();
    
    char *instance_layers[] = {
        "VK_LAYER_LUNARG_assistant_layer",
        "VK_LAYER_LUNARG_standard_validation" };
    u32 layer_count = sizeof(instance_layers) / sizeof(char *);
    
    char *instance_extensions[] = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
        "VK_EXT_debug_utils" };
    u32 extension_count = sizeof(instance_extensions) / sizeof(char *);
    
    InstanceCreate(instance_layers, layer_count,
                   instance_extensions, extension_count);
    
    Vulkan_LoadExtensionFunctions(vk.instance);
    
    Vulkan_SetupDebugging(vk.instance, vk.debug_messenger);
    GetGPU();
    EnumerateDeviceExtensions();
    EnumerateDeviceLayers();
    CheckGPUFeatures();
    CreateSurface();
    
    SetupQueue();  
    char *device_extensions[] = { "VK_KHR_swapchain" };
    u32 device_extension_count = sizeof(device_extensions) / sizeof(char *);
    VkPhysicalDeviceFeatures enable_features = {};
    DeviceCreate(device_extensions, device_extension_count, enable_features);
    vkGetDeviceQueue(vk.device, vk.queue_family_index, 0, &vk.queue);
    
    GetFormatAndColorspace();
    CheckSurfaceCapabilities();
    SetPresentMode();
    SwapchainCreate();
    GetSwapchainImages();
    CreateSwapchainImageViews();
    
    CreateCommandPool();
    AllocateCommandBuffer();
    CheckDeviceMemoryProperties();
    
    CreateScissor();
    CreateViewport();
    
    TransitSwapchainImageLayouts();
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////         VULKAN FUNCTION ABSTRACTION ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                              GAME CONTROLS ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct
{
    r32 x;
    r32 c, f;
} collision_set;
collision_set set[10];

struct
{
    bool pause = false;
    bool collided = false;
    
    // physics
    r32 move_speed = 150.0f;
    r32 fall_speed;
    r32 gravity = 1000.0f;
    r32 state_dt = 0.0f;
    
    // player
    r32 player_size = 64.0f;
    r32 player_jump = 0.4f * gravity;
    
    // level
    r32 obstacle_width = 128.0f;
    r32 gap_size = 200.0f;
    r32 gap_padding = (r32)app.window_height * 0.2f;        // 20% of height
    r32 gap_yrange = (r32)app.window_height - gap_padding;  // 80% of height
    
    r32 *obstacle_heights;
    
    r32 level_start = 1000.0f;
    r32 dist = 400.0f;
    u32 gap_position[10] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
} game;

typedef struct
{
    r32 x, y;
} player_state;
player_state player;

void GameReset()
{
    data.view_matrix = TranslateMatrix(GenerateTranslationMatrix(Vector3(-data.distance, 0.0f, 0.0f)), data.view_matrix);
    data.distance = 0.0f;
    
    game.fall_speed = 0.0f;
    player.x = (r32)(app.window_width)/2.0f;
    player.y = (r32)(app.window_height)/2.0f;
    
    game.collided = false;
    game.pause = false;
}

void PlayerJump()
{
    if(game.fall_speed > 0.0f)
    {
        game.fall_speed = -game.player_jump;
    }
}
void GamePause()
{
    game.pause = !game.pause;
}

void GameCollision()
{
    game.collided = true;
    GamePause();
}




// --- obstacles
void ObstacleGenerate(renderstate *rs, u32 gap_pos, r32 x, u32 set_index)
{
    r32 gap_cy = game.gap_padding * 0.5f + (10 - gap_pos) * game.gap_yrange * 0.1f;
    
    r32 l = x - game.obstacle_width / 2.0f;
    r32 r = x + game.obstacle_width / 2.0f;
    
    r32 t0 = (r32)app.window_height;
    r32 b0 = gap_cy + game.gap_size / 2.0f;
    
    r32 t1 = gap_cy - game.gap_size / 2.0f;
    r32 b1 = 0.0f;
    
    r32 h_top    = t0 - b0;
    r32 h_bottom = t1 - b1;
    game.obstacle_heights[2*set_index]   = h_top / (game.obstacle_width / 2.0f);
    game.obstacle_heights[2*set_index+1] = h_bottom / (game.obstacle_width / 2.0f);
    
    set[set_index].x = x;
    set[set_index].c = b0;
    set[set_index].f = t1;
    
    vertex_uv *top = QuadGenerate_uv(l, t0, r, b0, true);
    VertexesWrite_uv(rs, top, 1);
    
    vertex_uv *bot = QuadGenerate_uv(l, t1, r, b1, false);
    VertexesWrite_uv(rs, bot, 1);
}

void IntegrateState(player_state *player, r32 dt)
{
    r32 move_speed_dt = game.move_speed * dt;
    
    r32 fall_accel    = game.gravity;
    r32 fall_accel_dt = game.gravity * dt;
    game.fall_speed   += fall_accel_dt;
    r32 fall_speed_dt = game.fall_speed * dt;
    
    data.distance += move_speed_dt;
    
    vector3 view_movement_vector = Vector3(-move_speed_dt, 0.0f, 0.0f);
    matrix4 view_movement_matrix = GenerateTranslationMatrix(view_movement_vector);
    
    // move camera
    data.view_matrix = MultMM(view_movement_matrix, data.view_matrix);
    
    // move player
    player->x += move_speed_dt;
    player->y -= fall_speed_dt;
}

r32 Radius(r32 x0, r32 y0, r32 x1, r32 y1)
{
    r32 dx = fabs(x0 - x1);
    r32 dy = fabs(y0 - y1);
    
    return sqrt(dx*dx + dy*dy);
}
r32 hdist(r32 x0, r32 x1)
{
    return fabs(x0 - x1);
}
r32 vdist(r32 y0, r32 y1)
{
    return fabs(y0 - y1);
}

bool WithinRect(r32 x,   r32 y,
                r32 rx, r32 ry, r32 rw, r32 rh)
{
    r32 rect_left  = rx - rw/2.0f;
    r32 rect_right = rx + rw/2.0f;
    r32 rect_top    = ry + rh/2.0f;
    r32 rect_bottom = ry - rh/2.0f;
    
    return( ((rect_left <= x) && (x <= rect_right)) &&
           ((rect_top >= y) && (y >= rect_bottom)) );
}

bool CheckCollision(player_state player)
{
    bool result = false;
    
    for(u32 i = 0; i < 10; i++)
    {
        if(!game.collided)
        {
            // four radius checks, padding the corners with circles
            if(Radius(player.x, player.y, set[i].x - game.obstacle_width/2.0f, set[i].c) < game.player_size / 2.0f) return true;
            if(Radius(player.x, player.y, set[i].x + game.obstacle_width/2.0f, set[i].c) < game.player_size / 2.0f) return true;
            if(Radius(player.x, player.y, set[i].x - game.obstacle_width/2.0f, set[i].f) < game.player_size / 2.0f) return true;
            if(Radius(player.x, player.y, set[i].x + game.obstacle_width/2.0f, set[i].f) < game.player_size / 2.0f) return true;
            
            // four rectangles, to pad the obstacles on the left and the gap
            if(WithinRect(player.x, player.y,
                          set[i].x-(game.obstacle_width/2.0f+game.player_size/4.0f), set[i].f/2.0f, game.player_size/2.0f, set[i].f)) return true;
            if(WithinRect(player.x, player.y,
                          set[i].x-(game.obstacle_width/2.0f+game.player_size/4.0f), ((r32)app.window_height+set[i].c)/2.0f, game.player_size/2.0f, (r32)app.window_height-set[i].c)) return true;
            if(WithinRect(player.x, player.y,
                          set[i].x, set[i].f+game.player_size/4.0f, game.obstacle_width, game.player_size/2.0f)) return true;
            if(WithinRect(player.x, player.y,
                          set[i].x, set[i].c-game.player_size/4.0f, game.obstacle_width, game.player_size/2.0f)) return true;
            
            // Two of these effectively comprise a working Minkowski-wannabe collision system
            //  for the purposes of this game :)
        }
        
        
    }
    
    return false;
}
// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                       GAME CONTROLS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                      SCREENSHOT FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

u8 *ReadImage(char *filename, u32 *width, u32 *height)
{
    s32 image_channels;
    s32 force_channels = 4;
    u8 *pixels = stbi_load(filename, (s32 *)width, (s32 *)height, &image_channels, force_channels);
    
    return pixels;
}

void Pixels32BitTo24Bit(u32 *screenshot_pixels, u8 *screenshot_final_pixels)
{
    u32 *reader = screenshot_pixels;
    u8  *writer = screenshot_final_pixels;
    
    for(u32 i = 0; i < app.window_height; i++)
    {
        for(u32 j = 0; j < app.window_width; j++)
        {
            u32 pixel = *reader++;
            
            u8 A = pixel >> 24;
            u8 R = pixel >> 16;
            u8 G = pixel >> 8;
            u8 B = pixel;
            
            *writer++ = R;
            *writer++ = G;
            *writer++ = B;
        }
    }
}

void WriteScreenshot(u32 counter, u8 *pixels, u32 channels)
{
    char *dir = "../screenshots/";
    if(!PathFileExistsA(dir))
    {
        CreateDirectoryA(dir, NULL);
    }
    
    char *format = "../screenshots/screenshot_%05d.png";
    
    char buf[50];
    snprintf(buf, 50, format, counter);
    
    stbi_write_png(buf,
                   app.window_width, app.window_height,
                   channels, pixels,
                   app.window_width * channels);
}

void TakeScreenshot(u32 acquired_index, u32 frame_counter)
{
    
    // --- Screenshot ---
    // ---
    
    // screenshot: -> dst
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       data.screenshot_image);
    
    // swapchain image: present -> transfer src
    TransitImageLayout(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                       vk.swapchain_images[acquired_index]);
    
    // copy swapchain image to screenshot image
    CopySwapchainImageToScreenshotImage(app.window_width, app.window_height,
                                        vk.swapchain_images[acquired_index], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                                        data.screenshot_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                       vk.swapchain_images[data.acquired_index]);
    
    // transit layout of screenshot image: dst -> general
    TransitImageLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL,
                       data.screenshot_image);
    
    // ---
    // --- Allocate memory blocks ---
    // ---
    
    void *screenshot_mapptr;
    vkMapMemory(vk.device, data.screenshot_memory, 0, VK_WHOLE_SIZE, 0, &screenshot_mapptr);
    
    s32 screenshot_channels = 4;
    u32 screenshot_pixels_datasize = app.window_width * app.window_height * screenshot_channels;
    
    u32 *screenshot_pixels = (u32 *)malloc(sizeof(u32) * screenshot_pixels_datasize);
    memcpy(screenshot_pixels, screenshot_mapptr, screenshot_pixels_datasize);
    vkUnmapMemory(vk.device, data.screenshot_memory);
    
    u32 screenshot_final_channels = 3;
    u32 screenshot_pixels_final_datasize = app.window_width * app.window_height * screenshot_final_channels;
    u8 *screenshot_final_pixels = (u8 *)malloc(sizeof(u8) * screenshot_pixels_final_datasize);
    
    // ---
    
    Pixels32BitTo24Bit(screenshot_pixels, screenshot_final_pixels);
    
    WriteScreenshot(frame_counter, screenshot_final_pixels, screenshot_final_channels);
    
    free(screenshot_final_pixels);
    free(screenshot_pixels);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////               SCREENSHOT FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                              MAIN CONTROLS ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void DataPrepare()
{
    // --- Application preparations ---
    background_render_init.rs   = &background_rs;
    background_render_init.vert = "../build/background_vert.spv";
    background_render_init.frag = "../build/background_frag.spv";
    CreateRenderstate_background(&background_render_init);
    
    player_render_init.rs   = &player_rs;
    player_render_init.vert = "../build/player_vert.spv";
    player_render_init.frag = "../build/player_frag.spv";
    CreateRenderstate_player(&player_render_init);
    
    level_render_init.rs   = &level_rs;
    level_render_init.vert = "../build/level_vert.spv";
    level_render_init.frag = "../build/level_frag.spv";
    CreateRenderstate_level(&level_render_init);
    
    overlay_render_init.rs   = &overlay_rs;
    overlay_render_init.vert = "../build/overlay_vert.spv";
    overlay_render_init.frag = "../build/overlay_frag.spv";
    overlay_font_init.fontfile  = "C:/Windows/Fonts/consola.ttf";
    overlay_font_init.font_size = 20.0f;
    overlay_font_init.color     = 0xFFFFFF;  // BGR
    CreateRenderstate_overlay(&overlay_render_init, &overlay_font_init);
    
    vk.framebuffers = CreateFramebuffers(&overlay_rs, vk.swapchain_imageviews, data.image_count);
    
    game.obstacle_heights = (r32 *)malloc(sizeof(r32) * 20);
    // ---
    
    
    // ---prepare screenshot facilities
    CreateImage(&data.screenshot_image, &data.screenshot_memory,
                app.window_width, app.window_height,
                VK_IMAGE_TILING_LINEAR,
                VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    // ---
    
    
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &data.semaphore_execution_complete);
    
    
    data.staging_buffer = CreateBuffer(10 * MEGABYTE, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                       vk.device, vk.gpu_memprops, &data.staging_memory);
    
    
    //// --- --- --- ATLAS PREPARATIONS --- --- ---
    void *staging_mapptr;
    vkMapMemory(vk.device, data.staging_memory, 0, overlay_rs.fd->atlas_data.pixels_datasize, 0, &staging_mapptr);
    memcpy(staging_mapptr, overlay_rs.fd->atlas_data.pixels, overlay_rs.fd->atlas_data.pixels_datasize);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateSamplerImage(overlay_rs.fd->atlas_data.width, overlay_rs.fd->atlas_data.height,
                       &overlay_rs.fd->atlas_data.image,
                       &overlay_rs.fd->atlas_data.memory);
    CreateImageView(&overlay_rs.fd->atlas_data.image, &overlay_rs.fd->atlas_data.imageview);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       overlay_rs.fd->atlas_data.image);
    StageImage(overlay_rs.fd->atlas_data.width, overlay_rs.fd->atlas_data.height,
               overlay_rs.fd->atlas_data.image);
    
    CreateSampler(&overlay_rs.fd->atlas_data.sampler);
    // ---
    
    
    
    //// --- --- --- TEXTURE PREPARATIONS --- --- ---
    // background
    background_rs.texture_data.pixels = (u32 *)ReadImage("../data/background.png", &(u32)background_rs.texture_data.width, &(u32)background_rs.texture_data.height);
    
    background_rs.texture_data.pixels_datasize = background_rs.texture_data.width * background_rs.texture_data.height * 4;
    
    vkMapMemory(vk.device, data.staging_memory, 0, background_rs.texture_data.pixels_datasize, 0, &staging_mapptr);
    memcpy(staging_mapptr, background_rs.texture_data.pixels, background_rs.texture_data.pixels_datasize);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateSamplerImage(background_rs.texture_data.width, background_rs.texture_data.height,
                       &background_rs.texture_data.image,
                       &background_rs.texture_data.memory);
    CreateImageView(&background_rs.texture_data.image, &background_rs.texture_data.imageview);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       background_rs.texture_data.image);
    StageImage(background_rs.texture_data.width, background_rs.texture_data.height,
               background_rs.texture_data.image);
    
    CreateSampler(&background_rs.texture_data.sampler);
    
    
    // player
    player_rs.texture_data.pixels = (u32 *)ReadImage("../data/fish.png", &(u32)player_rs.texture_data.width, &(u32)player_rs.texture_data.height);
    
    player_rs.texture_data.pixels_datasize = player_rs.texture_data.width * player_rs.texture_data.height * 4;
    
    vkMapMemory(vk.device, data.staging_memory, 0, player_rs.texture_data.pixels_datasize, 0, &staging_mapptr);
    memcpy(staging_mapptr, player_rs.texture_data.pixels, player_rs.texture_data.pixels_datasize);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateSamplerImage(player_rs.texture_data.width, player_rs.texture_data.height,
                       &player_rs.texture_data.image,
                       &player_rs.texture_data.memory);
    CreateImageView(&player_rs.texture_data.image, &player_rs.texture_data.imageview);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       player_rs.texture_data.image);
    StageImage(player_rs.texture_data.width, player_rs.texture_data.height,
               player_rs.texture_data.image);
    
    CreateSampler(&player_rs.texture_data.sampler);
    
    
    // level
    level_rs.texture_data.pixels = (u32 *)ReadImage("../data/block.png", &(u32)level_rs.texture_data.width, &(u32)level_rs.texture_data.height);
    
    level_rs.texture_data.pixels_datasize = level_rs.texture_data.width * level_rs.texture_data.height * 4;
    
    vkMapMemory(vk.device, data.staging_memory, 0, level_rs.texture_data.pixels_datasize, 0, &staging_mapptr);
    memcpy(staging_mapptr, level_rs.texture_data.pixels, level_rs.texture_data.pixels_datasize);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateSamplerImage(level_rs.texture_data.width, level_rs.texture_data.height,
                       &level_rs.texture_data.image,
                       &level_rs.texture_data.memory);
    CreateImageView(&level_rs.texture_data.image, &level_rs.texture_data.imageview);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       level_rs.texture_data.image);
    StageImage(level_rs.texture_data.width, level_rs.texture_data.height,
               level_rs.texture_data.image);
    
    CreateSampler_tile(&level_rs.texture_data.sampler);
    
    
    u32 heightsize = sizeof(r32) * 20;
    data.obstacle_heightsbuf = CreateBuffer(heightsize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                            vk.device, vk.gpu_memprops, &data.obstacle_heightsmemory);
    
    
    //// --- --- --- GEOMETRY PREPARATIONS --- --- ---
    
    // Orthographics matrix for overlay renderstate's pipeline
    data.orthographic_matrix = GenerateOrthographicMatrix(app.window_width, app.window_height);
    
    
    // --- Writing matrix info
    u32 matrix_datasize = sizeof(r32) * 16;
    data.matrix_buffer = CreateBuffer(matrix_datasize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                      vk.device, vk.gpu_memprops, &data.matrix_memory);
    void *matrix_mapptr;
    vkMapMemory(vk.device, data.matrix_memory, 0, VK_WHOLE_SIZE, 0, &matrix_mapptr);
    memcpy(matrix_mapptr, data.orthographic_matrix, matrix_datasize);
    vkUnmapMemory(vk.device, data.matrix_memory);
    // ---
    
    
    // Initialize view matrix
    data.view_matrix = Matrix4();
    
    GameReset();
}

struct
{
    r32 player_x, player_y;
    r32 width, height;
} shader_inputs;

u32 fish_offset = 0;

void Process()
{
    // --- index cleanup
    MemoryReset_indexes(&background_rs);
    MemoryReset_indexes(&player_rs);
    MemoryReset_indexes(&level_rs);
    MemoryReset_indexes(&overlay_rs);
    
    
    //// --- --- --- VARIABLE CONTROL
    if(!game.pause)
        game.state_dt = data.dt;
    else
        game.state_dt = 0.0f;
    
    
    //// --- --- --- PHYSICS
    IntegrateState(&player, game.state_dt);
    if(CheckCollision(player))
    {
        while(CheckCollision(player))
            IntegrateState(&player, -game.state_dt/100.0f);
        GameCollision();
    }
    
    if(game.fall_speed > 0.0f)
        fish_offset = 0;
    else
        fish_offset = 1;
    
    //// --- --- --- GEOMETRY --- --- ---
    // --- Generate
    // background
    vertex_uv *background_vertexes = QuadGenerate_centered_uv(app.window_width, app.window_height);
    VertexesWrite_uv(&background_rs, background_vertexes, 1);
    WriteRenderstateMemory(&background_rs);
    
    // player
    vertex_uv *player_vertexes = QuadGenerate_uv_center(game.player_size, game.player_size, player.x, player.y);
    VertexesWrite_uv(&player_rs, player_vertexes, 1);
    
    // level
    for(u32 i = 0; i < 10; i++)
    {
        // generates and writes two quads
        ObstacleGenerate(&level_rs, game.gap_position[i], game.level_start + i * game.dist, i);
    }
    // ---
    void *heights_memptr;
    vkMapMemory(vk.device, data.obstacle_heightsmemory, 0, VK_WHOLE_SIZE, 0, &heights_memptr);
    memcpy(heights_memptr, game.obstacle_heights, sizeof(r32) * 20);
    vkUnmapMemory(vk.device, data.obstacle_heightsmemory);
    
    
    vector4 ptr = (vector4)player_rs.geometry->start;
    for(u32 i = 0; i < player_rs.quad_count * 4; i++)
    {
        vector4 modify = MultMV(data.view_matrix, ptr);
        memcpy(ptr, modify, sizeof(r32) * 4);
        ptr += 6;
    }
    WriteRenderstateMemory(&player_rs);
    // ---
    
    ptr = (vector4)level_rs.geometry->start;
    for(u32 i = 0; i < level_rs.quad_count * 4; i++)
    {
        vector4 modify = MultMV(data.view_matrix, ptr);
        memcpy(ptr, modify, sizeof(r32) * 4);
        ptr += 6;
    }
    WriteRenderstateMemory(&level_rs);
    // ---
    
    
    
    //// --- --- --- OVERLAY --- --- ---
    // --- generate
    u32 font_index = 0;
    r32 v_advance = overlay_rs.fd->v_advance;
    
    r32 pad = 5.0f;
    r32 v_pad = 5.0f;
    r32 h_pad = 5.0f;
    
    if(!game.collided)
    {
        RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad,                 "Warmup time: %6.3f ms", data.time_warmup);
        RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 1 * v_advance, "Delta t: %f", data.dt);
        RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 2 * v_advance, "Current FPS: %6.3f", 1.0f / data.dt);
        
        RenderString(&overlay_rs, font_index, right, bottom, h_pad, v_pad + 1 * v_advance, "Press space to jump");
        RenderString(&overlay_rs, font_index, right, bottom, h_pad, v_pad + 0 * v_advance, "Press enter to pause");
    }
    else
        RenderString(&overlay_rs, font_index, h_center, v_center, 0.0f, 0.0f, "[Press ENTER to try again]");
    // ---
    
    
    WriteRenderstateMemory(&overlay_rs);
    //// --- --- ---
    
    
    
    // --- geometry cleanup
    MemoryReset_geometry(&background_rs);
    MemoryReset_geometry(&player_rs);
    MemoryReset_geometry(&level_rs);
    MemoryReset_geometry(&overlay_rs);
}

void Render()
{
    // --- Acquire image ---
    // ---
    VkFence fence_acquisition_complete;
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &fence_acquisition_complete);
    
    vkAcquireNextImageKHR(vk.device, vk.swapchain, UINT64_MAX, VK_NULL_HANDLE, fence_acquisition_complete, &data.acquired_index);
    
    vkWaitForFences(vk.device, 1, &fence_acquisition_complete, VK_TRUE, UINT64_MAX);
    vkDestroyFence(vk.device, fence_acquisition_complete, NULL);
    // ---
    
    
    // Transit into color attachment for rendering
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                       vk.swapchain_images[data.acquired_index]);
    
    
    // --- Prepare renderpass ---
    // ---
    VkClearValue clear_color;
    clear_color = { 0.15f, 0.15f, 0.15f, 1.0f };
    
    VkRenderPassBeginInfo background_renderpass_bi = {};
    background_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    background_renderpass_bi.pNext           = NULL;
    background_renderpass_bi.renderPass      = background_rs.renderpass;
    background_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    background_renderpass_bi.renderArea      = vk.scissor;
    background_renderpass_bi.clearValueCount = 1;
    background_renderpass_bi.pClearValues    = &clear_color;
    
    VkRenderPassBeginInfo player_renderpass_bi = {};
    player_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    player_renderpass_bi.pNext           = NULL;
    player_renderpass_bi.renderPass      = player_rs.renderpass;
    player_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    player_renderpass_bi.renderArea      = vk.scissor;
    player_renderpass_bi.clearValueCount = 0;
    player_renderpass_bi.pClearValues    = NULL;
    
    VkRenderPassBeginInfo level_renderpass_bi = {};
    level_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    level_renderpass_bi.pNext           = NULL;
    level_renderpass_bi.renderPass      = level_rs.renderpass;
    level_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    level_renderpass_bi.renderArea      = vk.scissor;
    level_renderpass_bi.clearValueCount = 0;
    level_renderpass_bi.pClearValues    = NULL;
    
    VkRenderPassBeginInfo overlay_renderpass_bi = {};
    overlay_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    overlay_renderpass_bi.pNext           = NULL;
    overlay_renderpass_bi.renderPass      = overlay_rs.renderpass;
    overlay_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    overlay_renderpass_bi.renderArea      = vk.scissor;
    overlay_renderpass_bi.clearValueCount = 0;
    overlay_renderpass_bi.pClearValues    = NULL;
    // ---
    
    
    //// --- --- --- Render resource management --- --- ---
    // --- write matrixes
    VkDescriptorBufferInfo matrix_buffer_info = {};
    matrix_buffer_info.buffer = data.matrix_buffer;
    matrix_buffer_info.offset = 0;
    matrix_buffer_info.range  = VK_WHOLE_SIZE;
    
    VkWriteDescriptorSet background_matrix_write = {};
    background_matrix_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    background_matrix_write.pNext            = NULL;
    background_matrix_write.dstSet           = background_rs.dset;
    background_matrix_write.dstBinding       = data.matrix_binding;
    background_matrix_write.dstArrayElement  = 0;
    background_matrix_write.descriptorCount  = background_rs.descset_count;
    background_matrix_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    background_matrix_write.pImageInfo       = NULL;
    background_matrix_write.pBufferInfo      = &matrix_buffer_info;
    background_matrix_write.pTexelBufferView = NULL;
    
    VkWriteDescriptorSet player_matrix_write = {};
    player_matrix_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    player_matrix_write.pNext            = NULL;
    player_matrix_write.dstSet           = player_rs.dset;
    player_matrix_write.dstBinding       = data.matrix_binding;
    player_matrix_write.dstArrayElement  = 0;
    player_matrix_write.descriptorCount  = player_rs.descset_count;
    player_matrix_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    player_matrix_write.pImageInfo       = NULL;
    player_matrix_write.pBufferInfo      = &matrix_buffer_info;
    player_matrix_write.pTexelBufferView = NULL;
    
    VkWriteDescriptorSet level_matrix_write = {};
    level_matrix_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    level_matrix_write.pNext            = NULL;
    level_matrix_write.dstSet           = level_rs.dset;
    level_matrix_write.dstBinding       = data.matrix_binding;
    level_matrix_write.dstArrayElement  = 0;
    level_matrix_write.descriptorCount  = level_rs.descset_count;
    level_matrix_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    level_matrix_write.pImageInfo       = NULL;
    level_matrix_write.pBufferInfo      = &matrix_buffer_info;
    level_matrix_write.pTexelBufferView = NULL;
    
    VkWriteDescriptorSet overlay_matrix_write = {};
    overlay_matrix_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    overlay_matrix_write.pNext            = NULL;
    overlay_matrix_write.dstSet           = overlay_rs.dset;
    overlay_matrix_write.dstBinding       = data.matrix_binding;
    overlay_matrix_write.dstArrayElement  = 0;
    overlay_matrix_write.descriptorCount  = overlay_rs.descset_count;
    overlay_matrix_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    overlay_matrix_write.pImageInfo       = NULL;
    overlay_matrix_write.pBufferInfo      = &matrix_buffer_info;
    overlay_matrix_write.pTexelBufferView = NULL;
    // ---
    
    
    // --- Samplers write
    VkDescriptorImageInfo background_sampler_image_info = {};
    background_sampler_image_info.sampler     = background_rs.texture_data.sampler;
    background_sampler_image_info.imageView   = background_rs.texture_data.imageview;
    background_sampler_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    
    VkWriteDescriptorSet background_sampler_write = {};
    background_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    background_sampler_write.pNext            = NULL;
    background_sampler_write.dstSet           = background_rs.dset;
    background_sampler_write.dstBinding       = 1;
    background_sampler_write.dstArrayElement  = 0;
    background_sampler_write.descriptorCount  = 1;
    background_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    background_sampler_write.pImageInfo       = &background_sampler_image_info;
    background_sampler_write.pBufferInfo      = NULL;
    background_sampler_write.pTexelBufferView = NULL;
    
    
    VkDescriptorImageInfo player_sampler_image_info = {};
    player_sampler_image_info.sampler     = player_rs.texture_data.sampler;
    player_sampler_image_info.imageView   = player_rs.texture_data.imageview;
    player_sampler_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    
    VkWriteDescriptorSet player_sampler_write = {};
    player_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    player_sampler_write.pNext            = NULL;
    player_sampler_write.dstSet           = player_rs.dset;
    player_sampler_write.dstBinding       = 1;
    player_sampler_write.dstArrayElement  = 0;
    player_sampler_write.descriptorCount  = 1;
    player_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    player_sampler_write.pImageInfo       = &player_sampler_image_info;
    player_sampler_write.pBufferInfo      = NULL;
    player_sampler_write.pTexelBufferView = NULL;
    
    
    VkDescriptorImageInfo level_sampler_image_info = {};
    level_sampler_image_info.sampler     = level_rs.texture_data.sampler;
    level_sampler_image_info.imageView   = level_rs.texture_data.imageview;
    level_sampler_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    
    VkWriteDescriptorSet level_sampler_write = {};
    level_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    level_sampler_write.pNext            = NULL;
    level_sampler_write.dstSet           = level_rs.dset;
    level_sampler_write.dstBinding       = 1;
    level_sampler_write.dstArrayElement  = 0;
    level_sampler_write.descriptorCount  = 1;
    level_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    level_sampler_write.pImageInfo       = &level_sampler_image_info;
    level_sampler_write.pBufferInfo      = NULL;
    level_sampler_write.pTexelBufferView = NULL;
    
    
    VkDescriptorImageInfo overlay_sampler_image_info = {};
    overlay_sampler_image_info.sampler     = overlay_rs.fd->atlas_data.sampler;
    overlay_sampler_image_info.imageView   = overlay_rs.fd->atlas_data.imageview;
    overlay_sampler_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    
    VkWriteDescriptorSet overlay_sampler_write = {};
    overlay_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    overlay_sampler_write.pNext            = NULL;
    overlay_sampler_write.dstSet           = overlay_rs.dset;
    overlay_sampler_write.dstBinding       = overlay_rs.fd->atlas_data.sampler_binding;
    overlay_sampler_write.dstArrayElement  = 0;
    overlay_sampler_write.descriptorCount  = overlay_rs.descset_count;
    overlay_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    overlay_sampler_write.pImageInfo       = &overlay_sampler_image_info;
    overlay_sampler_write.pBufferInfo      = NULL;
    overlay_sampler_write.pTexelBufferView = NULL;
    
    
    // obstacle heights for uv-mapping
    VkDescriptorBufferInfo level_heights_buffer_info = {};
    level_heights_buffer_info.buffer = data.obstacle_heightsbuf;
    level_heights_buffer_info.offset = 0;
    level_heights_buffer_info.range  = VK_WHOLE_SIZE;
    
    VkWriteDescriptorSet level_heights_write = {};
    level_heights_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    level_heights_write.pNext            = NULL;
    level_heights_write.dstSet           = level_rs.dset;
    level_heights_write.dstBinding       = 2;
    level_heights_write.dstArrayElement  = 0;
    level_heights_write.descriptorCount  = level_rs.descset_count;
    level_heights_write.descriptorType   = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    level_heights_write.pImageInfo       = NULL;
    level_heights_write.pBufferInfo      = &level_heights_buffer_info;
    level_heights_write.pTexelBufferView = NULL;
    
    // ---
    
    VkWriteDescriptorSet desc_writes[] = { background_matrix_write, player_matrix_write, level_matrix_write, overlay_matrix_write,
        background_sampler_write, player_sampler_write, level_sampler_write, overlay_sampler_write,
        level_heights_write };
    
    vkUpdateDescriptorSets(vk.device, 9, desc_writes, 0, NULL);
    // ---
    
    
    // --- Record render commands ---
    // ---
    VkDeviceSize offset = 0;
    
    vkBeginCommandBuffer(vk.command_buffer, &vk.cb_bi);
    
    // background
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &background_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, background_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, background_rs.pipeline);
    vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, background_rs.pipeline_layout, 0, background_rs.descset_count, &background_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &background_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDrawIndexed(vk.command_buffer, background_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    // player
    vkCmdPushConstants(vk.command_buffer, player_rs.pipeline_layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(u32), &fish_offset);
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &player_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, player_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, player_rs.pipeline);
    vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, player_rs.pipeline_layout, 0, player_rs.descset_count, &player_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &player_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDrawIndexed(vk.command_buffer, player_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    // obstacles
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &level_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, level_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, level_rs.pipeline);
    vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, level_rs.pipeline_layout, 0, level_rs.descset_count, &level_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &level_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDrawIndexed(vk.command_buffer, level_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    // overlay
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &overlay_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, overlay_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, overlay_rs.pipeline);
    vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, overlay_rs.pipeline_layout, 0, overlay_rs.descset_count, &overlay_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &overlay_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDrawIndexed(vk.command_buffer, overlay_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    vkEndCommandBuffer(vk.command_buffer);
    // ---
    
    
    // --- Render ---
    // ---
    VkFence fence_render_complete;
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &fence_render_complete);
    
    VkPipelineStageFlags wait_stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo render_queue_si = {};
    render_queue_si.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    render_queue_si.pNext                = NULL;
    render_queue_si.waitSemaphoreCount   = 0;
    render_queue_si.pWaitSemaphores      = NULL;
    render_queue_si.pWaitDstStageMask    = &wait_stage_mask;
    render_queue_si.commandBufferCount   = 1;
    render_queue_si.pCommandBuffers      = &vk.command_buffer;
    render_queue_si.signalSemaphoreCount = 1;
    render_queue_si.pSignalSemaphores    = &data.semaphore_execution_complete;
    vkQueueSubmit(vk.queue, 1, &render_queue_si, fence_render_complete);
    
    vkWaitForFences(vk.device, 1, &fence_render_complete, VK_TRUE, UINT64_MAX);
    vkDestroyFence(vk.device, fence_render_complete, NULL);
    // ---
}

void Present()
{
    VkResult present_result;
    VkPresentInfoKHR queue_pi = {};
    queue_pi.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    queue_pi.pNext              = NULL;
    queue_pi.waitSemaphoreCount = 1;
    queue_pi.pWaitSemaphores    = &data.semaphore_execution_complete;
    queue_pi.swapchainCount     = 1;
    queue_pi.pSwapchains        = &vk.swapchain;
    queue_pi.pImageIndices      = &data.acquired_index;
    queue_pi.pResults           = &present_result;
    vkQueuePresentKHR(vk.queue, &queue_pi);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                       MAIN CONTROLS ------ ------
// //////////////////////////////////////////////////////////////////////////////