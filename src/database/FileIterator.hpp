#pragma once

#include <boost/filesystem.hpp>
#include <boost/iterator/iterator_facade.hpp>


namespace Xeth{

namespace fs = boost::filesystem;



template<class Value, class Parser>
class FileIterator : 
    public boost::iterator_facade
        <
            FileIterator<Value, Parser>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        typedef boost::iterator_facade
            <
                FileIterator<Value, Parser>,
                Value,
                boost::forward_traversal_tag,
                Value
            > Base;

    public:
        FileIterator(const std::string &path, const std::string &ext);
        FileIterator(const fs::directory_iterator &, const std::string &ext);
        FileIterator();

        void increment();

        Value dereference() const;
        bool equal(const FileIterator &) const;

        const fs::path & path() const;

    private:
        fs::directory_iterator findValid(const fs::directory_iterator &);

    private:
        Parser _parser;
        std::string _ext;
        fs::directory_iterator _handle;

};





}

#include "FileIterator.ipp"
