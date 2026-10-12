$ErrorActionPreference = "Stop"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
if ($LASTEXITCODE -ne 0) { throw "CMake configure failed" }
cmake --build build --config Release
if ($LASTEXITCODE -ne 0) { throw "Build failed" }
ctest --test-dir build -C Release --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Tests failed" }
