#ifndef RTERMO_CLIENT_H
#define RTERMO_CLIENT_H

#include "tcp_client.h"
#include <vector>

// command list and sequence as it is in MCU program
enum RTERMOCommandCode
{
    Empty = 0x00,
    Enable_RDOSE = 0x01,
    Disable_RDOSE = 0x02
};


// value list and sequence as it is in MCU program
enum RTERMOValueCode
{
   	Message_Num,
    Temp_A,
    Temp_B,
    RDOSE_Enabled,
    Version_Major,
    Version_Minor,
	Size 
};

class RTERMOClient : public TCPClient
{
    static const int kRxBufferSize = 15;
    static const int kTxBufferSize = 8;

    struct ValueAddress
    {
        uint32_t offset;
        uint32_t size;
    };

    std::vector<ValueAddress> map;
    uint8_t tx[kTxBufferSize];

public:
    RTERMOClient(std::string ip, uint16_t port);
    ~RTERMOClient();
    int getMessageNum();
    int getTempA();
    int getTempB(); 
    uint8_t getRDOSEStatus();
    void enableRDOSE();
    void disableRDOSE();   
private:
};

#endif
