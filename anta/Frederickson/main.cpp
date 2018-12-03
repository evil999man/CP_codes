#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using std::cerr; using std::endl;

//Frederickson, Greg N. "An optimal algorithm for selection in a min-heap." Information and Computation 104.2 (1993): 197-214.
//<http://www.sciencedirect.com/science/article/pii/S0890540183710308>
//(��SEL1�ƌĂ΂�Ă����{�I�ȕ����̂�)
//
//"clan"�ƌĂ΂��Afloor(log k)�T�C�Y�̃O���[�v��(lazy��)�����āA
//���ꂼ��� *�ő�l* �����߂đ�\(representative)�Ƃ��A
//���ꂪ�����q�[�v(auxiliary heap)��𕁒ʂɒT������B
//clans��K�؂ɍ\�z����΁Aauxiliary heap��ł̒T����ceil(k/floor(log k))��ڂ̂��̂�rank��k�`2k�ƂȂ�B
//������S�����o���Ĕz����selection algorithm��p�����O(k)�ƂȂ�B
//�T�������̓�((k/log k) log (k/log k))�Ȃ̂ŁAO(k)�ł���B
//����āA�ǂ̂悤��clan�ɕ������邩�����ƂȂ�B
//
//Algorithm SEL1.
//�܂��Aclan C_j �ɑ΂��� offspring os(C_j) ���A{ u | v \in C_j, u \in children(v), u \notin C_j }�ƒ�`����B
//clan���\�z����2�̕��@���l����B
//1�ڂ̕��@�F
//	auxiliary heap��̒T����clan C_j�����o�������A
//	os(C_j)���������Ƃ���subheaps�̂�������������floor(log k)��V����clan C_i�Ƃ���B
//2�ڂ̕��@�F
//	1�ڂ̕��@�őI�΂�Ȃ�����os(C_j)�̃m�[�h�͉i�v�ɑI�΂�邱�Ƃ������Ȃ��Ă��܂��͍̂���B
//	����āA�I�΂�Ȃ������m�[�h������V���ɍ����clan C_i�Ɋ֘A�t����B
//	�����poor relations pr(C_i)�ƌĂԁB
//	auxiliary heap��̒T����clan C_j�����o����������pr(C_j)����Ŗ�����΁A
//	pr(C_j)���������Ƃ���subheaps�̂�������������floor(log k)��V����clan C_{i+1}�Ƃ���B
//	���̂Ƃ��Apr(C_j)�̂����I�΂�Ȃ��������_������pr(C_{i+1})�Ƃ���B
//os(C_j)��pr(C_j)���T�C�Y���ő�ł� 2 floor(log k) �ȉ��ł��邱�Ƃɒ��ӂ���B
//���ʂ̃q�[�v�ŒT�����č\�z�����O(log k log log k)���Ԃ�1��clan���\�z�ł���B
//ceil(k/floor(log k))�ڂ̑�\�����o���āA�Ō�ɂ��̑�\�ȉ��̑S�Ẵm�[�h��񋓂���k�Ԗڂ����߂�B
//
//�������F
//	ceil(k/floor(log k))�ڂ̑�\��rank�͏��Ȃ��Ƃ�k�ł���B
//	�Ȃ��Ȃ�Aceil(k/floor(log k))��clan�̑�\�͂���ȉ��ł����āA����ɂ��ꂼ��ɑ�\�ȉ������邩��A���ړI��k������B	
//	�܂��A�Ō�̑�\�����̃m�[�h�́A�S�Ă�clan�ɑ����Ă���B
//	�Ȃ��Ȃ�A������\�����ő����Ă��Ȃ��m�[�h����������A
//	�܂����������ɂ�����clan�ɂԂ������n�_���l����ƁAheap property��肻�̃m�[�h����\�����ł����āA
//	���ꂪ���clan�Ɋ܂܂�Ă��Ȃ��Ƃ������Ƃ́A����clan�͑S�Ă��̃m�[�h�ȉ��̒l���������Ȃ����ƂɂȂ��āA
//	���̂��߂���clan�͑�\�l�����̃m�[�h�ȉ��ł��邪�A
//	���̂��߂ɍŌ�̑�\��葁��extract����Ă���͂��ł���B
//	�܂��A����extract���ꂽ����A���̌��poor relation���炱�̃m�[�h���I�΂�Ă��Ȃ��Ƃ������Ƃ́A
//	�����Ƃ��̃m�[�h��菬���ȃm�[�h�݂̂ō��ꂽclan�����������Ă����Ƃ������ƂɂȂ邪�A
//	����clan�͍Ō�̑�\�����Ȃ̂ōŌ��clan�łȂ����Ƃ��l����ƁA�i���ɑ����Ȃ���΂��������A�L���Ȃ̂Ŗ����B
//�v�Z�ʁF
//	�eclan���\�z����̂Ƀ�(log k log log k)�B�������(k/log k)��J��Ԃ��̂�����A��(k log log k)�B
//	clan�̑�\�l����Ȃ�q�[�v�T���́A�T�C�Y����(k/log k)�ŏo�������萔(�ő��os��pr��2��)�ł���̂ŁA���ʂ̃q�[�v���g����O(k)�B
//	�Ō�ɑI�ԃm�[�h�̐������ƂȂ�B2���؂ł���̂ŁA�ǂ�����Ă�2*ceil(k/floor(log k))+1��clan��������Ȃ��B
//	��\�ȉ��̒��_�͑S��clan�ɑ����Ă���̂ŁA�����̐��̓�(k/log k)�~��(log k)����(k)�B
//	����čŌ��k�Ԗڂ𓾂�̂Ƀ�(k)�B
//	�v�Z�ʂ̓�(k log log k)�ƂȂ�B
//
//Algorithm SEL2.
//SEL1�ł�clan��floor(log k)�̒l�𓾂�̂ɕ��ʂ̃q�[�v�T�����g���Ă������A
//����͎��ۂɂ͂��̖�莩�̂ł���B����čċA�I�ɃA���S���Y����K�p�ł���B
//�e�ċA��r�Ԗڂ����߂�Ƃ���B�ŏ���r = k�ł���B�ċA�̕s�Ϗ����Ƃ��āA�q�[�v�̌���2r�ȉ��ł���Ƃł���B
//�������A�P���ɂ���x�̃q�[�v���烦(x log r)��clan����낤�Ƃ��Čv�Z�ʂ��傫���Ȃ��Ă��܂��̂łǂ��ɂ����Ȃ���΂Ȃ�Ȃ��B
//�܂��A�q�[�v������2*floor(log r)�T�C�Y��subsets�ɕ�������B
//���ꂼ���subset Hs_i�ōċA�I��floor(log r)�Ԗڂɏ������l�܂ł����߁A�����clan C_i�Ƃ���B
//sp(C_i)�͕��ʂ�clan�Ɠ����悤�Ɍ��߁Apr(C_i)��Hs_i�̍��̂���C_i�Ɋ܂܂�Ȃ��m�[�h�����Ƃ���B
//�C���[�W�Ƃ��ẮA���z�I��x�̃m�[�h��floor(log r)����clan���Ȃ��Ă��āA����offspring�Ƃ��ăq�[�v���������݂��Ă���C���[�W�B
//���Ƃ�SEL1�Ɠ����悤�ɂ���B
//
//�v�Z�ʁF
//	
//	�\�z���Ȃ���΂Ȃ�Ȃ�clan�̐��͑�\���I�΂��܂ł̐��Ƃ��̎qclan�𑫂��čő�ł�3�{�ł���B
//	T(r) �� c r + 3 ceil(r/floor(log r)) T(2 floor(log r))
//	�Ƃ����������B������c�͒萔�ł���B
//	�x�[�X�P�[�X�͎����ɒ萔�ł���B
//	�����������T(r) �� O(r 3^{log^* r})�ƂȂ�B
//
//TODO: SEL3 �� SEL4 ��ǂ݉����H
//
//������
//offspring�����鎞�ɁAclan�̂����ǂꂪ�t�ł���̂��𔻒肷��K�v������B
//	����͑�\�ƍ��������i�[���Ă����Ė��񓯂��悤��dfs����Δ���\�ł���B
//poor relation���ǂ�����ĕ\�킷���H
//	�܂��A���̐e��clan�̃I�t�Z�b�g�����B����clan��offspring����������poor relations sets�̂��ƂƂȂ�B
//	���̒��_�������g�����Aclan�̍\�����@���A�uoffspring���̂̂������钸�_�ȉ�����(�̑S��)���g���v�Ƃ������_������ł���B
//	���̒��_��ۑ����Ă����g���Ƃ��Ɍ��Ă��΂悢�B
//nodes�ւ�clan��extract���ꂽ�����߂Ēǉ��������B
//	���̎���representative��p����dfs������΂悢�B
//	���̂��߂ɂ́A�eclan�������Ă��������ł悢�B
//�����ɂ���ă�����(2k nodes + O(k/log k) (words + nodes))�ƂȂ邩�ȁB
//�q�[�v�̒[�̖��B
//	���z�I�ɑ傫�Ȓl�����Ƃ���΂悢���A����ɂ͂܂���肪�����āA
//	�P���Ɂ���P��̓���Ȓl�Ƃ����uniqueness�����藧���Ȃ��Ȃ��Ă��܂��B
//	uniqueness�͏d�v�ł���̂ŁA���Ƃ����Ȃ���΂Ȃ�Ȃ��B
//	�����ŁA���̓t���O�Ƃ��āA���̒��O�̃m�[�h�̏�����ۑ�����悤�ɂ���΂悢�B
//	���Ɣ�r���K�v�ȉӏ���K�؂ɍl���Ă��΂悢�B
//������2�ȊO�ł�������B�ł��萔���������낢��ς�邩�Ǝv��

