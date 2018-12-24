#!/bin/bash
$SCRIPT_BEGIN

#cd "$BUILD_DIR"

export CONFIG="Debug,Magick,GMP,ITK,FFTW3,Debug,Cairo,QGLviewer,HDF5,EIGEN"

# OS dependent deps
source "$SRC_DIR/.travis/install_eigen.sh"
echo $EIGEN_ROOT
cd build
echo "SRCDIR=$SRC_DIR"
echo "PWDDDDD = $PWD"
echo " -DDOXYGEN_EXECUTABLE=$HOME/doxygen/doxygen-1.8.14/bin/doxygen"

export BTYPE="$BTYPE -DBUILD_EXAMPLES=true -DBUILD_TESTING=false"
export BTYPE="$BTYPE -DCMAKE_BUILD_TYPE=Debug -DWITH_MAGICK=true -DWITH_GMP=true\
                     -DWITH_FFTW3=true -DWARNING_AS_ERROR=ON -DCMAKE_BUILD_TYPE=Debug \
                     -DWITH_HDF5=true -DWITH_CAIRO=true -DWITH_QGLVIEWER=true -DWITH_EIGEN=true\
                     -DWARNING_AS_ERROR=OFF -DEIGEN3_INCLUDE_DIR='$EIGEN_ROOT/include/eigen3'\
                     -DDOXYGEN_EXECUTABLE=$TRAVIS_BUILD_DIR/doxygen/bin/doxygen"


echo "export BTYPE=$BTYPE -DCMAKE_BUILD_TYPE=Debug -DWITH_MAGICK=true -DWITH_GMP=true\
                     -DWITH_FFTW3=true -DWARNING_AS_ERROR=ON -DCMAKE_BUILD_TYPE=Debug \
                     -DWITH_HDF5=true -DWITH_CAIRO=true -DWITH_QGLVIEWER=true -DWITH_EIGEN=true\
                     -DWARNING_AS_ERROR=OFF -DEIGEN3_INCLUDE_DIR='$EIGEN_ROOT/include/eigen3'\
                     -DDOXYGEN_EXECUTABLE=$TRAVIS_BUILD_DIR/doxygen/bin/doxygen"

#############################
#     cmake
#############################
#Build directory
cd build
echo "Build folder= $BUILD_DIR"

# Common build options
export BTYPE="$BTYPE -DCMAKE_CXX_COMPILER=$CXXCOMPILER -DCMAKE_C_COMPILER=$CCOMPILER"

# Cmake
echo "Using C++ = $CXXCOMPILER"
echo "CMake options = $BTYPE"
cmake "$SRC_DIR" $BTYPE

### Downloading tag file for DGtalTools
wget --no-check-certificate -O "$BUILD_DIR/DGtalTools-tagfile" http://dgtal.org/doc/tags/DGtalTools-tagfile;

### DGtal Doc
make doc > buildDoc.log

$SCRIPT_END