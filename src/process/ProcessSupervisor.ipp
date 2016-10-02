namespace Xeth{


template<class Loader>
void ProcessSupervisor::addLoader(const Loader &loader)
{
    _loaders.connect(loader);
}


}
