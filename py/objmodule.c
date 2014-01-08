#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "nlr.h"
#include "misc.h"
#include "mpconfig.h"
#include "mpqstr.h"
#include "obj.h"
#include "runtime.h"
#include "map.h"

typedef struct _mp_obj_module_t {
    mp_obj_base_t base;
    qstr name;
    mp_map_t *globals;
} mp_obj_module_t;

void module_print(void (*print)(void *env, const char *fmt, ...), void *env, mp_obj_t self_in) {
    mp_obj_module_t *self = self_in;
    print(env, "<module '%s' from '-unknown-file-'>", qstr_str(self->name));
}

const mp_obj_type_t module_type = {
    { &mp_const_type },
    "module",
    .print = module_print,
};

mp_obj_t mp_obj_new_module(qstr module_name) {
    mp_obj_module_t *o = m_new_obj(mp_obj_module_t);
    o->base.type = &module_type;
    o->name = module_name;
    o->globals = mp_map_new(1);
    mp_map_lookup(o->globals, MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_MAP_LOOKUP_ADD_IF_NOT_FOUND)->value = mp_obj_new_str(module_name);
    return o;
}

mp_map_t *mp_obj_module_get_globals(mp_obj_t self_in) {
    assert(MP_OBJ_IS_TYPE(self_in, &module_type));
    mp_obj_module_t *self = self_in;
    return self->globals;
}
