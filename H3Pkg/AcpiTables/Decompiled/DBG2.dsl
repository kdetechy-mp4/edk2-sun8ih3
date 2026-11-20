/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20260930 (64-bit version)
 * Copyright (c) 2000 - 2026 Intel Corporation
 * 
 * Disassembly of DBG2.aml
 *
 * ACPI Data Table [DBG2]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue (in hex)
 */

[000h 0000 004h]                   Signature : "DBG2"    [Debug Port Table type 2]
[004h 0004 004h]                Table Length : 00000054
[008h 0008 001h]                    Revision : 01
[009h 0009 001h]                    Checksum : 80
[00Ah 0010 006h]                      Oem ID : "ALWINR"
[010h 0016 008h]                Oem Table ID : "H3EDK2 "
[018h 0024 004h]                Oem Revision : 00000616
[01Ch 0028 004h]             Asl Compiler ID : "INTL"
[020h 0032 004h]       Asl Compiler Revision : 20260930

[024h 0036 004h]                 Info Offset : 0000002C
[028h 0040 004h]                  Info Count : 00000001

[02Ch 0044 001h]                    Revision : 00
[02Dh 0045 002h]                      Length : 0028
[02Fh 0047 001h]              Register Count : 01
[030h 0048 002h]             Namepath Length : 0002
[032h 0050 002h]             Namepath Offset : 0026
[034h 0052 002h]             OEM Data Length : 0000 [Optional field not present]
[036h 0054 002h]             OEM Data Offset : 0000 [Optional field not present]
[038h 0056 002h]                   Port Type : 8000
[03Ah 0058 002h]                Port Subtype : 0012
[03Ch 0060 002h]                    Reserved : 0000
[03Eh 0062 002h]         Base Address Offset : 0016
[040h 0064 002h]         Address Size Offset : 0022

[042h 0066 00Ch]       Base Address Register : [Generic Address Structure]
[042h 0066 001h]                    Space ID : 00 [SystemMemory]
[043h 0067 001h]                   Bit Width : 20
[044h 0068 001h]                  Bit Offset : 00
[045h 0069 001h]        Encoded Access Width : 03 [DWord Access:32]
[046h 0070 008h]                     Address : 0000000001C28000

[04Eh 0078 004h]                Address Size : 00001000

[052h 0082 002h]                    Namepath : "."

Raw Table Data: Length 84 (0x54)

    0000: 44 42 47 32 54 00 00 00 01 80 41 4C 57 49 4E 52  // DBG2T.....ALWINR
    0010: 48 33 45 44 4B 32 20 00 16 06 00 00 49 4E 54 4C  // H3EDK2 .....INTL
    0020: 30 09 26 20 2C 00 00 00 01 00 00 00 00 28 00 01  // 0.& ,........(..
    0030: 02 00 26 00 00 00 00 00 00 80 12 00 00 00 16 00  // ..&.............
    0040: 22 00 00 20 00 03 00 80 C2 01 00 00 00 00 00 10  // ".. ............
    0050: 00 00 2E 00                                      // ....
