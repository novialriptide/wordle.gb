# Wordle (GameBoy Edition)
Everyone's favorite game, now on GameBoy.

## Compile From Source
```shell
cd src
rgbasm -L -o main.o main.asm;
rgblink -o wordle.gb main.o;
rgbfix -v -p 0xFF wordle.gb;
```

## Special Thanks
 - https://spkelly.net/tilegen/
 - https://eldred.fr/gb-asm-tutorial
 - https://rgbds.gbdev.io/
