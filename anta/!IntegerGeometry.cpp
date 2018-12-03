/*
	���x�ɂ͒��ӁB�K�v�ɉ����ăC�����C���������邱��
*/

struct P {
	typedef int T; typedef ll T2;	//T2��{a*b | a:T, b:T}���܂ރ^�C�v
	T x, y;
	P(T x_, T y_): x(x_), y(y_) {}
	P(): x(0), y(0) {}
};
inline bool operator==(const P& a, const P& b) { return a.x == b.x && a.y == b.y; }
inline bool operator<(const P& a, const P& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline P operator+(const P& a, const P& b) { return P(a.x+b.x, a.y+b.y); }
inline P operator-(const P& a, const P& b) { return P(a.x-b.x, a.y-b.y); }
inline P operator-=(P& a, const P& b) { a.x -= b.x, a.y -= b.y ; return a; }
inline P::T2 cross(const P& a, const P& b) { return (P::T2)a.x*b.y - (P::T2)a.y*b.x; }
inline P::T2 dot(const P& a, const P& b) { return (P::T2)a.x*b.x + (P::T2)a.y*b.y; }
inline P::T2 norm(const P& a) { return (P::T2)a.x*a.x + (P::T2)a.y*a.y; }
ostream& operator<<(ostream& out, const P& x) { out << "(" << x.x << ", " << x.y << ")"; return out; }

struct L {
	P a, b;
	L(const P &a_, const P &b_): a(a_), b(b_) {}
	const P& operator[](size_t i) const { return i ? b : a; }
};

inline int ccw(const P& a, const P& b, const P& c) {
	int ax = b.x - a.x, ay = b.y - a.y, bx = c.x - a.x, by = c.y - a.y;
	P::T2 t = (P::T2)ax*by - (P::T2)ay*bx;
	if (t > 0) return 1;
	if (t < 0) return -1;
	if((P::T2)ax*bx + (P::T2)ay*by < 0) return +2;
	if((P::T2)ax*ax + (P::T2)ay*ay < (P::T2)bx*bx + (P::T2)by*by) return -2;
	return 0;
}

//��育�Ƃɐ����̃I�[�o�[���b�v�Ȃǂ��l���ď��������邱��
//�I����"�_�����L���Ă���"�ł����Ă�3�Ȃ�OK��2�͑ʖڂł��邱�Ƃ������̂Œ��ӁI
//���S�Ɍ������Ă��� : 0
//�_�����L���Ă���   : 2, 3
//���������L���Ă��� : 0
//���L�_�͖���       : 1
int intersectSS(const L &s, const L &t) {
	int a = ccw(s.a,s.b,t.a), b = ccw(s.a,s.b,t.b), c = ccw(t.a,t.b,s.a), d = ccw(t.a,t.b,s.b);
	int x = a * b, y = c * d;
	if(x == -1 && y == -1) return 0;	//cross
	else if(
		((abs(b) == 1 || b == -2) && s.b == t.a) ||
		((abs(b) == 1 || b ==  2) && s.a == t.a) ||
		((abs(a) == 1 || a == -2) && s.b == t.b) ||
		((abs(a) == 1 || a ==  2) && s.a == t.b)
		) return 2;	// point overlap (�^�񒆂ƒ[�����L����)
	else if(
		(x == 0 && (abs(a) + abs(b) == 1)) ||
		(y == 0 && (abs(c) + abs(d) == 1))
		) return 3;	// point overlap (�[�_�݂̂����L����)
	else if(x <= 0 && y <= 0) return 0;	//segment overlap
	else return 1;
}

bool intersectLP(const L &l, const P &p) {
  return cross(l[1]-p, l[0]-p) == 0;
}

//Verify����Ă��Ȃ��I
bool containsSP(const L &s, const P &p) {
	return s.a == p || s.b == p || ccw(s.a, p, s.b) == -2;
}

//���p�`�Ɠ_�̕�ܔ���
bool contains(const vector<P>& o, const P& p) {
	bool in = false;
	for (int i = 0; i < o.size(); ++i) {
		P a = o[i] - p, b = o[(i+1)%o.size()] - p;
		if (a.y > b.y) swap(a, b);
		if (a.y <= 0 && 0 < b.y)
			if (cross(a, b) < 0) in = !in;
		if (cross(a, b) == 0 && dot(a, b) <= 0) return true;	//point on edge
	}
	return in;
}

//�ʕ�
vector<P> convex_hull(vector<P> ps) {
	int n = ps.size(), k = 0;
	sort(ps.begin(), ps.end());
	vector<P> ch(2*n);
	for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
		while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
	for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
		while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
	ch.resize(k-1);
	return ch;
}

//�ʐς�2�{
P::T2 area(const vector<P>& o) {
  P::T2 A = 0;
  for (int i = 0; i < o.size(); ++i) 
    A += cross(o[i], o[(i+1)%o.size()]);
  return abs(A);
}

//�I���p�`�Ɛ����̌�������B�����؁B���̂܂܂ł͎g���ȁI
//�܂��A���������p�`�̓����ɂ���ꍇ�ȂǊԈ����������Ԃ�
//intersectSS��point overlap�Ƃ���K�؂ɕԂ��邱�Ƃ�O��ɂ��Ă���
bool intersectPolySegBBBBBBBBBBAAAAAAAAADDDDDD(const vector<P>& p, const L& l) {
	int touchCount = 0;
	rep(i, p.size()) {
		int t = intersectSS(L(p[i], p[(i+1)%p.size()]), l);
		if(t == 0) return true;
		touchCount += t == 2;
	}
	//���[���G��Ă��邱�Ƃ��킩���Ă���Ȃ�touchCount > 4 ��
}


/*
	10^7����xintersectSS����ꍇ�A���ꂾ��600ms���x�����X�p�Q�b�e�B�\�[�X�̂����TLE����
	��������̍������ɗ͂����ꂽ�o�[�W����
*/

struct P {
	typedef int T; typedef ll T2;	//T2��{a^2 | a:T}��ς�����^�C�v
	T x, y;
	P(T x_, T y_): x(x_), y(y_) {}
	P(): x(0), y(0) {}
};
bool operator<(const P& a, const P& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
P operator-(const P& a, const P& b) { return P(a.x-b.x, a.y-b.y); }
P::T2 cross(const P& a, const P& b) { return (P::T2)a.x*b.y - (P::T2)a.y*b.x; }
P::T2 dot(const P& a, const P& b) { return (P::T2)a.x*b.x + (P::T2)a.y*b.y; }
P::T2 norm(const P& a) { return (P::T2)a.x*a.x + (P::T2)a.y*a.y; }

//3�_���꒼����ɏd�Ȃ�ꍇ���l�����Ă��Ȃ�
int ccw(const P& a, const P& b, const P& c) {
  P::T2 t = (P::T2)(b.x-a.x)*(c.y-a.y) - (P::T2)(b.y-a.y)*(c.x-a.x);
  if (t > 0) return 1;
  if (t < 0) return -1;
  return 0;
}

//�����3�_���꒼����ɏd�Ȃ�ꍇ�Ȃǂ��l�����Ă��Ȃ�
//���ځA4�̈����œn��
bool intersectSS(const P& s0, const P& s1, const P& t0, const P& t1) {
  return ccw(s0,s1,t0) != ccw(s0,s1,t1) &&
         ccw(t0,t1,s0) != ccw(t0,t1,s1);
}
