# cub3D

<p align="center">
	<img src="https://github.com/user-attachments/assets/9a54a2ca-6555-43b2-acc7-99c8d00e2fc6"
</p>

The goal of this project is to develop a "realistic" first-person 3D graphical representation of a maze using ray-casting, similar to [Wolfenstein3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). The rendering will be implemented using MiniLibX and standard C library functions, primarily math functions.

## Status
Finished: 2025-03-14. Grade: 125/100.

## Preview
![Demo](https://github.com/user-attachments/assets/7256535c-9ec2-48e9-8eef-6bba6a3cb8d9)

## Controls
|   Key   |      Action     |
|:-------:|:---------------:|
| `ESC`   | Exit            |
| `W`     | Move forward    |
| `S`     | Move backward   |
| `A`     | Strafe left     |
| `D`     | Strafe right    |
| `←`     | Turn left       |
| `→`     | Turn right      |
| `E`     | Interact        |
| `T`     | Toggle torch    |
| `M`     | Toggle minimap  |

`MOUSE` can also be used to turn around.

## Dependencies
- GCC/Clang Compiler
- GNU Make
- X11
- zlib
- libbsd

### Installation for MiniLibX dependencies
For Linux or WSL:
```sh
sudo apt install libx11-dev libxext-dev zlib1g-dev libbsd-dev
```
macOS should have the necessary dependencies already

## How To Use
To clone and and run this application. From your command line:
```sh
# Clone this repository
$ git clone git@github.com:exellaz/cub3D.git

# Go into repository
$ cd cub3D

# Build program
$ make

# Run program
$ ./cub3D maps/valid/[map_name].cub

# Example
$ ./cub3D maps/valid/demo.cub
```
