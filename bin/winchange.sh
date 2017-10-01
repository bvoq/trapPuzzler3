#!/bin/sh

rm -rf ｔｒａｐｐｕｚｚｌｅｒwin
mkdir ｔｒａｐｐｕｚｚｌｅｒwin
cp -a data ｔｒａｐｐｕｚｚｌｅｒwin/data
cp READMEWIN.txt ｔｒａｐｐｕｚｚｌｅｒwin/README.txt
cp trapPuzzler3.exe ｔｒａｐｐｕｚｚｌｅｒwin/ｔｒａｐｐｕｚｚｌｅｒ.exe 
cp *.dll ｔｒａｐｐｕｚｚｌｅｒwin/
zip -r ｔｒａｐｐｕｚｚｌｅｒwin.zip ｔｒａｐｐｕｚｚｌｅｒwin
rm -rf ｔｒａｐｐｕｚｚｌｅｒwin

