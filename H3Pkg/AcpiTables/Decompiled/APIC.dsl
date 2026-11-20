/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20260930 (64-bit version)
 * Copyright (c) 2000 - 2026 Intel Corporation
 * 
 * Disassembly of APIC.aml
 *
 * ACPI Data Table [APIC]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue (in hex)
 */

[000h 0000 004h]                   Signature : "APIC"    [Multiple APIC Description Table (MADT)]
[004h 0004 004h]                Table Length : 0000018C
[008h 0008 001h]                    Revision : 03
[009h 0009 001h]                    Checksum : 70
[00Ah 0010 006h]                      Oem ID : "ALWINR"
[010h 0016 008h]                Oem Table ID : "H3EDK2 "
[018h 0024 004h]                Oem Revision : 00000003
[01Ch 0028 004h]             Asl Compiler ID : "INTL"
[020h 0032 004h]       Asl Compiler Revision : 20260930

[024h 0036 004h]          Local Apic Address : 00000000
[028h 0040 004h]       Flags (decoded below) : 00000000
                         PC-AT Compatibility : 0

[02Ch 0044 001h]               Subtable Type : 0B [Generic Interrupt Controller]
[02Dh 0045 001h]                      Length : 52
[02Eh 0046 002h]                    Reserved : 0000
[030h 0048 004h]        CPU Interface Number : 00000000
[034h 0052 004h]               Processor UID : 00000000
[038h 0056 004h]       Flags (decoded below) : 00000001
                           Processor Enabled : 1
          Performance Interrupt Trigger Mode : 0
          Virtual GIC Interrupt Trigger Mode : 0
[03Ch 0060 004h]    Parking Protocol Version : 00000000
[040h 0064 004h]       Performance Interrupt : 00000098
[044h 0068 008h]              Parked Address : 0000000000000000
[04Ch 0076 008h]                Base Address : 0000000001C82000
[054h 0084 008h]    Virtual GIC Base Address : 0000000001C86000
[05Ch 0092 008h] Hypervisor GIC Base Address : 0000000001C84000
[064h 0100 004h]       Virtual GIC Interrupt : 00000019
[068h 0104 008h]  Redistributor Base Address : 0000000000000000
[070h 0112 008h]                   ARM MPIDR : 0000000000000000
[078h 0120 001h]            Efficiency Class : 00
[079h 0121 001h]                    Reserved : 00
[07Ah 0122 002h]      SPE Overflow Interrupt : 0000
[07Ch 0124 002h]              TRBE Interrupt : 0000

[07Eh 0126 001h]               Subtable Type : 0B [Generic Interrupt Controller]
[07Fh 0127 001h]                      Length : 52
[080h 0128 002h]                    Reserved : 0000
[082h 0130 004h]        CPU Interface Number : 00000001
[086h 0134 004h]               Processor UID : 00000001
[08Ah 0138 004h]       Flags (decoded below) : 00000000
                           Processor Enabled : 0
          Performance Interrupt Trigger Mode : 0
          Virtual GIC Interrupt Trigger Mode : 0
[08Eh 0142 004h]    Parking Protocol Version : 00000000
[092h 0146 004h]       Performance Interrupt : 00000099
[096h 0150 008h]              Parked Address : 0000000000000000
[09Eh 0158 008h]                Base Address : 0000000001C82000
[0A6h 0166 008h]    Virtual GIC Base Address : 0000000001C86000
[0AEh 0174 008h] Hypervisor GIC Base Address : 0000000001C84000
[0B6h 0182 004h]       Virtual GIC Interrupt : 00000019
[0BAh 0186 008h]  Redistributor Base Address : 0000000000000000
[0C2h 0194 008h]                   ARM MPIDR : 0000000000000001
[0CAh 0202 001h]            Efficiency Class : 00
[0CBh 0203 001h]                    Reserved : 00
[0CCh 0204 002h]      SPE Overflow Interrupt : 0000
[0CEh 0206 002h]              TRBE Interrupt : 0000

[0D0h 0208 001h]               Subtable Type : 0B [Generic Interrupt Controller]
[0D1h 0209 001h]                      Length : 52
[0D2h 0210 002h]                    Reserved : 0000
[0D4h 0212 004h]        CPU Interface Number : 00000002
[0D8h 0216 004h]               Processor UID : 00000002
[0DCh 0220 004h]       Flags (decoded below) : 00000000
                           Processor Enabled : 0
          Performance Interrupt Trigger Mode : 0
          Virtual GIC Interrupt Trigger Mode : 0
