#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>

//���_��: <http://www.ics.uci.edu/~eppstein/pubs/Epp-SJC-98.pdf>
//�Љ�X���C�h: <http://www.isi.edu/natural-language/people/epp-cs562.pdf>
//Steps(�_���̂��̂ƕϐ��̖��O�Ȃǂ��Ⴄ�̂Œ���)
//1. shortest path tree���\�z����(������DAG�ł��鎞�Ȃǂ̂��߂ɕ����ł���)
//2. ���ꂼ��̒��_v�ɑ΂��āAv����o�Ă���sidetrack�̂����ŏ��̂��̂�best(v)�Ƃ���B
//   ���ꂼ��̒��_v�ɑ΂��āAv����t�ւ̃p�X��̒��_w�ɑ΂���best(w)�̏W������Ȃ�񕪃q�[�v�����(H_best(v)�Ƃ���)�B
//3. ���ꂼ��̒��_v�ɑ΂��āAv����o�Ă���sidetracks����best(v)�����������̂̏W������Ȃ�񕪃q�[�v�����(H_out(v)�Ƃ���)�B
//4. ���ꂼ��̒��_v�ɑ΂��āAH_best(v)�̍�����H_out(v)�ւ̕ӂ𒣂�(�����H_3(v)�Ƃ���)�B
//5. ���ꂼ��̒��_v�ɑ΂��āAH_3(v)�̂��ꂼ��̃m�[�hn�ɑ΂��āAn���\������ӂ̍s����̒��_��u�Ƃ���ƁA
//   n����H_3(u)�̍��ւ̕ӂ𒣂�B�S�č��킹��D_4'�Ƃ���B
//6. D_4'�̒��ł��Ƃ���H_3(s)�ł������m�[�h�֐V���ɍ����������ӂ𒣂�B�����D_4�Ƃ���B
//7. D_4�̕ӂ��d�݂��ɂ���B5�܂���6�Œǉ����ꂽ�ӂ̏d�݂͍s����̃m�[�h�̏d�݂Ƃ���B
//   ����ȊO�̕ӂ̏d�݂͏d�݂̍��Ƃ���B
//8. ���܁AD_4�͏o������������4�̃O���t�ŁA�����炠�钸�_�ւ̃E�H�[�N�͌��̃O���tG�ł�s����t�ւ̃E�H�[�N�ɑΉ�����B
//   ������(D_4��̋��� + s����t�ւ̍ŒZ����)�ł���B
//   2�ō\�z�����q�[�v���~��邱�Ƃ́Ashortest path tree�̂��镔����ʂ邱�ƂɑΉ�����B
//   3�ō\�z�����q�[�v���~��邱�Ƃ́A���钸�_����o�Ă���sidetrack��I�Ԃ��ƂɑΉ�����B
//   5�Œǉ������ӂ�ʂ邱�Ƃ́A����sidetrack edge��ʂ邱�ƂɑΉ�����B
//   ���钸�_�ŏI�����邱�Ƃ́A���̒��_�ɑΉ�����sidetrack edge���Ō�ɒʂ��Ă�������shortest path tree��ʂ���t�֍s�����ƂɑΉ�����B
//9. ���̃O���t���nearest first search���邱�Ƃɂ����O(k log k)�Ō�������B
//
//Improvements
//1. 2�ŉi���I�ɂ���āA�܂�5�ŕӂ𒣂鎞�ɂ͈ÖٓI�܂��͔j��I�ɂ���ăV�F�A�����邱�Ƃɂ����O(n log n + m)�ƂȂ�B
//2. ����ɁA�Ȃ񂩖؂𕪉������肷��Ɛ��`�ō\�z�ł���炵���B
//3. D_4���k�Ԗڂ𓾂�̂�Frederickson�ɂ��A���S���Y����O(k)�łł���B
//
//TODO:
//�E���ۂ̃p�X�𓾂���悤�ɂ���
//�E�ӂ̐��Ȃǂ̒l�����ۂɃp�X��H��Ȃ��Ă�������悤�ɂ���
//�EDAG�ɑΉ�����(���̕ӂɂ�)
//�E��(k)�̃q�[�vk�ԖڃA���S���Y���H
//�E���`�ł̍\�z�H
//
//�p�X���L�^����ɂ�(k�Ԗځ�(prev�����Ԗڂ�,��))��k���Ă΂�������
//��(k)�̃q�[�vk�ԖڃA���S���Y���͏�����������k�S���擾���邱�Ƃɂ͉��p�ł��Ȃ����ۂ��H
//  �Ō�ɔz����selecting algorithm���g���Ă���̂ŁB
//  ����Ak�Ԗڂ̂��̂𓾂���ɂ���ȉ��̂��̂�DFS�ŗ񋓂���� *���s���łȂ�* k�񋓂ł���B
//  �����������Ԓʂ�ɂ��ɂ̓�(k log k)���K�v�B��(n)�Ńq�[�v�\�z���Ă�����g���΃\�[�g�ł��Ă��܂��̂ŁB
//
//k�Ԗڂ̕H: <http://utpc2013.contest.atcoder.jp/submissions/140415>

