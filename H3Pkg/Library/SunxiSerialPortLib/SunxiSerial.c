/*
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 * Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
 * Copyright (c) 2012 - 2014, ARM Ltd. All rights reserved.
 * Copyright (c) Artur Kowalski. <arturkow2000@gmail.com>
 */

#include <Uefi.h>
#include <Library/SerialPortLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Resources/font5x12.h>

#include "Hw.h"

#define FB_ADDR       0x7E000000U
#define FB_WIDTH      1280U
#define FB_HEIGHT     720U
#define FB_STATE_ADDR (FB_ADDR + FB_WIDTH * FB_HEIGHT * 4U)
#define FB_STATE_MAGIC 0x46424442U
#define FB_STATE_DISABLED 0x474F5021U

#define CHAR_W        (FONT_WIDTH * SCALE_FACTOR + 2U)   /* 12 px */
#define CHAR_H        (FONT_HEIGHT * SCALE_FACTOR + 4U)  /* 28 px */
#define FB_COLS       (FB_WIDTH / CHAR_W)                /* 106 cols */
#define FB_ROWS       (FB_HEIGHT / CHAR_H)               /* 25 rows */

#define FB_FG_COLOR   0xFFE0E0E0U
#define FB_BG_COLOR   0xFF000000U

typedef struct {
  UINT32 Magic;
  UINT32 Col;
  UINT32 Row;
} FB_CONSOLE_STATE;

STATIC VOID FbFlushRange(UINTN StartAddr, UINTN Size)
{
  UINTN Addr = StartAddr & ~63U;
  UINTN End  = StartAddr + Size;

  __asm__ volatile ("dsb" ::: "memory");
  while (Addr < End) {
    __asm__ volatile ("mcr p15, 0, %0, c7, c10, 1" :: "r"(Addr) : "memory");
    Addr += 64;
  }
  __asm__ volatile ("dsb" ::: "memory");
}

STATIC VOID FbClearRows(UINT32 StartY, UINT32 Height)
{
  volatile UINT32 *Fb = (volatile UINT32 *)(UINTN)FB_ADDR + (StartY * FB_WIDTH);
  UINT32 Count = Height * FB_WIDTH;
  UINT32 i;

  for (i = 0; i < Count; i++) {
    Fb[i] = FB_BG_COLOR;
  }
  FbFlushRange((UINTN)Fb, Count * 4U);
}

STATIC VOID FbEnsureInit(VOID)
{
  volatile FB_CONSOLE_STATE *State = (volatile FB_CONSOLE_STATE *)(UINTN)FB_STATE_ADDR;

  if (State->Magic == FB_STATE_DISABLED) {
    return;
  }

  if (State->Magic != FB_STATE_MAGIC) {
    FbClearRows(0, FB_HEIGHT);
    State->Col   = 0;
    State->Row   = 0;
    State->Magic = FB_STATE_MAGIC;
    FbFlushRange((UINTN)State, sizeof(FB_CONSOLE_STATE));
  }
}

STATIC VOID FbNewLine(volatile FB_CONSOLE_STATE *State)
{
  State->Col = 0;
  State->Row++;
  if (State->Row >= FB_ROWS) {
    State->Row = 0;
  }
  FbClearRows(State->Row * CHAR_H, CHAR_H);
}

STATIC VOID FbPutChar(UINT8 Ch)
{
  volatile FB_CONSOLE_STATE *State = (volatile FB_CONSOLE_STATE *)(UINTN)FB_STATE_ADDR;
  volatile UINT32 *Fb = (volatile UINT32 *)(UINTN)FB_ADDR;
  UINT32 BaseX;
  UINT32 BaseY;
  UINT32 Word0;
  UINT32 Word1;
  UINT32 R;
  UINT32 C;
  UINT32 Sy;
  UINT32 Sx;
  UINT32 Index;

  FbEnsureInit();
  if (State->Magic == FB_STATE_DISABLED) {
    return;
  }

  if (Ch == '\r') {
    State->Col = 0;
    FbFlushRange((UINTN)State, sizeof(FB_CONSOLE_STATE));
    return;
  }

  if (Ch == '\n') {
    FbNewLine(State);
    FbFlushRange((UINTN)State, sizeof(FB_CONSOLE_STATE));
    return;
  }

  if (Ch == '\t') {
    UINT32 Spaces = 4U - (State->Col % 4U);
    while (Spaces--) {
      FbPutChar(' ');
    }
    return;
  }

  if (State->Col >= FB_COLS) {
    FbNewLine(State);
  }

  if (Ch < 0x20 || Ch > 0x7F) {
    Ch = ' ';
  }

  Index = (UINT32)(Ch - 0x20) * 2U;
  Word0 = font5x12[Index];
  Word1 = font5x12[Index + 1U];

  BaseX = State->Col * CHAR_W;
  BaseY = State->Row * CHAR_H;

  for (R = 0; R < FONT_HEIGHT; R++) {
    UINT32 RowBits = (R < 6U) ? ((Word0 >> (R * 5U)) & 0x1FU)
    : ((Word1 >> ((R - 6U) * 5U)) & 0x1FU);
    for (C = 0; C < FONT_WIDTH; C++) {
      UINT32 Color = ((RowBits >> C) & 1U) ? FB_FG_COLOR : FB_BG_COLOR;
      for (Sy = 0; Sy < SCALE_FACTOR; Sy++) {
        UINT32 Py = BaseY + (R * SCALE_FACTOR) + Sy;
        for (Sx = 0; Sx < SCALE_FACTOR; Sx++) {
          UINT32 Px = BaseX + (C * SCALE_FACTOR) + Sx;
          Fb[Py * FB_WIDTH + Px] = Color;
        }
      }
    }
  }

  FbFlushRange((UINTN)&Fb[BaseY * FB_WIDTH], CHAR_H * FB_WIDTH * 4U);
  State->Col++;
  FbFlushRange((UINTN)State, sizeof(FB_CONSOLE_STATE));
}

