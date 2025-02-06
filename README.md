# perceptron
Single layer perceptron, written entirely in C++ for Windows x64, inspired by TheCodingTrain

# How it works

The perceptron generates a list of 100 random points, and initializes random weights. From there, it classsifies the points as above or below the line, and we train it multiple times to eventually sort the points correctly


# How to run:

the .vscode files should already be setup, this is for mingw64 compiler, make sure to install the one on winlibs.com and add it to env variables, also the base app.exe should be in the bin folder so you can probably just run it from there, also if you're gonna add on make sure to update the compilerPath in c_cpp_properties.json for intellisense.

Make sure to install sfml for mingw64 from their homepage and put it somewhere accessible (preferably C:/SFML-3.0.0). Keep in mind this does come precompiled.

If you don't want to download the SFML files, the lib and include files also come preinstalled in the **master** branch of the repo.
## Command to run (from terminal)
g++ -g src/main.cpp -o bin/app -std=c++17 -IC:/SFML-3.0.0/include -LC:/SFML-3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system 

The compiler NEEDS to support c++17 for certain libraries linked by Graphics and Windows

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Yeah not gonna lie I enjoyed making this, it was definitely a lot more rewarding than the java and python versions (python not posted on github) and for future projects (e.g. multilayer perceptrons) I'll probably use C++.