struct WeightedStaticGraph {
	typedef int Vertex;
	typedef long long Weight; static const Weight InfWeight;
	struct To {
		Vertex to; Weight w;
		To() { }
		To(Vertex to_, Weight w_): to(to_), w(w_) { }
	};
	typedef std::pair<Vertex,To> Edge;
	typedef const To *const_iterator;

	void init(int n_, const std::vector<Edge> &edges) {
		n = n_; int m = edges.size();
		tos.resize(m+1); offsets.resize(n+1);
		for(int e = 0; e < m; e ++) offsets[edges[e].first] ++;
		for(int v = 1; v <= n_; v ++) offsets[v] += offsets[v-1];
		for(int e = 0; e < m; e ++)
			tos[-- offsets[edges[e].first]] = edges[e].second;
	}
	int numVertices() const { return n; }

	inline const_iterator edgesBegin(int v) const { return &tos[offsets[v]]; }
	inline const_iterator edgesEnd(int v) const { return &tos[offsets[v+1]]; }
private:
	int n;
	std::vector<To> tos;
	std::vector<int> offsets;
};
const WeightedStaticGraph::Weight WeightedStaticGraph::InfWeight = 0x3f3f3f3f3f3f3f3fLL;	//2�{���I�[�o�[�t���[���Ȃ��K�v������
typedef WeightedStaticGraph Graph;

void transposeGraph(const WeightedStaticGraph &g, WeightedStaticGraph &h) {
	int n = g.numVertices();
	std::vector<Graph::Edge> edges;
	for(int v = 0; v < n; v ++)
		for(Graph::const_iterator it = g.edgesBegin(v), et = g.edgesEnd(v); it != et; ++ it) {
			Graph::To t = *it; t.to = v;
			edges.push_back(Graph::Edge(it->to, t));
		}
	h.init(n, edges);
}

class KShortestPaths {
	friend int main();
public:
	typedef Graph::Weight Weight; typedef Graph::Vertex Vertex;

	void build(const Graph &g, Vertex destination);
	void buildMain(const Graph &g, const Weight dist[], const Vertex treeParent[], const std::vector<Vertex> &treeOrder);

	void getDistances(Vertex source, int k, std::vector<Weight> &lengths) const;
private:
	typedef int NodeIndex;
	struct HBestNode {	//H_best���\������m�[�h(�i���I2���q�[�v)
		Vertex vertex;	//�ǂ̒��_��best��
		NodeIndex left, right;	//�q�[�v�̎q�B�|�C���^�̑���ɃC���f�b�N�X
	};
	std::vector<HBestNode> hBestNodes;
	std::vector<NodeIndex> hBestRoots;
	std::vector<bool> hasSidetrack;
	std::vector<Graph::To> bestSidetracks;
	std::vector<Graph::To> sidetrackHeaps;
	std::vector<int> sidetrackHeapOffsets;
	std::vector<Weight> toDestinationDistance;
	std::vector<int> vertexIndices;

