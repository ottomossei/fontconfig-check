#!/bin/bash

if [ -d "build" ]; then
    echo "Removing existing build directory..."
    rm -r build
fi

mkdir build
pushd build

cmake .. -DWITH_IMAGE_GENERATION=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja
ninja

popd

pushd build/example/familiy
./fontconfig_familiy
popd

pushd build/example/module
./fontconfig_module NotoSans
popd
