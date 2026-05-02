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
cmake -B cmake-build-debug -S .
cmake --build cmake-build-debug
```

Бинарный файл появится в `.release/ROVER.exe`.

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

Также уберите `${WINDOWED_MODE}` из `add_executable` (флаг `WIN32` актуален только для Windows) или оставьте как есть — на Linux он просто игнорируется.

### 3. Установить зависимости для SFML (если нужно)

```bash
sudo apt install \
    libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libudev-dev libflac-dev libvorbis-dev libgl1-mesa-dev \
    libopenal-dev libfreetype-dev
```

### 4. Сборка

```bash
cmake -B cmake-build-debug -S .
cmake --build cmake-build-debug
```

Бинарный файл появится в `.release/ROVER`.

---

## Флаги CMake

| Флаг | Значение | Описание |
|------|----------|----------|
| `RELEASE_FLAG` | `TRUE` / `FALSE` | `TRUE` — оконный режим (без консоли), компилирует с иконкой через `windres`. По умолчанию `FALSE`. |
