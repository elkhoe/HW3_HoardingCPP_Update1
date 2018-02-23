
all:
	g++ -Wall -Werror -std=c++14 -o hoarding.out *.cpp

hoarding.out: main.o GameState.o PropertyManager.o Board.o Move.o Space.o Property.o Player.o PropertySet.o Rules.o DiceRoller.o CSVReader.o Go.o MonopolyUtility.o
	g++ -g -Wall -Werror -o hoarding.out main.o GameState.o PropertyManager.o Board.o Move.o Space.o Property.o Player.o PropertySet.o Rules.o DiceRoller.o CSVReader.o Go.o MonopolyUtility.o

main.o: main.cpp GameState.h
	g++ -g -Wall -Werror -c main.cpp

GameState.o: GameState.cpp GameState.h MonopolyUtility.h Move.h PropertyManager.h DiceRoller.h
	g++ -g -Wall -Werror -c GameState.cpp

PropertyManager.o: PropertyManager.cpp PropertyManager.h Board.h Player.h
	g++ -g -Wall -Werror -c PropertyManager.cpp

Board.o: Board.cpp Board.h MonopolyUtility.h Player.h
	g++ -g -Wall -Werror -c Board.cpp

Move.o: Move.cpp Move.h
	g++ -g -Wall -Werror -c Move.cpp

Space.o: Space.cpp Space.h MonopolyUtility.h Player.h Auction.h GameState.h Auction.h
	g++ -g -Wall -Werror -c Space.cpp

Property.o: Property.cpp Property.h Player.h
	g++ -g -Wall -Werror -c Property.cpp

Player.o: Player.cpp Player.h GameState.h
	g++ -g -Wall -Werror -c Player.cpp

PropertySet.o: PropertySet.cpp PropertySet.h
	g++ -g -Wall -Werror -c PropertySet.cpp

Rules.o: Rules.cpp Rules.h
	g++ -g -Wall -Werror -c Rules.cpp

DiceRoller.o: DiceRoller.cpp DiceRoller.h MonopolyUtility.h
	g++ -g -Wall -Werror -c DiceRoller.cpp

CSVReader.o: CSVReader.cpp CSVReader.h
	g++ -g -Wall -Werror -c CSVReader.cpp

Go.o: Go.cpp Go.h
	g++ -g -Wall -Werror -c Go.cpp

MonopolyUtility.o: MonopolyUtility.cpp MonopolyUtility.h
	g++ -g -Wall -Werror -c Utility.cpp

clean:
	rm *.o hoarding.out
