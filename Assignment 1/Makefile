EQoutput.exe: eventQueue.o Soutput.exe main.exe test.exe
	g++ eventQueue.o -o EQoutput.exe

Soutput.exe: status.o
	g++ status.o -o Soutput.exe

main.exe: main.o
	g++ main.o -o main.exe

test.exe: test.o
	g++ test.o -o test.exe

eventQueue.o: eventQueue.cpp EQBalancedBST.cpp
	g++ -c eventQueue.cpp
	g++ -c EQBalancedBST.cpp

status.o: status.cpp SBalancedBST.cpp
	g++ -c status.cpp
	g++ -c SBalancedBST.cpp

main.o: main.cpp
	g++ -c main.cpp

test.o: test.cpp
	g++ -c test.cpp

clean:
	del .\*.o .\*.exe .\*.gch .\output.txt