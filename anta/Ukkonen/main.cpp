//maximal repeat: <http://www.e-olimp.com/en/solutions/1317275>
/*
	Suffix Tree�Ƃ́A������S�ɑ΂��āA
		S$�̑S�Ă�suffix(init. tails$ s++"$")�̃p�g���V�A��(compressed trie)�ł���B
	�}�𕶎����Ԃ̃|�C���^�ŕ\������悤�ɂ���ƁA��(n)�̃������ŕ\���ł���B

	Ukkonen's��p�����Suffix Tree����(n) where n = |S| �ō\�z�ł���B
		�������A�A���t�@�x�b�g�����p�����[�^�Ɏ��ꍇ�A
		�����ɂ���ă�(n a), ��(n log a), ��(n log min(a,n)) where a = �A���t�@�x�b�g�� ���̌v�Z�ʂɂȂ�B
	Ukkonen's�͂���Ӗ��Łu�I�����C���v�A���S���Y���ł���B
		�擪�̕������珇�Ԃɍ\�z���Ă������Ƃ��ł���B
		�������A�����̕�����͘A�������A�h���X�ɂȂ���΂Ȃ�Ȃ��B
		���p����ƁAGeneralized Suffix Tree���A������𖾎��I�Ɍ������邱�ƂȂ��\�z���邱�Ƃ��o����B
		���̏ꍇ�A�e������͓Ɨ����Ă���̂ŁA�A�������A�h���X�ɂ���K�v�͂Ȃ��B
		�������A���܂�Ӗ��͖����B

	Suffix Tree�̌��_�̓�����������Ȃ�ɕK�v�ł��邱�ƁB
		�m�[�h���Ƃ̎}���ǂ̂悤�ɊǗ����邩�ɂ���āA���x�ƃ������̃g���[�h�I�t������B
		�E�T�C�Ya�̔z��
			������a�ł͍ő������A�傫��a�ł̓���������(a)�ŏ����B
			�܂��A�}�̗񋓂ɂ��ň���(a)�̎��Ԃ�������B
		�E�A�����X�g
			������a�ł͍����ŁA�����������a�Ɉˑ����Ȃ����A�傫��a�ł͍ň���(a)�Œx���Ȃ�B
			�}���\�[�g���邱�Ƃ����R�ɂł���B
		�E�n�b�V���}�b�v
			���ϒ萔�̌v�Z�ʂł͂��邪�A���̒萔������Ȃ�ɏd���B�܂��A����������̒萔���d���B
			�}�̗񋓂�ŏ��̎}�𓾂邱�Ƃ�o(a)�ł͎��R�ɂł��Ȃ��B
		�E���t��
			log�̌v�Z�ʂ͂�͂肻��Ȃ�ɏd���B�܂��A����������̒萔���d���B
			�}�̗񋓂�ŏ��̎}�𓾂邱�ƁAk�Ԗڂ̎}�𓾂邱�Ƃ��悭�ł���B
		������K�؂ɐ؂�ւ�����g�ݍ��킹���肷�邱�Ƃ��ł���B
			���̂悤�Ȍ����͕s���B

	Suffix Tree��DFS����ꍇ�A�ň��[����n�ɂȂ邱�Ƃɒ���(1�̕����̌J��Ԃ��̕�����ɂ���ĒB���ł���)�B
		�ċA�ł��ƃX�^�b�N�I�[�o�[�t���[���邱�Ƃ������B

	Suffix Tree�𗘗p����ƕ�����Ɋւ���l�X�ȁA��ɉ��炩�́u�����v�������ɂł���B
	��{�I�ȍl���Ƃ��āASuffix Tree���ɂ͑S�Ă̕��������񂪊܂܂�Ă���Ƃ������ƁB
		���Ƃ��΁A�����񂪏o�����邩�ǂ����̔���͎����Ƀ�(m) where m = |����������|�łł���B

	�Ek-�Œ����ʕ���������(k-longest common substring)
		�u���̃m�[�h�̎q����k�̑S�Ă̏I�[�������o������v�Ƃ��������𖞂����m�[�h�̂�����Ԃ����܂ł��������̂����߂�΂����B
		�I�[�����̏W���̊Ǘ��Ƀr�b�g���Z���g���Ɨǂ��B

	�E������̑S��/�ŏ�/�Ō�/��/�O�ɏo������ʒu�����߂�
		��(n)�Ŋe�t�ɑ΂��Ē���(�����m�[�h�̐��ł͂Ȃ��A������̒���)�����߂Ă����B
		�ʒu�̗񋓂��������ꍇ�́A���������ɕ��ׂĂ����΁A�e�m�[�h�̎q���ɋ�Ԃ��Ή�����(euler tour �t����ver.)�B
		���ۂ̈ʒu�́A(������̒��� - ����)�ŋ��߂���B
		�����ƈꏏ�ɂǂ̏I�[���������L�^���Ă����Ε����̕�����ł��Ή��ł���B
		���ƁA�i���Z�O�����g�؂�WaveletMatrix�ŊǗ�����΁uk�Ԗڂ̏o���ʒu�v���ł���Ǝv��(���悢���@�͕s��)�B

	�Ematching statistics
		matching statistics�Ƃ́A(map (commonPrefixLength s). init. tails$ s)�B
		Ukkonen's��Suffix Tree�\�z�̂悤�ȁAsuffix link���g�����g���o�[�X�ɂ���ĉ�����B
		�����悤�ȉ�͂ɂ���ă�(m)�Ńg���o�[�X�ł��邱�Ƃ��킩��B
		suffix link���g�����тɐ擪�̈ʒu���E�ɂ����ƍl������B������L�^���Ă����A
		�e�ʒu�ɑ΂��� statistics[�擪�̈ʒu .. ���݂̈ʒu] ���C���N�������g����B
		�����ݐϘa�@�ł��΃�(m)�ɂȂ�B

	�E[longest ]k-repeated substring
		k-repeated substring�Ƃ́AS����k��ȏ�o�����镶����B
		k�ȏ�̗t���q���Ɏ��m�[�h���S�Ă���B
		just k�ł���S�Ă����߂����āA�t�̐���k���傫���ꍇ�Ak-�g�ݍ��킹��S�ċ��߂�΂����B

	�E[shortest ]at most k-repeated substring
		���O�͓K���ɍ�����B
		k-repeated substring�Ɠ����悤�ɂ��΂����B
		���̂Ƃ���shortest k=1 (1�x�����o��)�̂ݎ���(allShortestOccurringOnlyOnceSubstrings)�B

	�Esupermaximal k-repeated substring (supermaximal 2-repeated = supermaximal repeat)
		supermaximal k-repeated substring�Ƃ́AS����k��ȏ�o�����A
		���̕���������E�̂ǂ���ɍL���Ă�S����k��ȏ�o�����Ȃ��Ȃ镶����B
		�E�ɋɑ�́A�q���̃m�[�h��k-repeated�������m�[�h�݂̂��l����΂����B
		���ɋɑ�́Ak-repeated�����suffix link�œ��B�ł��Ȃ��m�[�h�݂̂��l����΂����B
		����𗼕����΋ɑ�(supermaximal)�ɂȂ�B

	�Emaximal k-repeeated substring (maximal 2-repeated = maximal repeat / maximal pair)
		*���傤��* k�� *�ʒu* �ɑ΂��ċɑ�ł���Ak��ȏ�o�����镔��������B
		�E�ɋɑ�́Ak�̗t���A�����̃m�[�h���猩�āu�S�ē����}�v�ł͂Ȃ����̂��l����΂����B
		���ɋɑ�́Ak�̗t���A�u������\��������̍��̕������S�ē����v�ł͂Ȃ����̂��l����΂����B
			����͗t���܂߂��m�[�h���ƂɁusingleton���H�����Ȃ�ǂ̕������H�v���ċA�I�Ɍv�Z������΂����B
		"maximal pair"�Ȃǈʒu�ŋ�ʂ���ꍇ�͓K���ɑg�ݍ��킹������B
		"maximal repeat"�ȂǕ����񂾂����l����ꍇ�̓m�[�h���Ƃ�1�����l����B

	�E�ŕp���������� with �ŏ���������
		�m�[�h�̎q���̗t�̐��𐔂��邾��

	�E����������łȂ��ŒZ������(�����Z�b�g���^������)
		�}�̒�����2�ȏ�̂��̂ɒ��ӁB
		|��|=1�̂Ƃ����܂������悤�ɂ��������v�����Ȃ������̂ŕʃ��[�`���ɂ��Ă���B

	�E����������ɑ΂���Œ����ʐړ���(Longest Common Extension, LCE, Longest Common Prefix, LCP)
		�؂�LCA�ƂȂ�B�K�؂ȃA���S���Y�����g���΃N�G����(1)�B
		���O��(�ʒu(����, GST�̏ꍇ�͐����g) �� �m�[�h�|�C���^��������LCA�p�m�[�h�ԍ�)�̃e�[�u��������Ă����B

	�E�����񌟍� with ���C���h�J�[�h(1���������Ƀ}�b�`����)
		�܂��Ώە�����ƃp�^�[����GST�����B
		�Ώە�����̂ǂ̈ʒu����}�b�`���邩��S�T������B
		�ŏ��ɗ���0�ʒu�����LCE�����߂�B����Ƃǂ��܂Ń}�b�`���邩���킩��B
		���̏ꏊ�����C���h�J�[�h�ł������ꍇ�A���̕������΂�(�J�n�ʒu��LCE����+1�𑫂�)�B
		LCE���p�^�[���̍Ō�܂ōs���Ă���}�b�`�B
		�S�T��n��ɁA���C���h�J�[�h�̂��тɃ��[�v����̂Ń�(n k) (n=|�Ώە�����|, k=���C���h�J�[�h�̐�)

	�Ek��܂Ń~�X�}�b�`�����������񌟍� (k-mismatches)
		���C���h�J�[�h�̂��̂̂悤�ɑS�T��+LCE�Ői�ށB
		LCE�̏ꏊ����ő�k��܂�1�����i�߂Ă�����B
		�������(n k)�B

	�E�Œ��񕶂͑��Ɍ����I�ȃA���S���Y��(Manacher's)������̂Ŗ����B
		����Gap��mismatches�̂���o�[�W�����͎����������c�H
*/

