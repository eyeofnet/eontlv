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

#define UUID1           "12345678-1234-1234-1234-123456789abc"
#define UUID2           "87654321-4321-4321-4321-cba987654321"
#define UUID3           "55555555-5555-5555-5555-555555555555"
#define UUID4           "50505050-5050-5050-5050-505050505050"
#define UUID5           "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa"
#define UUID6           "0a0a0a0a-0a0a-0a0a-0a0a-0a0a0a0a0a0a"
#define UUID7           "283249d7-cc79-42a9-bae9-bfff248fe31a"
#define UUID8           "669b1776-c7ea-465f-b1be-a362211088f1"
#define UUID9           "60d219ba-b214-4913-b3c9-542bd83c863c"

#define STR_LEN         36

int test_uuid(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int line_number_idx = 0;
    char str[STR_LEN];
    tlv_t *tlv;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }
    test_node_set_name(rec,__func__);

    tlv = create_tlv();
    if (tlv) {
        // UUID1
        tlv_insert_uuid_string(tlv,UUID1,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID1,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID2
        tlv_insert_uuid_string(tlv,UUID2,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID2,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID3
        tlv_insert_uuid_string(tlv,UUID3,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID3,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID4
        tlv_insert_uuid_string(tlv,UUID4,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID4,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID5
        tlv_insert_uuid_string(tlv,UUID5,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID5,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID6
        tlv_insert_uuid_string(tlv,UUID6,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID6,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID7
        tlv_insert_uuid_string(tlv,UUID7,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID7,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID8
        tlv_insert_uuid_string(tlv,UUID8,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
        if (0 == strcmp(UUID8,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // UUID9
        tlv_insert_uuid_string(tlv,UUID9,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_uuid_string(tlv,str,STR_LEN,&err);
        line = __LINE__ + 1;
        if (0 == strcmp(UUID9,str)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }


        destroy_tlv(tlv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}


