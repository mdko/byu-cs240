//test.cpp
//for running unit tests
#include <iostream>
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "ChessBoard.h"
#include "BoardPosition.h"
#include "XMLHandler.h"

int main() {

	bool success = true;
	
	/*std::cout << "---------------Running Unit Tests---------------" << std::endl;
	std::cout << "***\n***\n***\n***\n***\n***" << std::endl;
	std::cout << "------------All Unit Tests Completed------------" << std::endl;*/
	
	if (!King::Test(std::cout))
		success = false;
	if (!Queen::Test(std::cout))
		success = false;
	if (!Rook::Test(std::cout))
		success = false;
	if (!Bishop::Test(std::cout))
		success = false;
	if (!Knight::Test(std::cout))
		success = false;
	if (!Pawn::Test(std::cout))
		success = false;
		
	if (success)
		std::cout << "Tests succeeded!" << std::endl;
	else
		std::cout << "Tests Failed!" << std::endl;
	
	return 0;
}
