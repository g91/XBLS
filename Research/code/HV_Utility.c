// this file contains several security related things related to online cheating that can be abused
// removed until I can filter through it and decide what should be here and what shouldn't
// for now here's the prototypes of the functions

// 17511
// HV utility functions

// These assume they are compiled for 64bit machines, where pointers are 64 bits
// The HV handles everything in 64 bit mode

// Xbox doesn't write cachelines back unless a dcbst instruction is used
// or unless the data was being forced out of the cacheline
// This will make sure your RAM is up to date with the cache
// Used to write cachelines for a given memory range to RAM
void HvpSaveCachelines(PVOID pAddy, DWORD cAddy);

// Writes zeroed cache blocks directly to RAM without 
// loading RAM into cache, zeroing, writing back to memory
// Efficient way to zero memory blocks
// Using the dbcz128 instruction effectively is documented in the SDK
void HvpZeroCacheLines(PVOID pAddy, DWORD cAddy);

// Used to invalidate cachelines for a given address range
// Takes byte count as cAddy input, NOT CACHELINE COUNT
void HvpInvalidateCachelines(PBYTE pAddy, DWORD cbAddy);

// Relocates data in 0x80 byte blocks and invalidates the old location
void HvpRelocateCacheLines(PVOID pSrc, PVOID pDest, DWORD cBlockCount);

// Sets address flags and re-writes with the new flags, returns new address
QWORD HvpRelocatePhysicalToEncrypted(PBYTE pbBuf, DWORD cbBuf);
QWORD HvpRelocatePhysicalToProtected(PBYTE pbBuf, DWORD cbBuf, BYTE bKF);

// Get the real address of a physical address
// The HV works with memory paging disabled
QWORD HvpPhysicalToReal(PVOID pAddy, DWORD cAddy);

// Gets non-zero timebase value
QWORD HvpGetTimebase();

QWORD HvpGetFlashBaseAddress();
QWORD HvpBuildSocMMIORegs(DWORD offset) ;
QWORD HvpBuildPciConfigRegs(DWORD offset);
QWORD HvpBuildHostBridgeRegs(DWORD offset);

// work in progress...
