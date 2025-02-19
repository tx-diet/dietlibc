#ifndef	_ENDIAN_H
#define	_ENDIAN_H

#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321

#ifdef __mips__
#if _MIPS_SIM == _ABI64
#define __mips64__
#else
#undef __mips64__
#endif
#endif

#if defined(__i386__) || defined(__x86_64__) || defined(__ia64__) || defined(__alpha__) || defined(__aarch64__)
#define __BYTE_ORDER		__LITTLE_ENDIAN
#define __FLOAT_WORD_ORDER	__BYTE_ORDER
#endif

#if (defined(__mips__) && !defined(__MIPSEB)) || (defined(__arm__) && !defined(__ARMEB__)) || ((defined(__powerpc__) || defined(__sparc__)) && defined(__LITTLE_ENDIAN__))
#define __BYTE_ORDER		__LITTLE_ENDIAN
#define __FLOAT_WORD_ORDER	__BYTE_ORDER
#endif

/* rest is big endian */

#ifndef __BYTE_ORDER
#define __BYTE_ORDER		__BIG_ENDIAN
#define __FLOAT_WORD_ORDER	__BYTE_ORDER
#endif

#define LITTLE_ENDIAN		__LITTLE_ENDIAN
#define BIG_ENDIAN		__BIG_ENDIAN
#define BYTE_ORDER		__BYTE_ORDER

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define __LONG_LONG_PAIR(HI, LO) LO, HI
#elif __BYTE_ORDER == __BIG_ENDIAN
# define __LONG_LONG_PAIR(HI, LO) HI, LO
#endif

#if defined(__alpha__) || defined(__mips64__) || defined(__sparcv9) || defined(__ia64__) || defined(__powerpc64__) || defined(__s390x__) || defined(__aarch64__)
#define __WORDSIZE 64
#endif

#if defined(__x86_64__)
#if defined(__ILP32__)
#define __OFF_T_MATCHES_OFF64_T
#else
#define __WORDSIZE 64
#endif
#endif

#if defined(__x86_64__) || defined(__powerpc64__) || defined(__sparcv9) || defined(__aarch64__)
#define __WORDSIZE_COMPAT32 1
#endif

#if defined(__sparc__) && (__arch64__)
#define __WORDSIZE 64
#define __WORDSIZE_COMPAT32 1
#endif

#ifdef __WORDSIZE
#define __OFF_T_MATCHES_OFF64_T
#else
#define __WORDSIZE 32
#endif

#if defined(__x86_64__) || defined(__i386__)
#define __UNALIGNED_MEMORY_ACCESS_OK 1
#endif

#ifndef __ASSEMBLER__

#include <stdint.h>

#if __BYTE_ORDER == BIG_ENDIAN

static inline uint16_t htobe16(uint16_t host_16bits) { return host_16bits; }
static inline uint16_t htole16(uint16_t host_16bits) { return (host_16bits << 8) | (host_16bits >> 8); }
static inline uint16_t be16toh(uint16_t big_endian_16bits) { return big_endian_16bits; }
static inline uint16_t le16toh(uint16_t little_endian_16bits) { return (little_endian_16bits << 8) | (little_endian_16bits >> 8); }

static inline uint32_t htobe32(uint32_t host_32bits) { return host_32bits; }
static inline uint32_t htole32(uint32_t host_32bits) { return __builtin_bswap32(host_32bits); }
static inline uint32_t be32toh(uint32_t big_endian_32bits) { return big_endian_32bits; }
static inline uint32_t le32toh(uint32_t little_endian_32bits) { return __builtin_bswap32(little_endian_32bits); }

static inline uint64_t htobe64(uint64_t host_64bits) { return host_64bits; }
static inline uint64_t htole64(uint64_t host_64bits) { return __builtin_bswap64(host_64bits); }
static inline uint64_t be64toh(uint64_t big_endian_64bits) { return big_endian_64bits; }
static inline uint64_t le64toh(uint64_t little_endian_64bits) { return __builtin_bswap64(little_endian_64bits); }

#else

static inline uint16_t htobe16(uint16_t host_16bits) { return (host_16bits << 8) | (host_16bits >> 8); }
static inline uint16_t htole16(uint16_t host_16bits) { return host_16bits; }
static inline uint16_t be16toh(uint16_t big_endian_16bits) { return (big_endian_16bits << 8) | (big_endian_16bits >> 8); }
static inline uint16_t le16toh(uint16_t little_endian_16bits) { return little_endian_16bits; }

static inline uint32_t htobe32(uint32_t host_32bits) { return __builtin_bswap32(host_32bits); }
static inline uint32_t htole32(uint32_t host_32bits) { return host_32bits; }
static inline uint32_t be32toh(uint32_t big_endian_32bits) { return __builtin_bswap32(big_endian_32bits); }
static inline uint32_t le32toh(uint32_t little_endian_32bits) { return little_endian_32bits; }

static inline uint64_t htobe64(uint64_t host_64bits) { return __builtin_bswap64(host_64bits); }
static inline uint64_t htole64(uint64_t host_64bits) { return host_64bits; }
static inline uint64_t be64toh(uint64_t big_endian_64bits) { return __builtin_bswap64(big_endian_64bits); }
static inline uint64_t le64toh(uint64_t little_endian_64bits) { return little_endian_64bits; }

#endif

#endif

#endif
