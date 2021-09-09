int main(int ArraySize, char ** ppArgs)
{
	for (size_t i = 0; i < ArraySize; i++)
	{
		cout << i + 1 << " : " << ppArgs[i] << endl;
	}

	if (string(ppArgs[1]) == "-A")
	{
		cout << "Hello world!";
	}

	if (string(ppArgs[2]) == "-B")
	{
		cout << "Bye world!";
	}

	cin.get();
