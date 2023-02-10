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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eontlv.h"
#include "test_eontlv.h"

int g_verbose = 0;
test_node_t *g_tests = NULL;

test_node_t *add_test_node()
{
    test_node_t *rv = create_test_node();
    if (rv) {
        if (g_tests) {
            test_node_t *ptr = g_tests;
            while(ptr->next) {
                ptr = ptr->next;
            }
            ptr->next = rv;
        } else {
            g_tests = rv;
        }
    }
    return rv;
}

void print_test_node(test_node_t *v)
{
    int i;
    if (v) {
        if (v->name) {
            printf("%s\n",v->name);
        }
        printf("\tpassed: %u\n",v->passed_test_count);
        printf("\tfailed: %u\n",v->failed_test_count);
        printf("\tskipped: %u\n",v->skipped_test_count);
        if (v->failed_test_count > 0) {
            printf("\tFailures on lines:\n");
            for (i=0;i<MAX_REPORTED_TEST_LINES;i++) {
                if (v->failed_test_lines[i] > 0) {
                    printf("\t\t%d\n",v->failed_test_lines[i]);
                }
            }
        }
        printf("-----------------\n");
    }
}

/*
 * Returns a newly allocated test node that contains total results
 */
test_node_t *print_test_results(void)
{
    test_node_t *rv;
    test_node_t *ptr;

    rv = create_test_node(); 
    if (rv) {
        test_node_set_name(rv,"TOTALS");
        ptr = g_tests;
        while (ptr) {
            rv->passed_test_count += ptr->passed_test_count;
            rv->failed_test_count += ptr->failed_test_count;
            rv->skipped_test_count += ptr->skipped_test_count;
            print_test_node(ptr);
            ptr = ptr->next;
        }
    }
    return rv;
}

void destroy_test_list(void)
{
    test_node_t *ptr;
    test_node_t *kill;

    ptr = g_tests;
    while (ptr) {
        kill = ptr;
        ptr = ptr->next;
        destroy_test_node(kill);
    }
}

int main(int argc,char *argv[])
{
    int rv = 0;
    test_node_t *nd;

    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_int8(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_uint8(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_int16(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_uint16(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_int32(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_uint32(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_date(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_time(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_datetime(nd);
    if (rv) {
        goto out;
    }
    nd = add_test_node();
    if (!nd) {
        rv = ENOMEM;
        goto out;
    }
    rv = test_uuid(nd);
    if (rv) {
        goto out;
    }
    rv = test_cstr(nd);
    if (rv) {
        goto out;
    }


out:
    if (g_tests) {
        test_node_t *totals = print_test_results();
        printf("\n\n");
        print_test_node(totals);
        destroy_test_node(totals);
        destroy_test_list();
    }
    if (rv) {
        fprintf(stderr,"Error encountered: %s\n",strerror(rv));
    }
    return rv;
}
