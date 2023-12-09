#include "HashMap.h"

#define MEM_TAG_UTIL 'HASH'

ULONGLONG Hash(VOID* key)
{
	return (ULONGLONG)key % HASH_SIZE;
}

struct KeyValuePair* CreateKeyValuePair(void* key, void* value)
{
	struct KeyValuePair* newPair = ExAllocatePoolWithTag(NonPagedPool, sizeof(struct KeyValuePair), MEM_TAG_UTIL);

	if (newPair != NULL)
	{
		newPair->Key = key;
		newPair->Value = value;
		newPair->Next = NULL;
	}
	return newPair;
}

NTSTATUS HashMap_Insert(struct HashMap* hashTable, void* key, void* value)
{
	ULONGLONG index = Hash(key);

	struct KeyValuePair* keyPair = CreateKeyValuePair(key, value);
	if (keyPair == NULL)
		return STATUS_INSUFFICIENT_RESOURCES;

	if (hashTable->Table[index] == NULL)
	{
		hashTable->Table[index] = keyPair;
	}
	else
	{
		struct KeyValuePair* currentPairNode = hashTable->Table[index];

		while (currentPairNode->Next != NULL)
			currentPairNode = currentPairNode->Next;

		currentPairNode->Next = keyPair;
	}

	return STATUS_SUCCESS;
}

NTSTATUS HashMap_Get(struct HashMap* hashTable, void* key, void** value)
{
	ULONGLONG index = Hash(key);

	struct KeyValuePair* keyPair = hashTable->Table[index];
	while (keyPair != NULL)
	{
		if (keyPair->Key == key)
		{
			*value = keyPair->Value;
			return STATUS_SUCCESS;
		}
		keyPair = keyPair->Next;
	}

	return STATUS_NOT_FOUND;
}

NTSTATUS HashMap_Erase(struct HashMap* hashTable, void* key)
{
	ULONGLONG index = Hash(key);

	struct KeyValuePair* current = hashTable->Table[index];
	struct KeyValuePair* previous = NULL;

	while (current != NULL)
	{
		if (current->Key == key)
		{
			if (previous == NULL)
				hashTable->Table[index] = current->Next;
			else
				previous->Next = current->Next;

			ExFreePoolWithTag(current, MEM_TAG_UTIL);
			return STATUS_SUCCESS;
		}

		previous = current;
		current = current->Next;
	}

	return STATUS_NOT_FOUND;
}

VOID HashMap_Clear(struct HashMap* hashTable)
{
	for (int i = 0; i < HASH_SIZE; ++i) 
	{
		struct KeyValuePair* current = hashTable->Table[i];

		while (current != NULL) 
		{
			struct KeyValuePair* temp = current;
			current = current->Next;
			ExFreePoolWithTag(temp, MEM_TAG_UTIL);
		}
		hashTable->Table[i] = NULL;
	}
}