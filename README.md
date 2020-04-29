# licenta
cd Engine
make
cd ..
make
export LD_LIBRARY_PATH=./Engine:$LD_LIBRARY_PATH
./mandelbrot