#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
#include <cmath>
#include "../Util/StaticGraph_Simple.cpp"
#include "../LowestCommonAncestor/EulerTourLCA.cpp"

#undef assert
void assert(bool b) {
	if(!b) {
		std::cerr << "Assertion error!" << std::endl;
		abort();
	}
}

typedef unsigned char Alpha; const int NAlpha = 256;
inline bool IsTerminatingAlpha(Alpha a) { return a < 32; }
void OutAlpha(std::ostream &o, Alpha a) {
	if(IsTerminatingAlpha(a))
		o << '$' << static_cast<unsigned>(a);
	else
		o << static_cast<char>(a);
}

const int ListToArrayParam = (int)pow(NAlpha*1., 0.4);
class GeneralizedSuffixTree {
public:
	typedef std::pair<const Alpha*, const Alpha*> StrPair;
private:
	struct Leaf {
		const Alpha *begin, *end;	//1�̕����񂾂��Ȃ�end��Leaf�ɂ͂���Ȃ����ǁAgeneralized���ƕK�v�ȋC������
		Leaf *next;
		Leaf() { }
		Leaf(const Alpha *b): begin(b), next(NULL), end(NULL) { }
		Alpha terminatingAlpha() const { return *(end-1); }
		int length() const { return end - begin; }
	};
	struct Node : Leaf {	//root��internal node
		union { Leaf *head; Leaf **edges; };
		Node *suffix;
		Node() { suffix = NULL; head = NULL; }
	};

	int nNodes, nLeafs;
	Node *nodes; Leaf *leafs, *poolend;
	Node *root;
	std::vector<Leaf**> edgeArrays;
	std::vector<StrPair> addedStrings;

