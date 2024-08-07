echo "Building CMake project..."
mkdir -p build

BUILD_DIR=build/${BUILD_CONFIGURATION}

mkdir -p ${BUILD_DIR}

if [ "$(uname)" != "MINGW"* ] && [ "$(uname)" != "CYGWIN"* ] && [ "$(uname)" != "MSYS"* ]; then
  # Use sed to replace '\\' with '/' in the file cmake/st-project.cmake
  sed -i 's#\\\\#/#g' cmake/st-project.cmake
fi

echo "Generating build files..."
cmake -DCMAKE_BUILD_TYPE=${BUILD_CONFIGURATION} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake -S . -B ${BUILD_DIR} -G Ninja

echo "Building project..."
cmake --build ${BUILD_DIR} --config ${BUILD_CONFIGURATION} --target cat-toy-stm