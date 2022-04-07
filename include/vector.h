#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>

#define DEFINE_ARRAY(type) typedef struct{ \
    uint8_t is_own; \
    uint32_t size; \
    type *data; \
} type##_vector_t



#endif