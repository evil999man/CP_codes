//Edge��src�͕K�v�Ȃ����͓K���Ȓl�����Ă���
//operator<�͋t�Ȃ̂Œ���

typedef int Weight;
struct Edge {
  int src, dst;
  Weight weight;
	Edge(int src_, int dst_, Weight weight_) : src(src_), dst(dst_), weight(weight_) { }
};
bool operator<(const Edge &e, const Edge &f) {
  return e.weight != f.weight ? e.weight > f.weight : e.dst < f.dst;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

//Edges��Graph�\�z�̃w���p�[

//Edges��src�Ɋ�Â�Graph���\�z����
void edgesToGraph(const Edges &e, int n, Graph &g) {
	g.assign(n, Edges());
	each(i, e) g[i->src].push_back(*i);
}
//Edges��src, dst�Ɋ�Â�Graph���\�z����
//�����O���t�p�ɁAsrc->dst, dst->src ��2�ӂ𒣂�
void edgesToGraphUndir(const Edges &e, int n, Graph &g) {
	g.assign(n, Edges());
	each(i, e) {
		g[i->src].push_back(*i);
		g[i->dst].push_back(Edge(i->dst, i->src, i->weight));
	}
}

