#!/bin/sh

echo "Clean Up"
echo "--------"

make clean
cd Engine
make clean

echo "Building library"
echo "-----------------"

make

echo
echo "Removing library from /usr/lib..."
echo "---------------------------------"
echo

rm -f -- /usr/lib/libengineGlut.so

echo "Copy built library to /usr/lib..."
echo "---------------------------------"
cp libengineGlut.so /usr/lib

cd ..

echo
echo "Building Mandelbrot"
echo
make



