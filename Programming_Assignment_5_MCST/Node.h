enum MARK{ VISITED, UNVISITED };
#pragma once
template <typename E>
class Node {
private:
	int index;
	E* dataptr;
	MARK mark;
public:
	Node(int i, E* d) : index{ i }, dataptr{ d }, {}
	~Node() {
		dataptr = NULL;
	}
	int getIndex() const {
		return index;
	}
	E getData() const {
		return (*dataptr);
	}
	MARK getMark() const {
		return mark;
	}
	void setMark(MARK m) {
		mark = m;
	}
};