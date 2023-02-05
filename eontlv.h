/***************************************************************************
 *  EONTLV is a C-language library that provides access to 
 *  TLV (type, length, value) structures.
 *  Copyright (C) 2023 Winslow Williams 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef _EONTLV_20230115
#define _EONTLV_20230115

#include <stdio.h>
#include <stdint.h>

#define TLV_NULL                        0x0000 /* TLV with NULL value (length = 0) */
#define TLV_DATA                        0x0001 /* Data with no specific type */
#define TLV_LIST                        0x0002 /* List of tlv objects */
#define TLV_LIST_FIRT                   0x0003 /* List of tlv objects, first in series */
#define TLV_LIST_LAST                   0x0004 /* List of tlv objects, last in series */
#define TLV_ID                          0x0005 /* TLV identifier object (two-byte big-endian integer) (applies to next data TLV in stream) */
#define TLV_ID_CSTR_NAME_TABLE          0x0006 /* Array of TLV_CSTR_STRING objects containing names indexed by a TLV_ID value */
#define TLV_ID_UTF8_NAME_TABLE          0x0007 /* Array of TLV_UTF8_STRING objects containing names indexed by a TLV_ID value */
#define TLV_ID_UTF16_NAME_TABLE         0x0008 /* Array of TLV_UTF16_STRING objects containing names indexed by a TLV_ID value */
#define TLV_ID_UTF32_NAME_TABLE         0x0009 /* Array of TLV_UTF32_STRING objects containing names indexed by a TLV_ID value */

#define TLV_INT8                        0x0010 /* Signed one-byte integer */
#define TLV_UINT8                       0x0011 /* Unsigned one-byte integer */
#define TLV_INT8_ARRAY                  0x0012 /* Array of 8-bit signed integers */
#define TLV_INT8_ARRAY_FIRST            0x0013 /* Array of 8-bit signed integers, first in a series */
#define TLV_INT8_ARRAY_LAST             0x0014 /* Array of 8-bit signed integers, last in a series */
#define TLV_UINT8_ARRAY                 0x0015 /* Array of 8-bit unsigned integers */
#define TLV_UINT8_ARRAY_FIRST           0x0016 /* Array of 8-bit unsigned integers, first in a series */
#define TLV_UINT8_ARRAY_LAST            0x0017 /* Array of 8-bit unsigned integers, last in a series */

#define TLV_INT16_BE                    0x0020 /* Signed 16-bit big-endian integer */
#define TLV_UINT16_BE                   0x0021 /* Unsigned 16-bit big-endian integer */
#define TLV_INT16_BE_ARRAY              0x0022 /* Array of 16-bit big-endian signed integers */
#define TLV_INT16_BE_ARRAY_FIRST        0x0023 /* Array of 16-bit big-endian signed integers, first in a series */
#define TLV_INT16_BE_ARRAY_LAST         0x0024 /* Array of 16-bit big-endian signed integers, last in a series */
#define TLV_UINT16_BE_ARRAY             0x0025 /* Array of 16-bit big-endian unsigned integers */
#define TLV_UINT16_BE_ARRAY_FIRST       0x0026 /* Array of 16-bit big-endian unsigned integers, first in a series */
#define TLV_UINT16_BE_ARRAY_LAST        0x0027 /* Array of 16-bit big-endian unsigned integers, last in a series */

#define TLV_INT16_LE                    0x0028 /* Signed 16-bit little-endian integer */
#define TLV_UINT16_LE                   0x0029 /* Unsigned 16-bit little-endian integer */
#define TLV_INT16_LE_ARRAY              0x002A /* Array of 16-bit little-endian signed integers */
#define TLV_INT16_LE_ARRAY_FIRST        0x002B /* Array of 16-bit little-endian signed integers, first in a series */
#define TLV_INT16_LE_ARRAY_LAST         0x002C /* Array of 16-bit little-endian signed integers, last in a series */
#define TLV_UINT16_LE_ARRAY             0x002D /* Array of 16-bit little-endian unsigned integers */
#define TLV_UINT16_LE_ARRAY_FIRST       0x002E /* Array of 16-bit little-endian unsigned integers, first in a series */
#define TLV_UINT16_LE_ARRAY_LAST        0x002F /* Array of 16-bit little-endian unsigned integers, last in a series */

