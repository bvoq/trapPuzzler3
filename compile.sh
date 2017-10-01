mv src/main2.cpp .
make clean
make
mv main2.cpp src
cd bin
if [ $(uname | grep MSYS | wc -l) == 1 ]
	then
	echo Windows detected
	./trapPuzzler3.exe
else
	echo no Windows detected
	./trapPuzzler3
fi
cd ..
