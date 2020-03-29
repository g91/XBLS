#pragma once

typedef unsigned __int64 QWORD;
namespace xbox {
	namespace Hvx
	{
		// syscalls
		QWORD HvExpansionInstall(DWORD PhysicalAddress, DWORD CodeSize);
		QWORD HvExpansionCall(DWORD ExpansionId, QWORD Param1, QWORD Param2, QWORD Param3, QWORD Param4);
		//QWORD HvKeysExecute(PVOID pvPayload, DWORD cbPayload, QWORD arg1 = NULL, QWORD arg2 = NULL, QWORD arg3 = NULL, QWORD arg4 = NULL);

		// the peek/poke expansion
		typedef enum _PEEK_POKE_TYPE {
			PEEK_BYTE = 0,
			PEEK_WORD = 1,
			PEEK_DWORD = 2,
			PEEK_QWORD = 3,
			PEEK_BYTES = 4,
			POKE_BYTE = 5,
			POKE_WORD = 6,
			POKE_DWORD = 7,
			POKE_QWORD = 8,
			POKE_BYTES = 9,
		} PEEK_POKE_TYPE;

		extern DWORD HvPeekPokeExpID;
		HRESULT InitializeHvPeekPoke(); // init the expansion

		// reading with the expansion
		BYTE    HvPeekBYTE(QWORD Address);
		WORD    HvPeekWORD(QWORD Address);
		DWORD   HvPeekDWORD(QWORD Address);
		QWORD   HvPeekQWORD(QWORD Address);
		HRESULT HvPeekBytes(QWORD Address, PVOID Buffer, DWORD Size);

		// writing with the expansion
		HRESULT HvPokeBYTE(QWORD Address, BYTE Value);
		HRESULT HvPokeWORD(QWORD Address, WORD Value);
		HRESULT HvPokeDWORD(QWORD Address, DWORD Value);
		HRESULT HvPokeQWORD(QWORD Address, QWORD Value);
		HRESULT HvPokeBytes(QWORD Address, PVOID Buffer, DWORD Size);
	}
}