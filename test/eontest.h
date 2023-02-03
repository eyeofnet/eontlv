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

#ifndef _EONTEST_H_20230124
#define _EONTEST_H_20230124

#include <stdint.h>

#define MAX_REPORTED_TEST_LINES     16


typedef struct test_node
{
    char *name;
    uint32_t total_test_count;
    uint32_t failed_test_count;
    uint32_t passed_test_count;
    uint32_t skipped_test_count;
    uint32_t failed_test_lines[MAX_REPORTED_TEST_LINES];
    struct test_node *next;
} test_node_t;

test_node_t *create_test_node(void);
void destroy_test_node(test_node_t *v);
void test_node_set_name(test_node_t *nd,const char *name);



#endif /* _EONTEST_H_20230124 */

