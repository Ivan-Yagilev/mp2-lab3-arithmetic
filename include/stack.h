// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть

template <class T>
class Stack {

private:
	int stack_size;
	int top;
	T* data;
public:
	Stack() 
	{ 
		stack_size = 100; 
		data = new T[stack_size];
		top = -1; 
	}
	Stack(int _size)
	{
		if (!_size) 
			throw "Null size";
		stack_size = _size; 
		data = new T[stack_size]; 
		top = -1;
	}

	// - просмотр верхнего элемента (без удалени€)
	T get_top()
	{
		if (empty())
			throw "Stack is empty";
		return data[top];
	}
	// - получение количества элементов в стеке
	T get_size()
	{
		return top + 1;
	}
	// - извлечение элемента
	T pop()
	{
		if (!empty())
			return data[top--];
		else 
			throw "Stack is empty";
	}
	// - вставка элемента
	void push(const T& x)
	{
		if (full()) 
		{
			stack_size = (stack_size + 1) * 2;
			T* tmp = new T[stack_size];
			for (int i = 0; i < top + 1; i++)
				tmp[i] = data[i];
			
			delete[] data;
			data = tmp;
		}
		top++;
		data[top] = x;
	}
	// - очистка стека
	void clear()
	{
		top = -1;
		delete[] data;
		data = new T[stack_size];
	}
	// - проверка на пустоту
	bool empty()
	{
		return top == -1;
	}
	// - проверка на полный стек
	bool full()
	{
		return top >= stack_size - 1;
	}
};