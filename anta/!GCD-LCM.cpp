//GCD�B�}�C�i�X�͖��Ή�
template<typename T>T gcd(T x, T y){if(y==0)return x;else return gcd(y,x%y);}

//�}�C�i�X�̐���abs���Ƃ��΂���
template<typename T>T gcd_positive(T x, T y) { return y == 0 ? x : gcd_positive(y,x%y); }
template<typename T>T gcd(T x, T y) { return gcd_positive(abs(x), abs(y)); }

//LCM
//�ő�x*y�ɂȂ肤��̂ŁA�I�[�o�[�t���[�ɒ���
template<typename T>T lcm(T x, T y){ return x/gcd(x,y)*y; }

//�g�����[�N���b�h
//a*m + b*n = gcd(m, n) = g �̉��ƂȂ鐮��a,b�̑g��������
//��������
template<typename T>
void extendedEuclid(T m, T n, T& a, T& b, T& g) {
	if(n == 0) {
		a = 1; b = 0; g = m;
	}else {
		extendedEuclid(n, m%n, a, b, g);
		swap(a, b);
		b -= a * (m/n);
	}
}