	void buildShortestPathTree(const Graph &g, int t, Weight dist[], Vertex prev[], std::vector<Vertex> &order) const;

	NodeIndex insertToBestHeap(NodeIndex rootNode, int heapSize, Vertex v);
	NodeIndex newHBestNode(Vertex v, NodeIndex left = -1, NodeIndex right = -1);

	struct HeapCompareEdge {
		bool operator()(const Graph::To &x, const Graph::To &y) const { return x.w > y.w; }
	};

	struct SearchState {
		Weight dist;
		Vertex vertex;
		int index;
		SearchState() { }
		SearchState(Weight d, Vertex v, int i): dist(d), vertex(v), index(i) { }
		bool operator>(const SearchState &that) const { return dist > that.dist; }
	};
};

void KShortestPaths::buildShortestPathTree(const Graph &g, int t, Weight dist[], Vertex prev[], std::vector<Vertex> &order) const {
	int n = g.numVertices();
	Graph h; transposeGraph(g, h);
	for(int v = 0; v < n; v ++) {
		dist[v] = Graph::InfWeight;
		prev[v] = -1;
	}
	dist[t] = 0;
	order.clear();
	std::vector<bool> visited(n, false);
	typedef std::pair<Weight,Vertex> DistPair;
	std::priority_queue<DistPair,std::vector<DistPair>,std::greater<DistPair> > q;
	q.push(DistPair(0, t));
	while(!q.empty()) {
		Vertex v = q.top().second; q.pop();
		if(visited[v]) continue;
		visited[v] = true;
		order.push_back(v);
		for(Graph::const_iterator it = h.edgesBegin(v), et = h.edgesEnd(v); it != et; ++ it) {
			Weight d = dist[v] + it->w; Vertex u = it->to;
			if(d < dist[u]) {
				prev[u] = v;
				dist[u] = d;
				q.push(DistPair(d, u));
			}
		}
	}
}

KShortestPaths::NodeIndex KShortestPaths::newHBestNode(Vertex v, NodeIndex left, NodeIndex right) {
	HBestNode newNode = { v, left, right };
	hBestNodes.push_back(newNode);
	return (NodeIndex)hBestNodes.size() - 1;
}
 
KShortestPaths::NodeIndex KShortestPaths::insertToBestHeap(NodeIndex rootNode, int heapSize, Vertex v) {
	if(rootNode == -1) return newHBestNode(v, -1, -1);
	int newPosition = heapSize + 1, height = 0;
	while((1 << height) <= newPosition) height ++;	//1: 1, 2,3: 2
	NodeIndex levelNodes[32], currentNode = rootNode;
	int insertHeight = 0;
	for(int h = height - 1; h > 0; h --) {
		levelNodes[h] = currentNode;
		const HBestNode &cnt = hBestNodes[currentNode];
		if(insertHeight == 0 && bestSidetracks[v].w <= bestSidetracks[cnt.vertex].w)
			insertHeight = h;
		currentNode = newPosition >> (h-1) & 1 ? cnt.right : cnt.left;
	}
	currentNode = -1;
	for(int h = 0; h <= insertHeight; h ++) {
		Vertex u = h == insertHeight ? v : hBestNodes[levelNodes[h+1]].vertex;
		if(h == 0)
			currentNode = newHBestNode(u, -1, -1);
		else if(newPosition >> (h-1) & 1)
			currentNode = newHBestNode(u, hBestNodes[levelNodes[h]].left, currentNode);
		else
			currentNode = newHBestNode(u, currentNode, hBestNodes[levelNodes[h]].right);
	}
	for(int h = insertHeight+1; h < height; h ++) {
		const HBestNode &node = hBestNodes[levelNodes[h]];
		if(newPosition >> (h-1) & 1)
			currentNode = newHBestNode(node.vertex, node.left, currentNode);
		else
			currentNode = newHBestNode(node.vertex, currentNode, node.right);
	}
	return currentNode;
}

