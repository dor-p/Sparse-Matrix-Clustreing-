#ifndef GROUP_H
#define GROUP_H

typedef struct Group
{
	int* indices;
	int size;
	int capacity;

} Group;

typedef struct GroupSet
{
	Group* groups;
	int size;
	int capacity;

} GroupSet;

#endif

