//����: first, second
//x: ��v���Ă鐔
//n: first�ɗ~����(first - second)�̐�
//m: first�ɗv��Ȃ�(second - first)�̐�
//�C���N�������g���Ă�Ƃ����push_back���ɂ���Η񋓂��\
//STL�ɂ͖����̂��Ȃ��H

sort(all(first)); sort(all(second));
aut(i, first.begin());
aut(j, second.begin());
int x = 0, n = 0, m = 0;
while(i != first.end() || j != second.end()) {
	if(i == first.end() || (j != second.end() && *j < *i)) ++j, n ++;
	else if(j == second.end() || *j > *i) ++i, m ++;
	else x ++, ++i, ++j;
}
