#pragma once

#include <cstdint>

#ifdef WIN32
#define WIN32_LINUX(x, y) x
#define THISCALL __thiscall
#define STDCALL __stdcall
#define FASTCALL __fastcall
#define CDECL __cdecl
#define GETMODULEHANDLE(x) GetModuleHandleA(x)
#else
#define WIN32_LINUX(x, y) y
#define THISCALL
#define STDCALL
#define FASTCALL
#define CDECL
#define GETMODULEHANDLE(x) x
#endif

#define CLIENT_DLL WIN32_LINUX("client.dll", "csgo/bin/linux64/client_client.so")
#define ENGINE_DLL WIN32_LINUX("engine.dll", "engine_client.so")
#define PANORAMA_DLL WIN32_LINUX("panorama.dll", "panorama_gl_client.so")

namespace tsf
{
    template <typename T>
        struct utl_vector_t
    {
        T *mem;
        int alloc_count;
        int grow_size;
        int size;
        T *els;
    };
    
    struct ui_panel_t
    {
        const char *get_id()
        {
            return ((const char *(THISCALL *)(ui_panel_t *))((*(uintptr_t **)(this))[9]))(this);
        }
        
        ui_panel_t* get_parent()
        {
            return ((ui_panel_t *(THISCALL *)(ui_panel_t *))((*(uintptr_t **)(this))[25]))(this);
        }
        
        void set_visible(bool to)
        {
            return ((void(THISCALL *)(ui_panel_t *, bool))((*(uintptr_t **)(this))[27]))(this, to);
        }
        
        ui_panel_t *find_child_traverse(const char *name)
        {
            return ((ui_panel_t *(THISCALL *)(ui_panel_t *, const char *))((*(uintptr_t **)(this))[40]))(this, name);
        }
        
        void find_children_with_class_traverse(const char *class_name, utl_vector_t<ui_panel_t *> *out)
        {
            return ((void(THISCALL *)(ui_panel_t *, const char *, utl_vector_t<ui_panel_t *> *))((*(uintptr_t **)(this))[302]))(this, class_name, out);
        }
    };
    
    struct ui_engine_t 
    {
        bool is_valid_panel_pointer(ui_panel_t const *panel)
        {
            return ((bool(THISCALL *)(ui_engine_t *, ui_panel_t const *))((*(uintptr_t **)(this))[36]))(this, panel);
        }
        
        ui_panel_t *get_last_dispatched_event_target_panel()
        {
            return ((ui_panel_t *(THISCALL *)(ui_engine_t *))((*(uintptr_t **)(this))[56]))(this);
        }
        
        
        void run_script(ui_panel_t *panel, const char *js, const char *schema_path, int a5 = 8, int a6 = 10, bool a7 = false, bool a8 = false)
        {
            return ((void(THISCALL *)(ui_engine_t *, ui_panel_t *, const char *, const char *, int, int, bool, bool))((*(uintptr_t **)(this))[113]))(this, panel, js, schema_path, a5, a6, a7, a8);
        }
    };
    
    struct panorama_t
    {
        ui_engine_t *access_ui_engine() 
        {
            return ((ui_engine_t *(THISCALL *)(panorama_t *))((*(uintptr_t **)(this))[11]))(this);
        }
    };
    
    struct player_t
    {
        bool in_buyzone()
        {
            return *(bool*)((uintptr_t)this + 0x99B5);
        }
    };
    
    struct user_cmd_t 
    {
        int get_command_number() 
        {
            return *(int*)((uintptr_t)this + 0x4);
        }
        
        int get_tick_count() 
        {
            return *(int*)((uintptr_t)this + 0x8);
        }
    };
    
    struct cvar_t
    {
        float get_float() 
        {
            return ((float(THISCALL *)(cvar_t *))((*(uintptr_t **)(this))[12]))(this);
        }
        
        int get_int() 
        {
            return ((int(THISCALL *)(cvar_t *))((*(uintptr_t **)(this))[13]))(this);
        }
    };
    
    struct cvars_t
    {
        cvar_t *get_var(const char *name) 
        {
            return ((cvar_t *(THISCALL *)(cvars_t *, const char *))((*(uintptr_t **)(this))[16]))(this, name);
        }
    };
    
    struct event_t
    {
        const char *get_name() 
        {
            return ((const char *(THISCALL *)(event_t *))((*(uintptr_t **)(this))[1]))(this);
        }
        
        int get_int(const char *key, int def = 0) 
        {
            return ((int(THISCALL *)(event_t *, const char *, int))((*(uintptr_t **)(this))[6]))(this, key, def);
        }
    };
}