RETURN_STATUS EFIAPI SerialPortInitialize(VOID)
{
  FbEnsureInit();
  return EFI_SUCCESS;
}

UINTN EFIAPI SerialPortWrite(
  IN UINT8 *Buffer,
  IN UINTN NumberOfBytes)
{
  UINTN i;

  for (i = 0; i < NumberOfBytes; i++)
  {
    while ((MmioRead32(UART_LSR) & UART_LSR_THRE) == 0)
    {
    }

    MmioWrite32(UART_THR, Buffer[i]);
    FbPutChar(Buffer[i]);
  }

  return NumberOfBytes;
}

/**
  Read data from serial device and save the datas in buffer.

  Reads NumberOfBytes data bytes from a serial device into the buffer
  specified by Buffer. The number of bytes actually read is returned.
  If the return value is less than NumberOfBytes, then the rest operation failed.
  If Buffer is NULL, then ASSERT().
  If NumberOfBytes is zero, then return 0.

  @param  Buffer           Pointer to the data buffer to store the data read from the serial device.
  @param  NumberOfBytes    Number of bytes which will be read.

  @retval 0                Read data failed, no data is to be read.
  @retval >0               Actual number of bytes read from serial device.

**/
UINTN EFIAPI SerialPortRead(
    OUT UINT8 *Buffer,
    IN UINTN NumberOfBytes)
{
  UINTN i;

  for (i = 0; i < NumberOfBytes; i++, Buffer++)
  {
    while (SerialPortPoll() == FALSE)
    {
    }
    *Buffer = (UINT8)MmioRead32(UART_RBR);
  }
  return NumberOfBytes;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls a serial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN EFIAPI SerialPortPoll(VOID)
{
  return !!(MmioRead32(UART_LSR) & UART_LSR_DR);
}

/**
  Sets the control bits on a serial device.

  @param Control                Sets the bits of Control that are settable.

  @retval RETURN_SUCCESS        The new control bits were set on the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS EFIAPI SerialPortSetControl(IN UINT32 Control)
{
  return RETURN_UNSUPPORTED;
}

/**
  Retrieve the status of the control bits on a serial device.

  @param Control                A pointer to return the current control signals from the serial device.

  @retval RETURN_SUCCESS        The control bits were read from the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS EFIAPI SerialPortGetControl(OUT UINT32 *Control)
{
  return RETURN_UNSUPPORTED;
}

/**
  Sets the baud rate, receive FIFO depth, transmit/receice time out, parity,
  data bits, and stop bits on a serial device.

  @param BaudRate           The requested baud rate. A BaudRate value of 0 will use the
                            device's default interface speed.
                            On output, the value actually set.
  @param ReveiveFifoDepth   The requested depth of the FIFO on the receive side of the
                            serial interface. A ReceiveFifoDepth value of 0 will use
                            the device's default FIFO depth.
                            On output, the value actually set.
  @param Timeout            The requested time out for a single character in microseconds.
                            This timeout applies to both the transmit and receive side of the
                            interface. A Timeout value of 0 will use the device's default time
                            out value.
                            On output, the value actually set.
  @param Parity             The type of parity to use on this serial device. A Parity value of
                            DefaultParity will use the device's default parity value.
                            On output, the value actually set.
  @param DataBits           The number of data bits to use on the serial device. A DataBits
                            vaule of 0 will use the device's default data bit setting.
                            On output, the value actually set.
  @param StopBits           The number of stop bits to use on this serial device. A StopBits
                            value of DefaultStopBits will use the device's default number of
                            stop bits.
                            On output, the value actually set.

  @retval RETURN_SUCCESS            The new attributes were set on the serial device.
  @retval RETURN_UNSUPPORTED        The serial device does not support this operation.
  @retval RETURN_INVALID_PARAMETER  One or more of the attributes has an unsupported value.
  @retval RETURN_DEVICE_ERROR       The serial device is not functioning correctly.

**/
RETURN_STATUS EFIAPI SerialPortSetAttributes(
  IN OUT UINT64 *BaudRate,
  IN OUT UINT32 *ReceiveFifoDepth,
  IN OUT UINT32 *Timeout,
  IN OUT EFI_PARITY_TYPE *Parity,
  IN OUT UINT8 *DataBits,
  IN OUT EFI_STOP_BITS_TYPE *StopBits)
{
  if (*BaudRate == 0) {
    *BaudRate = 115200;
  }
  if (*ReceiveFifoDepth == 0) {
    *ReceiveFifoDepth = 64;
  }
  if (*Timeout == 0) {
    *Timeout = 1000000;
  }
  if (*Parity == DefaultParity) {
    *Parity = NoParity;
  }
  if (*DataBits == 0) {
    *DataBits = 8;
  }
  if (*StopBits == DefaultStopBits) {
    *StopBits = OneStopBit;
  }

  // Enable FIFO to prevent losing data on input
  MmioWrite32(UART_FCR, UART_FCR_ENABLE_FIFO);

  return RETURN_SUCCESS;
}