	bool isLeaf(const Leaf *p) const { return leafs <= p; }
	bool isListStyle(const Node *p) const { return !p->head || ((Leaf*)nodes <= p->head && p->head < poolend); }

#define FOR_EACH_EDGES_(e, n, c)\
	for(Leaf *c *e##_ = isListStyle(n) ? &n->head : n->edges;\
	isListStyle(n) ? (*e##_ != NULL) : (e##_ < n->edges + NAlpha);\
	isListStyle(n) ? (e##_ = &(*e##_)->next) : (++ e##_))\
	if(c Leaf *e = *e##_)
#define FOR_EACH_EDGES_V(e, n) FOR_EACH_EDGES_(e, n, )
#define FOR_EACH_EDGES_C(e, n) FOR_EACH_EDGES_(e, n, const)

	Leaf **listToArray(Node *node) {
		Leaf **edges = (Leaf**)malloc(NAlpha * sizeof(Leaf*));
		memset(edges, 0, sizeof(Leaf*) * NAlpha);
		FOR_EACH_EDGES_V(leaf, node)
			edges[*leaf->begin] = leaf;
		edgeArrays.push_back(edges);
		return edges;
	}

	inline Leaf **getEdgeRef(Node *node, Alpha a) {
		if(!isListStyle(node)) return &node->edges[a];
		Leaf **ref; int len = 0;
		for(ref = &node->head; *ref != NULL; ref = &(*ref)->next, ++ len) {
			if(len >= ListToArrayParam)
				return &(node->edges = listToArray(node))[a];
			if(*(*ref)->begin == a)
				return ref;
		}
		return ref;
	}
	inline Leaf *getEdge(const Node *node, Alpha a) const {
		if(!isListStyle(node)) return node->edges[a];
		for(Leaf *leaf = node->head; leaf != NULL; leaf = leaf->next)
			if(*leaf->begin == a) return leaf;
		return NULL;
	}
	inline void addEdge(Node *node, Alpha a, Leaf *edge) {
		if(!isListStyle(node)) {
			node->edges[a] = edge;
		}else {
			Leaf *head = node->head;
			node->head = edge;
			edge->next = head;
		}
	}
	void outLeafName(std::ostream &o, const Leaf *leaf) const {
		o << '"' << static_cast<const void*>(leaf) << '"';
	}
	void outRec(std::ostream &o, const Node *node, bool visSuffix) const {
		if(visSuffix && node->suffix) {
			outLeafName(o, node); o << " -> "; outLeafName(o, node->suffix); o << ' ';
			o << "[style=dotted, constraint=false]" << ";\n";
		}
		FOR_EACH_EDGES_C(edge, node) {
			outLeafName(o, node); o << " -> "; outLeafName(o, edge); o << ' ';
			o << "[label=<";
			for(const Alpha *p = edge->begin; p < edge->end; ++ p) {
				OutAlpha(o, *p);
			}
			o << ">];\n";
			if(!isLeaf(edge))
				outRec(o, (Node*)edge, visSuffix);
		}
	}
public:
	GeneralizedSuffixTree(int n): nNodes(0), nLeafs(0),
		nodes((Node*)malloc(sizeof(Node) * n + sizeof(Leaf) * n)), leafs((Leaf*)(nodes + n)),
		poolend(leafs + n), root(new(&nodes[nNodes ++]) Node()) {
		root->begin = root->end = NULL;
		initTraversalData();
	}
	~GeneralizedSuffixTree() {
		free(nodes);
		for(int i = 0; i < (int)edgeArrays.size(); i ++)
			free(edgeArrays[i]);
		deleteTraversalData();
	}

	//str��IsTerminatingAlpha(a)��true�ƂȂ镶���ŏI�[����Ă���K�v������
	//�����̕������ǉ�����ꍇ�́A���ꂼ��̏I�[��������ӂłȂ���΂Ȃ�Ȃ�
	void addString(const Alpha *str) {
		Node *active = root; const Alpha *activePos; int activeLen = 0;
		const Alpha *currentPos = str, *proceeded = str;
		int old_nLeafs = nLeafs;
		do {
			if(currentPos-str && (currentPos-str) % 100000 == 0) std::cout << (proceeded-str) << ", " << (currentPos-str) << ": edgeArrays = " << edgeArrays.size() << std::endl;
			Alpha currentAlpha = *currentPos; Node *prevNode = NULL;
			while(proceeded <= currentPos) {
				if(activeLen == 0) activePos = currentPos;
				Leaf **activeEdgeRef = getEdgeRef(active, *activePos);
				Leaf *activeEdge = *activeEdgeRef;
				Node *splitNode = active;
				if(activeEdge) {
					if(!isLeaf(activeEdge) && activeLen >= activeEdge->length()) {
						active = (Node*)activeEdge;
						activePos += ((Node*)activeEdge)->length();
						activeLen -= ((Node*)activeEdge)->length();
						continue;
					}else if(*(activeEdge->begin + activeLen) == currentAlpha) {
						activeLen ++;
						if(prevNode) prevNode->suffix = active;
						break;
					}else {
						const Alpha *splitPos = activeEdge->begin + activeLen;
						Leaf *nextLeaf = activeEdge->next;
						*activeEdgeRef = splitNode = new(&nodes[nNodes ++]) Node();
						splitNode->begin = activeEdge->begin;
						splitNode->end = activeEdge->begin = splitPos;
						addEdge(splitNode, *splitPos, activeEdge);
						splitNode->next = nextLeaf;
					}
				}
				addEdge(splitNode, currentAlpha, new(&leafs[nLeafs ++]) Leaf(currentPos));
				if(prevNode) prevNode->suffix = splitNode;
				prevNode = splitNode;
				proceeded ++;
				if(active == root && activeLen > 0) {
					activeLen --;
					activePos = proceeded;
				}else
					active = active->suffix ? active->suffix : root;
			}
		}while(!IsTerminatingAlpha(*(currentPos ++)));
		assert(currentPos == proceeded);
		addedStrings.push_back(std::make_pair(str, currentPos));
		for(int i = old_nLeafs; i < nLeafs; i ++)
			leafs[i].end = currentPos;
	}

	void debugOutDotGraph(std::ostream &o, bool visSuffix = true) const {
		o << "digraph {\n";
		o << "style = dot;\n";
		o << "node [shape=point];\n";
		outRec(o, root, visSuffix);
		o << "}" << std::endl;
	}

private:
	struct Position {
		const Leaf *leaf;
		const Alpha *pos;
		Position(const Leaf *l, const Alpha *p): leaf(l), pos(p) { }
	};
	inline Position initialPosition() const {
		return Position(root, NULL);
	}
	//Leaf�̍Ō�ɍs�������ƂɃ}�b�`����ꍇ�͖���`�B
	//�I�[�������o�����Ȃ����Ō��1�񂾂��o���Ȃ���Ȃ�
	inline void matchAlpha(Position &p, Alpha a) const {
		if(!p.leaf) return;
		if(p.leaf->end == p.pos) {
			const Leaf *edge = getEdge(static_cast<const Node*>(p.leaf), a);
			p.leaf = edge;
			if(edge) p.pos = edge->begin + 1;
		}else {
			if(*p.pos == a) ++ p.pos;
			else p.leaf = NULL;
		}
	}
	//�}�b�`���Ȃ���؂��~��Ă���
	inline void matchString(Position &p, const Alpha *begin, const Alpha *end) const {
		while(begin < end) matchAlpha(p, *(begin ++));
	}

public:
	bool isSuffix(const Alpha *begin, const Alpha *end, Alpha terminatingAlpha) const {
		Position p = initialPosition();
		matchString(p, begin, end);
		matchAlpha(p, terminatingAlpha);
		return p.leaf != NULL;
	}
	bool isSubString(const Alpha *begin, const Alpha *end) const {
		Position p = initialPosition();
		matchString(p, begin, end);
		return p.leaf != NULL;
	}
	static const Alpha *getStringLast(const Alpha *str) {
		while(!IsTerminatingAlpha(*str)) ++ str;
		return str;
	}
	//Tested
	bool isSuffix(const Alpha *str) const {
		const Alpha *end = getStringLast(str);
		return isSuffix(str, end, *end);
	}

	//Verified: POJ 2217 (788K / 79MS)
	//�J��Ԃ��̑�������������ł��ꍇ�ɂ̓X�^�b�N�I�[�o�[�t���[�EMLE�ɒ���
	int longestCommonSubstringLength(unsigned kmask) const {
		return longestCommonSubstring_rec(root, kmask).second;
	}

private:
	//�Ԃ�l: (�r�b�g�Z�b�g, if �r�b�g�Z�b�g���t�� then ���� else 0)
	//����������߂����Ȃ�K���Ɍo�H��������΂悢�B
	std::pair<unsigned, int> longestCommonSubstring_rec(const Leaf *leaf, unsigned kmask) const {
		if(isLeaf(leaf)) {	//�I�[�P�[�X
			return std::make_pair(1U << leaf->terminatingAlpha(), 0);
		}
		const Node *node = static_cast<const Node*>(leaf);
		unsigned bits = 0;
		std::pair<int, const Leaf*> p = std::make_pair(-1, (const Leaf*)NULL);
		FOR_EACH_EDGES_C(edge, node) {
			std::pair<unsigned, int> q;
			q = longestCommonSubstring_rec(edge, kmask);
			bits |= q.first;
			if((q.first & kmask) == kmask)
				p = std::max(p, std::make_pair(q.second + edge->length(), edge));
		}
		if(!p.second) return std::make_pair(bits, 0);
		return std::make_pair(bits, p.first);
	}

public:
	void addByteString(const char *s) { addString((const Alpha*)s); }

private:
	//suffix link���g���p�B���Leaf�łȂ�Node���w�����Ƃ��|�C���g
	struct PositionS {
		const Node *node;
		Alpha alpha;
		const Leaf *cache_edge;
		int length;
	};

	PositionS initialPositionS() const {
		PositionS pos;
		pos.node = root;
		pos.length = 0;
		pos.cache_edge = NULL;
		return pos;
	}

	//�߂�l: suffix link���g������(������root����ړ����悤�Ƃ����̂��܂܂��)
	//Ukkonen's�̃��C�������Ǝ��Ă���B
	//(pos.node�܂ł̒��� + pos.length)�ŗ}�����āA�Ȃ炵��(1)�̂͂�
	int matchAlphaS(PositionS &pos, Alpha a) const {
		int count = 0;
		while(1) {
			if(pos.length == 0)
				pos.cache_edge = getEdge(pos.node, pos.alpha = a);
			if(pos.cache_edge && *(pos.cache_edge->begin + pos.length) == a)
				break;
			count ++;
			const Alpha *p = pos.cache_edge ? pos.cache_edge->begin : NULL;
			if(pos.node == root) {
				if(pos.length == 0) break;
				if(-- pos.length)
					pos.cache_edge = getEdge(pos.node, pos.alpha = *(++ p));
			}else {
				pos.node = pos.node->suffix;
				if(pos.length) pos.cache_edge = getEdge(pos.node, pos.alpha);
			}
			if(pos.cache_edge)
				while(pos.length >= pos.cache_edge->length()) {
					pos.length -= pos.cache_edge->length();
					p += pos.cache_edge->length();
					pos.node = static_cast<const Node*>(pos.cache_edge);
					if(pos.length)
						pos.cache_edge = getEdge(pos.node, pos.alpha = *p);
					else {
						pos.cache_edge = NULL;
						break;
					}
				}
		}
		if(pos.cache_edge) {
			if(pos.cache_edge->length() == ++ pos.length) {
				pos.node = static_cast<const Node*>(pos.cache_edge);
				pos.length = 0;
				pos.cache_edge = NULL;
			}
		}
		return count;
	}

private:

	struct LeafData {
		Leaf *leaf;
		int substringLength;
		const Alpha *getBegin() const { return leaf->end - substringLength; }
	};

	int *nodeLeftIndex, *nodeRightIndex, *leafIndex;
	LeafData *leafSequence;
	const LeafData **leftestSubstringLeaf;
	int *nodeSubstringLength;

	void initTraversalData() {
		nodeLeftIndex = nodeRightIndex = leafIndex = NULL;
		leafSequence = NULL;
		leftestSubstringLeaf = NULL;
		nodeSubstringLength = NULL;
	}
	void deleteTraversalData() {
		delete[] nodeLeftIndex;
		delete[] nodeRightIndex;
		delete[] leafIndex;
		delete[] leafSequence;
		delete[] leftestSubstringLeaf;
		delete[] nodeSubstringLength;
		initTraversalData();
	}

public:
	//�X�^�b�N�I�[�o�[�t���[�ɒ���
	//�������E���x���������ꍇ�͕K�v�ȃf�[�^�����ɂ��邱��
	void leafTraversal() {
		deleteTraversalData();
		leafIndex = new int[nLeafs];
		nodeLeftIndex = new int[nNodes];
		nodeRightIndex = new int[nNodes];
		leafSequence = new LeafData[nLeafs];
		nodeSubstringLength = new int[nNodes];
		int tmp_i = 0;
		leafTraversal_rec(root, tmp_i, 0);
		assert(tmp_i == nLeafs);
	}

private:
	void leafTraversal_rec(Leaf *leaf, int &inout_i, int len) {
		if(isLeaf(leaf)) {
			leafIndex[leaf - leafs] = inout_i;
			LeafData &data = leafSequence[inout_i ++];
			data.leaf = leaf;
			data.substringLength = len;
			return;
		}
		Node *node = (Node*)leaf;
		nodeSubstringLength[node - nodes] = len;
		nodeLeftIndex[node - nodes] = inout_i;
		FOR_EACH_EDGES_V(edge, node)
			leafTraversal_rec(edge, inout_i, len + edge->length());
		nodeRightIndex[node - nodes] = inout_i;
	}


	void getLeafInterval(const Leaf *leaf, int &out_left, int &out_right) const {
		if(isLeaf(leaf))
			out_right = (out_left = leafIndex[leaf - leafs]) + 1;
		else {
			const Node *node = (const Node*)leaf;
			out_left = nodeLeftIndex[node - nodes];
			out_right = nodeRightIndex[node - nodes];
		}
	}
public:
	//v���̏����͌��܂��Ă��Ȃ����Ƃɒ���
	void findAll(const Alpha *begin, const Alpha *end, std::vector<const Alpha *> &out_v) const {
		assert(nodeLeftIndex && nodeRightIndex && leafSequence);
		Position p = initialPosition();
		matchString(p, begin, end);
		if(p.leaf == NULL) return;
		int left, right;
		getLeafInterval(p.leaf, left, right);
		for(int i = left; i < right; i ++)
			out_v.push_back(leafSequence[i].getBegin());
	}

	int countSubstring(const Alpha *begin, const Alpha *end) {
		assert(nodeLeftIndex && nodeRightIndex);
		Position p = initialPosition();
		matchString(p, begin, end);
		if(p.leaf == NULL) return 0;
		int left, right;
		getLeafInterval(p.leaf, left, right);
		return right - left;
	}

	int longestKRepeatedSubstringLength(int k) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength);
		int maxLen = 0;
		if(k <= 1)	//�R�[�i�[�P�[�X�Bk=1���Ɨt������K�v������B
					//����ɁA�����ɏI�[�������܂ނ��Ƃɒ���(��肪����΍�邱��)
			for(int i = 0; i < nLeafs; i ++)
				maxLen = std::max(maxLen, leafSequence[i].substringLength);
		else for(int i = 0; i < nNodes; i ++)
			if(k <= nodeRightIndex[i] - nodeLeftIndex[i])
				maxLen = std::max(maxLen, nodeSubstringLength[i]);
		return maxLen;
	}

	//out_sets�̊e�v�f�̃T�C�Y��k *�ȏ�* �B�����͌��܂��Ă��Ȃ����Ƃɒ���
	int allLongestKRepeatedSubstrings(int k, std::vector<std::vector<const Alpha*> > &out_sets) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength && leafSequence);
		int maxLen = longestKRepeatedSubstringLength(k);
		if(k <= 1) {	//�I�[�������܂ނ��Ƃɒ���
			for(int i = 0; i < nLeafs; i ++)
				if(leafSequence[i].substringLength == maxLen) {
					out_sets.push_back(std::vector<const Alpha*>());
					out_sets.back().push_back(leafSequence[i].getBegin());
				}	//�]�k�F������if�̂����Ł���if(k <= 1)�ɊJ�����ʂ�����K�v������
		}else for(int i = 0; i < nNodes; i ++)
			if(k <= nodeRightIndex[i] - nodeLeftIndex[i] &&
				nodeSubstringLength[i] == maxLen) {
				out_sets.push_back(std::vector<const Alpha*>());
				for(int j = nodeLeftIndex[i]; j < nodeRightIndex[i]; j ++)
					out_sets.back().push_back(leafSequence[j].getBegin());
			}
		return maxLen;
	}