#define TLV_INT32_BE                    0x0030 /* Signed 32-bit big-endian integer */
#define TLV_UINT32_BE                   0x0031 /* Unsigned 32-bit big-endian integer */
#define TLV_INT32_BE_ARRAY              0x0032 /* Array of 32-bit big-endian signed integers */
#define TLV_INT32_BE_ARRAY_FIRST        0x0033 /* Array of 32-bit big-endian signed integers, first in a series */
#define TLV_INT32_BE_ARRAY_LAST         0x0034 /* Array of 32-bit big-endian signed integers, last in a series */
#define TLV_UINT32_BE_ARRAY             0x0035 /* Array of 32-bit big-endian unsigned integers */
#define TLV_UINT32_BE_ARRAY_FIRST       0x0036 /* Array of 32-bit big-endian unsigned integers, first in a series */
#define TLV_UINT32_BE_ARRAY_LAST        0x0037 /* Array of 32-bit big-endian unsigned integers, last in a series */

#define TLV_INT32_LE                    0x0038 /* Signed 32-bit little-endian integer */
#define TLV_UINT32_LE                   0x0039 /* Unsigned 32-bit little-endian integer */
#define TLV_INT32_LE_ARRAY              0x003A /* Array of 32-bit little-endian signed integers */
#define TLV_INT32_LE_ARRAY_FIRST        0x003B /* Array of 32-bit little-endian signed integers, first in a series */
#define TLV_INT32_LE_ARRAY_LAST         0x003C /* Array of 32-bit little-endian signed integers, last in a series */
#define TLV_UINT32_LE_ARRAY             0x003D /* Array of 32-bit little-endian unsigned integers */
#define TLV_UINT32_LE_ARRAY_FIRST       0x003E /* Array of 32-bit little-endian unsigned integers, first in a series */
#define TLV_UINT32_LE_ARRAY_LAST        0x003F /* Array of 32-bit little-endian unsigned integers, last in a series */

#define TLV_CSTR_CHAR                   0x0040 /* Single ASCII character */
#define TLV_CSTR_STRING                 0x0041 /* Null-terminated c-style ASCII character string */
#define TLV_CSTR_STRING_FIRST           0x0042 /* Null-terminated c-style ASCII character string, first in a series */
#define TLV_CSTR_STRING_LAST            0x0043 /* Null-terminated c-style ASCII character string, last in a series */

#define TLV_UTF8_CHAR                   0x0044 /* Single UTF-8 character */
#define TLV_UTF8_STRING                 0x0045 /* UTF-8 character string (not terminated) */
#define TLV_UTF8_STRING_FIRST           0x0046 /* UTF-8 character string, first in a series (not terminated) */
#define TLV_UTF8_STRING_LAST            0x0047 /* UTF-8 character string, last in a series (not terminated) */

#define TLV_UTF16_CHAR                  0x0048 /* Single UTF-16 character */
#define TLV_UTF16_STRING                0x0049 /* UTF-16 character string (not terminated) */
#define TLV_UTF16_STRING_FIRST          0x004A /* UTF-16 character string, first in a series (not terminated) */
#define TLV_UTF16_STRING_LAST           0x004B /* UTF-16 character string, last in a series (not terminated) */

#define TLV_UTF32_CHAR                  0x004C /* Single UTF-32 character */
#define TLV_UTF32_STRING                0x004D /* UTF-32 character string (not terminated) */
#define TLV_UTF32_STRING_FIRST          0x004E /* UTF-32 character string, first in a series (not terminated) */
#define TLV_UTF32_STRING_LAST           0x004F /* UTF-32 character string, last in a series (not terminated) */

#define TLV_UUID                        0x0050 /* 16-byte big-endian UUID */
#define TLV_DATE                        0x0051 /* 32-bit big-endian integer containing YYYYMMDD formatted date */
#define TLV_TIME                        0x0052 /* 16-bit big-endian integer containing HMSM (hour, minute, second, millisecond) formatted time */
#define TLV_DATETIME                    0x0053 /* 32-bit big-endian integer formatted as above-described date and time */

