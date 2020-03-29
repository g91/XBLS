#include "stdafx.h"
namespace XBLAPI {

	class XKE {
	public:
		static VOID FillBuffer(PBYTE pBuffer, BOOL crl, BOOL fcrt, BOOL Type1, DWORD UpdateSequence, PBYTE SpoofedCPUKey, PBYTE ECCDigest, PBYTE Signature, PBYTE HVDigest, PBYTE kv);
	};

	class XOSC {
	public:
		static VOID FillBuffer(PBYTE pBuffer, BOOL crl, BOOL fcrt, BOOL Type1, PBYTE SpoofedCPUKey, PBYTE SecurityDigest, PBYTE FuseDigest, PBYTE kv);
	};

	class Utilities {
	public:
		static FARPROC ResolveFunction(PCHAR ModuleName, DWORD Ordinal);
	};
}