	typedef std::pair<int, std::vector<const Alpha*> > MaximalTuple;	//Tuple�Ƃ����Ă����Ȃ��珇�������Ȃ̂ł�
	//k=2�̏ꍇ��"supermaximal repeat"�ƌĂ΂��
	//out_sets��{(����, [�擪])}�Bout_sets�̊e�v�f�̃T�C�Y��k *�ȏ�* �B�����͌��܂��Ă��Ȃ����Ƃɒ���
	void allSupermaximalKRepeatedSubstrings(int k, std::vector<MaximalTuple> &out_sets) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength && leafSequence);
		if(k <= 1) {	//�R�[�i�[�P�[�X�B�S�Ă̕������P�ɕԂ��΂���
			for(int i = 0; i < (int)addedStrings.size(); i ++) {
				const std::pair<const Alpha*, const Alpha*> &p = addedStrings[i];
				out_sets.push_back(std::make_pair(p.second - p.first, std::vector<const Alpha*>(1, p.first)));
			}
			return;
		}
		char *tmp = new char[nNodes];
		memset(tmp, 0, nNodes);
		allSupermaximalKRepeatedSubstrings_rec(root, k, tmp);
		for(int i = 0; i < nNodes; i ++)
			if(tmp[i] == 1) {
				out_sets.push_back(std::make_pair(nodeSubstringLength[i], std::vector<const Alpha*>()));
				for(int j = nodeLeftIndex[i]; j < nodeRightIndex[i]; j ++)
					out_sets.back().second.push_back(leafSequence[j].getBegin());
			}
		delete[] tmp;
	}
private:
	bool allSupermaximalKRepeatedSubstrings_rec(const Leaf *leaf, const int k, char out_tmp[]) const {
		if(isLeaf(leaf))	//k=1�͂����ł͖���
			return false;
		const Node *node = (const Node*)leaf;
		bool b = false;
		FOR_EACH_EDGES_C(edge, node)
			b |= allSupermaximalKRepeatedSubstrings_rec(edge, k, out_tmp);
		int i = node - nodes;
		if(!b && nodeRightIndex[i] - nodeLeftIndex[i] >= k) {
			b = true;
			out_tmp[i] |= 1;
			if(node != root) out_tmp[node->suffix - nodes] |= 2;
		}
		return b;
	}
public:
	typedef std::vector<std::pair<std::pair<Alpha, Alpha>, const Alpha*> > MaximalSet;
	typedef std::vector<std::pair<int, MaximalSet> > MaximalSets;
	//minimumLength�ȏ�̂��̂�����񍐂���B�f�t�H���g��1(0���Ƌ󕶎����񍐂����)�B
	//k=2�̏ꍇ��"maximal pair"�ƌĂ΂��B
	//out_sets��{(����, [(�O�̕���,�擪)])}�B
	//out_sets�̂����A�u�S��first.first�������v�łȂ� ���u�S��first.second�������v�łȂ� k-�g�ݍ��킹�����ׂ�k-repeated tuple�ɂȂ�B
	void allMaximalKRepeatedSubstrings(int k, MaximalSets &out_sets, int minimumLength = 1) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength && leafSequence);
		if(k <= 1) {
			for(int i = 0; i < (int)addedStrings.size(); i ++) {
				const std::pair<const Alpha*, const Alpha*> &p = addedStrings[i];
				if(p.second - p.first >= minimumLength) {
					out_sets.push_back(std::make_pair(p.second - p.first, MaximalSet()));
					out_sets.back().second.push_back(std::make_pair(
						std::make_pair(*(p.second-1), *(p.second-1)), p.first));
				}
			}
			return;
		}
		allMaximalKRepeatedSubstrings_rec(root, k, minimumLength, out_sets);
	}

	//out_combs�̊e�v�f.second�̃T�C�Y�� *���傤��* k�B
	//allMaximalKRepeatedSubstrings�̌��ʂ�g�ݍ��킹�邾���B���͎w���֐��I�ɑ�������̂Œ��ӁB
	void allMaximalKRepeatedTupleCombinations(int k, std::vector<MaximalTuple> &out_combs, int minimumLength = 1) {
		MaximalSets sets;
		allMaximalKRepeatedSubstrings(k, sets, minimumLength);
		if(k <= 1) {
			for(int i = 0; i < (int)sets.size(); i ++) {
				out_combs.push_back(std::make_pair(sets[i].first, std::vector<const Alpha*>()));
				out_combs.back().second.push_back(sets[i].second[0].second);
			}
		}else for(int i = 0; i < (int)sets.size(); i ++) {
			const MaximalSet &set = sets[i].second;
			std::vector<const Alpha*> tmp;
			allMaximalKRepeatedTupleCombinations_rec(0, k, 0, Alpha(), Alpha(), tmp, sets[i].first, set, out_combs);
		}
	}

	//k=2�̏ꍇ��"maximal repeat"�ƌĂ΂��B
	//�󕶎����Ԃ��̂ŁA�v��Ȃ��Ȃ�͂�������
	void allMaximalKRepeatedSubstrings_stringOnly(int k, std::vector<StrPair> &out_strs) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength && leafSequence);
		if(k <= 1) {
			for(int i = 0; i < (int)addedStrings.size(); i ++)
				out_strs.push_back(addedStrings[i]);
			return;
		}
		allMaximalKRepeatedSubstrings_stringOnly_rec(root, k, out_strs);
	}