void KShortestPaths::buildMain(const Graph &g, const Weight dist[], const Vertex treeParent[], const std::vector<Vertex> &treeOrder) {
	int n = g.numVertices();
	hBestNodes.clear();
	hBestRoots.assign(n, -1);
	bestSidetracks.resize(n);
	hasSidetrack.assign(n, false);
	bestSidetracks.resize(n);
	sidetrackHeaps.clear();
	sidetrackHeapOffsets.resize(treeOrder.size()+1);
	toDestinationDistance.assign(dist, dist + n);
	vertexIndices.assign(n, -1);
	std::vector<int> hBestSizes(n, 0);

	for(int idx = 0; idx < (int)treeOrder.size(); idx ++) {
		Vertex v = treeOrder[idx], p = treeParent[v];
		vertexIndices[v] = idx;

		Graph::To bestSidetrack; bestSidetrack.w = Graph::InfWeight;
		int treeEdgeIndex = -1, bestEdgeIndex = -1;
		{	bool sawTreeEdge = false;
			int ei = 0; 
			for(Graph::const_iterator it = g.edgesBegin(v), et = g.edgesEnd(v); it != et; ++ it, ++ ei) {
				Vertex u = it->to; Weight delta = it->w - (dist[v] - dist[u]);
				if(!sawTreeEdge && treeParent[v] == u && delta == 0) {
					treeEdgeIndex = ei;
					sawTreeEdge = true;
				}else if(bestSidetrack.w > delta) {
					hasSidetrack[v] = true;
					bestEdgeIndex = ei;
					Graph::To t = *it; t.w = delta;
					bestSidetrack = t;
				}
			}
		}
		bestSidetracks[v] = bestSidetrack;
		hBestRoots[v] = p == -1 ? -1 : hBestRoots[p];
		hBestSizes[v] = p == -1 ? 0 : hBestSizes[p];
		if(hasSidetrack[v]) {
			hBestRoots[v] = insertToBestHeap(hBestRoots[v], hBestSizes[v], v);
			hBestSizes[v] ++;
		}
		sidetrackHeapOffsets[idx] = sidetrackHeaps.size();
		{	int ei = 0;
			for(Graph::const_iterator it = g.edgesBegin(v), et = g.edgesEnd(v); it != et; ++ it, ++ ei) {
				Vertex u = it->to; Weight delta = it->w - (dist[v] - dist[u]);
				if(ei != treeEdgeIndex && ei != bestEdgeIndex && delta < Graph::InfWeight) {
					Graph::To t = *it; t.w = delta;
					sidetrackHeaps.push_back(t);
				}
			}
		}
		std::make_heap(sidetrackHeaps.begin() + sidetrackHeapOffsets[idx], sidetrackHeaps.end(), HeapCompareEdge());
	}
	sidetrackHeapOffsets[treeOrder.size()] = sidetrackHeaps.size();
}

void KShortestPaths::build(const Graph &g, Vertex destination) {
	int n = g.numVertices();
	std::vector<Graph::Weight> dist(n);
	std::vector<Graph::Vertex> treeParent(n);
	std::vector<Graph::Vertex> treeOrder;
	buildShortestPathTree(g, destination, &dist[0], &treeParent[0], treeOrder);
	buildMain(g, &dist[0], &treeParent[0], treeOrder);
}

