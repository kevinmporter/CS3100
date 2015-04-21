Build with the following command line: (the -Wl,-rpath=/usr/local/lib64 options are needed because g++ is misconfigured on Thor)
$ g++ -Wall -Werror -O3 *.cpp -o game.out -Wl,-rpath=/usr/local/lib64

Run with 
./game.out 0 for computer vs. computer
./game.out 2 for two player mode

