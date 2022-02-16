# Socket example

## Overview

This project is an example of the socket connection with UNIX domain sockets.

Product

- `reader`: Create a listen socket and read/print data from it
- `writer`: Connect to the peer socket and write/send data to it

## Build

```shell-session
$ gn gen out
$ ninja -C out
```

## Run

```shell-session
$ ./out/reader ./sock &
$ ./out/writer ./sock ABCDEFG
ABCDEFG
```
