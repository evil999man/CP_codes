//��Ԃ��O���[�o���Ɏ��o�[�W�����B�f�t�H���g�ł̓}�b�`�������𐔂���B
const int Alphabets = ;		//���������邱�ƁI
const int AlphabetBase = ;	//���������邱�ƁI
struct PMA {
	PMA *fail;
	PMA *next[Alphabets];
	int accepts;
	PMA(): fail(NULL), accepts(0) { mset(next, 0); }
};
PMA PMAs[/* ���������邱�ƁI */];
PMA *buildPMA(const vector<string> &p) {
	nPMAs = 0;
	PMA *root = new(&PMAs[nPMAs++])PMA;
	for(int i = 0; i < p.size(); ++i) {
		PMA *t = root;
		for(int j = 0; j < p[i].size(); ++j) {
			int c = p[i][j] - AlphabetBase;
			if(t->next[c] == NULL) t->next[c] = new(&PMAs[nPMAs++])PMA;
			t = t->next[c];
		}
		t->accepts ++;
	}
	queue<PMA*> Q;
	rep(c, Alphabets) {
		if(root->next[c]) {
			root->next[c]->fail = root;
			Q.push(root->next[c]);
		}else root->next[c] = root;
	}
	while(!Q.empty()) {
		PMA *t = Q.front(); Q.pop();
		rep(c, Alphabets) {
			if (t->next[c]) {
				Q.push(t->next[c]);
				PMA *r = t->fail;
				while (!r->next[c]) r = r->fail;
				t->next[c]->fail = r->next[c];
				t->next[c]->accepts += r->next[c]->accepts;
			}
		}
	}
	return root;
}
//����v��inout
int match(const string &s, PMA *&v) {
	int matches = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		int c = s[i] - AlphabetBase;
		while (!v->next[c]) v = v->fail;
		v = v->next[c];
		matches += v->accepts;
	}
	return matches;
}


//�I�A���t�@�x�b�g��['a'..'z']�Ŗ������́AAlphabets��( - 'a')�̏�(2�ӏ�)�����������悤
const int Alphabets = 26;
struct PMA {
	PMA *fail;
	PMA *next[Alphabets];
	ll accept;	//63��葽���̃p�^�[�����g������ll[N]��vector<int>�Ȃǂɏ��������悤
	PMA(): fail(NULL), accept(0) { mset(next, 0); }
};
//O(��|p[i]| Alphabets)�H�A���t�@�x�b�g�T�C�Y���|���邱�Ƃɒ���
PMA *buildPMA(const vs &p) {
	PMA *root = new PMA;
	for (int i = 0; i < p.size(); ++i) { // make trie
		PMA *t = root;
		for (int j = 0; j < p[i].size(); ++j) {
			char c = p[i][j] - 'a';
			if (t->next[c] == NULL) t->next[c] = new PMA;
			t = t->next[c];
		}
		t->accept |= 1LL << i;
	}
	queue<PMA*> Q;
	rep(c, Alphabets) {
		if (root->next[c]) {
			root->next[c]->fail = root;
			Q.push(root->next[c]);
		} else root->next[c] = root;	//�����̓X���C�h�̂ɂ͂Ȃ��������ǁc
	}
	while (!Q.empty()) {
		PMA *t = Q.front(); Q.pop();
		rep(c, Alphabets) {
			if (t->next[c]) {
				Q.push(t->next[c]);
				PMA *r = t->fail;
				while (!r->next[c]) r = r->fail;
				t->next[c]->fail = r->next[c];
				t->next[c]->accept |= r->next[c]->accept;	//spaghetti source �̂��̂ł͂������Ȃ��������ǁc
			}
		}
	}
	return root;
}
//O(n + ��|p[i]|)�H�A���t�@�x�b�g�T�C�Y�͂�����Ȃ����ȁH
ll match(char *t, int n, PMA *v) {
	ll r = 0;
	for (int i = 0; i < n; ++i) {
		char c = t[i] - 'a';
		while (!v->next[c]) v = v->fail;
		v = v->next[c];
		r |= v->accept;	//����������������ΐ��𐔂��邱�Ƃ��ł���
	}
	return r;
}