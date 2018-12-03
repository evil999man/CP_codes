#pragma once
#include "SuffixArray.hpp"
#include <algorithm>

//KLAAP algorithm <http://www.cs.iastate.edu/~cs548/references/linear_lcp.pdf>
//lcpArray[i]��suffixArray[i]��suffixArray[i+1]��LCP�̒�����ێ�����(������lcpArray[n] = 0)
//	�����lcp(suffixArray[i-1],suffixArray[i])�Ƃ�����̂���ʓI�Ȃ̂Œ��ӁB
//	'$'���ő�̂��̂Ƃ��Ĉ����Ă��镶����������suffixArray�������̂ŁA����lcpArray�Ɠ����ɂȂ�悤�ɂ��Ă���B
//lcpArray�̓T�C�Y(n+2)
static void computeLCPArray(const Alpha *str, const Index *suffixArray, const Index *inverseSuffixArray, Index n, Index *lcpArray) {
	Index h = 0;
	for(Index i = 0; i < n; i ++) {
		Index pos = inverseSuffixArray[i];
		Index j = suffixArray[pos-1];
		Index hbound = std::min(n - j, n - i);
		for(Index k = 0; h < hbound && str[i+h] == str[j+h]; ++ h) ;
		lcpArray[pos-1] = h;
		if(h > 0) -- h;
	}
	lcpArray[n] = lcpArray[n+1] = 0;
}
