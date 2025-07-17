# RDI Kitchen Routing System Library

RDI Kitchen Routing System Library is a multi-thread safe dynamic library with can be used to route orders comming to the kitchen from many
PoS (Points of Sales). This was a task for an interview process that I did a while ago (see ABOUT file). I did pass this test, but I was rejected in the last round. This is not something for production. Feel free to do whatever you want with this.

---

## 📦 Installation

### Dependencies
- GCC >= 13, Clang >= 15, MSVC (C++17)
- CMake >= 3.16
- Doxygen 1.9.x (optional, for documentation)

---

### 🔨 Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

To compile with Clang:

```
cmake -DCMAKE_CXX_COMPILER=clang++ ..
```

---

### 📚 Generate Docs

```bash
cmake --build . --target doc
```

---

## 🚀 Running Examples

The build will produce two binary example on a build/bin folder:

- example_usage(.exe): a small multithread example of the library usage.
- tiny_kitchen_system(.exe): a small interactive console application like a kitchen system.

Run it with:

```bash
./example_usage

```

(on Windows use example_usage.exe/tiny_kitchen_system.exe directly).

---

The example demonstrates how to:

- Create kitchen areas (fries, grill, salad, drink, dessert)
- Create items and add them to menus
- Simulate two PoS (point-of-sale) threads sending orders
- Route orders to appropriate kitchen areas
- Retrieve and display prepared orders

* See app/example_usage.cpp for details.

## 🖥️ Visual Studio

To use Visual Studio, generate the solution with:

```bash
cmake -S . -G "Visual Studio 17 2022" ..
```

Then open the generated .sln file inside the build directory. Or continue with cmake:

```bash
cmake --build build --config Debug
```

You can use either `--config Debug` or `--config Release` or just compile the target.

You can also select x64-Debug or x64-Release configurations in Visual Studio.

---

## 🐧 Supported Platforms

✅ Linux

✅ Windows (MinGW / MSVC)

❓ MacOS (Should work - needs test)

---

## Notes

### About Examples

```
valgrind --tool=helgrind -s --verbose  ./build/bin/example_usage

--2215773-- REDIR: 0x4cc4460 (libc.so.6:pthread_cond_broadcast@@GLIBC_2.3.2) redirected to 0x48544d3 (pthread_cond_broadcast@*)
--2215773-- REDIR: 0x4cc4810 (libc.so.6:pthread_cond_destroy@@GLIBC_2.3.2) redirected to 0x48544f1 (pthread_cond_destroy@*)
==2215773== 
==2215773== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 216 from 14)
--2215773-- 
--2215773-- used_suppression:    216 helgrind-glibc2X-005 /usr/libexec/valgrind/default.supp:1016
==2215773== 
==2215773== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 216 from 14)
```

---

```
valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--verbose \
./build/bin/example_usage

==2231463== 
==2231463== HEAP SUMMARY:
==2231463==     in use at exit: 0 bytes in 0 blocks
==2231463==   total heap usage: 99 allocs, 99 frees, 89,372 bytes allocated
==2231463== 
==2231463== All heap blocks were freed -- no leaks are possible
==2231463== 
==2231463== For lists of detected and suppressed errors, rerun with: -s
==2231463== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

---

### 📝 TODO/ISSUES

- TODO: A function to wrap `getKitchenArea(area)->takeOrderItem()` to get the OrderItem
- TODO: A function that can rebuild the Order onde every OrderItem is marked as done so we can return a finished Order?
- TODO: Generate error codes instead return true/false for some functions.
- TODO: Review locks, maybe refectoring Kitchen.cpp to use shared_mutex ?
- TODO: Review Cmake files. It was troublesome on Windows. 

---
