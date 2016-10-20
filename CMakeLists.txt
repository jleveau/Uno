# cmake_minimum_required(VERSION <specify CMake version here>)
project(Graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/graph/Graph.h src/graph/Node.cpp src/graph/Node.h src/graph/Edge.cpp src/graph/Edge.h src/cards/Card.cpp src/cards/Card.h src/graph/Graph.cpp src/cards/CardReader.cpp src/cards/CardReader.h src/builder/GraphBuilder.cpp src/builder/GraphBuilder.h src/builder/BuilderCard.h src/builder/BuilderPotatoes.h src/builder/DrawingBuilderPotatoes.cpp src/builder/DrawingBuilderPotatoes.h COLOR.h src/solvers/PotatoesSolver.cpp src/solvers/PotatoesSolver.h src/solvers/Solver.cpp src/solvers/Solver.h src/solvers/SolverItf.h src/solvers/BruteSolver.cpp src/solvers/BruteSolver.h src/solvers/Signature.cpp src/solvers/Signature.h)
add_executable(Graph ${SOURCE_FILES})