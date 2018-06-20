# My personal ErgoDox EZ layout

This is a highly customized layout compared to the default one being flashed in
ErgoDox EZ.  Some of the key combos are present due to historic reasons and this
configuration may be changed over the time.


# Building the firmware

```
$ git clone https://github.com/qmk/qmk_firmware.git
$ cd qmk_firmware
$ pushd keyboards/ergodox_ez/keymaps
$ git submodule add https://github.com/phatina/ergodox_ez_layout phatina
$ git submodule update --init --recursive
$ popd
$ make ergodox_ez:phatina
```


# Flashing

```
$ teensy_loader_cli -v --mcu=atmega32u4 -w .build/ergodox_ez_phatina.hex
```
