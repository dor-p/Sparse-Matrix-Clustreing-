#ifndef GROUP_FUNCTIONS_H
#define GROUP_FUNCTIONS_H

#include "matrix.h"
#include "group.h"

/* creates an empty group set with the given capacity */
GroupSet group_set_allocate_capacity(int capacity);

/* creates a group set with capacity vertexCount and one group containing the vertex indices from 0 to vertexCount-1 */
GroupSet group_set_create(int vertexCount);

/* creates an empty group with the given capacity */
Group group_allocate_capacity(int capacity);

/* creates a group with capacity vertexCount containing the vertex indices from 0 to vertexCount-1 */
Group group_create(int vertexCount);

/* deletes all groups from the group set and frees all associated memory */
void group_set_free(GroupSet* groupSet);

/* deletes all vertices from the group and frees all associated memory */
void group_free(Group* group);

/* removes the last group from this group set and returns a pointer to it */
Group group_set_remove_group(GroupSet* groupSet);

/* adds the given group to the group set */
void group_set_add_group(GroupSet* groupSet, Group* group);

/* divide g into g1 and g2, mat is a modularity matrix */
int group_divide(SparseMatrix mat, Group g, Group* g1, Group* g2);

/* print given group */
void group_print(Group group);

/* print given group set */
void group_set_print(GroupSet groupSet);

/* writes given group set to a file */
int group_set_write(GroupSet groupSet, const char* filename);

#endif