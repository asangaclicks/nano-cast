/////////////////////////////////////////////////////////////////////////////////
//
// Caster is the main program for the NTRIP caster.
//   The mount points are defined in the "Caster.mounts" file
//   where each entry has the form:
//        mountpoint; password; STR data
//
//   For each mount point, an NTRIP server can log in and start
//   providing data.
//
//   Once an NTRIP server attaches to a mount point, 
//   multiple clients can attach and receive the data.
//
//   There is no interpretation of the data. The Caster
//   simply passes on the bytes from the server to the clients.
//
///////////////////////////////////////////////////////////////////////
#include "Dispatcher.h"
#include "DataBuffer.h"
#include "AcceptConnection.h"


int main()
{

    // Configure the dispatcher to handle a bunch of connections
    if (Dispatcher::Configure(1024) != OK)
        SysError("Can't configure Dispatcher\n");

    // Read in the mount points from the "Caster.mounts" configuration file
    MountTable mounts;
    if (mounts.ReadFromFile("Caster.mounts") != OK)
        return Error("Can't read mount points from %s\n", "Caster.mounts");

    // Prepare to accept incoming network connections
    AcceptConnection accpt(mounts);

    // Start the dispatcher loop with a single handler to accept the incoming connections
    Dispatcher::Start(&accpt);
    
    return 0;
}