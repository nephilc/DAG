cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DANDROID_MODULES=OFF


ninja -j4 
