# Tigran

## Introduction
Tigran is an chess program under development and written in C.

## Building and running

### Individual Commands
- `docker build -t tigran .` - Builds the Docker image with the tag 'tigran' using the Dockerfile in the current directory
- `docker run -it tigran` - Runs the container interactively with a terminal session

### Combined Commands
To build and run in one step:
`docker build -t tigran . && docker run -it tigran`

### Development Commands
For memory leak checking with valgrind:
`docker build -t tigran . && docker run -it tigran valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tigran`

# Development
Run with valgrind memory checking:
`docker build -t tigran . && docker run -it tigran valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tigran`

## Roadmap

The development of Tigran is guided by a series of progressive milestones aimed at enhancing its capabilities and user experience. Below is an overview of the key features and improvements I'm planning:

- ASCII chess board [x]
- Text input for moves [x]
- Legal move and checkmate recognition [ ]
    - Move the pieces [x]
- Random play of legal moves by CPU [ ]
- Better play of legal moves by CPU (methodology to be expanded upon later) [ ]
