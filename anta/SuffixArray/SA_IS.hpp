#pragma once
#include "SuffixArray.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

template<typename AlphaT>
static void sa_is_countingAlphabets(const AlphaT *str, Index n, int AlphaSize, std::vector<Index> &bucketOffsets, bool b = false) {
	if(b || (int)bucketOffsets.size() / 2 >= AlphaSize) {
		std::vector<Index>::iterator alphabetCounts =
			b ? bucketOffsets.begin() : bucketOffsets.begin() + AlphaSize;
		std::fill(alphabetCounts, alphabetCounts + AlphaSize, 0);
		for(Index i = 0; i < n; i ++)
			alphabetCounts[(int)str[i]] ++;
	}
}

template<typename AlphaT>
static void sa_is_getBucketOffsets(const AlphaT *str, Index n, bool dir, int AlphaSize, std::vector<Index> &bucketOffsets) {
	//AlphaSize���傫���ꍇ�ɂ�bucketOffset���߂邽�т�alphabet�𐔂��ă������ʂ����Ȃ����A
	//AlphaSize���������ꍇ�ɂ�bucketOffset��alphabetCounts�ƕʂ̏ꏊ�ɒu�����Ƃɂ���B
	std::vector<Index>::iterator alphabetCounts;
	if((int)bucketOffsets.size() / 2 < AlphaSize) {
		sa_is_countingAlphabets(str, n, AlphaSize, bucketOffsets, true);
		alphabetCounts = bucketOffsets.begin();
	}else alphabetCounts = bucketOffsets.begin() + AlphaSize;
	Index cumsum = 1;	//'$'�̕�
	if(dir) {
		for(int i = 0; i < AlphaSize; i ++) {
			cumsum += alphabetCounts[i];
			bucketOffsets[i] = cumsum;
		}
	}else {
		for(int i = 0; i < AlphaSize; i ++) {
			Index x = alphabetCounts[i];
			bucketOffsets[i] = cumsum;
			cumsum += x;
		}
	}
}


template<typename AlphaT>
static void sa_is_inducedSort(const AlphaT *str, Index n, int AlphaSize, const std::vector<bool> &types, Index *sa, std::vector<Index> &bucketOffsets) {
	sa_is_getBucketOffsets(str, n, false, AlphaSize, bucketOffsets);
	for(Index i = 0; i < n; i ++) {
		Index j = sa[i] - 1;
		if(j >= 0 && !types[j]) sa[bucketOffsets[(int)str[j]] ++] = j;
	}

	sa_is_getBucketOffsets(str, n, true, AlphaSize, bucketOffsets);
	for(Index i = n; i >= 1; i --) {
		Index j = sa[i] - 1;
		if(j >= 0 && types[j]) sa[-- bucketOffsets[(int)str[j]]] = j;
	}
}

