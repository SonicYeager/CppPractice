#include "pch.h"
#include <iostream>

void SwapPointers(void* &pLeft, void* &pRight) {
	void* pTemp = pLeft;
	pLeft = pRight;
	pRight = pTemp;
}

int main()
{
	void* pLeft = new int[0];
	void* pRight = new int[0];
	void* pOldLeft = pLeft;
	void* pOldRight = pRight; //missing semicol
	SwapPointers(pLeft, pRight);
	if (pLeft == pOldRight && pRight == pOldLeft){
		std::cout << "correct";
	}
	else {
		std::cout << "wrong";
	}

	&SwapPointers
}
