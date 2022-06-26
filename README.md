# Wordle (GameBoy Edition)
Everyone's favorite game, now on GameBoy.

[![wakatime](https://wakatime.com/badge/user/9797ee4f-4108-45bb-8fc2-b36b9c1a1c89/project/ab548926-d82e-4ef8-8b79-3343f96b337e.svg?style=for-the-badge)](https://wakatime.com/badge/user/9797ee4f-4108-45bb-8fc2-b36b9c1a1c89/project/ab548926-d82e-4ef8-8b79-3343f96b337e)

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