struct ArrayHeap {
	typedef int T;
	typedef const T *HeapNode;
	const HeapNode a; const int N;
	ArrayHeap(HeapNode a_, int N_): a(a_), N(N_) { }

	bool is_null(HeapNode x) const {
		return x >= a + N;
	}
	bool compare(HeapNode x, HeapNode y) const {
		return *x != *y ? *x < *y : x < y;
	}
	static const int D = 2;
	HeapNode get_child(HeapNode x, int i) const {
		return a + ((x - a) * 2 + 1 + i);
	}
};

template<typename Heap>
class Frederickson {
	typedef typename Heap::HeapNode Node;
	static const int D = Heap::D;

	struct ClanP {	//priority queue�ɓ����p
		Node representative;
		bool infinity;
		int parentindex;	//�eclan��index
		ClanP() { }
		ClanP(const Node &representative_, bool infinity_, int parentindex_):
			representative(representative_), infinity(infinity_), parentindex(parentindex_) { }
		struct GT {
			const Heap &h;
			GT(const Heap &h_): h(h_) { }
			inline bool operator()(const ClanP &a, const ClanP &b) const {
				if(a.infinity != b.infinity) return a.infinity > b.infinity;
				return h.compare(b.representative, a.representative);	//PQ�p�ɋt
			}
		};
	};
	struct Clan {
		Node representative;
		int offset, numsubheaps;	//numsubheaps�̓T�u�q�[�v�̐�(�A�������̐�)�Bnodes[offset, offset+numsubheaps)���������ɂȂ�B
		Node poorbound;	//!ispoor�̏ꍇ����͖���`�Bpoorbound�ȉ���offspring�͊��Ɏg���Ă��邱�Ƃ�\���Ă���
						//���Ԃ�extract�����̂ŁA���I�ɕύX�����
		bool ispoor;	//1��ȏ�g��ꂽ���B����ȍ~��poor relation�Ƃ��Ďg���邱�ƂɂȂ�B���I�ɕύX�����B
		int parentindex;	//�eclan��index
		Clan() { }
		Clan(Node representative_, int offset_, int numsubheaps_, int parentindex_):
			representative(representative_), offset(offset_), numsubheaps(numsubheaps_), poorbound(), ispoor(false), parentindex(parentindex_) { }
	};
	struct NodeLT {
		const Heap &h;
		NodeLT(const Heap &h_): h(h_) { }
		inline bool operator()(const Node &a, const Node &b) const {
			return h.compare(a, b);
		}
	};
	struct NodeGT {
		const Heap &h;
		NodeGT(const Heap &h_): h(h_) { }
		inline bool operator()(const Node &a, const Node &b) const {
			return h.compare(b, a);	//PQ�p�ɋt
		}
	};

