#ifndef RESCODELIST_H_INCLUDED
#define RESCODELIST_H_INCLUDED

class ResCodeList {
public:
	ResCodeList();
	ResCodeList(const ResCodeList& aSeatList);
	~ResCodeList();
	bool isEmpty() const;
	int getLength() const;
	bool retrieve(int index, int& rescode) const;
	bool insert(int index, long rescode);
	bool remove(int index);
private:
	struct SeatNode {
		long ResCode;
		SeatNode* next;
	};
	int size;
	SeatNode* head;
	SeatNode* find(int index) const;
};
#endif 
