/*
	��ʊ֐��̍ő�l��T��
	�߂�l�͂��̈���
	"<"������ς��邩�A�֐����}�C�i�X�ɂ���΍ŏ��l���\
*/

double goldenSectionSearch(double a, double b) {
	const double r = 2 / (3 + sqrt(5.));
	double c = a + r * (b - a), d = b - r * (b - a);
	double fc = find_func(c), fd = find_func(d);
	rep(ii, 100) {
		if (fc < fd) { // '<': maximum, '>': minimum
			a = c; c = d; d = b - r * (b - a);
			fc = fd; fd = find_func(d);
		} else {
			b = d; d = c; c = a + r * (b - a);
			fd = fc; fc = find_func(c);
		}
	}
	return c;
}
