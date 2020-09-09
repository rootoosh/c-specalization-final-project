
char* f_ingnoreSpaces(char* string)
{
	while ((*string == ' ') || (*string == '\t'))
	{
		string++;
	}
	return string;
}