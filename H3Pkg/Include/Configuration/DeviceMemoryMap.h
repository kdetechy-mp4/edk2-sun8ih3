#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 128

#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES                               \
EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED |        \
EFI_RESOURCE_ATTRIBUTE_TESTED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |         \
EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |                                   \
EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |                             \
EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |                                \
EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum { NoHob, AddMem, AddDev, HobOnlyNoCacheSetting, MaxMem } DeviceMemoryAddHob;

#define MEMORY_REGION_NAME_MAX_LENGTH 32

typedef struct {
    CHAR8 Name[MEMORY_REGION_NAME_MAX_LENGTH];
    EFI_PHYSICAL_ADDRESS Address;
    UINT64 Length;
    DeviceMemoryAddHob HobOption;
    EFI_RESOURCE_TYPE ResourceType;
    EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute;
    EFI_MEMORY_TYPE MemoryType;
    ARM_MEMORY_REGION_ATTRIBUTES ArmAttributes;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

#define MEM_RES EFI_RESOURCE_MEMORY_RESERVED
#define MMAP_IO EFI_RESOURCE_MEMORY_MAPPED_IO
#define SYS_MEM EFI_RESOURCE_SYSTEM_MEMORY

#define SYS_MEM_CAP SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES
#define UNCACHEABLE EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE
#define WRITE_COMBINEABLE EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE

#define Reserv EfiReservedMemoryType
#define Conv EfiConventionalMemory
#define BsData EfiBootServicesData
#define BsCode EfiBootServicesCode
#define MmIO EfiMemoryMappedIO

#define DEVICE ARM_MEMORY_REGION_ATTRIBUTE_DEVICE
#define WRITE_BACK ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define UNCACHED_UNBUFFERED ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* MemLabel(32 Char.),        MemBase,    MemSize,    BuildHob, ResourceType, ResourceAttribute,                MemoryType, CacheAttributes */

    //--------------------- H3 Registers (MMIO) ---------------------
    {"SRAM",                    0x00000000, 0x00100000, AddDev,   MMAP_IO,      UNCACHEABLE,                      MmIO,       DEVICE},
    {"DE2 + Deinterlace",       0x01000000, 0x00500000, AddDev,   MMAP_IO,      UNCACHEABLE,                      MmIO,       DEVICE},
    {"SoC Peripherals",         0x01C00000, 0x00400000, AddDev,   MMAP_IO,      UNCACHEABLE,                      MmIO,       DEVICE},

    //------------------------ H3 DDR (1 GB: 0x40000000 - 0x80000000) -----------------------
    {"RAM Partition 1",         0x40000000, 0x00280000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      Conv,       WRITE_BACK},
    {"UEFI Stack",              0x40280000, 0x00040000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      BsData,     WRITE_BACK},
    {"CPU Vectors",             0x402C0000, 0x00010000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      BsCode,     WRITE_BACK},
    {"RAM Partition 2",         0x402D0000, 0x03330000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      Conv,       WRITE_BACK},
    {"UEFI FD",                 0x43600000, 0x00200000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      BsCode,     WRITE_BACK},
    {"RAM Partition 3",         0x43800000, 0x3A800000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      Conv,       WRITE_BACK},
    {"Display Reserved",        0x7E000000, 0x00400000, AddMem,   MEM_RES,      UNCACHEABLE | WRITE_COMBINEABLE,  Reserv,     UNCACHED_UNBUFFERED},
    {"RAM Partition 4",         0x7E400000, 0x01C00000, AddMem,   SYS_MEM,      SYS_MEM_CAP,                      Conv,       WRITE_BACK},

    //--------------- Terminator -----------------
    {"Terminator",              0,          0,          0,        0,            0,                                0,          0}
};

#endif
