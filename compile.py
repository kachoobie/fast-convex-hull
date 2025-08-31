import os

os.system("clang++ -std=c++20 -o exec.out main.cpp src/*.cpp -I include `pkg-config --libs --cflags sdl3`")