#define TLV_APPLICATION_SPECIFIC_START  0x7000 /* Start of reserved application-specific values */ 
#define TLV_APPLICATION_SPECIFIC_END    0x7FFF /* End of reserved application-specific values */

#define TLV_ERR_BASE                    17000
#define TLV_ERR_INVALID_TYPE    TLV_ERR_BASE + 1
/* Be sure to update "LAST_ERROR" when adding new error codes */
#define TLV_ERR_LAST_ERROR      TLV_ERR_INVALID_TYPE

#define UUID_LEN                        16

typedef struct tlv
{
    uint16_t type;
    uint16_t len;
    uint8_t  *value;
    struct tlv *next;
} tlv_t;

tlv_t *create_tlv(void);
int init_tlv(tlv_t *v);
void destroy_tlv(tlv_t *tlv);
void destroy_tlv_list(tlv_t *head);

typedef struct tlv_date
{
    uint16_t year;
    uint8_t month;       // 1 = January, 2 = February etc.
    uint8_t day;         // 1 - 31
} tlv_date_t;

typedef struct tlv_time
{
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    int8_t gmt_offset;
} tlv_time_t;

typedef struct tlv_datetime
{
    tlv_date_t date;
    tlv_time_t time;
} tlv_datetime_t;

typedef struct tlv_uuid
{
    uint8_t d[UUID_LEN]; 
} tlv_uuid_t;

void tlv_alloc_value(tlv_t *tlv,uint32_t size,int *err);
void tlv_free_value(tlv_t *tlv,int *err);
uint32_t tlv_size(tlv_t *tlv);
int tlv_is_value_no_alloc(tlv_t *tlv);
void tlv_to_buffer(tlv_t *v,uint8_t *buf,uint32_t buflen,int *err);
tlv_t *tlv_from_buffer(uint8_t *buf,uint32_t buflen,int *err);
void tlv_to_FILE(tlv_t *tlv,FILE *fptr,int *err);
tlv_t *tlv_from_FILE(FILE *fptr,int *err);

void tlv_insert_int8(tlv_t *tlv,int8_t v,int *err);
int8_t tlv_extract_int8(tlv_t *tlv,int *err);
void tlv_insert_uint8(tlv_t *tlv,uint8_t v,int *err);
uint8_t tlv_extract_uint8(tlv_t *tlv,int *err);

void tlv_insert_int16(tlv_t *tlv,int16_t v,int *err);
int16_t tlv_extract_int16(tlv_t *tlv,int *err);
void tlv_insert_uint16(tlv_t *tlv,uint16_t v,int *err);
uint16_t tlv_extract_uint16(tlv_t *tlv,int *err);

void tlv_insert_int32(tlv_t *tlv,int32_t v,int *err);
int32_t tlv_extract_int32(tlv_t *tlv,int *err);
void tlv_insert_uint32(tlv_t *tlv,uint32_t v,int *err);
uint32_t tlv_extract_uint32(tlv_t *tlv,int *err);

void tlv_insert_int64(tlv_t *tlv,int64_t v,int *err);
int64_t tlv_extract_int64(tlv_t *tlv,int *err);
void tlv_insert_uint64(tlv_t *tlv,uint64_t v,int *err);
uint64_t tlv_extract_uint64(tlv_t *tlv,int *err);

void tlv_insert_date(tlv_t *tlv,tlv_date_t *d,int *err);
void tlv_extract_date(tlv_t *tlv,tlv_date_t *d,int *err);
void tlv_insert_time(tlv_t *tlv,tlv_time_t *t,int *err);
void tlv_extract_time(tlv_t *tlv,tlv_time_t *t,int *err);
void tlv_insert_datetime(tlv_t *tlv,tlv_datetime_t *dt,int *err);
void tlv_extract_datetime(tlv_t *tlv,tlv_datetime_t *dt,int *err);

void tlv_insert_uuid_string(tlv_t *tlv,const char *str,int *err);
void tlv_extract_uuid_string(tlv_t *tlv,char *str,uint32_t strlen,int *err);

int tlv_is_valid_error_code(int code);
const char *tlv_get_error_string(int code);

#endif /* _EONTLV_20230115 */




