/*
	���`�v�����P�̖@�ŉ����B
	Maximize:
		c * x
	Subject to:
		A * x <= b
		x >= 0
	�����ŁA(<=)�̓x�N�g���̑Ή�����v�f���S��(<=)�ł��邱�Ƃ�\��
	
	���I���ӁI
		�ő剻�AMAXIMIZE�ł���I
		�덷�E�I�[�o�[�t���[�ɂ͒��ӁI
		�v�Z�ʂ��ň��ł͎w�����炢�����炵���̂Œ��ӁI
		Unbounded, NoSolution�͂���������������悤�ɂȂ��Ă��邪�A
		���؂��Ă��Ȃ��̂ňႤ�����B����
	
	������
	n: �ϐ��̐�
	m: ���񎮂̐�
	A: Mat(m, Vec(n))
		A[i][j] �ŁA�ϐ�j���琧��i�ɑ������ޔ{�����w�肷��
	b: Vec(m)
		b[j] �Ő���j�̉E�ӂ��w�肷��
	c: Vec(n)
		c[i] �ŕϐ�i�̍ŏI�I�ȃX�R�A�ւ̑������ޔ{�����w�肷��
	
	�����񎮂̕ό`
	�E�ړI��minimize(�ŏ���)�̏ꍇ
		c[i]��S��*=-1
		�Ō�ɉ���*=-1
	�E���񂪓��l����(ax + by + cz + ... = ��)�̏ꍇ
		���񎮂̐���2�{�ɂ���(m *= 2)
		(A[j][i] = x)��(A[j][i] = x, A[m/2+j][i] = -x)�ɂ���
		(b[j] = x)��(b[j] = x, b[m/2+j] = -x)�ɂ���
	�E�ϐ������̒l���Ƃ肤��ꍇ
		�ϐ��̐���2�{�ɂ���(n *= 2)
		(A[j][i] = x)��(A[j][i] = x, A[j][n/2+i] = -x)�ɂ���
		(c[i] = x)��(c[i] = x, c[n/2+i] = -x)�ɂ���
	
	���ϐ��̊��蓖�Ă��擾�������Ƃ�
		��ԍŌ�Ɉȉ��̃R�[�h
		Vec v(n+m+1, 0);
		rep(i, m) v[id[n+i]] = D[i][n];
		��v��[0,n)���ϐ��̊��蓖�ĂɂȂ��Ă���
*/

typedef long double Num;
typedef vector<Num> Vec;
typedef vector<Vec> Mat;
const Num Inf = numeric_limits<Num>::infinity();
const Num NoSolution = numeric_limits<Num>::quiet_NaN();
#define IsSolution(x) (x == x)
const Num EPS = 1e-10;

Num simplex(const Mat& A, const Vec& b, const Vec& c) {
	const int m = A.size(), n = A[0].size();
	Mat D(m+1, Vec(n+1)); vi id(n+m+1);
	rer(i, 0, n+m) id[i] = i;
	rep(i, m) {
		rep(j, n) D[i][j] = -A[i][j];
		D[i][n] = b[i];
	}
	rep(j, n) D[m][j] = c[j];
	while(1) {
		int r = m, s = n+m;
		rep(i, m) if(D[i][n] < -EPS && id[n+r] > id[n+i]) r = i;
		rep(j, n) if(D[m][j] > EPS && id[s] > id[j]) s = j;
		if(r == m && s == n + m) break;
		if(id[n + r] < id[s]) {
			s = n + m;
			rep(j, n) if(D[r][j] > EPS && id[s] > id[j]) s = j;
		}else {
			r = m;
			rep(i, m) if(D[i][s] < -EPS && id[n+r] > id[n+i]) r = i;
		}
		if(r == m) { /* Unbounded */ return NoSolution; }
		if(s == n + m) { /* NoSolution */ return NoSolution; }
		swap(id[s], id[n+r]);
		D[r][s] = 1. / D[r][s];
		rer(j, 0, n) if(j != s) D[r][j] *= -D[r][s];
		rer(i, 0, m) if(i != r && abs(D[i][s]) > EPS) {
			rer(j, 0, n) if(j != s) D[i][j] += D[r][j] * D[i][s];
			D[i][s] *= D[r][s];
		}
	}
	return D[m][n];
}
