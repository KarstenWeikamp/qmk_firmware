# tijo

![tijo](https://media.discordapp.net/attachments/1316025124276932628/1367488385123356734/IMG_20250501_150800315.jpg?ex=6818100d&is=6816be8d&hm=ee45d5fdf01b804ce385379403305d8ecb8eaf3cac90068f7a29e3fb0b57b080&=&format=webp&width=910&height=683)

RP2040-based keyboard with high polling rate analog hall effect switches

* Keyboard Maintainer: [Karsten Weikamp](https://github.com/KarstenWeikamp)
* Hardware Supported: RP2040
* Hardware Availability: n/a

Make example for this keyboard (after setting up your build environment):

    make tijo:default

Flashing example for this keyboard:

    make tijo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
