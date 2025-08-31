# Fast Convex Hull

Implementation of convex hull algorithm in O(nlogn).

To run, clone the repo and install SDL3 and CMake. Python3.x is also required. Instructions for installing SDL3 from source are in [this repo](https://github.com/kachoobie/SDL3-setup-instructions). Once installed, run the Python compilation script:
```bash
python3 compile.py
```

Then, run the executable:
```bash
./exec.out
```

## Controls

Clicking anywhere on the window adds a point. Pressing the `space` key adds 10 random points. The `t` key adds 1000 random points. Pressing the `c` key clears the screen of all drawn objects. Pressing `return` finds the convex hull and presents it in the window.