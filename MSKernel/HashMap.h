#include <ntifs.h>

#ifndef HASHMAP_H
#define HASHMAP_H

#define HASH_SIZE 0x1000

struct KeyValuePair
{
	void* Key;
	void* Value;
	struct KeyValuePair* Next;
};

struct HashMap
{
	struct KeyValuePair* Table[HASH_SIZE];
};

NTSTATUS HashMap_Insert(struct HashMap* hashTable, void* key, void* value);
NTSTATUS HashMap_Get(struct HashMap* hashTable, void* key, void** value);
NTSTATUS HashMap_Erase(struct HashMap* hashTable, void* key);
VOID HashMap_Clear(struct HashMap* hashTable);

#endif
