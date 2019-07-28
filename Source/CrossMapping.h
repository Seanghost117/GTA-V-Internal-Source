#ifndef __CROSS_MAPPING_H__
#define __CROSS_MAPPING_H__

#pragma once

typedef std::unordered_map<uint64_t, uint64_t> nMap;
static std::vector<uint64_t> nativeFailedVec;

struct CrossMappingEntry
{
	uint64_t first;
	uint64_t second;
};

class CrossMapping
{
public:
	static void initNativeMap();
	static uint64_t MapNative(uint64_t inNative);
	static void dumpNativeMappingCache();
	static bool searchMap(nMap map, uint64_t inNative, uint64_t *outNative);
};

#endif // __CROSS_MAPPING_H__