private:
	const Alpha *getLeafPrevAlpha(const Leaf *leaf) const {
		const LeafData &data = leafSequence[leafIndex[leaf - leafs]];
		//�Ƃ肠�����B������̐��̓A���t�@�x�b�g�T�C�Y�ŗ}�����čň���(n a)�Ȃ̂ŁA�ꉞa���萔�Ȃ���`
		for(int j = 0; j < (int)addedStrings.size(); j ++) {
			const std::pair<const Alpha*, const Alpha*> &p = addedStrings[j];
			if(p.second == data.leaf->end && p.second - p.first == data.substringLength)
				return p.second-1;
		}
		return data.getBegin()-1;
	}

	const Alpha *allMaximalKRepeatedSubstrings_rec(const Leaf *leaf, const int k, const int minimumLength, MaximalSets &out_sets) const {
		if(isLeaf(leaf)) return getLeafPrevAlpha(leaf);
		const Node *node = (const Node*)leaf;
		const Alpha *a; bool first = true;
		FOR_EACH_EDGES_C(edge, node) {
			const Alpha *b = allMaximalKRepeatedSubstrings_rec(edge, k, minimumLength, out_sets);
			if(first) a = b, first = false;
			else if(a == NULL || b == NULL || *a != *b) a = NULL;
		}
		const int i = node - nodes;
		if(a == NULL && nodeRightIndex[i] - nodeLeftIndex[i] >= k &&
			nodeSubstringLength[i] >= minimumLength) {
			out_sets.push_back(std::make_pair(nodeSubstringLength[i], MaximalSet()));
			FOR_EACH_EDGES_C(edge, node) {
				int left, right;
				getLeafInterval(edge, left, right);
				for(int j = left; j < right; j ++) {
					const LeafData &data = leafSequence[j];
					std::pair<Alpha, Alpha> p(
						*allMaximalKRepeatedSubstrings_rec(data.leaf, k, minimumLength, out_sets),
						*edge->begin);
					out_sets.back().second.push_back(std::make_pair(p, data.getBegin()));
				}
			}
		}
		return a;
	}

	const Alpha *allMaximalKRepeatedSubstrings_stringOnly_rec(const Leaf *leaf, const int k, std::vector<StrPair> &out_strs) const {
		if(isLeaf(leaf)) return getLeafPrevAlpha(leaf);
		const Node *node = (const Node*)leaf;
		const Alpha *a; bool first = true;
		FOR_EACH_EDGES_C(edge, node) {
			const Alpha *b = allMaximalKRepeatedSubstrings_stringOnly_rec(edge, k, out_strs);
			if(first) a = b, first = false;
			else if(a == NULL || b == NULL || *a != *b) a = NULL;
		}
		const int i = node - nodes;
		if(a == NULL && nodeRightIndex[i] - nodeLeftIndex[i] >= k) {
			const Alpha *s = leafSequence[nodeLeftIndex[i]].getBegin();
			out_strs.push_back(std::make_pair(s, s + nodeSubstringLength[i]));
		}
		return a;
	}

	//�i�C�[�u�ɑg�ݍ��킹�𐶐�����
	void allMaximalKRepeatedTupleCombinations_rec(int i, int remK, unsigned bitflags, Alpha a, Alpha b, std::vector<const Alpha*> &inout_seq, const int strLen, const MaximalSet &set, std::vector<MaximalTuple> &out_combs) {
		if(i == set.size()) {
			if(remK == 0 && bitflags == 7)
				out_combs.push_back(std::make_pair(strLen, inout_seq));
			return;
		}
		//�g��Ȃ��ꍇ
		if(remK < (int)set.size() - i)
			allMaximalKRepeatedTupleCombinations_rec(i+1, remK, bitflags, a, b, inout_seq, strLen, set, out_combs);
		//�g���ꍇ
		if(remK > 0) {
			Alpha aa = set[i].first.first, bb = set[i].first.second;
			if(bitflags == 0) {
				bitflags = 1;
				a = aa; b = bb;
			}
			if(a != aa) bitflags |= 2;
			if(b != bb) bitflags |= 4;
			inout_seq.push_back(set[i].second);
			allMaximalKRepeatedTupleCombinations_rec(i+1, remK-1, bitflags, a, b, inout_seq, strLen, set, out_combs);
			inout_seq.pop_back();
		}
	}

public:
	int mostFrequentlyOccurrings(int minimumLength) const {
		assert(nodeLeftIndex && nodeRightIndex && nodeSubstringLength && leafSequence);
		int maxCount = 0;
		for(int i = 0; i < nNodes; i ++)
			if(nodeSubstringLength[i] >= minimumLength)
				maxCount = std::max(maxCount, nodeRightIndex[i] - nodeLeftIndex[i]);
		for(int i = 0; i < nLeafs; i ++)
			if(leafSequence[i].substringLength >= minimumLength)
				maxCount = std::max(maxCount, 1);
		return maxCount;
	}

	int allMostFrequentlyOccurringSubstring(int minimumLength, std::vector<StrPair> &out_v) const {
		int maxCount = mostFrequentlyOccurrings(minimumLength);
		for(int i = 0; i < nNodes; i ++)
			if(nodeRightIndex[i] - nodeLeftIndex[i] == maxCount) {
				int maxLen = nodeSubstringLength[i];
				const Alpha *p = leafSequence[nodeLeftIndex[i]].getBegin();
				//�}�̊Ԃ̒��r���[�ȏꏊ���K�v�Ȃ��Ƃɒ��ӁB���p�I�ɂ�maximal�ɂ���̂��ȁH
				for(int len = maxLen; len >= minimumLength && maxLen - len < nodes[i].length(); len --)
					out_v.push_back(std::make_pair(p, p + len));
			}
		for(int i = 0; i < nLeafs; i ++)
			if(maxCount == 1) {
				const LeafData &data = leafSequence[i];
				int maxLen = data.substringLength;
				const Alpha *p = data.getBegin();
				for(int len = maxLen; len >= minimumLength && maxLen - len < data.leaf->length(); len --)
					out_v.push_back(std::make_pair(p, p + len));
			}
		return maxCount;
	}

	//�I�[�����͊܂܂Ȃ��B"aaa$"��"a$"�͑ʖ�(���������Ǝ����ɒ���2�ȉ��ɂȂ��Ă��܂�)
	//�󕶎��ɂ�0��Ԃ�(����`�ł���)�B
	int shortestOccurringOnlyOnceSubstringLength() const {
		assert(leafSequence != NULL);
		int minLen = INT_MAX;
		for(int i = 0; i < nLeafs; i ++) {
			const Leaf *leaf = leafSequence[i].leaf;
			if(leaf->length() > 1)
				minLen = std::min(minLen, leafSequence[i].substringLength - (leaf->length() - 1));
		}
		return minLen != INT_MAX ? minLen : 0;
	}
	int allShortestOccurringOnlyOnceSubstrings(std::vector<StrPair> &out_v) const {
		int minLen = shortestOccurringOnlyOnceSubstringLength();
		if(minLen == 0) return 0;
		for(int i = 0; i < nLeafs; i ++) {
			const LeafData &data = leafSequence[i];
			const Leaf *leaf = data.leaf;
			if(leaf->length() > 1 && data.substringLength - (leaf->length() - 1) == minLen)
				out_v.push_back(std::make_pair(data.getBegin(), data.getBegin() + minLen));
		}
		return minLen;
	}
