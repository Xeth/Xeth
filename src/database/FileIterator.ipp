namespace Xeth{



template<class Value, class Parser>
FileIterator<Value, Parser>::FileIterator(const fs::directory_iterator &it, const std::string &ext) :
    _ext(ext),
    _handle(findValid(it))
{}


template<class Value, class Parser>
FileIterator<Value, Parser>::FileIterator(const std::string &path, const std::string &ext) :
    _ext(ext),
    _handle(findValid(fs::directory_iterator(path)))
{}

template<class Value, class Parser>
FileIterator<Value, Parser>::FileIterator()
{}


template<class Value, class Parser>
fs::directory_iterator FileIterator<Value, Parser>::findValid(const fs::directory_iterator &begin)
{
    if(begin==fs::directory_iterator())
    {
        return begin;
    }

    fs::directory_iterator it = begin;
    while(!fs::is_regular_file(it->status())||it->path().extension().string() != _ext)
    {
        ++it;
        if(it==fs::directory_iterator())
        {
            break;
        }
    }
    return it;
}


template<class Value, class Parser>
void FileIterator<Value, Parser>::increment()
{
    _handle = findValid(++_handle);
}



template<class Value, class Parser>
bool FileIterator<Value, Parser>::equal(const FileIterator &it) const
{
    return _handle == it._handle;
}


template<class Value, class Parser>
Value FileIterator<Value, Parser>::dereference() const
{
    return _parser(_handle->path());
}


template<class Value, class Parser>
const fs::path & FileIterator<Value, Parser>::path() const
{
    return _handle->path();
}



}
