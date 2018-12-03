/*
	Fenwick��
	Binary Indexed Tree, BIT �Ƃ��Ă΂��
	
	�ݐϘa�ERMQ�����ł���B
	�Ez[k] = z[k] + a �ƍX�V����
	�Ez[i] + z[i+1] + ... + z[j] ���v�Z����
	�����ŁA+���Z�q�͉��Z�łȂ��Ă�min,max�₻�̑��A
		�������C���� ������K�v������B
	���Z�q�ɂ���Ă͋t���Z�q-������Ȃ�A
		ft.add(x - ft.sum(i, i+1))
		�Ƃ��邱�Ƃɂ���Ĉ��l�̐ݒ肪�ł���B
	
	���t�񕪒T���؂Ɋ܂܂�邪�A�P���ȃ��[�v�Ȃ̂ő��x�����ɑ���
*/

//�Vver. �f�[�^�̎������ɋ�ver.�Ƃ̌݊����������̂Œ��ӁB
struct FenwickTree {
	typedef int T;
	vector<T> v; int highestOneBit;
	FenwickTree() { }
	void init(int n) {
		highestOneBit = 1; while(highestOneBit * 2 <= n) highestOneBit *= 2;
		v.assign(n+1, T());
	}

	template<typename U> void init(const U *a, int n) {
		highestOneBit = 1; while(highestOneBit * 2 <= n) highestOneBit *= 2;
		v.resize(n+1);
		for(int i = 0; i < n; i ++) v[i+1] = a[i];
		for(int i = 1; i <= n; i ++) {
			int j = i + (i & -i);
			if(j <= n) v[j] += v[i];
		}
	}

	void add(int i, T x) {
		int n = v.size();
		for(i ++; i < n; i += i & -i) v[i] += x;
	}
	T sum(int i) const {	//[0, i)
		T r = 0;
		for( ; i > 0; i -= i & -i) r += v[i];
		return r;
	}
	T sum(int left, int right) const {	//[left, right)
		return sum(right) - sum(left);
	}
	int kth(T x) const {	//x <= sum[0,i) �ƂȂ�ŉE(�E�ł��邱�Ƃɒ��ӁI)��i��Ԃ�
		int n = v.size(), i = 0;
		for(int b = highestOneBit; b != 0 && i < n; b >>= 1) {
			if(i + b < n) {
				int t = i + b; T u = v[t];
				if(x >= u) { i = t; x -= u; }
			}
		}
		return i;	//�����Ŏc���x���Ӗ������̂œK���ɂł���
	}
};


//========================================================================
//��ver.
struct FenwickTree {
	typedef ll T;
	vector<T> v;
	FenwickTree(int n): v(n, 0) {}
	void add(int i, T x) {
		for(; i < (int)v.size(); i |= i+1) v[i] += x;
	}
	T sum(int i) {	//[0, i)
		T r = 0;
		for(-- i; i >= 0; i = (i & (i+1)) - 1) r += v[i];
		return r;
	}
	T sum(int left, int right) {	//[left, right)
		return sum(right) - sum(left);
	}
};

//3D�B���[�v�𑝂₹�Ύ����͕ς�����
struct FenwickTree3D {
	typedef long long Val;
	static const int MaxN = 101;
	Val data[MaxN][MaxN][MaxN];
	FenwickTree3D() { }
	void init() { mset(data, 0); }
	inline void add(int x, int y, int z, Val v) {
		for(int i = x; i < MaxN; i |= i+1)
			for(int j = y; j < MaxN; j |= j+1)
				for(int k = z; k < MaxN; k |= k+1)
					data[i][j][k] += v;
	}
	inline Val sum(int x, int y, int z) const {
		x --, y --, z --;
		Val r = 0;
		for(int i = x; i >= 0; i = (i & (i+1)) - 1)
			for(int j = y; j >= 0; j = (j & (j+1)) - 1)
				for(int k = z; k >= 0; k = (k & (k+1)) - 1)
					r += data[i][j][k];
		return r;
	}
	inline Val sum2(int x1, int y1, int z1, int x2, int y2, int z2) const {
		Val r = 0;
		r += sum(x2, y2, z2);
		r -= sum(x1, y2, z2);
		r -= sum(x2, y1, z2);
		r -= sum(x2, y2, z1);
		r += sum(x1, y1, z2);
		r += sum(x1, y2, z1);
		r += sum(x2, y1, z1);
		r -= sum(x1, y1, z1);
		return r;
	}
};

//�������ŁB�K�؂ɍċA�̃O���[�o�����E�A�����[�������邱��
struct MultiDimensionalFenwickTree {
	typedef char Index;
	typedef ll Val;
	vector<Index> dim;
	vector<Val> data;
	MultiDimensionalFenwickTree(const vector<Index> &dimension): dim(dimension) {
		int n = 1;
		rep(i, dim.size()) n *= dim[i];
		data.assign(n, 0);
	}
	inline void add(const vector<Index> &indices, Val x) {
		add_rec(indices, 0, 0, x);
	}
	inline Val sum(const vector<Index> &indices) const {
		return sum_rec(indices, 0, 0);
	}
	inline Val sum2(const vector<Index> &a, const vector<Index> &b) const {
		vector<Index> t(a.size());
		return sum2_rec(0, a, b, t);
	}
private:
	void add_rec(const vector<Index> &indices, int k, int t, Val x) {
		int d = dim[k];
		t *= d;
		if(k+1 == dim.size()) {
			Val *p = &data[t];
			for(int i = indices[k]; i < d; i |= i+1)
				p[i] += x;
		}else
			for(int i = indices[k]; i < d; i |= i+1)
				add_rec(indices, k+1, t + i, x);
	}
	Val sum_rec(const vector<Index> &indices, int k, int t) const {
		int d = dim[k];
		t *= d;
		Val res = 0;
		if(k+1 == dim.size()) {
			const Val *p = &data[t];
			for(int i = indices[k]; i > 0; i -= i & -i)
				res += p[i-1];
		}else
			for(int i = indices[k]; i > 0; i -= i & -i)
				res += sum_rec(indices, k+1, t + i - 1);
		return res;
	}
	Val sum2_rec(int d, const vector<Index> &a, const vector<Index> &b, vector<Index> &t) const {
		if(d == dim.size())
			return sum(t);
		Val r = 0;
		t[d] = b[d];
		r += sum2_rec(d+1, a, b, t);
		t[d] = a[d];
		r -= sum2_rec(d+1, a, b, t);
		return r;
	}
};


