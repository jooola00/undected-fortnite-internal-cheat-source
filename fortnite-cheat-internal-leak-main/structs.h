#pragma once
#include "stdafx.h"
#include <xlocale>

namespace UtilK
{
	class UClass {
	public:
		BYTE _padding_0[0x40];
		UClass* SuperClass;
	};

	class UObject {
	public:
		PVOID VTableObject;
		DWORD ObjectFlags;
		DWORD InternalIndex;
		UClass* Class;
		BYTE _padding_0[0x8];
		UObject* Outer;

		inline BOOLEAN IsA(PVOID parentClass) {
			for (auto super = this->Class; super; super = super->SuperClass) {
				if (super == parentClass) {
					return TRUE;
				}
			}

			return FALSE;
		}
	};

	class FUObjectItem {
	public:
		UObject* Object;
		DWORD Flags;
		DWORD ClusterIndex;
		DWORD SerialNumber;
		DWORD SerialNumber2;
	};

	class TUObjectArray {
	public:
		FUObjectItem* Objects[9];

	};

	class GObjects {
	public:
		TUObjectArray* ObjectArray;
		BYTE _padding_0[0xC];
		DWORD ObjectCount;
	};



	template<class T>
	struct TArray
	{
		friend struct FString;

	public:
		inline TArray()
		{
			Data = nullptr;
			Count = Max = 0;
		};

		inline int Num() const
		{
			return Count;
		};

		inline T& operator[](int i)
		{
			return Data[i];
		};

		inline const T& operator[](int i) const
		{
			return Data[i];
		};

		inline bool IsValidIndex(int i) const
		{
			return i < Num();
		}

	private:
		T* Data;
		int Count;
		int Max;
	};

	struct FString : private TArray<wchar_t>
	{
		inline FString()
		{
		};

		inline bool IsValid() const
		{
			return Data != nullptr;
		}

		inline const wchar_t* c_str() const
		{
			return Data;
		}

		std::string ToString() const
		{
			auto length = std::wcslen(Data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

			return str;
		}
	};

	class FText {
	private:
		char _padding_[0x28];
		PWCHAR Name;
		DWORD Length;

	public:
		inline PWCHAR c_str() {
			return Name;
		}
	};

	typedef struct {
		float X, Y, Z;
	} FVector;

	typedef struct {
		float X, Y;
	} FVector2D;

	typedef struct {
		float Pitch;
		float Yaw;
		float Roll;
	} FRotator;


	typedef struct
	{
		FVector Location;
		FRotator Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	} FMinimalViewInfo;


	typedef struct {
		float M[4][4];
	} FMatrix;

	typedef struct {
		FVector ViewOrigin;
		char _padding_0[4];
		FMatrix ViewRotationMatrix;
		FMatrix ProjectionMatrix;
	} FSceneViewProjectionData;

	typedef struct {
		FVector Origin;
		FVector BoxExtent;
		float SphereRadius;
	} FBoxSphereBounds;
}