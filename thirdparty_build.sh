cd thirdparty/eigen3
mkdir {build,install}
cd build
cmake ../eigen/ -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release
make -j
sudo make install

cd ../../matplotlib-cpp
mkdir {build,install}
cd build
cmake ../matplotlib-cpp/ -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release
make -j
sudo make install

cd ../../../