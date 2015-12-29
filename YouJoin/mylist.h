//实现一个链表

#ifndef LIST_H
#define LIST_H

#define DEFAULI_SIZE 1050
#define NULL 0

//singly linked list node with freelist support
template<typename E> class Link{

private:

	static Link<E> *freelist;

public:
	E element;
	Link *next;

	Link(const E& elemval, Link* nextval = NULL)
	{
		element = elemval;
		next = nextval;
	}

	Link(Link* nextval = NULL)
	{
		next = nextval;
	}

	void* operator new(size_t)
	{
		if (freelist == NULL) return ::new Link;
		Link<E>* temp = freelist;
		temp->next = NULL;
		freelist = freelist->next;
		
		return temp;
	}

	void operator delete(void* ptr)
	{
		((Link<E>*)ptr)->next = freelist;
		freelist = (Link<E>*)ptr;
	}
};

template<typename E>
Link<E>* Link<E>::freelist = NULL;

template<typename E>
class LList{
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *curr;
	int cnt;

	void init()
	{
		curr = tail = head = new Link<E>;
		cnt = 0;
	}

	void removeall()
	{
		while (head != NULL){
			curr = head;
			head = head->next;
			delete curr;
		}
		tail = NULL;
		curr = NULL;
		head = NULL;
		cnt = 0;
	}
public:
	LList(int size = DEFAULI_SIZE)
	{
		init();
	}

	~LList()
	{
		removeall();
	}

	void print()
	{
		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			cout << this->getValue() << endl;
		}
	}

	void clear()
	{
		removeall();
		init();
	}

	void insert(const E& it)
	{
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr) tail = curr->next;
		cnt++;
	}

	void append(const E& it)
	{
		tail->next = new Link<E>(it);
		tail = tail->next;
		cnt++;
	}

	E remove()
	{

		E it = curr->next->element;
		Link<E> *ltemp = curr->next;
		if (tail == curr->next) tail = curr;
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}

	void moveToStart()
	{
		curr = head;
	}

	void moveToEnd()
	{
		curr = tail;
	}

	void prev()
	{
		if (curr == head) return;
		Link<E> *temp = head;
		while (temp->next != curr) temp = temp->next;
		curr = temp;
	}

	void next()
	{
		if (curr != tail) curr = curr->next;
	}

	int length() const
	{
		return cnt;
	}

	int currPos() const
	{
		Link<E> *temp = head;
		int i;
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}

	void moveToPos(int pos)
	{

		curr = head;
		for (int i = 0; i < pos; i++)curr = curr->next;
	}

	const E& getValue() const
	{
		return curr->next->element;
	}

	bool getable() const
	{
		return (curr != NULL && curr->next != NULL);
	}

	//利用临时数组，反转链表中的元素
	//共需遍历链表两次，经估计可达到线性时间复杂度
	void reverse()
	{
		if (head->next == NULL) return;
		E *a = new E[this->length()];
		int k = 0;

		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			a[k++] = this->getValue();
		}

		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			curr->next->element = a[--k];
		}

		return;
	}

	//将有序链表（由低到高）in1与in2合并，结果储存在in1中
	static LList<E>& merge(LList<E>& in1, LList<E>& in2)
	{

		//初始化位置，准备添加
		in1.moveToStart();
		in2.moveToStart();
		in2.next();
		Link<E>* temp;

		//用于记录in2中已添加的元素
		int k = 0;

		while (in1.currPos() <= in1.length()){
			//添加in2中 小于in1中最大元素的 元素
			//同时记录in2中已添加元素的数量k

			if (in2.curr->element < in1.curr->element){
				temp = new Link<E>(in2.curr->element, in1.curr);

				if (in1.curr == in1.head) {
					in1.head->next = temp;
					in1.curr->next = temp;
				}
				else{
					in1.prev();
					in1.curr->next = temp;
				}
				in1.cnt++;
				k++;

				if (in2.curr == in2.tail) return in1;
				in2.next();
			}

			if (in1.currPos() == in1.length()) break;
			in1.next();
		}

		//从位置k开始，添加in2中的其他元素
		for (in2.moveToPos(k); in2.currPos() < in2.length(); in2.next()){
			in1.append(in2.getValue());
		}

		return in1;
	}

};

#endif //LIST_H