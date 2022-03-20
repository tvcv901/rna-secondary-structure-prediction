EQoutput.exe: eventQueue.o Soutput.exe
	g++ eventQueue.o -o EQoutput.exe

Soutput.exe: status.o
	g++ status.o -o Soutput.exe

eventQueue.o: eventQueue.cpp EQBalancedBST.cpp
	g++ -c eventQueue.cpp
	g++ -c EQBalancedBST.cpp

status.o: status.cpp SBalancedBST.cpp
	g++ -c status.cpp
	g++ -c SBalancedBST.cpp

clean:
	del .\*.o .\*.exe .\*.gch