void KShortestPaths::getDistances(Vertex source, int k, std::vector<Weight> &lengths) const {
	lengths.clear();
	Weight shortestDistance = toDestinationDistance[source];
	if(shortestDistance == Graph::InfWeight || k <= 0) return;
	lengths.push_back(shortestDistance);
	int hBests = hBestNodes.size();
	//index��-1�Ȃ�bestTree�A�����łȂ��Ȃ�sidetrackHeap
	typedef SearchState State;
	std::priority_queue<State,std::vector<State>,std::greater<State> > q;
	NodeIndex root = hBestRoots[source];
	if(root != -1) {
		Vertex rootVertex = hBestNodes[root].vertex;
		q.push(State(bestSidetracks[rootVertex].w, rootVertex, root));
	}
	while(!q.empty() && (int)lengths.size() < k) {
		Weight d = q.top().dist;
		Vertex v = q.top().vertex, vIndex = vertexIndices[v];
		int index = q.top().index;
		q.pop();
		lengths.push_back(shortestDistance + d);
		if(index < hBests) {
			const HBestNode &node = hBestNodes[index];
			const Graph::To &edge = bestSidetracks[v];
			Weight e = d - edge.w;
			//H_best�̎q����
			NodeIndex left = node.left, right = node.right;
			if(left != -1) {
				Vertex leftVertex = hBestNodes[left].vertex;
				q.push(State(e + bestSidetracks[leftVertex].w, leftVertex, left));
			}
			if(right != -1) {
				Vertex rightVertex = hBestNodes[right].vertex;
				q.push(State(e + bestSidetracks[rightVertex].w, rightVertex, right));
			}
			//�ӂ̍s����
			Vertex u = edge.to; NodeIndex uRoot = hBestRoots[u];
			if(uRoot != -1) {
				Vertex rootVertex = hBestNodes[uRoot].vertex;
				q.push(State(d + bestSidetracks[rootVertex].w, rootVertex, uRoot));
			}
			//best�ȊO�̕�
			int heapRoot = sidetrackHeapOffsets[vIndex];
			if(heapRoot != sidetrackHeapOffsets[vIndex+1])
				q.push(State(e + sidetrackHeaps[heapRoot].w, v, hBests + heapRoot));
		}else {
			const Graph::To &edge = sidetrackHeaps[index - hBests];
			Weight e = d - edge.w;
			int heapBase = sidetrackHeapOffsets[vIndex], heapEnd = sidetrackHeapOffsets[vIndex+1];
			int localIndex = index - hBests - heapBase;
			int left = heapBase + localIndex * 2 + 1, right = heapBase + localIndex * 2 + 2;
			//H_out�̎q����
			if(left < heapEnd)
				q.push(State(e + sidetrackHeaps[left].w, v, hBests + left));
			if(right < heapEnd)
				q.push(State(e + sidetrackHeaps[right].w, v, hBests + right));
			//�ӂ̍s����
			Vertex u = edge.to; NodeIndex uRoot = hBestRoots[u];
			if(uRoot != -1) {
				Vertex rootVertex = hBestNodes[uRoot].vertex;
				q.push(State(d + bestSidetracks[rootVertex].w, rootVertex, uRoot));
			}
		}
	}
}

#include "../Util/TimeIt_Simple.hpp"
#include "../Util/GetCurrentHeapSize.hpp"
double getMiB(long long x) { return (int)(x / 1024. / 1024. * 1000) / 1000.; }
int main() {
	using namespace std;
	int n, k;
	scanf("%d%d", &n, &k);
	vector<Graph::Edge> edges;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < 2; j ++)
			edges.push_back(Graph::Edge(i, Graph::To((i+1)%n, 1)));
	}
	cerr << "Nodes, Edges:   " << n << ", " << edges.size() << endl;
	int s = 0, t = 0;
	Graph g; g.init(n, edges);
	long long h1 = getCurrentHeapSize(), mem;
	int bestHeapNodes, bestHeapCapa;
	TIMEIT("Eppstein") {
	KShortestPaths kShortestPaths;
	kShortestPaths.build(g, t);
	vector<Graph::Weight> lengths;
	TIMEIT("getDistances") {
	kShortestPaths.getDistances(s, k, lengths);
	}
	bestHeapNodes = kShortestPaths.hBestNodes.size();
	bestHeapCapa = kShortestPaths.hBestNodes.capacity();
	mem = getCurrentHeapSize() - h1;
	}
	cerr << "Total:         " << getMiB(mem) << "MiB" << endl;
	cerr << "bestHeapNodes: " << getMiB(bestHeapCapa * sizeof(KShortestPaths::HBestNode)) << "MiB" << " (" << bestHeapNodes << ", x" << (int)(bestHeapNodes * 1. / n * 100) / 100. << ")" << endl;
	/*
	for(int i = 0; i < k; i ++) {
		if((int)lengths.size() <= i)
			puts("-1");
		else
			printf("%lld\n", lengths[i]);
	}
	*/
	return 0;
}
