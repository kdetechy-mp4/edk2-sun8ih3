DefinitionBlock ("DSDT_minimal.aml", "DSDT", 2, "ALWINR", "H3EDK2 ", 0x00000003)
{
     Scope (\_SB)
    {
        Method (_OSC, 4, Serialized)
        {
            CreateDWordField (Arg3, 0x00, CDW1)
            If (LEqual (Arg0, ToUUID ("0811B06E-4A27-44F9-8D60-3CBBC22E7B38")))
            {
                Return (Arg3)
            }
            Else
            {
                Or (CDW1, 0x04, CDW1)
                Return (Arg3)
            }
        }

        Device (CPU0)
        {
            Name (_HID, "ACPI0007")
            Name (_UID, 0x00)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
        }

        Device (CPU1)
        {
            Name (_HID, "ACPI0007")
            Name (_UID, 0x01)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x00)
            }
        }

        Device (CPU2)
        {
            Name (_HID, "ACPI0007" /* Processor Device */)
            Name (_UID, 0x02)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x00)
            }
        }

        Device (CPU3)
        {
            Name (_HID, "ACPI0007")
            Name (_UID, 0x03)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x00)
            }
        }

        Device (EHC0)
        {
            Name (_HID, EisaId ("PNP0D20"))
            Name (_UID, 0x01)
            Name (_CCA, Zero)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C1A000, 0x00000100)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 104 }
            })
        }

        Device (EHC1)
        {
            Name (_HID, EisaId ("PNP0D20"))
            Name (_UID, 0x01)
            Name (_CCA, Zero)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C1B000, 0x00000100)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 106 }
            })
        }

        Device (EHC2)
        {
            Name (_HID, EisaId ("PNP0D20"))
            Name (_UID, 0x02)
            Name (_CCA, Zero)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C1C000, 0x00000100)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 108 }
            })
        }

        Device (EHC3)
        {
            Name (_HID, EisaId ("PNP0D20"))
            Name (_UID, 0x03)
            Name (_CCA, Zero)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C1D000, 0x00000100)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 110 }
            })
        }

        // never got to bring this up lmao
        Device (SDC0)
        {
            Name (_HID, "AWMC0001")
            Name (_UID, 0x00)
            Name (_CCA, Zero)
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }
            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C0F000, 0x00001000)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 92 }
            })
        }

        Device (EMAC)
        {
            Name (_HID, "AWEM0001")
            Name (_UID, Zero)
            Name (_CCA, Zero)

            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }

            Name (_CRS, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite, 0x01C30000, 0x00010000)
                Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 114 }
            })
        }
    }
}
