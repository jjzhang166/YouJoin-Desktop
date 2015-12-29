#ifndef LINK_H
#define LINK_H
template<typename E>class Link{
private:
	E element;
	Link *next;
public:
	Link(E& eleval, Link*nextval = NULL){
		element = eleval;
		next = nextval;
	}
	Link(Link* nextval = NULL){
		next = nextval;
	}
	E getElement(){
		return element;
	}
	Link* getNext(){
		return next;
	}
	void setNext(Link* nextval){
		next = nextval;
	}
};
#endif