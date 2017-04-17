
namespace Xeth{


template<class Probe>
void SystemProber::addProbe()
{
    registerProbe(new Probe());
}


template<class Probe, class Args>
void SystemProber::addProbe(const Args &args)
{
    registerProbe(new Probe(args));
}



}
