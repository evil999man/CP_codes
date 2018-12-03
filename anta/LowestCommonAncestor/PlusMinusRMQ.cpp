#pragma once

/*
	��{��O(n log n)�O�����̃A���S���Y��(Sparse Table, ST)�B
	�}1�Ȃ̂Ŕz��̊e�v�f��1bit�������������Ă��Ȃ����Ƃ𗘗p����B
	�����"word trick"�̂悤�Ȃ��̂�p���āA���������̃u���b�N���܂Ƃ߂Čv�Z����B
	��̓I�ɂ́Alog n/2�̃u���b�N("normalized block"�ƌĂ�)�S�Ăɑ΂��ău���b�N����RMQ��S�Ď��O�v�Z����B
	�����āA������傫���T�C�Y�̃u���b�N�́A�ulog n/2��؂�ŁvST�A���S���Y���Ɠ����悤�ɂ�DP�ŋ��߂�B
	log n/2�̃T�C�Y�̃u���b�N��O(��n)��ނ������݂��Ȃ��B���ꂼ���O(log^2 n)�̃e�[�u��������Ă�O(��n log^2 n) �� O(n)
	������傫���T�C�Y�̃u���b�N��(<= (n/(log n/2)) * (log n - log log n) <= 2*n/log n*log n = 2*n �� O(n))
*/
//Tested
template<typename Val, typename BlockSizeVal, int BlockSize>
class PlusMinusRMQ {
public:
	typedef unsigned BitSet;
	static const int BitSetSize = sizeof(BitSet) * CHAR_BIT;

private:
	BlockSizeVal table[1<<BlockSize][BlockSize][BlockSize];	//���
	BlockSizeVal (**blockTable)[BlockSize];	//normalized block�̃|�C���^
	Val *blockLeftValues, *sparseTable;
	int blocks, stHeight;

	void buildNormalizedBlockTable() {
		for(int i = 0; i < 1 << BlockSize; i ++) {
			BlockSizeVal x = BlockSizeVal(), mx = BlockSizeVal();
			for(int l = 0; l < BlockSize; l ++) {
				BlockSizeVal y = x, my = x;
				for(int r = l; r < BlockSize; r ++) {
					table[i][l][r] = my;
					if((i >> r & 1 ? -- y : ++ y) < my) my = y;
				}
				if((i >> l & 1 ? -- x : ++ x) < mx) mx = x;
			}
		}
	}

	//BlockSize < BitSetSize �����肷��
	void buildBlockTable(const BitSet a[], int n) {
		for(int i = 0, blockIndex = 0; i < n; i += BlockSize) {
			int floordivi = i / BitSetSize;
			BitSet word = a[floordivi] >> i % BitSetSize;
			if(floordivi != (i+BlockSize-1) / BitSetSize)
				word |= a[floordivi+1] << (BitSetSize - (i % BitSetSize));
			blockTable[blockIndex ++] = table[word & (1 << BlockSize) - 1];
		}
	}
	void buildBlockLeftValues(const BitSet a[], int n, Val leftValue) {
		Val x = leftValue;
		for(int i = 0, blockIndex = 0; i < n; ++ i) {
			if(i % BlockSize == 0)
				blockLeftValues[blockIndex ++] = x;
			if(a[i / BitSetSize] >> i % BitSetSize & 1) -- x; else ++ x;
		}
	}
	void buildSparseTable(int n, int blocks) {
		Val *b = sparseTable;
		if(stHeight) for(int i = 0; i < blocks; i ++)
			b[i] = blockLeftValues[i] + blockTable[i][0][BlockSize-1];
		for(int t = 1; t*2 < blocks; t *= 2) {
			memcpy(b + blocks, b, blocks * sizeof(Val)); b += blocks;
			for(int i = 0; i < blocks - t; ++ i)
				if(b[i + t] < b[i]) b[i] = b[i + t];
		}
	}

public:
	PlusMinusRMQ() {
		blocks = stHeight = 0;
		blockLeftValues = sparseTable = NULL; blockTable = NULL;
		buildNormalizedBlockTable();
	}
	~PlusMinusRMQ() {
		destruct();
	}

	//a�̓r�b�g��B1���}�C�i�X��0���v���X
	//�I�d�v�Ia�̗v�f����n-1�ł��邪�A�ȒP�̂���(n / BitSetSize + 2)�����͊m�ۂ��āA�Ō��0���߂���Ă���Ƃ���
	void build(const BitSet a[], int n, Val leftValue = Val()) {
		blocks = (n + BlockSize - 1) / BlockSize;
		stHeight = 0; while(1 << stHeight < blocks) ++ stHeight;
		typedef BlockSizeVal (*P)[BlockSize];
		delete[] blockTable; blockTable = new P[blocks];
		delete[] blockLeftValues; blockLeftValues = new Val[blocks];
		delete[] sparseTable; sparseTable = new Val[blocks * stHeight];

		buildBlockTable(a, n);
		buildBlockLeftValues(a, n, leftValue);
		buildSparseTable(n, blocks);
	}
	
	//[l, r]�̕�ԁBl <= r �����肷��B
	Val query(int l, int r) const {
		int x = l / BlockSize, y = r / BlockSize, z = y - x, k = 0, e = 1, s;
		if(z == 0) return blockLeftValues[x] + blockTable[x][l % BlockSize][r % BlockSize];
		Val edge = std::min(
			blockLeftValues[x] + blockTable[x][l % BlockSize][BlockSize-1],
			blockLeftValues[y] + blockTable[y][0][r % BlockSize]);
		if(z == 1) return edge;
		z -= 2;
		s = ((z & 0xffff0000) != 0) << 4; z >>= s; e <<= s; k |= s;
		s = ((z & 0x0000ff00) != 0) << 3; z >>= s; e <<= s; k |= s;
		s = ((z & 0x000000f0) != 0) << 2; z >>= s; e <<= s; k |= s;
		s = ((z & 0x0000000c) != 0) << 1; z >>= s; e <<= s; k |= s;
		s = ((z & 0x00000002) != 0) << 0; z >>= s; e <<= s; k |= s;
		return std::min(edge, std::min(
			sparseTable[x + 1 + blocks * k],
			sparseTable[y + blocks * k - e]));
	}

	void destruct() {
		blocks = stHeight = 0;
		delete[] blockTable;
		delete[] blockLeftValues;
		delete[] sparseTable;
		blockLeftValues = sparseTable = NULL; blockTable = NULL;
	}
};

//PlusMinusOneRMQ�p�B
//typedef PlusMinusOneRMQ<ValAndPos<int, int>, ValAndPos<char, char>, BlockSize>
//���ȂǂƂ��āA�ŏ��l�̈ʒu���Ԃ��悤�ɂł���
template<typename Val, typename Pos>
struct ValAndPos {
	Val val; Pos pos;
	ValAndPos(): val(), pos() { }
	ValAndPos(const Val &val_, int pos_): val(val_), pos(pos_) { }
	bool operator<(const ValAndPos &y) const { return val < y.val; }
	//����tricky�ȉ��Z�q�B�}1�Ȃ̂ŁA�����K�p���Ă����Ɉꏏ�Ɉʒu���ړ��ł���B
	ValAndPos &operator++() { ++ val; ++ pos; return *this; }
	ValAndPos &operator--() { -- val; ++ pos; return *this; }
};
template<typename Val1, typename Pos1, typename Val2, typename Pos2>
ValAndPos<Val1, Pos1> operator+(const ValAndPos<Val1, Pos1> &x, const ValAndPos<Val2, Pos2> &y) {
	return ValAndPos<Val1, Pos1>(x.val + y.val, x.pos + y.pos);
}
