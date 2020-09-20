main: aStruct.o bFuncDir.o cFuncArch.o dFuncLin.o fFuncPap.o xFuncOb1.o xFuncOb2.o
			g++ main.cpp -o obligatorio aStruct.o bFuncDir.o cFuncArch.o dFuncLin.o fFuncPap.o xFuncOb1.o xFuncOb2.o

#clases
aStruct.o: aStruct.cpp aStruct.h
			g++ aStruct.cpp -o aStruct.o
