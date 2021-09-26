#pragma once
#include "stdafx.h"
#include <Windows.h>


std::string GetById(int id);
class UObject;

class FUObjectItem
{
public:
	UObject* Object;
	int32_t Flags;
	int32_t ClusterIndex;
	int32_t SerialNumber;
	char padding[0x4];

	enum class ObjectFlags : int32_t
	{
		None = 0,
		Native = 1 << 25,
		Async = 1 << 26,
		AsyncLoading = 1 << 27,
		Unreachable = 1 << 28,
		PendingKill = 1 << 29,
		RootSet = 1 << 30,
		NoStrongReference = 1 << 31
	};

	inline bool IsUnreachable() const
	{
		return !!(Flags & static_cast<std::underlying_type_t<ObjectFlags>>(ObjectFlags::Unreachable));
	}
	inline bool IsPendingKill() const
	{
		return !!(Flags & static_cast<std::underlying_type_t<ObjectFlags>>(ObjectFlags::PendingKill));
	}
};

class PreFUObjectItem
{
public:
	FUObjectItem* FUObject[10];
};

class TUObjectArray
{
public:
	inline void NumChunks(int* start, int* end) const
	{
		int cStart = 0, cEnd = 0;

		if (!cEnd)
		{
			//find where chunks start
			while (1)
			{
				if (Objects->FUObject[cStart] == 0)
				{
					cStart++;
				}
				else
				{
					break;
				}
			}

			cEnd = cStart;
			//find where chunks end
			while (1)
			{
				if (Objects->FUObject[cEnd] == 0)
				{
					break;
				}
				else
				{
					cEnd++;
				}
			}
		}

		*start = cStart;
		*end = cEnd;
	}

	inline UObject* GetByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		FUObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		//this is so it stays in the previous chunk when the sizes are the same
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
			Object = Objects->FUObject[chunkPos] + (index - chunkSize * chunkIndex);
			if (!Object) { return NULL; }

			return Object->Object;
		}

		return nullptr;
	}

	inline FUObjectItem* GetItemByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		FUObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		//this is so it stays in the previous chunk when the sizes are the same
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
			Object = Objects->FUObject[chunkPos] + (index - chunkSize * chunkIndex);
			if (!Object) { return NULL; }

			return Object;
		}

		return nullptr;
	}

	inline int32_t Num() const
	{
		return NumElements;
	}

private:
	PreFUObjectItem* Objects;
	char padding[8];
	int32_t MaxElements;
	int32_t NumElements;
};

class FUObjectArray
{
public:
	//int32_t ObjFirstGCIndex;
	//int32_t ObjLastNonGCIndex;
	//int32_t MaxObjectsNotConsideredByGC;
	//int32_t OpenForDisregardForGC;
	TUObjectArray ObjObjects;
};

