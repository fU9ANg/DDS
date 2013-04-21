
#include "DDSException.h"

using namespace DDS::SHAREDLIB;

DDSException::DDSException (const char* what)
{
}

DDSException::DDSException (const string& what)
{
}

DDSException::~DDSException (void) throw ()
{
}

const char* DDSException::What (void) const throw ()
{
}

const char* DDSException::StackTrace (void) const throw ()
{
}

void DDSException::FillStackTrace (void)
{
}
