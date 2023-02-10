# Typy - Typing Speed Game

Typy is a small application built using SFML, a multimedia library, for caculating typing speed.

## Build
To build the project, you have to have ![SFML](https://www.sfml-dev.org/tutorials/2.5/) installed.
After installation, follow the steps below to build and run the game.
```
cd build
cmake ..
make
./Typy
```

## GamePlay
- Words are not typed one by one as in typical typing speed games; however, 8 words appear on the screen moving from the very left to the right.
- Each time you type a word correctly, the word disappears and a popping sound plays.

## Features
- Calculate the net gross speed according to the formulas [here](https://www.speedtypingonline.com/typing-equations).
- Let you know the number of errors made so far as your playing the game.
- The user has a rank according to their speed, e.g., speed <=20 is a newbie. 
- There is no time limit, but you will lose if you reach 15 errors.
## UI
![alt text](https://github.com/islameehassan/Typy/blob/main/Images/UI.png?raw=true])
![alt text](https://github.com/islameehassan/Typy/blob/main/Images/UI2.png?raw=true])