private:

public:

	//euler tour���������ƂɌĂԁBfindFirst�ɕK�v
	void makeFindFirstData() {
		assert(leafSequence != NULL);
		delete[] leftestSubstringLeaf;
		leftestSubstringLeaf = new const LeafData*[nNodes];
		makeFindFirstData_rec(root);
	}
	const Alpha *findFirst(const Alpha *begin, const Alpha *end) {
		assert(leafIndex != NULL && leafSequence != NULL && leftestSubstringLeaf != NULL);
		Position p = initialPosition();
		matchString(p, begin, end);
		if(p.leaf == NULL) return NULL;
		const LeafData *data;
		if(isLeaf(p.leaf))
			data = &leafSequence[leafIndex[p.leaf - leafs]];
		else
			data = leftestSubstringLeaf[(const Node*)p.leaf - nodes];
		return data->getBegin();
	}

private:

	const LeafData *makeFindFirstData_rec(const Leaf *leaf) {
		if(isLeaf(leaf))
			return &leafSequence[leafIndex[leaf - leafs]];
		const Node *node = (const Node*)leaf;
		const LeafData *leftest = NULL;
		FOR_EACH_EDGES_C(edge, node) {
			const LeafData *data = makeFindFirstData_rec(edge);
			if(!leftest || leftest->substringLength < data->substringLength)
				leftest = data;
		}
		leftestSubstringLeaf[node - nodes] = leftest;
		return leftest;
	}

public:
	//Tested
	void matchingStatistics(const Alpha *begin, const Alpha *end, int out_lengths[/*end - begin*/]) const {
		int n = end - begin;
		std::fill(out_lengths, out_lengths + n, 0);
		int matchHead = 0;
		PositionS pos = initialPositionS();
		for(int i = 0; i < n; ++ i) {
			matchHead += matchAlphaS(pos, *(begin + i));
			//out_lengths[matchHead..i] ++;
			out_lengths[i] ++;
			if(matchHead) out_lengths[matchHead-1] --;
		}
		//�ݐϘa�����
		for(int i = n-2; i >= 0; i --) out_lengths[i] += out_lengths[i+1];
	}

	//Tested
	int commonPrefixLength(const Alpha *begin, const Alpha *end) const {
		Position pos = initialPosition();
		for(const Alpha *p = begin; p < end; ++ p) {
			matchAlpha(pos, *p);
			if(pos.leaf == NULL) return p - begin;
		}
		return end - begin;
	}

public:
	//alphas�̓\�[�g����Ă���K�v������
	int notOccurringShortestStringLength(const std::vector<Alpha> &alphas) {
		if(alphas.size() == 1) {	//�R�[�i�[�P�[�X
			Position p = initialPosition();
			int len = 0;
			while(p.leaf)
				matchAlpha(p, alphas[0]), len ++;
			return len;
		}else
			return notOccurringShortestString_rec(root, NULL, alphas);
	}
	//���̎����ł͎������ŏ��̂��̂�Ԃ�
	int notOccurringShortestString(const std::vector<Alpha> &alphas, std::vector<Alpha> &out_str) {
		if(alphas.size() == 1) {
			int len = notOccurringShortestStringLength(alphas);
			for(int i = 0; i < len; i ++)
				out_str.push_back(alphas[0]);
			return len;
		}else
			return notOccurringShortestString_rec(root, &out_str, alphas);
	}

private:
	//|alphas|=1�͂����ł͖���
	int notOccurringShortestString_rec(const Leaf *leaf, std::vector<Alpha> *out_str, const std::vector<Alpha> &alphas) {
		if(isLeaf(leaf)) {
			if(out_str) out_str->push_back(alphas[0]);
			return 1;
		}
		const Node *node = (const Node*)leaf;
		std::vector<std::pair<Alpha, const Leaf*> > nexts;
		FOR_EACH_EDGES_C(edge, node)
			nexts.push_back(std::make_pair(*edge->begin, edge));
		std::sort(nexts.begin(), nexts.end());
		std::vector<Alpha>::const_iterator i = alphas.begin();
		std::vector<std::pair<Alpha, const Leaf*> >::const_iterator j = nexts.begin();

		std::pair<std::pair<int, Alpha>, const Leaf*> mini =
			std::make_pair(std::make_pair(INT_MAX, Alpha()), (const Leaf*)NULL);
		while(i != alphas.end() || j != nexts.end()) {
			if(i == alphas.end() || (j != nexts.end() && j->first < *i))
				++ j;
			else if(j == nexts.end() || j->first > *i) {
				mini = std::min(mini, std::make_pair(std::make_pair(1, *i), (const Leaf*)NULL));
				++ i;
			}else {
				const Leaf *edge = j->second;
				if(edge->length() > 1)
					mini = std::min(mini, std::make_pair(std::make_pair(2, *i), edge));
				else
					mini = std::min(mini, std::make_pair(std::make_pair(
						1 + notOccurringShortestString_rec(edge, NULL, alphas), *i),
						edge));
				++ i, ++ j;
			}
		}
		if(out_str) {
			out_str->push_back(mini.first.second);
			const Leaf *edge = mini.second;
			if(edge && edge->length() > 1) {
				for(int i = 0; i < (int)alphas.size(); i ++)
					if(alphas[i] != *(edge->begin+1)) {
						out_str->push_back(alphas[i]);
						break;
					}
			}else if(edge)
				notOccurringShortestString_rec(edge, out_str, alphas);
		}
		return mini.first.first;
	}

	inline Graph::Vertex getLeafNumber(const Leaf *leaf) const {
		if(isLeaf(leaf)) return leaf - leafs;
		else return nLeafs + ((const Node*)leaf - nodes);
	}
	inline const Leaf *numberToLeaf(Graph::Vertex v) const {
		if(v < nLeafs) return &leafs[v];
		else return &nodes[v - nLeafs];
	}

	std::vector<std::vector<Leaf*> > positionLeafs;
	EulerTourLCA lca;
public:
	void buildLCEData() {
		assert(leafSequence && leafIndex);
		{
			std::vector<Graph::Edge> edges;
			edges.reserve(nLeafs + nNodes - 1);
			for(int i = 0; i < nNodes; i ++) {
				const Node *node = &nodes[i];
				int num = getLeafNumber(node);
				FOR_EACH_EDGES_C(edge, node) {
					edges.push_back(Graph::Edge(num, getLeafNumber(edge)));
				}
			}

			Graph g(nLeafs + nNodes, edges); edges.shrink_to_fit();
			lca.build(g, getLeafNumber(root));
		}

		positionLeafs.assign(addedStrings.size(), std::vector<Leaf*>());
		int index = 0;
		for(int i = 0; i < (int)addedStrings.size();i ++) {
			int len = addedStrings[i].second - addedStrings[i].first;
			positionLeafs[i].resize(len);
			for(int j = index; j < index + len; j ++) {
				int x = len - leafSequence[leafIndex[j]].substringLength;
				positionLeafs[i][x] = &leafs[j];
			}
			index += len;
		}
	}

	//Longest Common Prefix �Ƃ��Ă΂��B����͕����������generalize����Ă���B
	//xi,yi�͕�����̃C���f�b�N�X���Axj,yj�̓I�t�Z�b�g���w�肷��
	int longestCommonExtension(int xi, int xj, int yi, int yj) const {
		return substringLength(nodeLCA(positionLeafs[xi][xj], positionLeafs[yi][yj]));
	}
	int longestCommonExtension(int x, int y) const {
		return longestCommonExtension(0, x, 0, y);
	}
private:
	const Leaf *nodeLCA(const Leaf *x, const Leaf *y) const {
		return numberToLeaf(lca.query(getLeafNumber(x), getLeafNumber(y)));
	}

	int substringLength(const Leaf *leaf) const {
		if(isLeaf(leaf)) return leafSequence[leafIndex[leaf - leafs]].substringLength;
		else return nodeSubstringLength[(const Node*)leaf - nodes];
	}

