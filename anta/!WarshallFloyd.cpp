//�C�����C���ŏ����ׂ�
//INF�̃I�[�o�[�t���[�ɂ͋C�𗯂߂邱��

int wf[N][N];
int n = size

//�O����
rep(i, n) rep(j, n) wf[i][j] = INF;
rep(i, n) wf[i][i] = 0;

//min����邱�Ƃɒ���
each(e, graph) {
	wf[e->src][e->dst] = min(wf[e->src][e->dst], e->weight);
}

rep(k, n) rep(i, n) rep(j, n) {
	if(wf[i][k] != INF && wf[k][j] != INF)
		wf[i][j] = min(wf[i][j], wf[i][k] + wf[k][j]);
}

if(wf[i][j]==INF)	//���B�\��
dist = wf[i][j];	//�ŒZ����
if(wf[i][i] < 0)	//i��ʂ镉�H�����݂��邩
rep(i, n)
	if(wf[origin][i]!=INF && wf[i][destination]!=INF && wf[i][i]<0)
		return "ENDLESS PROFIT";
	//origin����destination�֌��������ł����āA���H��ʂ���̂����݂��邩

