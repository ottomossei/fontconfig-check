#!/bin/bash

if [ -d "build" ]; then
    echo "Removing existing build directory..."
    rm -r build
fi

mkdir build
pushd build

# TODO xterm is under development
cmake .. -DWITH_IMAGE_GENERATION=ON -DWITH_XTERMINAL_FONT=OFF -DCMAKE_BUILD_TYPE=Release -G Ninja
ninja

popd

pushd build/example/familiy
./fontconfig_familiy
popd

pushd build/example/module
./fontconfig_module NotoSans
popd
