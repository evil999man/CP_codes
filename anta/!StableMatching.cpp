/*
	����}�b�`���O, ���茋�����, Stable Matching, Stable Marrige Problem
	�v�Z��: O(n^2)
	
	�E����
	http://www.prefield.com/algorithm/misc/stable_matching.html
	> ����}�b�`���O�͎��̂悤�Ȗ��Ő����ł���Dn �l�̒j���� n �l�̏������^������D�e�j���͏����ɑ΂��đI�D���ʂƌĂ΂��S�����������C�e���������l�Ɋe�j���ɑ΂��đI�D���ʂ����D�j���Ə�������l�Ây�A�ɂ��邱�Ƃ��l����D���̂Ƃ��C�y�A�ƂȂ��Ă��Ȃ��j���̑� (m, w) ���u���b�L���O�y�A�ł���Ƃ͎��̓�����𖞂������Ƃ������D
	> �j���s�����Fw �� m �̌��݂̃y�A w' �����D�܂����D
	> �����s�����Fm �� w �̌��݂̃y�A m' �����D�܂����D
	> ����}�b�`���O�Ƃ́C�u���b�L���O�y�A�̑��݂��Ȃ��}�b�`���O�̂��Ƃ������D
	�񕔃O���t�������āA�D�揇�ʂ����܂��ĂāA�D�揇�ʂ��ɑ�ȃ}�b�`���O�����߂銴���B
	�܂��A����͒j���ŗǈ���}�b�`���O�����߂�B
		�e�j�����ƂɁA����}�b�`���O�̒��ōŗǂ̏����ƃy�A�ɂȂ��Ă���B(�ꕾ�����邩���H�Ȃ�Ƃ������A�ɑ�Ȋ���)
		����͈�ӂł��邱�Ƃɒ��ӁB���̂��߁A�����Ԃ���������B
	
	�E�C�ӂɃ_�~�[�̐l��u����
		�_�~�[�̐l�͑��̑S�Ă̗D�揇�ʂ��_�~�[�łȂ��l��菬��������΂���
	�E���E�̐l��������Ă�����
		�_�~�[�̐l��u���΂����B
		�_�~�[�̐l�ƌ������Ă���Ƃ����̂͌������肪���Ȃ��Ƃ�������
	���Ɂu��΂Ƀy�A��g�݂����Ȃ��j���΂����݂���ꍇ�v�u��v���Ȑ��v�Ȃǂ��ł���炵��
		(http://www.prefield.com/algorithm/misc/stable_matching.html�Q��)
	�E����
		SRM 263 DIV1 Hard RobotRace
		�u���̂𗼕��̐l����鎞�ɂ͏��ʂ����܂��Ă��āA���ꂼ��1�ȉ��~����������肽���Ƃ��A
			(�����ɍl����)�S�Ă̐l���ŗǂ�I�Ԃ��Ƃ��킩���Ă��鎞�̍ŗǁv
		�l�Ƃ��̂̓񕔃O���t�ŁA(����̗~����, ��������Ƃ��̏���)�ō��ŗǈ���}�b�`���O�B
		�u���b�L���O���ux�̂��̂��y�̕����~�����āA����y������Ă�l����Ɏ���v�Ƃ����ӂ��ɂȂ�B
		�ŗǂ́A�P���Ɉ�ԗ~�������̂���銴���ŁB
*/

/*
	(n,n)�̊��S�񕔃O���t��v������ʏ�̂��́B
	
	v: �e�����_�ɑ΂���E���_�̏���(���Ԓʂ�ɉE���_����ׂ�)
	u: �e�E���_�ɑ΂��鍶���_�̏���(����)
	�߂�l: �e`�E'���_�ɑΉ�����`��'���_
		�I�E���獶�ł��邱�Ƃɒ��ӁI
*/
vi stableMatching(const vector<vi>& v, const vector<vi>& u) {
	int n = v.size();
	vector<vi> p(n, vi(n+1, n));
	vi match(n, n), s(n, 0);
	rep(w, n) rep(i, n) p[w][u[w][i]] = i;
	rep(m0, n) for(int m = m0; m < n; ) {
		int w = v[m][s[m]++];
		if(p[w][m] < p[w][match[w]]) swap(m, match[w]);
	}
	return match;
}

/*
	���E�̃T�C�Y������Ă��悭�A�����S�񕔃O���t�łȂ��Ă������o�[�W����
	�����͏�L�̂��̂Ɠ����B�߂�l�͍�����E�ւ̊��蓖�Ă�Ԃ��B
	�߂�l��-1�̗v�f�͂��̒��_�Ɍ��΂��ӂ��������Ƃ�\���B
*/
vi stableMatching(const vector<vi>& v, const vector<vi>& u) {
	int nm = v.size(), nw = u.size();
	vector<queue<int> > p(nm);
	rep(i, nm) each(j, v[i]) p[i].push(*j);
	queue<int> q;
	rep(i, nm) if(v[i].size()) q.push(i);
	vector<vi> wr(nw, vi(nm, -1));
	rep(i, nw) rep(j, u[i].size()) wr[i][u[i][j]] = j;
	vi wm(nw, -1), mw(nm, -1);
	while(!q.empty()) {
		int m = q.front(); q.pop();
		while(!p[m].empty()) {
			int w = p[m].front(); p[m].pop();
			if(wm[w] == -1) {
				wm[w] = m; mw[m] = w;
				break;
			}else {
				int d = wm[w];
				if(wr[w][m] < wr[w][d]) {
					wm[w] = m; mw[m] = w;
					q.push(d); mw[d] = -1;
					break;
				}
			}
		}
	}
	return mw;
}