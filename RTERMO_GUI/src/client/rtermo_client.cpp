#include "rtermo_client.h"
#include <string.h>

RTERMOClient::RTERMOClient(std::string ip, uint16_t port) : TCPClient(ip, port, kRxBufferSize, kTxBufferSize)
{
    map = std::vector<ValueAddress>(RTERMOValueCode::Size);
    map[RTERMOValueCode::Message_Num]   = {0, 4};
    map[RTERMOValueCode::Temp_A]        = {4, 4};
    map[RTERMOValueCode::Temp_B]        = {8, 4};
    map[RTERMOValueCode::RDOSE_Enabled] = {12, 1};
    map[RTERMOValueCode::Version_Major] = {13, 1};
    map[RTERMOValueCode::Version_Minor] = {14, 1};
}

RTERMOClient:: ~RTERMOClient()
{
}

int RTERMOClient::getMessageNum()
{
    int res = 0;
    TCPClient::copyFromRx(
        &res,
        map[RTERMOValueCode::Message_Num].offset,
        map[RTERMOValueCode::Message_Num].size
        );
    return res;
}

int RTERMOClient::getTempA()
{
    int res = 0;
    TCPClient::copyFromRx(
        &res,
        map[RTERMOValueCode::Temp_A].offset,
        map[RTERMOValueCode::Temp_A].size
        );
    return res;
}

int RTERMOClient::getTempB()
{
    int res = 0;
    TCPClient::copyFromRx(
        &res,
        map[RTERMOValueCode::Temp_B].offset,
        map[RTERMOValueCode::Temp_B].size
        );
    return res;
}

uint8_t RTERMOClient::getRDOSEStatus()
{
    uint8_t res = 0;
    TCPClient::copyFromRx(
        &res,
        map[RTERMOValueCode::RDOSE_Enabled].offset,
        map[RTERMOValueCode::RDOSE_Enabled].size
        );
    return res;
}

void RTERMOClient::enableRDOSE()
{
    int command = RTERMOCommandCode::Enable_RDOSE;
    int parameter = 0;
    memset(this->tx, 0, this->kTxBufferSize);
    memcpy(this->tx + 0, &command, 4); // copy command
    memcpy(this->tx + 4, &parameter, 4); // copy parameter
    TCPClient::copyToTx(this->tx, 0, this->kTxBufferSize);
}

void RTERMOClient::disableRDOSE()
{
    int command = RTERMOCommandCode::Disable_RDOSE;
    int parameter = 0;
    memset(this->tx, 0, this->kTxBufferSize);
    memcpy(this->tx + 0, &command, 4); // copy command
    memcpy(this->tx + 4, &parameter, 4); // copy parameter
    TCPClient::copyToTx(this->tx, 0, this->kTxBufferSize);
}
