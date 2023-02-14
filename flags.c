#include "eontlv.h"



int tlv_should_free_value(tlv_t *tlv)
{
    int rv = 0;
    if (tlv) {
        uint32_t flags;
        flags = (tlv->id & 0xff000000) >> 24;
        rv = (flags &  FLAG_FREE_VALUE);
    }
    return rv;
}

int tlv_should_free_as_list(tlv_t *tlv)
{
    int rv = 0;
    if (tlv) {
        uint32_t flags;
        flags = (tlv->id & 0xff000000) >> 24;
        rv = (flags &  FLAG_FREE_AS_LIST);
    }
    return rv;
}

int tlv_set_free_value_flag(tlv_t *tlv,uint32_t v)
{
    int rv = 0;
    if (tlv) {
        uint32_t flags = (tlv->id & 0xff000000) >> 24;
        if (v) {
            flags |= FLAG_FREE_VALUE;
        } else {
            flags &= ~FLAG_FREE_VALUE;
        }
        tlv->id |= ((uint32_t) flags) << 24;
    }
    return rv;
}

int tlv_set_free_as_list_flags(tlv_t *tlv,uint32_t v)
{
    int rv = 0;
    if (tlv) {
        uint32_t flags = (tlv->id & 0xff000000) >> 24;
        if (v) {
            flags |= FLAG_FREE_AS_LIST;
        } else {
            flags &= ~FLAG_FREE_AS_LIST;
        }
        tlv->id |= ((uint32_t) flags) << 24;
    }
    return rv;
}

