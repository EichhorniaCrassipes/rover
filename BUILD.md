# Руководство по сборке

## Требования

- CMake >= 3.28
- Компилятор с поддержкой C++17 (MSVC, GCC, Clang)
- SFML 3.0.2

---

## Windows

### 1. Скачать SFML 3.0.2

Перейдите на страницу релизов SFML и скачайте **SFML 3.0.2** — архив для вашего компилятора (например, `SFML-3.0.2-windows-vc17-64-bit.zip` для MSVC или `SFML-3.0.2-windows-gcc-64-bit.zip` для MinGW).

### 2. Разместить SFML рядом с проектом

Распакуйте архив так, чтобы папка называлась `SFML-3.0.2` и находилась **внутри корневой папки проекта** (рядом с `CMakeLists.txt`):

```
...
├── CMakeLists.txt
├── SFML-3.0.2/      <-- сюда распаковать
│   ├── include/
│   ├── lib/
│   └── ...
├── engine/
├── objects/
└── ...
```

### 3. Настройка CMake (Windows)

В `CMakeLists.txt` путь до SFML уже прописан:

```cmake
find_package(
        SFML 3 REQUIRED
        COMPONENTS System Window Graphics Audio Network
        PATHS "${CMAKE_SOURCE_DIR}/SFML-3.0.2/lib/cmake/SFML"
)
```

Если вы переименовали папку или разместили SFML в другом месте — измените строку `PATHS` соответственно.

### 4. Сборка

```bash
cmake -B build -S .
cmake --build build
```

Бинарный файл появится в `.release/ROVER.exe`.

### 5. Копирование библиотек .dll из исходников SFML

После сборки в папку .release необходимо скопировать файлы с расширением ``.dll`` из папки ``SFML-3.0.2/bin``.
Нужно расположить их рядом со скомпилированным бинарным файлом RE.exe

---

## Linux

### 1. Установить SFML через пакетный менеджер

На большинстве дистрибутивов SFML 3 можно установить системно:

```bash
# Ubuntu/Debian (если доступна версия 3):
sudo apt install libsfml-dev

# Arch Linux:
sudo pacman -S sfml

# Fedora:
sudo dnf install SFML-devel
```

> Если в репозиториях доступна только SFML 2, соберите SFML 3.0.2 из исходников или используйте бинарный релиз с официального сайта.

### 2. Изменить CMakeLists.txt для Linux

Удалите строку `PATHS` из `find_package`, чтобы CMake искал SFML в системных путях:

```cmake
find_package(
        SFML 3 REQUIRED
        COMPONENTS System Window Graphics Audio Network
)
```


### 3. Установить зависимости для SFML (может понадобиться)

```bash
sudo apt install \
    libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libudev-dev libflac-dev libvorbis-dev libgl1-mesa-dev \
    libopenal-dev libfreetype-dev
```

### 4. Сборка

```bash
cmake -B build -S .
cmake --build build
```

Бинарный файл появится в `.release/ROVER`.

---

## Установка игровых ресурсов

После успешной компиляции необходимо скачать ресурсы со страницы [релизов](https://github.com/EichhorniaCrassipes/rover/releases) (для демо-версии 0.1: архив ``game resources.zip``)

Установка ресурсов производится в папку .release, правильная распаковка выглядит так:
```
...
└── .release
    ├── RE.exe (или RE для Linux)
    ├── *.dll
    ├── fonts/
    ├── image/
    ├── shaders/
    └── ...
```