	Heap heap;

	Node build_clan(std::vector<Node> &q, bool &infinity, const int clansize) const;
	int extract_clan(const ClanP &clanp, int heapsubsets, std::vector<Clan> &clans, const std::vector<Node> &roots, std::vector<Node> &nodes, bool last, std::vector<Node> &q1, std::vector<Node> &q2, std::vector<Node> &stk1, std::vector<Node> &stk2) const;
public:
	Frederickson(const Heap &heap_): heap(heap_) { }
	//roots�̊e�v�f��null�ł͂Ȃ��K�v������
	void enum_candidates(const std::vector<Node> &roots, int k, std::vector<Node> &nodes) const;
	void enum_candidates(Node root, int k, std::vector<Node> &nodes) const;
};

template<typename Heap>
typename Frederickson<Heap>::Node Frederickson<Heap>::build_clan(std::vector<Node> &q, bool &infinity, const int clansize) const {
	Node repr;
	if(clansize == 1) {
		infinity = false;
		repr = *std::min_element(q.begin(), q.end(), NodeLT(heap));
/*	}else {	//SEL2�A�x���c�H
		std::vector<Node> nodes;
		enum_candidates(q, clansize, nodes);
		if((int)nodes.size() < clansize) {
			infinity = true;
			repr = *std::max_element(nodes.begin(), nodes.end(), NodeLT(heap));
		}else {
			infinity = false;
			std::nth_element(nodes.begin(), nodes.begin() + (clansize-1), nodes.end(), NodeLT(heap));
			repr = nodes[clansize-1];
		}
*/
	}else {
		std::make_heap(q.begin(), q.end(), NodeGT(heap));
		repr = q.front(); int size = 0;
		while(!q.empty()) {
			Node x = q.front();
			std::pop_heap(q.begin(), q.end(), NodeGT(heap));
			q.pop_back();
			repr = x;
			if((++ size) == clansize) break;
			for(int i = 0; i < D; i ++) {
				Node y = heap.get_child(x, i);
				if(!heap.is_null(y)) {
					q.push_back(y);
					std::push_heap(q.begin(), q.end(), NodeGT(heap));
				}
			}
		}
		infinity = size < clansize;
	}

	q.clear();	//�C���^�[�t�F�C�X�I�ɍ�clear���Ă����̂��悳����
	return repr;
}

