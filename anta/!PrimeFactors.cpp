//vector��ver.
vector<int> primeFactors;
void getPrimeFactors(int n) {
	n = max(n, 1);
	primeFactors.assign(n+1, 0);
	primeFactors[1] = 1;
	rer(i, 2, n) if(!primeFactors[i]) {
		primeFactors[i] = i;
		if((ll)i * i <= n)
		for(int j = i * i; j <= n; j += i)
			if(!primeFactors[j]) primeFactors[j] = i;
	}
}

//�z��ver.
const int GETPRIMEFACTORS_MAXN = 1500000;
int primeFactors[GETPRIMEFACTORS_MAXN+1];
void getPrimeFactors() {
	primeFactors[1] = 1;
	rer(i, 2, GETPRIMEFACTORS_MAXN) if(!primeFactors[i]) {
		primeFactors[i] = i;
		if((ll)i * i <= GETPRIMEFACTORS_MAXN)
		for(int j = i * i; j <= GETPRIMEFACTORS_MAXN; j += i) {
			if(!primeFactors[j]) primeFactors[j] = i;
		}
	}
}
//������Q�l�ɑf�������C�e���[�g����悤�ȃR�[�h����������
int getDivisors(int x) {
	if(x == 0) return 0;
	int r = 1;
	while(x != 1) {
		int y = primeFactors[x], z = 0;
		while(primeFactors[x] == y)
			z ++, x /= y;
		r *= z + 1;
	}
	return r;
}
