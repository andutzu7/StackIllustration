#include <string>
template <class T>
class stack
{
private:
	T* elementArray;
	size_t length;
	size_t cap;
public:
	stack(const stack& c) : elementArray(c.elementArray), length(c.length), cap(c.cap) { }
	stack(const T* otherArray = nullptr, const size_t& otherLength = 0)
	{
		if (otherLength < 0)
		{
			throw "Array length out of memory bounds";
		}
		if (otherLength == 0)
			elementArray = nullptr;
		else
		{
			alloc(otherLength);
			for (size_t i = 0; i < otherLength; i++)
			{
				elementArray[i] = otherArray[i];
			
			}
			length = otherLength;
		}
	}
	~stack()///cumva aici ai strecurat greseala?
	{
		//delete elementArray;
		length = 0;
		cap = 0;
	}
public:
	size_t GetLength() const
	{
		return length;
	}
	size_t GetCap() const
	{
		return cap;
	}
private:
	void alloc(const size_t &); /////////////////////// se apeleaza cu scopul de  a mari memoria vectorului cu 2*lungimea actuala sau lungimea specifcata, daca e mai mare decat cea ceruta
	void dealloc(const size_t & = 0);

public:
	
	T Top();
	T Pop();
	void Push(const T&);
	void Push(const stack&);
	void Insert(const T&, const size_t& = -1); ///
	void Overwrite(const T&, const size_t& = -1); ///
	int Find(const T&);
	int BinaryFind(const T&);
	T& operator*() const //aici e greseala strecurata? faptu ca operatoroul e const si nu pot sa l modific?
	{//nush cum sa fac in afara clasei :))
		return *elementArray;//nu sunt sigur ca e corect
	}
    stack operator = (const stack& other) 
{
	elementArray = other.elementArray;
	length = other.length;
	cap = other.cap;
	return *this;

}
	bool isEmpty();
	friend std::istream& operator>> (std::istream&, stack&);
	friend stack operator+ (const stack& lhs,const stack& rhs)
	{
		stack lhsCopy = lhs;
		stack rhsCopy = rhs;
		T element;
		while (!(rhsCopy.isEmpty()))
		{
			element = rhsCopy.Pop();
			lhsCopy.Push(element);
		}
		return lhsCopy;
	}
	friend bool operator == (const stack&lhs, const stack&rhs)
	{
		if (lhs.GetLength() != rhs.GetLength())
			return false;
		stack lhsCopy = lhs;
		stack rhsCopy = rhs;
		while (!(lhsCopy.isEmpty()))
		{
			if (lhsCopy.Pop() != rhsCopy.Pop())
				return false;
		}
		return true;
	}
	friend bool operator != (const stack&lhs, const stack&rhs)
	{
		return (!(lhs == rhs));
	}
	friend bool operator > (const stack&lhs, const stack&rhs)
	{
		if (lhs.GetLength() > rhs.GetLength())
			return true;
		return false;
	}
	friend bool operator < (const stack& lhs, const stack& rhs)
	{
		if (lhs.GetLength() < rhs.GetLength())
			return true;
		return false;
	}
	friend bool operator >= (const stack&lhs, const stack&rhs)
	{
		if (lhs.GetLength() > rhs.GetLength())
			return true;
		if (lhs.GetLength() == rhs.GetLength())
			return false;
		return false;
	}
	friend bool operator <= (const stack&lhs, const stack&rhs)
	{
		if (lhs.GetLength() > rhs.GetLength())
			return false;
		if (lhs.GetLength() == rhs.GetLength())
			return false;
		return true;
	}
	T& operator[](size_t index)
	{
		if (index<0 || index>length)
			throw "index outside of bounds!";
		return elementArray[index];
	}
	friend std::ostream& operator<<(std::ostream& output,const stack<T>& s) 
	{
		for (size_t i = 0; i <s.GetLength(); i++)
 			output << s.elementArray[i] << " ";
		return output;
	}
	std::string ConvertToString()
	{
		std::string result;
		for (size_t i = 0; i < length; i++)
			result.push_back((std::string)elementArray[i]);
		return result;
	}
};
template <class T>
void stack<T>::alloc(const size_t& reqLength)
{
	size_t newSize = reqLength + length;
	newSize = newSize > (2 * cap) ? newSize : (2 * cap);
	T* otherArray = new T[newSize];
	for (size_t i = 0; i < newSize; i++)
	{
		otherArray[i] = (T)0;//aici trebuia cast pt cazuri cand bagi string sau alte kkturi;
	}
	for (size_t i = 0; i < length; i++)
	{
		otherArray[i] = elementArray[i];
	}

	elementArray = otherArray;
	cap = newSize;
}
template<class T>
T stack<T>::Top()
{
	return *(elementArray + length - 1);
}
template<class T>
T stack<T>::Pop()
{
	if (!length)
		throw "the stack is empty";
	length--;
	return *(elementArray + length );

	

}
template<class T>
void stack<T>::Push(const T& element)
{
	if (length == cap)
		alloc(1);
	elementArray[length] = element;
		length++;

}
template<class T>
std::istream& operator>>(std::istream& input, stack<T>& s)
{
	T value;
	input >> value ;
	s.Push(value) ;

}
template<class T>
void stack<T>::Push(const stack<T>& other)
{
	if(length+other.length>=cap)
	alloc(other.length);
	for (size_t i = 0; i < other.length; i++)
	{
		elementArray[i + length++] = other.elementArray[i];
	}
}
template <class T>
void stack<T>::Insert(const T& value, const size_t& index)
{
	if (index<0 || index>length)
		throw "index out of bounds";
	if (length + 1 > cap)//daca stackul era plin si noi incercam sa mai bagam un element
		alloc(1);//facem loc pentru inca un element
	size_t aux = length;//n am alta idee
	while (aux > index)
	{
		elementArray[aux] = elementArray[aux - 1]; //copiem toate elementele ca la insert sort 
		aux--;
	}
	elementArray[index] = value;//adaugam valoarea pe pozitia dorita
	length++;//actualizam dimensiunile stivei
}
template <class T>
void stack<T>::Overwrite(const T& value, const size_t& index)
{
	if (index<0 || index>length)
		throw "index out of bounds";
	elementArray[index] = value; //pur si simplu inlocim valoarea care era deja acolo
}
template <class T>
void stack<T>::dealloc(const size_t& sizeToBeDeleted)//not sure its ok
{
	if (sizeToBeDeleted > cap)
		throw "requested to delete more than the initial size";
///Implementez o dealocare abuziva care nu tine cont de faptul ca se aflau date acolo. Fac asta deoarece se specifica si o dimensiune, cred ca s-ar specifica altceva daca ar fi cazul sa golesc doar spatiile neutilizate din memorie
	cap -= sizeToBeDeleted;//stergem dim specificata;
	if (length > cap)//daca avem mai multe elemente decat ne permite capacitatea
		length = cap;//pastram doar elementele perimise pana la capacitate maxima

}
template <class T>
int stack<T>::Find(const T& element) //asta e cam ambigua, o fac cam ca la std::vector
{
	for (int i = 0; i < length; i++)
		if (elementArray[i] == element)
			return i;//returnez pozitia unde am gasit elementul
	return -1;//nu se afla in vector
}
template <class T>
int stack<T>::BinaryFind(const T& element) //aici n am inteles ce sa fac, banuiesc ca trebuie sa fac cautare binara
{
	size_t low = 0;//left side of the array
	size_t up = length;//right side of the array

	while (low <= up) {
		size_t middle = low + (up - low) / 2;//the middle element
        if (elementArray[middle] == element)
			return middle;//pozitia unde se afla elementul cautat

		// If x greater, ignore left half 
		if (elementArray[middle] < element)
			low = middle + 1;

		// If x is smaller, ignore right half 
		else
			up = middle - 1;
	}

	return -1;// in case we dont find the element
}
template <class T>
bool stack<T>::isEmpty()
{
	return (length == 0);
}
