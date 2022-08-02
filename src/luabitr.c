#include <stdbool.h>
#include <string.h> /* memset() */

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "bitr.h"

#define LUABITR_MT "luabitr_mt__"



/* defined in bitr.c */
extern size_t get_required_bitr_size(uint32_t num_bits);

/*
 * Return bit array userdata big enough to hold n bits.
 *
 * --> n @lua
 *     How many bits the bit array should be able to store.
 *
 * --> all_ones @lua @optional
 *     If true, initialize the bit array with all bits set rather
 *     than unset.
 */
int luabitr_new(lua_State *L){
    lua_settop(L, 2);
    LUA_INTEGER num_bits = 0;
    int rc = 0;

    luaL_checktype(L, 1, LUA_TNUMBER);
    num_bits = lua_tointegerx(L, 1, &rc);
    if (!rc){
        luaL_error(L, "invalid first argument, failed to convert to integer\n");
    }

    bool all_ones = false;
    if (lua_type(L, 2) != LUA_TNIL){
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        all_ones = lua_toboolean(L, 2);
    }

    size_t sz = get_required_bitr_size(num_bits);
    struct bitr *array = lua_newuserdata(L, sz);
    memset(array, 0, sizeof(struct bitr));
    array->size = sz- sizeof(array->size); /* only size of the array proper */

    if (all_ones){
        for (uint32_t i = 0; i < array->size; ++i){
            array->bits[i] = 0xFFu;
        }
    }

    luaL_setmetatable(L, LUABITR_MT);

    return 1;
}

int luabitr_set(lua_State *L){
    lua_settop(L, 2);
    luaL_checkudata(L, 1, LUABITR_MT);
    luaL_checktype(L, 2, LUA_TNUMBER);

    int rc = 0;
    uint32_t bitidx = lua_tointegerx(L, 2, &rc);
    if (!rc){
        luaL_error(L, "invalid argument 2 -- must be an integer");
    }

    struct bitr *bitr = lua_touserdata(L, 1);
    if (Bitr_set(bitr, bitidx) == -1){
        luaL_error(L, "Bitr: out of bounds\n");
    }

    return 0;
}

int luabitr_test(lua_State *L){
    lua_settop(L, 2);
    luaL_checkudata(L, 1, LUABITR_MT);
    luaL_checktype(L, 2, LUA_TNUMBER);

    int rc = 0;
    uint32_t bitidx = lua_tointegerx(L, 2, &rc);
    if (!rc){
        luaL_error(L, "invalid argument 2 -- must be an integer");
    }

    struct bitr *bitr = lua_touserdata(L, 1);
    int state = 0;
    if ((state = Bitr_test(bitr, bitidx)) == -1){
        luaL_error(L, "Bitr: out of bounds\n");
    }

    lua_pushboolean(L, state ? true: false);

    return 1;
}

int luabitr_clear(lua_State *L){
    lua_settop(L, 2);
    luaL_checkudata(L, 1, LUABITR_MT);
    luaL_checktype(L, 2, LUA_TNUMBER);

    int rc = 0;
    uint32_t bitidx = lua_tointegerx(L, 2, &rc);
    if (!rc){
        luaL_error(L, "invalid argument 2 -- must be an integer");
    }

    struct bitr *bitr = lua_touserdata(L, 1);
    if (Bitr_clear(bitr, bitidx) == -1){
        luaL_error(L, "Bitr: out of bounds\n");
    }

    return 0;
}

int luabitr_toggle(lua_State *L){
    lua_settop(L, 2);
    luaL_checkudata(L, 1, LUABITR_MT);
    luaL_checktype(L, 2, LUA_TNUMBER);

    int rc = 0;
    uint32_t bitidx = lua_tointegerx(L, 2, &rc);
    if (!rc){
        luaL_error(L, "invalid argument 2 -- must be an integer");
    }

    struct bitr *bitr = lua_touserdata(L, 1);
    if (Bitr_toggle(bitr, bitidx) == -1){
        luaL_error(L, "Bitr: out of bounds\n");
    }

    return 0;
}


/* Module functions */
const struct luaL_Reg luabitr_funcs[] = {
    {"new", luabitr_new},
    {NULL, NULL}
};

/* Module metamethods */
const struct luaL_Reg metamethods[] = {
    {"set", luabitr_set},
    {"test", luabitr_test},
    {"clear", luabitr_clear},
    {"toggle", luabitr_toggle},
    {NULL, NULL}
};

/* Open/initialize module */
int luaopen_luabitr(lua_State *L){

    /* add common metatable; point its __index metamethod to itself */
    if (!luaL_newmetatable(L, LUABITR_MT)){
        fprintf(stderr, "Could not initialize luabitr C library: luaL_newmetatable returned 1\n");
    }
    lua_pushvalue(L,-1);
    lua_setfield(L,-2, "__index");            
    luaL_setfuncs(L, metamethods, 0); 

    luaL_newlib(L, luabitr_funcs);
    return 1;
}


