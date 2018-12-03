#pragma once
#include "SuffixArray.hpp"
#include <cassert>
#include <iostream>

//inverseSuffixArray�̓T�C�Y(n+1)
static void computeInverseSuffixArray(const Index *suffixArray, Index n, Index *inverseSuffixArray) {
	for(Index i = 0; i <= n; i ++)
		inverseSuffixArray[suffixArray[i]] = i;
}
