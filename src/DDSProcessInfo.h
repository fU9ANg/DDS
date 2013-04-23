
#ifndef _DDS_SHAREDLIB_DDSPROCESSINFO_H
#define _DDS_SHAREDLIB_DDSPROCESSINFO_H

namespace DDS
{
namespace SHAREDLIB
{

namespace DDSProcessInfo
{
    pid_t   pid ();
    string  pidString ();
    uid_t   uid ();
    string  userName ();
    string  hostName ();

    string  status ();
    string  openedFiles ();

    vector<pid_t> threads ();
}

}
}

#endif // _DDS_SHAREDLIB_DDSPROCESSINFO_H
