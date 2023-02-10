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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "eontlv.h"
#include "test_eontlv.h"

#define MAX_STATIC_STR_LEN    1024
#define LONG_STR_LEN          0x20000

#define STR1                  ""
#define STR2                  "a"
#define STR3                  "ab"
#define STR4                  "abc"
#define STR5                  "abcdefghijklmnopqrstuvwxyz"
#define STR6                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890987654321ZYXWVUTSRQPONMLKJIHGFEDCBA"
#define STR7                  "The quick brown fox jumped over the lazy yellow dog."
#define STR8                  "~`!@#$%^&*()_+{}|:>?-=[];'./"
#define STR9                  "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 012345678901234567890123456789012345678901234567890123456789"

int test_cstr(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int line_number_idx = 0;
    char str[MAX_STATIC_STR_LEN];
    tlv_t *tlv;
    char *long_str_base;
    char *long_str_chk;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }
    test_node_set_name(rec,__func__);

    tlv = create_tlv();
    if (tlv) {
        // STR1
        tlv_insert_cstr_string(tlv,STR1,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR1,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR2
        tlv_insert_cstr_string(tlv,STR2,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR2,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR3
        tlv_insert_cstr_string(tlv,STR3,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR3,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR4
        tlv_insert_cstr_string(tlv,STR4,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR4,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR5
        tlv_insert_cstr_string(tlv,STR5,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR5,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR6
        tlv_insert_cstr_string(tlv,STR6,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR6,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR7
        tlv_insert_cstr_string(tlv,STR7,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR7,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR8
        tlv_insert_cstr_string(tlv,STR8,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(STR8,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR9
        tlv_insert_cstr_string(tlv,STR9,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_cstr_string(tlv,str,MAX_STATIC_STR_LEN,&err);
        line = __LINE__ + 1;
        if (0 == strcmp(STR9,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

	// Long string
        long_str_base = calloc(1,LONG_STR_LEN+1);
        if (long_str_base) {
            long_str_chk = calloc(1,LONG_STR_LEN+1);
            if (long_str_chk) {
                int i;
                for (i=0;i<LONG_STR_LEN;i++) {
                    long_str_base[i] = 'a';
                }
                long_str_base[i] = '\0';
                tlv_insert_cstr_string(tlv,long_str_base,&err);
                if (err) {
                    rv = err;
                    goto out;
                }
                tlv_extract_cstr_string(tlv,long_str_chk,LONG_STR_LEN+1,&err);
                line = __LINE__ + 1;
                if (0 == strcmp(long_str_base,long_str_chk)) {
                    ++(rec->passed_test_count);
                } else {
                    ++(rec->failed_test_count);
                   if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                       rec->failed_test_lines[line_number_idx++] = line;
                   }
                }
                free(long_str_chk);
            }
            free(long_str_base);
        }

        destroy_tlv(tlv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}