[0E0h 0224 004h]    Parking Protocol Version : 00000000
[0E4h 0228 004h]       Performance Interrupt : 0000009A
[0E8h 0232 008h]              Parked Address : 0000000000000000
[0F0h 0240 008h]                Base Address : 0000000001C82000
[0F8h 0248 008h]    Virtual GIC Base Address : 0000000001C86000
[100h 0256 008h] Hypervisor GIC Base Address : 0000000001C84000
[108h 0264 004h]       Virtual GIC Interrupt : 00000019
[10Ch 0268 008h]  Redistributor Base Address : 0000000000000000
[114h 0276 008h]                   ARM MPIDR : 0000000000000002
[11Ch 0284 001h]            Efficiency Class : 00
[11Dh 0285 001h]                    Reserved : 00
[11Eh 0286 002h]      SPE Overflow Interrupt : 0000
[120h 0288 002h]              TRBE Interrupt : 0000

[122h 0290 001h]               Subtable Type : 0B [Generic Interrupt Controller]
[123h 0291 001h]                      Length : 52
[124h 0292 002h]                    Reserved : 0000
[126h 0294 004h]        CPU Interface Number : 00000003
[12Ah 0298 004h]               Processor UID : 00000003
[12Eh 0302 004h]       Flags (decoded below) : 00000000
                           Processor Enabled : 0
          Performance Interrupt Trigger Mode : 0
          Virtual GIC Interrupt Trigger Mode : 0
[132h 0306 004h]    Parking Protocol Version : 00000000
[136h 0310 004h]       Performance Interrupt : 0000009B
[13Ah 0314 008h]              Parked Address : 0000000000000000
[142h 0322 008h]                Base Address : 0000000001C82000
[14Ah 0330 008h]    Virtual GIC Base Address : 0000000001C86000
[152h 0338 008h] Hypervisor GIC Base Address : 0000000001C84000
[15Ah 0346 004h]       Virtual GIC Interrupt : 00000019
[15Eh 0350 008h]  Redistributor Base Address : 0000000000000000
[166h 0358 008h]                   ARM MPIDR : 0000000000000003
[16Eh 0366 001h]            Efficiency Class : 00
[16Fh 0367 001h]                    Reserved : 00
[170h 0368 002h]      SPE Overflow Interrupt : 0000
[172h 0370 002h]              TRBE Interrupt : 0000

[174h 0372 001h]               Subtable Type : 0C [Generic Interrupt Distributor]
[175h 0373 001h]                      Length : 18
[176h 0374 002h]                    Reserved : 0000
[178h 0376 004h]       Local GIC Hardware ID : 00000000
[17Ch 0380 008h]                Base Address : 0000000001C81000
[184h 0388 004h]              Interrupt Base : 00000000
[188h 0392 001h]                     Version : 02
[189h 0393 003h]                    Reserved : 000000

Raw Table Data: Length 396 (0x18C)

    0000: 41 50 49 43 8C 01 00 00 03 70 41 4C 57 49 4E 52  // APIC.....pALWINR
    0010: 48 33 45 44 4B 32 20 00 03 00 00 00 49 4E 54 4C  // H3EDK2 .....INTL
    0020: 30 09 26 20 00 00 00 00 00 00 00 00 0B 52 00 00  // 0.& .........R..
    0030: 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00  // ................
    0040: 98 00 00 00 00 00 00 00 00 00 00 00 00 20 C8 01  // ............. ..
    0050: 00 00 00 00 00 60 C8 01 00 00 00 00 00 40 C8 01  // .....`.......@..
    0060: 00 00 00 00 19 00 00 00 00 00 00 00 00 00 00 00  // ................
    0070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0B 52  // ...............R
    0080: 00 00 01 00 00 00 01 00 00 00 00 00 00 00 00 00  // ................
    0090: 00 00 99 00 00 00 00 00 00 00 00 00 00 00 00 20  // ............... 
    00A0: C8 01 00 00 00 00 00 60 C8 01 00 00 00 00 00 40  // .......`.......@
    00B0: C8 01 00 00 00 00 19 00 00 00 00 00 00 00 00 00  // ................
    00C0: 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00  // ................
    00D0: 0B 52 00 00 02 00 00 00 02 00 00 00 00 00 00 00  // .R..............
    00E0: 00 00 00 00 9A 00 00 00 00 00 00 00 00 00 00 00  // ................
    00F0: 00 20 C8 01 00 00 00 00 00 60 C8 01 00 00 00 00  // . .......`......
    0100: 00 40 C8 01 00 00 00 00 19 00 00 00 00 00 00 00  // .@..............
    0110: 00 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00  // ................
    0120: 00 00 0B 52 00 00 03 00 00 00 03 00 00 00 00 00  // ...R............
    0130: 00 00 00 00 00 00 9B 00 00 00 00 00 00 00 00 00  // ................
    0140: 00 00 00 20 C8 01 00 00 00 00 00 60 C8 01 00 00  // ... .......`....
    0150: 00 00 00 40 C8 01 00 00 00 00 19 00 00 00 00 00  // ...@............
    0160: 00 00 00 00 00 00 03 00 00 00 00 00 00 00 00 00  // ................
    0170: 00 00 00 00 0C 18 00 00 00 00 00 00 00 10 C8 01  // ................
    0180: 00 00 00 00 00 00 00 00 02 00 00 00              // ............
