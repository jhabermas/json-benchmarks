# Python
pip install -r ./python/requirements.txt
pip install ./python --force-reinstall
# Node
cd node
npm install
npm test
cd ..
# Rust
cargo build --release
cargo test --release
# C++
pip install conan
conan profile detect
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install .
