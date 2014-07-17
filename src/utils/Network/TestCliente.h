#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Socket.h"
#include "Messages.h"
#include "Thread.h"
#include "Condition.h"

#include <string>
#include <vector>
#include <list>




class Cliente {
public:
	Cliente();
	Cliente(std::string playerID, char* ip, int port);
	~Cliente();

	bool serverAlive();
	
	//Listen changes in the network
	static int netListener(void* data);

	//notify over the network for a local change on the client
	static int notifyLocalUpdates(void* data);

	//Apply the changes that we receive on listen state
	static int applyNetworkChanges(void* data);

	static int clientSideEmulation(void* data);

	void lockLocalMutex();

	void unlockLocalMutex();

	void lockNetworkMutex();

	void unlockNetworkMutex();

	void addLocalChange(Playable p);

	bool updateModel(Playable p);

	void signalLocalChange();

	void signalNetworkChange();

	//

private:
	Socket input;
	Socket output;

	Player pl;

	// Se usa para controlar el timeout de los sockets
	time_t timeInicial;
	bool srvStatus;

	Mutex m;
	Mutex n;
	Condition somethingToTell;
	Condition somethingToUpdate;

	size_t revision;
	std::vector<Playable> localChanges;
	std::vector<Playable> networkChanges;

	void getRemoteWorld();
	int sendMsg(Messages type, std::vector<uint8_t> buffer);
	int sendDatagram(Datagram msg);
	int login();


};

typedef struct{
	Cliente* cli;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;

#endif /* CLIENTE_H_ */
