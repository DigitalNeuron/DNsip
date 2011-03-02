

class DNsock
{
	
public:
	int cnt;
	int curr;
	static char[100][100] receivedData;
	DNsock(void);
	~DNsock(void);
	void sendMessage(char* sipAddr,char* message);
};