//str��[0,n)���L���Ŕԕ��͊܂܂�Ȃ��Bsa��[0,n]���L��
template<typename AlphaT>
static void sa_is_rec(const AlphaT *str, Index n, int AlphaSize, Index *sa, std::vector<Index> &bucketOffsets) {
	std::vector<bool> types(n+1);
	types[n-1] = 0; types[n] = 1;
	for(Index i = n-2; i >= 0; i --)
		types[i] = str[i] < str[i+1] || (str[i] == str[i+1] && types[i+1]);

	sa_is_countingAlphabets(str, n, AlphaSize, bucketOffsets);
	sa_is_getBucketOffsets(str, n, true, AlphaSize, bucketOffsets);
	std::fill(sa, sa + n + 1, -1);
	for(Index i = 1; i < n; i ++)
		if(types[i] && !types[i-1]) sa[-- bucketOffsets[(int)str[i]]] = i;
	sa[0] = n;
	sa_is_inducedSort(str, n, AlphaSize, types, sa, bucketOffsets);

	Index n1 = 0;
	for(Index i = 0; i <= n; i ++) {
		Index j = sa[i];
		if(j > 0 && types[j] && !types[j-1]) sa[n1 ++] = j;
	}

	//LMS substrings��ԍ��t������Bsa[0..n1-1]�Ƀ\�[�g����Ă���B
	//�������̂��߂�sa�̉E�������o�b�t�@�ɗ��p����B
	//����ɂ�����pos�̏����Ő����\�[�g���邱�Ƃ𓯎��ɍs���B
	//������LMS substring���A�����Č���Ȃ����Ƃ�LMS substring�̐���n/2�ȉ��ł��邱�Ƃ𗘗p���ĂȂ�Ƃ�1�̔z��ł��
	Index *buffer = sa + n1;
	std::fill(buffer, sa + n + 1, -1);
	Index uniqueLMSCount = 0, prevPos = -1;
	assert(sa[0] == n);
	buffer[sa[0] / 2] = uniqueLMSCount ++;	//'$'
	for(Index i = 1; i < n1; i ++) {
		Index pos = sa[i]; bool diff = false;
		if(prevPos == -1) diff = true;
		else for(Index j = pos, k = prevPos; ; j ++, k ++) {
				if(str[j] != str[k] || types[j] != types[k]) {
					diff = true;
					break;
				}else if(j != pos && ((types[j] && !types[j-1]) || (types[k] && !types[k-1])))
					break;
			}
		if(diff) {
			uniqueLMSCount ++;
			prevPos = pos;
		}
		buffer[pos / 2] = uniqueLMSCount - 1;
	}
	for(Index i = n, j = n; i >= n1; i --)
		if(sa[i] >= 0) sa[j --] = sa[i];

	Index *sa1 = sa, *s1 = sa + n + 1 - n1;
	if(uniqueLMSCount == n1)
		for(Index i = 0; i < n1; i ++) sa1[s1[i]] = i;
	else
		sa_is_rec<Index>(s1, n1 - 1, uniqueLMSCount, sa1, bucketOffsets);

	sa_is_countingAlphabets(str, n, AlphaSize, bucketOffsets);
	sa_is_getBucketOffsets(str, n, true, AlphaSize, bucketOffsets);
	for(Index i = 1, j = 0; i <= n; i ++)
		if(types[i] && !types[i-1]) s1[j ++] = i;
	for(Index i = 0; i < n1; i ++) sa1[i] = s1[sa1[i]];
	std::fill(sa + n1, sa + n + 1, -1);
	for(Index i = n1-1; i >= 1; i --) {
		Index j = sa[i]; sa[i] = -1;
		sa[-- bucketOffsets[(int)str[j]]] = j;
	}
	sa_is_inducedSort(str, n, AlphaSize, types, sa, bucketOffsets);
}

//suffixArray��(n+1)�̃T�C�Y
static void buildSuffixArray(const Alpha *str, Index n, int AlphaSize, Index *suffixArray) {
	if(n == 0) suffixArray[0] = 0;
	else {
		//I = sizeof(Index) * CHAR_BITS �Ƃ���
		//suffixArray + bucketOffsets + types + �֐����[�J���ϐ�
		//= n*I + max(AlphaSize, n/2)*I + 2*n + O(log n) bits
		//I = 4 * 32��AlphaSize���\���������Ƃ����:
		//(6+1/16) * n + O(log n) bytes
		std::vector<Index> bucketOffsets(std::max(AlphaSize, (n+1) / 2) + 1);
		sa_is_rec<Alpha>(str, n, AlphaSize, &suffixArray[0], bucketOffsets);
	}
}

static void buildSuffixArray(const Alpha *str, Index n, Index *suffixArray) {
	Alpha maxElem = *std::max_element(str, str + n);
	assert(maxElem+0 < std::numeric_limits<int>::max());
	buildSuffixArray(str, n, (int)maxElem+1, suffixArray);
}
