// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

template <class T>
class Stack {
private:
	int stack_size;
	int end;
	T* stack_ptr;
public:
	Stack()
	{
		stack_size = 50;
		stack_ptr = new T[stack_size];
		end = -1;
	}
	Stack(const int tmp_size)
	{
		if (tmp_size == 0)
			throw "null size";
		stack_size = tmp_size;
		stack_ptr = new T[stack_size];
		end = -1;
	}
	~Stack()
	{
		delete[] stack_ptr;
		stack_ptr = 0;
		end = -1;
	}

	// ������� ��������
	void push(const T& el)
	{
		if (full())
		{
			stack_size = (stack_size + 1) * 2;
			T* tmp_ptr = new T[stack_size];
			for (size_t i = 0; i < end + 1; i++)
				tmp_ptr[i] = stack_ptr[i];
			delete[] stack_ptr;
			stack_ptr = tmp_ptr;
		}
		end++;
		stack_ptr[end] = el;
	}

	// ���������� ��������
	T pop()
	{
		if (empty())
			throw "empty";
		else 
		{
			stack_size--;
			return stack_ptr[end--];
		}
	}

	// ������� �����
	void clear()
	{
		end = -1;
		delete[] stack_ptr;
		stack_ptr = new T[stack_ptr];
	}

	// �������� �������� �������� ��� ��������
	T get_end()
	{
		if (empty())
			throw "empty";
		return stack_ptr[end];
	}

	// ��������� ������� �����
	T get_stack_size()
	{
		return end + 1;
	}

	// �������� �� ������ ����
	bool empty()
	{
		if (end == -1)
			return true;
		else
			return false;
	}

	// �������� �� ������ ����
	bool full()
	{
		if (end >= stack_size - 1)
			return true;
		else
			return false;
	}
};