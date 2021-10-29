#include <iostream>
#include <string>

template <typename T>
class Stack {
public:
    Stack() : data(NULL), next(nullptr)
    {}

    void push(int value) {
        Stack<T>* tmp = this;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new Stack<T>(value);
    }

    ~Stack()
    {
        if (next != nullptr) delete next;
    }

    int pop() {
        Stack<T>* tmp = this->next;
        Stack<T>* tmp1 = this;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            tmp1 = tmp1->next;
        }
        int ans = tmp->data;
        tmp->next = nullptr;
        delete tmp;
        tmp1->next = nullptr;
        return ans;
    }
private:
    Stack(int data) : data(data), next(nullptr)
    {}

    T data;
    Stack* next;
};


int main() {
	Stack<int> res;
	std::string tmp;
	std::cin >> tmp;

	while (tmp != "=")
	{
		if (tmp == "+")
		{
            auto a = res.pop();
            auto b = res.pop();
			res.push(a + b);
		}
		else if (tmp == "-")
		{
            auto a = res.pop();
            auto b = res.pop();
			res.push(- a + b);
		}
		else if (tmp == "*")
		{
            auto a = res.pop();
            auto b = res.pop();
			res.push(a * b);
		}
		else
		{
			res.push(std::stoi(tmp));
		}
		std::cin >> tmp;
	}

	std::cout << res.pop();

	return 0;
}
