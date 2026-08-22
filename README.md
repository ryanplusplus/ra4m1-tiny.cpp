# ra4m1-tiny.cpp
Sample project using [`tiny.cpp`](https://github.com/ryanplusplus/tiny.cpp) with RA4M1..

## Setup
- Install `gcc-arm-none-eabi`

## Use
### Compile
```shell
make -f target.mk
```

### Clean
```shell
make -f target.mk clean
```

### Erase via SWD
```shell
make -f target.mk erase
```

### Flash via SWD
```shell
make -f target.mk upload
```

## Resources
- [RA4M1 Datasheet](https://www.renesas.com/en/document/dst/ra4m1-group-datasheet?r=1054146)
- [RA4M1 Hardware Manual](https://www.renesas.com/en/document/mah/renesas-ra4m1-group-users-manual-hardware?r=1054146)
- [Arduino Uno R4 Minima Pinout](https://docs.arduino.cc/resources/pinouts/ABX00080-full-pinout.pdf)
- [Arduino Uno R4 Minima Schematic](https://docs.arduino.cc/resources/schematics/ABX00080-schematics.pdf)
- [Seeeduino XIAO RA4M1 Pinout](https://files.seeedstudio.com/wiki/XIAO-R4AM1/img/XIAO_RA4M1_front_pinout.png)
- [Seeeduino XIAO RA4M1 Schematic](https://files.seeedstudio.com/wiki/XIAO-R4AM1/res/XIAO%20RA4M1%20V1.01_SCH_PDF_260114%20.pdf.pdf)
