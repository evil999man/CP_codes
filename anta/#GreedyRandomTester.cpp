//���͒l�͈̔́E����͂�����ƃR�[�f�B���O���邱��
//���炩�ȃR�[�i�[�P�[�X�͐l�͂Ŏ������ق����ǂ�

int test() {
	vi v;
	rep(i, 1000) {
		//vector�̃T�C�Y��ݒ肷��
		int n = rand()%50+1;
		// �����œ��͒l�𐶐�����B0�ȂǃR�[�i�[�l�̊m���������Ă��ǂ�
		rep(j, n) v.pb(rand()%2 ? (rand()%3-1) : rand()%2000-1000);
		//�𓚂̒l
		ll a = maximalSum(v);
		rep(j, 1000) {
			random_shuffle(all(v));
			int k = 0;
			ll t = 0;
			vi h;
			//�����ŉ��炩�̃����_���������B
			//h�ɂ��̃����_���̗��������Ă���
			while(k < n) {
				if(rand()%2 && k+1 < n) t += v[k]*v[k+1], h.pb(2), k += 2;
				else t += v[k], h.pb(1), k ++;
			}
			//lt/gt�ɒ���
			if(t > a) {
				cout<<"NG: ";each(l, v) cout<<*l<<",";cout<<endl;
				cout<<"hist: ";each(l, h) cout<<*l<<",";cout<<endl;
				cout<<a<<", "<<t<<endl;
				goto ng;
			}
		}
		cout<<"OK: ";each(l, v) cout<<*l<<",";cout<<endl;
		ng:;
	}
}

