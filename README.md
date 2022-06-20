## Compile
```shell
cd src
rgbasm -L -o main.o main.asm;
rgblink -o wordle.gb main.o;
rgbfix -v -p 0xFF wordle.gb;
```
```shell
rgbasm -L -o main.o main.asm; rgblink -o wordle.gb main.o; rgbfix -v -p 0xFF wordle.gb;
```