<p align="center">
    <img src="logo.svg"/>
</p>
    [![Build (Linux)](https://github.com/Slava2001/Wanderfern/actions/workflows/build_linux.yml/badge.svg)](https://github.com/Slava2001/Wanderfern/actions/workflows/build_linux.yml)
    [![Build (Windows)](https://github.com/Slava2001/Wanderfern/actions/workflows/build_windows.yml/badge.svg)](https://github.com/Slava2001/Wanderfern/actions/workflows/build_windows.yml)

---

## Сборка

### Установка зависимостей

#### Linux

```sh
sudo apt update
sudo apt install build-essential libglfw3-dev libglu1-mesa-dev libglew-dev libx11-dev
```

#### Windows

Необходимо скачать и установить msys2: https://www.msys2.org/

```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-glew mingw-w64-x86_64-glfw
```

Убедитесь, что DLL-файлы GLFW находятся в PATH или рядом с исполняемым файлом.

### Сборка

#### Linux

```sh
make BUILD=release
```

#### Windows

```sh
mingw32-make BUILD=release
```

### Запуск

#### Linux

```sh
./wanderfern
```

#### Windows

```sh
.\wanderfern.exe
```