public:
	//���O��2�̕�����ō\�z���Ă����K�v������
	//�Ώە�����, �p�^�[�� �̏��Ԃ�
	//��(k (n + m)) where k = ���C���h�J�[�h�̐�
	void findAllWithWildCards(Alpha wildCard, std::vector<const Alpha*> &out_v) const {
		assert(addedStrings.size() == 2);
		const Alpha *s = addedStrings[0].first;
		const Alpha *t = addedStrings[1].first;
		int n = addedStrings[0].second - s - 1;
		int m = addedStrings[1].second - t - 1;
		for(int i = 0; i <= n - m; i ++) {
			int x = i, y = 0;
			while(1) {
				int matchLen = longestCommonExtension(0, x, 1, y);
				if(y + matchLen == m) {
					out_v.push_back(s + i);
					break;
				}
				if( *(s + x + matchLen) == wildCard ||
					*(t + y + matchLen) == wildCard) {
					x += matchLen + 1;
					y += matchLen + 1;
				}else break;
			}
		}
	}

	//��(k n)
	void findAllKMismatches(int k, std::vector<std::pair<int, const Alpha*> > &out_v) const {
		assert(addedStrings.size() == 2);
		const Alpha *s = addedStrings[0].first;
		const Alpha *t = addedStrings[1].first;
		int n = addedStrings[0].second - s - 1;
		int m = addedStrings[1].second - t - 1;
		for(int i = 0; i <= n - m; i ++) {
			int x = i, y = 0;
			for(int mismatches = 0; mismatches <= k; mismatches ++) {
				int matchLen = longestCommonExtension(0, x, 1, y);
				if(y + matchLen == m) {
					out_v.push_back(std::make_pair(mismatches, s + i));
					break;
				}
				x += matchLen + 1;
				y += matchLen + 1;
			}
		}
	}

};


int main() {
	void tests();
	void matching_interactions();
//	tests();
	matching_interactions();
	return 0;
}
void matching_interactions() {
	while(1) {
	std::string s;
	std::getline(std::cin, s);
	std::string t;
	std::getline(std::cin, t);

	s += '\0'; t += '\1';
	GeneralizedSuffixTree gst(s.length()+t.length());
	gst.addByteString(s.c_str());
	gst.addByteString(t.c_str());
	gst.leafTraversal();
	gst.buildLCEData();

	int lcp = gst.longestCommonExtension(0, 0, 1, 0);
	std::cout << "Longest Common Prefix: " << '"';
	for(int i = 0; i < lcp; i ++) std::cout << s[i];
	std::cout << '"' << std::endl;

	std::vector<const Alpha*> wwc;
	gst.findAllWithWildCards('?', wwc);
	std::cout << "wwc: ";
	for(int i = 0; i < (int)wwc.size(); i ++) {
		std::cout << '"';
		const Alpha *p = wwc[i];
		for(int j = 0; j < (int)t.length()-1; j ++)
			std::cout << *(p+j);
		std::cout << '"';
		if(i+1 != wwc.size()) std::cout << ", ";
	}
	std::cout << std::endl;

	int missK = 2;
	std::vector<std::pair<int, const Alpha*> > miss;
	gst.findAllKMismatches(2, miss);
	std::cout << "miss" << missK << ": ";
	for(int i = 0; i < (int)miss.size(); i ++) {
		std::cout << '"';
		const Alpha *p = miss[i].second;
		for(int j = 0; j < (int)t.length()-1; j ++)
			std::cout << *(p+j);
		std::cout << '"' << '(' << miss[i].first << ')';
		if(i+1 != miss.size()) std::cout << ", ";
	}
	std::cout << std::endl;
	}
}

void some_interactions() {
	while(1) {
	std::string str;
	std::getline(std::cin, str);

#if 0
	int k;
	std::cin >> k;
	while(getchar() != '\n');
#endif

	GeneralizedSuffixTree t(str.length()+1);
	t.addByteString(str.c_str());
	t.leafTraversal();
#if 0
	std::vector<std::vector<const char*> > v;
	int maxLen = t.allLongestKRepeatedSubstrings(k, *(std::vector<std::vector<const Alpha*> >*)&v);
	std::cout << "len: " << maxLen << std::endl;
	for(int i = 0; i < (int)v.size(); i ++) {
		std::cout << '"';
		for(int j = 0; j < maxLen; j ++)
			std::cout << v[i][0][j];
		std::cout << '"' << ": ";
		std::sort(v[i].begin(), v[i].end());
		for(int j = 0; j < (int)v[i].size(); j ++) {
			if(j != 0) std::cout << ", ";
			std::cout << v[i][j]-str.c_str();
		}
		std::cout << std::endl;
	}
#elif 0
	std::vector<std::pair<int, std::vector<const char*> > > v;
	std::vector<GeneralizedSuffixTree::MaximalTuple> *v_a = (std::vector<GeneralizedSuffixTree::MaximalTuple>*)&v;
	t.allSupermaximalKRepeatedSubstrings(k, *v_a);
	for(int i = 0; i < (int)v.size(); i ++) {
		std::cout << '"';
		std::vector<const char*> &w = v[i].second;
		for(int j = 0; j < v[i].first; j ++)
			std::cout << w[0][j];
		std::cout << '"' << ": ";
		std::sort(w.begin(), w.end());
		for(int j = 0; j < (int)w.size(); j ++) {
			if(j != 0) std::cout << ", ";
			std::cout << w[j]-str.c_str();
		}
		std::cout << std::endl;
	}
#elif 0
	std::vector<std::pair<int, std::vector<const char*> > > v;
	std::vector<GeneralizedSuffixTree::MaximalTuple> *v_a = (std::vector<GeneralizedSuffixTree::MaximalTuple>*)&v;
	t.allMaximalKRepeatedTupleCombinations(k, *v_a);
	for(int i = 0; i < (int)v.size(); i ++) {
		std::cout << '"';
		std::vector<const char*> &w = v[i].second;
		for(int j = 0; j < v[i].first; j ++)
			std::cout << w[0][j];
		std::cout << '"' << " ";
		std::sort(w.begin(), w.end());
		for(int j = 0; j < (int)w.size(); j ++) {
			if(j != 0) std::cout << ", ";
			std::cout << w[j]-str.c_str();
		}
		std::cout << std::endl;
	}
#elif 0
	std::vector<std::pair<const char*, const char*> > v;
	t.allMaximalKRepeatedSubstrings_stringOnly(k, *(std::vector<std::pair<const Alpha*, const Alpha*> >*)&v);
	for(int i = 0; i < (int)v.size(); i ++) {
		std::cout << '"';
		for(const char *p = v[i].first; p < v[i].second; ++ p)
			std::cout << *p;
		std::cout << '"' << std::endl;
	}
#elif 0
	std::vector<std::pair<const char*, const char*> > v;
	int count = t.allMostFrequentlyOccurringSubstring(k, *(std::vector<GeneralizedSuffixTree::StrPair>*)&v);
	std::cout << "count: " << count << std::endl;
	for(int i = 0; i < (int)v.size(); i ++) {
		std::cout << '"';
		for(const char *p = v[i].first; p < v[i].second; ++ p)
			std::cout << *p;
		std::cout << '"' << std::endl;
	}
#elif 0
	std::vector<unsigned char> alphas, v;
	for(int i = 0; i < k; i ++) alphas.push_back('a' + i);
	t.notOccurringShortestString(alphas, v);
	std::cout << '"';
	for(int i = 0; i < (int)v.size(); i ++)
		std::cout << (char)v[i];
	std::cout << '"' << std::endl;
#elif 0
	std::vector<GeneralizedSuffixTree::StrPair> v;
	int len = t.allShortestOccurringOnlyOnceSubstrings(v);
	std::cout << "length: " << len << std::endl;
	for(int i = 0; i < (int)v.size(); i ++) {
		for(const unsigned char *p = v[i].first; p < v[i].second; ++ p)
			std::cout << (char)*p;
		std::cout << std::endl;
	}
#endif
	}
}

