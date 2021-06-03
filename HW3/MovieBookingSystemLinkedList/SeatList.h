#ifndef SEATLIST_H_INCLUDED
#define SEATLIST_H_INCLUDED

class SeatList {
public:
	SeatList();
	SeatList(const SeatList& aSeatList);
	~SeatList();
	bool isEmpty() const;
	int getLength() const;
	bool retrieve(int index, int& empty) const;
	bool insert(int index, int  empty);
	bool remove(int index);
	bool update(int index, int newCheck);
private:
	struct SeatNode {
		int check;
		SeatNode* next;
	};
	int size;
	SeatNode* head;
	SeatNode* find(int index) const;
};
#endif