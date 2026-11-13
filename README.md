Attempt to create a minimal EDK2 for some MSM8909 devices

## Status
Untested

## Building
Tested on Fedora 45

First, clone EDK2.

```
cd ..
git clone https://github.com/tianocore/edk2.git -b edk2-stable202508 --recursive
git clone https://github.com/tianocore/edk2-platforms.git
```

You should have all three directories side by side.

Next, install dependencies:

Fedora 45:

```
sudo apt install build-essential uuid-dev iasl git nasm python3-distutils crossbuild-essential-armel
```

Also see [EDK2 website](https://github.com/tianocore/tianocore.github.io/wiki/Using-EDK-II-with-Native-GCC#Install_required_software_from_apt)

Then ./firstrun.sh

Finally, ./build.sh

Then use U-BOOT to chainload EDK2

# Credits

SimpleFbDxe screen driver is from imbushuo's [Lumia950XLPkg](https://github.com/WOA-Project/Lumia950XLPkg).