template<typename Heap>
int Frederickson<Heap>::extract_clan(const ClanP &clanp, int heapsubsets, std::vector<Clan> &clans, const std::vector<Node> &roots, std::vector<Node> &nodes, bool last, std::vector<Node> &q1, std::vector<Node> &q2, std::vector<Node> &stk1, std::vector<Node> &stk2) const {
	Node repr = clanp.representative;
	bool infinity = clanp.infinity;
	int parentindex = clanp.parentindex;
	bool parentisvirtual = parentindex < heapsubsets;
	Clan &parent = clans[parentindex];
	int offset = nodes.size();
	if(parentisvirtual) {
		for(int i = 0; i < parent.numsubheaps; i ++) {
			Node y = roots[parent.offset + i];
			if(parent.ispoor && !heap.compare(parent.poorbound, y)) {
				//���ɐe�E�����ȊO���g���Ă���
			}else if(infinity || !heap.compare(repr, y)) {
				//�e��offspring�ł����āA�������g�ł���B
				stk2.push_back(y);
				nodes.push_back(y);	//���͍ŏ��ɕ��ׂ�悤�ɂ���
			}else {
				//������poor relation set
				if(!last) q2.push_back(y);
			}
		}
	}else {
		for(int i = 0; i < parent.numsubheaps; i ++)
			stk1.push_back(nodes[parent.offset + i]);
		while(!stk1.empty()) {
			Node x = stk1.back(); stk1.pop_back();
			for(int i = 0; i < D; i ++) {
				Node y = heap.get_child(x, i);
				if(heap.is_null(y)) continue;
				if(!heap.compare(parent.representative, y)) {
					//�e���g���g���Ă���
					stk1.push_back(y);
				}else if(parent.ispoor && !heap.compare(parent.poorbound, y)) {
					//���ɐe�E�����ȊO���g���Ă���
				}else if(infinity || !heap.compare(repr, y)) {
					//�e��offspring�ł����āA�������g�ł���B
					stk2.push_back(y);
					nodes.push_back(y);	//���͍ŏ��ɕ��ׂ�悤�ɂ���
				}else {
					//������poor relation set
					if(!last) q2.push_back(y);
				}
			}
		}
	}
	parent.ispoor = true;
	parent.poorbound = repr;
	//����clan��W�J����(nodes�ɕ��ׂ�)
	int numsubheaps = (int)nodes.size() - offset;
	while(!stk2.empty()) {
		Node x = stk2.back(); stk2.pop_back();
		for(int i = 0; i < D; i ++) {
			Node y = heap.get_child(x, i);
			if(heap.is_null(y)) continue;
			if(infinity || !heap.compare(repr, y)) {
				stk2.push_back(y);
				nodes.push_back(y);	//���ȊO����ׂ�
			}else {
				//������offspring
				if(!last) q1.push_back(y);
			}
		}
	}
	return numsubheaps;
}

