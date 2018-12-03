#pragma once
#include <cassert>
#include <vector>
#include "../Util/StaticGraph_Simple.cpp"

//Schieber-Vishkin algorithm
//�Q�l: http://homepage.usask.ca/~ctl271/810/approximate_matching.shtml
//�p�X�ɕ������邱�Ƃ��l����B
//�������u(I(�) = �q�؂̒���(h(�) = in-order index�ō����sideways-heap��̍���)���ő�̒��_)�Ń��x���t������v
//���̕����͔��ɗǂ������𑽐������Ă���B���̐������r�b�g���Z�ɂ���Ĉ��������B
//�܂��A�uh(I(�))�͏�(������)�ɍs���ɂ��(�L�`)�P�������v
//	����́u�ő�́v�Ƃ�����`����킩��B
//�����āA�uI(�)�͈�ӂł���v
//	in-order index�ł͎q�؂͋�Ԃɂ���ĕ\�����Ƃ��ł���B
//	sideways-heap�ł̍����Ƃ����̂́A��ԉE(�����������牓��)��1�̃r�b�g�̈ʒu�B
//	�����d������Ȃ�A�����͘A�����Ă��āA���̂����ǂ��炩�͂���ɍ����Ȃ�A�Ƃ����ώ@�ŏؖ��ł���B
//���ꂩ��A�����Ƃ����̂�0�`floor(log n)�B
//�܂�A���钸�_���獪�ւ̃p�X���l�������A
//�u��������floor(log n)+1��ށv��h(I(�))���u�P�������v�ŏo������B
//�����ŁA(A(�) = ���̃p�X�̑c��(����܂�)��h(I(�))�̏W�����r�b�g�Z�b�g�ŕ\��)���Ƃ��l����B
//	����ƁA���̏W����AND���ԍ��̗����Ă�r�b�g�Ȃǂɂ���ď��𓾂���B

//Tested
class SchieberVishkinLCA {
public:
	typedef Graph::Vertex Vertex;
	typedef unsigned Word;
private:

	static inline Word lowestOneBit(Word v) {
		return v & (~v+1);
	}
	static inline Word highestOneBitMask(Word v) {
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		return v >> 1;
	}

	std::vector<Word> indices;			//Vertex -> index
	std::vector<Word> maxHIndices;		//Vertex -> index
	std::vector<Word> ancestorHeights;	//Vertex -> Word
	std::vector<Vertex> pathParents;	//index-1 -> Vertex
public:
	//g�͐e���q�̎}�̂��鍪�t����
	void build(const Graph &g, Vertex root) {
		assert(g.m == g.n - 1);

		ancestorHeights.resize(g.n);
		std::vector<Vertex> parents(g.n);
		maxHIndices.resize(g.n);
		std::vector<Vertex> vertices; vertices.reserve(g.n);
		indices.resize(g.n);

		//euler tour
		Word currentIndex = 1;
		parents[root] = root;	//���ւ��̂��߂�
		vertices.push_back(root);
		while(!vertices.empty()) {
			Vertex v = vertices.back(); vertices.pop_back();
			indices[v] = currentIndex ++;
			for(const Graph::To *it = g.edgesBegin(v); it != g.edgesEnd(v); ++ it) {
				parents[it->to] = v;
				vertices.push_back(it->to);
			}
		}

		//BFS (�g�|���W�J�����������߂邽�߂�)
		int head = 0, tail = 1;
		vertices.resize(g.n); vertices[0] = root;
		while(head != tail) {
			Vertex v = vertices[head ++];
			for(const Graph::To *it = g.edgesBegin(v); it != g.edgesEnd(v); ++ it)
				vertices[tail ++] = it->to;
		}

		//�[��������
		for(std::vector<Vertex>::const_iterator it = vertices.begin(); it != vertices.end(); ++ it)
			maxHIndices[*it] = indices[*it];
		for(std::vector<Vertex>::const_reverse_iterator it = vertices.rbegin(); it != vertices.rend(); ++ it) {
			Vertex v = *it, parent = parents[v];
			if(lowestOneBit(maxHIndices[parent]) < lowestOneBit(maxHIndices[v]))
				maxHIndices[parent] = maxHIndices[v];
		}

		//A�����߂�
		ancestorHeights[root] = 0;
		for(std::vector<Vertex>::const_iterator it = vertices.begin(); it != vertices.end(); ++ it) {
			Vertex v = *it;
			ancestorHeights[v] = ancestorHeights[parents[v]] | lowestOneBit(maxHIndices[v]);
		}

		pathParents.swap(parents);	//��������������
		pathParents[indices[root]-1] = root;
		for(std::vector<Vertex>::const_iterator it = vertices.begin(); it != vertices.end(); ++ it) {
			Vertex v = *it;
			for(const Graph::To *jt = g.edgesBegin(v); jt != g.edgesEnd(v); ++ jt) {
				if(maxHIndices[v] != maxHIndices[jt->to])
					pathParents[indices[jt->to]-1] = v;
				else
					pathParents[indices[jt->to]-1] = pathParents[indices[v]-1];
			}
		}
	}

	Vertex query(Vertex v, Vertex u) const {
		//binary tree��ł�LCA�̍��������߂�
		Word Iv = maxHIndices[v], Iu = maxHIndices[u];
		Word hIv = lowestOneBit(Iv), hIu = lowestOneBit(Iu);
		Word hbMask = highestOneBitMask((Iv ^ Iu) | hIv | hIu);
		Word j = lowestOneBit(ancestorHeights[v] & ancestorHeights[u] & ~hbMask);
		//j = hI(lca(v,u)) �ƂȂ� (�����ŁAhI(x) = 2^(complete binary tree��ł�I(x)�̍���), I(x) = maxHIndices[x])
		//(hI(lca(v,u)) = j)��hI(v)��hI(u)�����̑��̍ő�l�B�����Ĉ�ӂł��邱�Ƃ��l����Ɓc
		Vertex x, y;
		if(j == hIv) x = v;
		else {			//lca��v�̃p�X��ɂ͖���
			Word kMask = highestOneBitMask(ancestorHeights[v] & (j-1));	//v�̑c��ŁAj���͒Ⴂ���ǂ��̒��ň�ԏ�ɂ���p�X
			x = pathParents[(indices[v] & ~kMask | (kMask+1))-1];	//indices[v]��k�̍����̑c��̃p�X�̐e
		}
		if(j == hIu) y = u;
		else {			//lca��u�̃p�X��ɂ͖���
			Word kMask = highestOneBitMask(ancestorHeights[u] & (j-1));	//u�̑c��ŁAj���͒Ⴂ���ǂ��̒��ň�ԏ�ɂ���p�X
			y = pathParents[(indices[u] & ~kMask | (kMask+1))-1];	//indices[u]��k�̍����̑c��̃p�X�̐e
		}
		return indices[x] < indices[y] ? x : y;	//in-order�Ȃ̂ŁA�C���f�b�N�X���Ⴂ�����c��Ȃ͂�
	}
};
