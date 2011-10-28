#if !defined(_Smart_ptr_h_)
#define _Smart_ptr_h_

template <class T>
class smart_ptr {
public :
	explicit smart_ptr(T *p = NULL) : Counter(NULL) {
		if(p != NULL)
			Counter = new counter(p);
	}
	smart_ptr(const smart_ptr &r) {
		acquire(r.Counter);
	}
	~smart_ptr() {
		release();
	}
	smart_ptr& operator=(const smart_ptr &r) {
		if(this != &r) {
			release();
			acquire(r.Counter);
		}
		return *this;
	}
	bool operator==(const smart_ptr &r) {
		if(Counter == NULL || r.Counter == NULL)
			return false;

		return Counter->ptr == r.Counter->ptr;
	}

	T& operator *() const throw() {return *Counter->ptr;}
	T* operator ->() const throw() {return Counter->ptr;}
	T* get() const throw() {return (Counter != NULL) ? Counter->ptr:NULL;}
	bool unique() const throw() {return ((Counter != NULL) ? Counter->count == 1: true);}
private :
	struct counter {
		counter(T* p = NULL, unsigned c = 1) : ptr(p), count(c) {}
		T* ptr;
		unsigned count;
	}* Counter;
	void acquire(counter *c) throw () {
		Counter = c;
		if(c != NULL)
			++c->count;
	}
	void release() {
		if(Counter != NULL) {
			if(--Counter->count == 0) {
				delete Counter->ptr;
				delete Counter;
			}
			Counter = NULL;
		}
	}

};

#endif