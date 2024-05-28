//
// Created by lucac on 27/05/2024.
//

#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include <stdio.h>

#define   u8 uint8_t
#define  u16 uint16_t
#define  u32 uint32_t
#define  u64 uint64_t

#define   s8 int8_t
#define  s16 int16_t
#define  s32 int32_t
#define  s64 int64_t


#define AL_ASSERT(cond,message,...) if (!(cond)) { printf(message,__VA_ARGS__); __debugbreak();}
#endif //TYPES_H
