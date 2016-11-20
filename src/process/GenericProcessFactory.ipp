namespace Xeth{


template<class ProcessInitializer>
QProcess * GenericProcessFactory<ProcessInitializer>::Create(const Settings &settings)
{
    QProcess *process = new QProcess;
    ProcessInitializer::Initialize(*process, settings);
    return process;
}


template<class ProcessInitializer>
QProcess * GenericProcessFactory<ProcessInitializer>::Create()
{
    QProcess *process = new QProcess;
    process->setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    ProcessInitializer::Initialize(*process);
    return process;
}


template<class ProcessInitializer>
QProcess * GenericProcessFactory<ProcessInitializer>::Create(const Settings &settings, const QStringList &args)
{
    QProcess *process = new QProcess;
    ProcessInitializer::Initialize(*process, settings, args);
    return process;
}



}