template<typename Heap>
void Frederickson<Heap>::enum_candidates(const std::vector<Node> &roots, int k, std::vector<Node> &nodes) const {
	if(k <= 0 || roots.empty()) return;
	int clansize = 1;
	while(1 << (clansize+1) <= k) clansize ++;
	int maxextracts = (k + clansize - 1) / clansize;
	std::vector<Clan> clans;	//clan�����B�ŏ��̂������͍��q�[�v�̐e�Ƃ��Ẳ��z�I��clan����
	std::vector<Node> stk1, stk2;	//dfs�Ŏg���X�^�b�N
	std::vector<Node> q1, q2;	//priority_queue���Ƃ��䂢��(�܂Ƃ߂�make_heap�������Eclear�������E�����֌W�Ȃ��C�e���[�g������)�Ɏ肪�Ƃǂ��Ȃ��̂�vector�ł��
	std::vector<ClanP> clansq;	//�����priority queue
	//C_i�̍\�z
	int heapsubsetsize = clansize * 2;	//�萔�����͂��K�؂Ȓl�����邩������Ȃ��B�܂蕁�ʂ�os(C)�̃T�C�Y�܂łƂ������ƂȂ̂ŁH
	int heaps = roots.size(), heapsubsets = (heaps + heapsubsetsize - 1) / heapsubsetsize;
	for(int i = 0; i < heapsubsets; i ++) {
		std::vector<Node> q;
		int first = i * heapsubsetsize;
		int size = std::min(heapsubsetsize, heaps - first);
		for(int j = first; j < first + size; j ++)
			q.push_back(roots[j]);
		bool inf;
		Node r = build_clan(q, inf, clansize);
		clansq.push_back(ClanP(r, inf, clans.size()));
		clans.push_back(Clan(r, first, size, -1));	//repr = r�̓_�~�[�B���̍����ʂ̈Ӗ��ł���
	}
	std::make_heap(clansq.begin(), clansq.end(), typename ClanP::GT(heap));
	int extracts = 0;
	Node lastrepr = roots[0]; bool lastinfinity = false;
	while(!clansq.empty()) {
		ClanP clanp = clansq.front();
		std::pop_heap(clansq.begin(), clansq.end(), typename ClanP::GT(heap));
		clansq.pop_back();
		//�܂�����clan��W�J���Ȃ���΂Ȃ�Ȃ��B���̂��߂ɐeclan��offspring���獪�����𓾂Ȃ���΂Ȃ�Ȃ�
		int offset = nodes.size();
		int numsubheaps = extract_clan(clanp, heapsubsets, clans, roots, nodes, false, q1, q2, stk1, stk2);
		int clanindex = clans.size();
		clans.push_back(Clan(clanp.representative, offset, numsubheaps, clanp.parentindex));

		//�Ō��(k/log k)�Ԗڂ�W�J������I���
		if((++ extracts) == maxextracts) {
			lastrepr = clanp.representative;
			lastinfinity = clanp.infinity;
			break;
		}

		//offspring����h������clan���\�z����B���O��q1��offsprings�����Ă����B
		if(!q1.empty()) {
			bool inf;
			Node r = build_clan(q1, inf, clansize);
			clansq.push_back(ClanP(r, inf, clanindex));
			std::push_heap(clansq.begin(), clansq.end(), typename ClanP::GT(heap));
		}
		//poor relation set����h������clan���\�z����B���O��q2��poor relation set�����Ă����B
		if(!q2.empty()) {
			bool inf;
			Node r = build_clan(q2, inf, clansize);
			clansq.push_back(ClanP(r, inf, clanp.parentindex));
			std::push_heap(clansq.begin(), clansq.end(), typename ClanP::GT(heap));
		}
	}
	//clansq�̎c��̗v�f��W�J����
	for(int idx = 0; idx < (int)clansq.size(); idx ++) {
		ClanP clanp = clansq[idx];
		extract_clan(clanp, heapsubsets, clans, roots, nodes, true, q1, q2, stk1, stk2);
	}
}

