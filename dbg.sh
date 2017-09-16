rm bin/trapPuzzler3_debug
mv src/main2.cpp main2.cpp
make Debug
mv main2.cpp src
cd bin
echo r | gdb trapPuzzler3_debug
cd ..
