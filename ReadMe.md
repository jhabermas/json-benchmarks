# cpp-template

C++, CMake and conan repository template with library, app, tests and python bindings.

## Building

"id" - the last 8 characters of the original ID
"str" - only the first word from the original "string"
"num" - value of "number" + 1
"val" - 0 if "null" is None otherwise 1
"sum" - the sum of "array" elements
"obj" - "object"
"timestamp" - timestamp, but converted from unix to ISO time format

From virtual env:

```bash
pip install conan
conan profile detect
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install .
cd ..
pip install .
```
