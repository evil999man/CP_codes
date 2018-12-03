/*
	�K�E�X�̏����@�B�ϐ��̌��Ǝ��̌�����v�����A����������������B
	O(n^3)�B�������s��̏�Z���d���B
	�I�����̃P�[�X����Verify����Ă��Ȃ��I
	(A x^T = b^T) �������B^T�͂��ꂪ�c�ł���Ƃ������ƁB
		A�����ɂ��邱�Ƃɒ��ӁB[i][j]��j����i�ɑ������ށB
	(a xn = b xm)�Ƃ����`�̎���(a xn - b xm = 0) �Ƃ���B
	���l��(a x + b = c)��(a x = c - b)�Ƃ���B
	���s��ݏ�Ōv�Z�ł���Q�����̋Ɍ������߂�
	��geometric series�̖����a�Ƃ����l�������킩��₷���I�������s��ɂ��K�p�ł���B
	�m������Ғl�ŋɌ�����肽�����Ƃ�����B����͘A���������ŕ\���ł���B
	�E���̍s����}�C�i�X�ɂ���
	�EA[k][k] += 1	//���ƍ��킹�āA(a xn + b xm = xp)��\���Ă���
	�E�Ɍ�����肽����Ԃ͌W��1�����H
	�Eb[�Ɍ�����肽�����] = 1
	�Ex[�ŏ��̏��]������
	���킩���ĂȂ�
	��DP�����������΂������Ƃ�����
	����Ԑ����傫�����ɂ�O(n^3)�͂ł��Ȃ��̂Œ���
	���v�����x�ɂ���Ă͍s��ݏ�̂ق����������Ƃ�����(�s��̏�Z1��͑���)
	
*/

//�z��o�[�W����(vector�o�[�W�������150%���炢����)
typedef double Num;
const int VecSize = ���������������邱��;
struct Vec {
	Num a[VecSize];
	Num &operator[](int i) { return a[i]; }
	Vec() {mset(a, 0);}
};
struct Mat {
	Num a[VecSize][VecSize];
	Num *operator[](int i) { return a[i]; }
	Mat() {mset(a, 0);}
};

Vec gaussian_elimination(Mat A, Vec b) {
	const int n = VecSize, m = VecSize;
	int pi = 0, pj = 0;
	while(pi < n && pj < m) {
		reu(i, pi+1, n)
			if(fabs(A[i][pj]) > fabs(A[pi][pj])) {
				rep(k, m) swap(A[i][k], A[pi][k]);
				swap(b[i], b[pi]);
			}
		if(fabs(A[pi][pj]) > 1e-7) {	//�I���ӁI
			Num d = A[pi][pj];
			rep(j, m) A[pi][j] /= d;
			b[pi] /= d;
			reu(i, pi+1, n) {
				Num k = A[i][pj];
				rep(j, m) A[i][j] -= k * A[pi][j];
				b[i] -= k * b[pi];
			}
			pi ++;
		}
		pj ++;
	}
	reu(i, pi, n) if(fabs(b[i]) > 0) return Vec();	//Inconsistent
	if(pi < m || pj < m) return Vec();	//Ambiguous
	for(int j = m-1; j >= 0; j --)
		rep(i, j)
			b[i] -= b[j] * A[i][j];
	return b;
}

//vector�o�[�W����
typedef double Num;
typedef vector<Num> Vec;
typedef vector<Vec> Mat;

Vec gaussian_elimination(Mat A, Vec b) {
	const int n = A.size(), m = A[0].size();
	int pi = 0, pj = 0;
	while(pi < n && pj < m) {
		reu(i, pi+1, n)
			if(abs(A[i][pj]) > abs(A[pi][pj]))
				A[i].swap(A[pi]), swap(b[i], b[pi]);
		if(abs(A[pi][pj]) > 0) {
			Num d = A[pi][pj];
			rep(j, m) A[pi][j] /= d;
			b[pi] /= d;
			reu(i, pi+1, n) {
				Num k = A[i][pj];
				rep(j, m) A[i][j] -= k * A[pi][j];
				b[i] -= k * b[pi];
			}
			pi ++;
		}
		pj ++;
	}
	reu(i, pi, n) if(abs(b[i]) > 0) return Vec();	//Inconsistent
	if(pi < m || pj < m) return Vec();	//Ambiguous
	for(int j = m-1; j >= 0; j --)
		rep(i, j)
			b[i] -= b[j] * A[i][j];
	return b;
}

//���܂�
void print_equations(Mat &A, Vec &b) {
	int n = VecSize, m = VecSize;
	rep(i, n) {
		vector<Num> a; vi v;
		rep(j, m) if(A[i][j] != 0) a.push_back(A[i][j]), v.push_back(j);
		if(a.empty()) {
			if(b[i] == 0) continue;
			cout << "  0";
		}else {
			rep(j, a.size()) {
				cout.width(4);
				if(j == 0) {
					if(a[j] == 1) cout << " ";
					else cout << a[j] << "*";
				} else if(abs(a[j]) == 1) cout << " ";
				else cout << abs(a[j]) << "*";
				cout << "x";
				cout.width(2), cout.flags(cout.left);
				cout << v[j] << (j+1 == a.size() ? "" : (a[j+1] < 0 ? " -" : " +"));
				cout.flags(cout.right);
			}
		}
		cout << " = "; cout.width(3), cout << b[i] << endl;
	}
}

//mod2�o�[�W����
//<https://judge.npca.jp/submissions/detail/4658>
bool gaussian_elimination(vector<vector<bool> > A, vector<bool> b) {
	const int n = A.size(), m = A[0].size();
	vector<bool> used(n);
	rep(j, m) {
		int i = 0;
		while(i < n && (used[i] || !A[i][j]))
			i ++;
		if(i == n) continue;
		used[i] = true;
		rep(k, n) if(!used[k] && A[k][j]) {
			rep(l, m)
				A[k][l] = A[k][l] ^ A[i][l];
			b[k] = b[k] ^ b[i];
		}
	}
	rep(i, n) if(!used[i] && b[i]) return false;
	return true;
}