void matchingstatistics_interaction() {
	std::string str;
	std::getline(std::cin, str);
	std::cout << "input OK; length: " << str.length() << std::endl;
	GeneralizedSuffixTree t(str.length()+1);
	std::cout << "construct Suffix Tree ...";
	t.addByteString(str.c_str());
	std::cout << "OK" << std::endl;
	while(1) {
	std::string findstr;
	std::getline(std::cin, findstr);
	const Alpha *begin = (const Alpha*)findstr.c_str(), *end = begin + findstr.length();
	std::vector<int> statistics(end - begin);
	t.matchingStatistics(begin, end, statistics.data());

	std::string fs = findstr + '\1';
	GeneralizedSuffixTree u(str.length()+1+fs.length());
	u.addByteString(str.c_str());
	u.addByteString(fs.c_str());
	u.leafTraversal();
	u.buildLCEData();
	for(const Alpha *p = begin; p < end; p ++) {
		std::cout << p << ": " << statistics[p - begin] << ": ";
		int mx = 0;
		for(int i = 0; i < (int)str.length(); i ++) {
			int x = u.longestCommonExtension(0, i, 1, p - begin);
			mx = std::max(mx, x);
			for(int j = i; j < i+x; j ++)
				std::cout << str[j];
			if(i != str.length()) std::cout << ",";
		}
		std::cout << std::endl;
		assert(mx == statistics[p - begin]);
	}

	}
}

void findall_etc_interaction() {
	std::fstream f("C:\\test\\sagyo\\e.txt");
	std::string str;
	int lines = 0;
	while(1) {
		std::string tmp;
		std::getline(f, tmp);
		if(tmp == "$") break;
		str += tmp;
		lines ++;
	}
	std::cout << "input OK; length: " << str.length() << ", lines: " << lines << std::endl;
	GeneralizedSuffixTree t(str.length()+1);
	std::cout << "construct Suffix Tree ...";
	t.addByteString(str.c_str());
	std::cout << "OK" << std::endl;
	std::cout << "Euler tour ...";
	t.leafTraversal();
	std::cout << "OK" << std::endl;
	t.makeFindFirstData();
	while(1) {
	std::vector<const char *> v;
	std::string findstr;
	std::getline(std::cin, findstr);
	const Alpha *begin = (const Alpha*)findstr.c_str(), *end = begin + findstr.length();

	int count = t.countSubstring(begin, end);

	const Alpha *first = t.findFirst(begin, end);

	std::cout << "count: " << count << "; display all? (y/n): " << std::flush;
	std::string yn; std::getline(std::cin, yn);
	if(yn == "Y" || yn == "y") {
		t.findAll(begin, end, *(std::vector<const Alpha*>*)&v);
		assert(v.size() == count);
		std::sort(v.begin(), v.end());
		assert(v.empty() ? first == NULL : (const Alpha*)v[0] == first);
		for(int i = 0; i < (int)v.size(); i ++) {
			std::cout << v[i] - str.c_str() << ": ";
			const char *p;
			for(p = v[i]; *p && p < v[i] + 50; ++ p) std::cout << *p;
			if(*p) std::cout << "...";
			std::cout << std::endl;
		}
	}

	}
}

void branch_implement_speed_compare() {
	for(int ii = 0; ii < 10; ii ++) {
	static Alpha s[10000001];
	int l = sizeof(s)/sizeof(Alpha)-1, m = NAlpha - 1;
	//Array n=10^7 random   3  3600ms
	//List         random   3  4900ms
	//List         random  26 28400ms
	//ListA p=0    random  26  7000ms  508596
	//ListA p=5    random  26  9100ms  399082
	//ListA p=13   random  26 14000ms  172458
	//ListA p=24   random  26 17500ms   16276
	//ListA p=26   random  26 28700ms       0
	//ListB p=0    random   3  7600ms 5506556
	//ListB p=1    random   3  7000ms 4206663
	//ListB p=2    random   3  5000ms       0
	//ListB p=0    random  26  6600ms 1209396
	//ListB p=13   random  26 12800ms  309910
	//ListB p=0    random 256  4400ms  452262
	//ListB p=1    random 256  4400ms  451072
	//ListB p=2    random 256  4000ms  119840
	//ListB p=4    random 256  3800ms   65308
	//ListB p=8    random 256  4000ms   64772
	//ListB p=16   random 256  4800ms   64772
	//ListB p=32   random 256  8400ms   64772
	//ListB p=64   random 256 24100ms   64772
	//ListB p=128  random 256 81500ms    3365
	//ListB p=256  random 256 ...           0
	//ListB p=0    fib2   256 ...           0
	//Map          random   3 -       OutOfMemory
	//Hash         random   3 -       OutOfMemory
	//Treap        random   3 31800ms
	//Treap        random 256 53300ms
	//
	//char�Ɏ��܂肫��Ȃ��قǑ傫���A���t�@�x�b�g�̏ꍇ�́A��͂�n�b�V���}�b�v�헪�������Ǝv���B
#if 0	//FIBONACCI
	int al = 1, bl = 2;
	s[0] = 1; s[1] = 2;
	for(int j = 2; j < l; ) {
		memcpy(s+j, s, std::min(al, l-j)); j += al;
		al = bl; bl = j;
	}
#elif 1	//RANDOM
	for(int j = 0; j < l; j ++) s[j] = rand()/((RAND_MAX+m)/m) + 1;
#elif 0	//CONST1
	for(int j = 0; j < l; j ++) s[j] = 1;
#endif
	s[l] = 0;
	GeneralizedSuffixTree t(l+1);
	clock_t c = clock();
	t.addString((Alpha*)s);
	std::cout << (clock() - c) * 1000. / CLOCKS_PER_SEC << "msec." << std::endl;
	}
}

void tests() {
	void test(const char*, int = -1);
	test("0100101001001");
	test("asaadasdadasdasdasd");
	test("asdasdjkasjdasd");
	test("asdreqwrer");
	test("afdafasf");
	test("qqeweqwe");
	test("0");
	test("");
	test("00");
	test("010");
	test("cdddcdc");
	test("abcabxabcd");
	int testcase = 0;
	for(int ii = 0; ii < 1000; ii ++) {
		static char b[100];
		int l = rand() % sizeof(b), m = rand() % 26 + 1;
		for(int i = 0; i < l; i ++) {
			b[i] = 'a' + rand() % m;
		}
		b[l] = 0;
		test(b, testcase + ii);
	}
	testcase += 10000;

}

void test_isSuffix(GeneralizedSuffixTree &t, const char *s) {
	int len = strlen(s);

//	t.debugOutDotGraph(std::cout);

	char *buf = new char[len+1];
	memcpy(buf, s, len+1);
	for(int i = 0; i <= len; i ++) {
		assert(t.isSuffix((Alpha*)(s + i), (Alpha*)(s + len), '\0'));
		for(int j = i; j < len; j ++) {
			char &c = buf[j], d;
			while((d = 'a' + rand() % 26) == c) ;
			std::swap(c, d);
			assert(!t.isSuffix((Alpha*)(buf + i), (Alpha*)(buf + len), '\0'));
			std::swap(c, d);
		}
	}
	delete[] buf;
}

void test_matchingStatistics(GeneralizedSuffixTree &t, const char *s) {
	int len = strlen(s);
	for(int ii = 0; ii < 100; ii ++) {
		static char b[100];
		static int statistics[sizeof(b)];
		int l = rand() % sizeof(b), m = rand() % 26 + 1;
		for(int i = 0; i < l; i ++) {
			b[i] = 'a' + rand() % m;
		}
		t.matchingStatistics((Alpha*)b, (Alpha*)b+l, statistics);
		for(int i = 0; i < l; i ++) {
			int ans = t.commonPrefixLength((Alpha*)b+i, (Alpha*)b+l);
			assert(statistics[i] == ans);
		}
	}
}

void test(const char *s, int num = -1) {
	std::cout << "test ";
	if(num == -1) std::cout << s;
	else std::cout << num;
	std::cout << " ..." << std::flush;
	int len = strlen(s);
	GeneralizedSuffixTree t(len+1);
	t.addString((Alpha*)s);

	test_isSuffix(t, s);
	test_matchingStatistics(t, s);

	std::cout << "OK\r" << std::flush;
}

void poj2217() {
	int n;
	std::cin >> n; while(getchar() != '\n');
	for(int ii = 0; ii < n; ii ++) {
	std::string s, t;
	std::getline(std::cin, s);
	std::getline(std::cin, t);
	s += '\0'; t += '\1';
	GeneralizedSuffixTree u(s.length() + t.length());
	u.addByteString(s.c_str());
	u.addByteString(t.c_str());
//	u.debugOutDotGraph(std::cout, false);
	int ans = u.longestCommonSubstringLength(3);
	std::cout << "Nejdelsi spolecny retezec ma delku " << ans << "." << std::endl;
	}
}
