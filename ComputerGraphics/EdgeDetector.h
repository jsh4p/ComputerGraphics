#pragma once

#include <string>
#include "Image.h"

using namespace std;
typedef vector <vector <vector<int>>> m_nx;

	const m_nx LaplaceMask {
		{ {0,  1,  0},
		  {1, -4,  1},
		  {0,  1,  0} }
	};

	const m_nx RobertsMask {
		{ {1,  0},
		  {0, -1} },
					 { { 0, 1},
					   {-1, 0} }
	};

	const m_nx SobelMask {
		{ {1, 0, -1},
		  {2, 0, -2},
		  {1, 0, -1} }, 
						{ { 1,  2,  1},
						  { 0,  0,  0},
						  {-1, -2, -1} }
	};

class EdgeDetector {
public:
	static Image ApplyMask(const Image& image, const m_nx& mask);
	static Image LaplaceOperator(const Image& image);
	static Image RobertsOperator(const Image& image);
	static Image SobelOperator(const Image& image);
private:
};