template<typename Heap>
void Frederickson<Heap>::enum_candidates(Node root, int k, std::vector<Node> &nodes) const {
	if(heap.is_null(root)) return;
	std::vector<Node> roots(1, root);
	enum_candidates(roots, k, nodes);
}

#include "../Util/TimeIt_Simple.hpp"

const int N = 3000;
int a[N], sorted[N];
int main() {
	while(1) {
	for(int i = 0; i < N; i ++) a[i] = std::rand() % 100;
	std::make_heap(a, a + N, std::greater<int>());
//	for(int i = 0; i < N; i ++) cerr << a[i] << ", "; cerr << endl;
	for(int i = 0; i < N; i ++) sorted[i] = a[i];
	std::sort(sorted, sorted+N);
	ArrayHeap heap(a, N);
	Frederickson<ArrayHeap> frederickson(heap);
	TIMEIT("frederickson_selection k<-[0..N)")
	for(int k = 0; k < N; k ++) {
		std::vector<ArrayHeap::HeapNode> nodes;
		frederickson.enum_candidates(a, k + 1, nodes);
		std::nth_element(nodes.begin(), nodes.begin() + k, nodes.end(), [&heap](const int *x, const int *y) -> bool {
			return heap.compare(x, y);
		});
		ArrayHeap::HeapNode res = nodes[k];
		if(*res != sorted[k])
			cerr << k << ": " << *res << " != " << sorted[k] << endl;
	}
	cerr << "OK" << endl;
	}
	return 0;
}
