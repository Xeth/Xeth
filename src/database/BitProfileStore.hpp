#pragma once

#include <QObject>
#include "bitprofile/Network.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileStore.hpp"
#include "bitprofile/Registrar.hpp"


namespace Xeth{


class BitProfileStore : public QObject
{
    Q_OBJECT
    public:
        typedef BitProfile::ProfileStore::Iterator Iterator;

    public:
        BitProfileStore(BitProfile::Network);

        bool insert(const BitProfile::ProfileDescriptor &);
        bool remove(const BitProfile::Profile::URI &);
        bool remove(const QString &uri);

        bool rename(const BitProfile::Profile::URI &, const BitProfile::Profile::URI &);

        Iterator find(const QString &) const;
        Iterator find(const char *) const;
        Iterator begin() const;
        Iterator end() const;

    signals:
        void NewItem(const BitProfile::ProfileDescriptor &) const;
        void Removed(const QString &uri) const;
        void Renamed(const QString &old, const QString &uri) const;


    private:
        BitProfile::ProfileStore _store;

};


}
