
g++ -c ../Number/Number.cpp -o ../Number/Number.o -fpic
g++ -c ../Vector/Vector.cpp -o ../Vector/Vector.o -fpic -INumber
g++ -shared -o ../Vector/libVector.so ../Vector/Vector.o ../Number/libNumber.a
g++ main.cpp -IVector ../Vector/libVector.so -INumber ../Number/libNumber.a

./main
