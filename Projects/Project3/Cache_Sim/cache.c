// Driver for cache hit/miss simulation
// Sam Disharoon & Brock Forsythe
// 
// NOTES
// =============================
// Three types of single-core cache misses:
//
// 1 ~> First-time referencing data
// is always a cache miss,
// this is called COMPULSORY CACHE MISS
//
// 2 ~> If data is overwritten because 
// cache wasn't large enough, 
// this is called CAPACITY CACHE MISS
//
// 3 ~> If one data item is mapped 
// to the same cache location as another item,
// this is called CONFLICT CACHE MISS
// ====================================
// Mult-core cache misses:
//
// Same as the three above, as well as 
// if an item is invalid due to another core
// changing its value,
// this is called INVALIDATION CACHE MISS
// ************************************
// TYPICAL MEMORY HEIRARCHY
// ===========================
// the lower the cache level, 
// the harder it is to transfer data to procs
//
// LAYOUT and AVERAGE SIZE/LATENCY in time cycles
//
// Registers	~> 192 bytes	
// L1 cache	~> 32 KB	4
// L2 cache	~> 256 KB	12
// L3 cache	~> 2 MB		26
// Main Memory	~> 2 GB		230-360
// ************************************
// TWO DIFFERENT REPLACEMENT ALGS
// =================================
// 1 ~> Least-Recently Used (LRU)
// Overwrites data that is used least recently
// 
// 2 ~> First in First out (FIFO)
// Overwrites data that came in first
// ************************************
// PEAK-PERFORMANCE 
// ================================
// The quickest time for a proc to compute an equation
// this is timed by OPERATIONS/SECOND
#include<stdio.h>
int main(int argc, char** argv){

return 0;
}
