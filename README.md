<p align="center">
    <img src="logo.svg"/>
    <a href="https://github.com/Slava2001/Wanderfern/actions/workflows/build_linux.yml">
        <img src="https://github.com/Slava2001/Wanderfern/actions/workflows/build_linux.yml/badge.svg" alt="Linux" />
    </a>
    <a href="https://github.com/Slava2001/Wanderfern/actions/workflows/build_windows.yml">
        <img src="https://github.com/Slava2001/Wanderfern/actions/workflows/build_windows.yml/badge.svg" alt="Windows" />
    </a>
</p>

---

## Сборка

### Установка зависимостей

#### Linux
```sh
sudo apt update
sudo apt install build-essential libglfw3-dev libglu1-mesa-dev libglew-dev libx11-dev
```

#### Windows
```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-glew mingw-w64-x86_64-glfw
```

Убедитесь, что DLL-файлы GLFW находятся в PATH или рядом с исполняемым файлом.

### Сборка
```sh
make BUILD=release
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
