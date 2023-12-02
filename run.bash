echo This can take some time, there are over 30000 lines of code to compile in the libraries...
# g++ -pthread -std=c++17 -o main main.cpp; ./main
g++ -pthread -std=c++17 -c ./helpers/algorithms/cautious.cpp -o cautious.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/dog.cpp -o dog.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/hungry.cpp -o hungry.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/inyourface.cpp -o inyourface.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/onedirection.cpp -o onedirection.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/random.cpp -o random.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/sim.cpp -o sim.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms/terminator.cpp -o terminator.o;
g++ -pthread -std=c++17 -c ./helpers/algorithms.cpp -o algorithms.o;
g++ -pthread -std=c++17 -c ./helpers/astar.cpp -o astar.o;
g++ -pthread -std=c++17 -c ./helpers/movement.cpp -o movement.o;
g++ -pthread -std=c++17 -c ./helpers/simulator.cpp -o simulator.o;
g++ -pthread -std=c++17 -c ./helpers/snakelib.cpp -o snakelib.o;
g++ -pthread -std=c++17 -c ./helpers/timing.cpp -o timing.o;
g++ -pthread -std=c++17 -c ./main.cpp -o main.o;
g++ -pthread -std=c++17 cautious.o dog.o hungry.o inyourface.o onedirection.o random.o sim.o terminator.o algorithms.o astar.o movement.o simulator.o snakelib.o main.o timing.o -o a ;
# g++ -pthread -std=c++17 -c a.cpp -o a.o
# g++ -pthread -std=c++17 -c b.cpp -o b.o
# g++ -pthread -std=c++17 a.o b.o -o a
# ./a
./a