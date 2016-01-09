include(destination.pri)

 QT += widgets webkit webkitwidgets

TARGET = xeth
TEMPLATE = lib
CONFIG += staticlib

HEADERS = \
    ../src/database/AddressBookStore.hpp \
    ../src/database/ConstIterator.hpp \
    ../src/database/ConstReverseIterator.hpp \
    ../src/database/ScanIndexStore.hpp \
    ../src/database/Store.hpp \
    ../src/database/TransactionStore.hpp \
    ../src/synchronizer/AccountScanCriterion.hpp \
    ../src/synchronizer/ChainProgress.hpp \
    ../src/synchronizer/ChainSanner.hpp \
    ../src/synchronizer/ScanAction.hpp \
    ../src/synchronizer/ScanCriteria.hpp \
    ../src/synchronizer/ScanCriterion.hpp \
    ../src/synchronizer/ScanProgress.hpp \
    ../src/wallet/AddressValidator.hpp \
    ../src/wallet/ExportKeyCommand.hpp \
    ../src/wallet/GetAccountsCommand.hpp \
    ../src/wallet/GetBalanceCommand.hpp \
    ../src/wallet/GetTransactionCommand.hpp \
    ../src/wallet/ImportKeyCommand.hpp \
    ../src/wallet/ListTransactionsCommand.hpp \
    ../src/wallet/SendToAddressCommand.hpp \
    ../src/BigInt.hpp \
    ../src/DataBase.hpp \
    ../src/Enum.hpp \
    ../src/EthProcess.hpp \
    ../src/EthProcessSupervisor.hpp \
    ../src/Invoker.hpp \
    ../src/macros.hpp \
    ../src/Notifier.hpp \
    ../src/Settings.hpp \
    ../src/Synchronizer.hpp \
    ../src/WalletFacade.hpp \
    ../src/database/DataBaseDirectory.hpp \
    ../src/database/Store.ipp \
    ../src/database/ConstReverseIterator.ipp \
    ../src/database/ConstIterator.ipp \
    ../src/synchronizer/ScanCriteria.ipp \
    ../src/TransactionCategory.hpp \
    ../src/database/StoreRange.hpp \
    ../src/database/RangeIterator.hpp \
    ../src/database/RangeIterator.ipp \
    ../src/database/StoreRange.ipp \
    ../src/addressbook/EditContactCommand.hpp \
    ../src/addressbook/ListContactsCommand.hpp \
    ../src/addressbook/RemoveContactCommand.hpp \
    ../src/Application.hpp \
    ../src/Window.hpp \
    ../src/addressbook/AddContactCommand.hpp \
    ../src/addressbook/RenameConactCommand.hpp \
    ../src/AddressBookFacade.hpp




SOURCES = \
    ../src/database/AddressBookStore.cpp \
    ../src/database/ScanIndexStore.cpp \
    ../src/database/TransactionStore.cpp \
    ../src/synchronizer/AccountScanCriterion.cpp \
    ../src/synchronizer/ChainProgress.cpp \
    ../src/synchronizer/ChainScanner.cpp \
    ../src/synchronizer/ScanAction.cpp \
    ../src/synchronizer/ScanCriteria.cpp \
    ../src/synchronizer/ScanCriterion.cpp \
    ../src/synchronizer/ScanProgress.cpp \
    ../src/wallet/AddressValidator.cpp \
    ../src/wallet/ExportKeyCommand.cpp \
    ../src/wallet/GetAccountsCommand.cpp \
    ../src/wallet/GetBalanceCommand.cpp \
    ../src/wallet/GetTransactionCommand.cpp \
    ../src/wallet/ImportKeyCommand.cpp \
    ../src/wallet/ListTransactionsCommand.cpp \
    ../src/wallet/SendToAddressCommand.cpp \
    ../src/DataBase.cpp \
    ../src/EthProcess.cpp \
    ../src/EthProcessSupervisor.cpp \
    ../src/Notifier.cpp \
    ../src/Settings.cpp \
    ../src/Synchronizer.cpp \
    ../src/WalletFacade.cpp \
    ../src/database/DataBaseDirectory.cpp \
    ../src/addressbook/AddContactCommand.cpp \
    ../src/addressbook/EditContactCommand.cpp \
    ../src/addressbook/ListContactsCommand.cpp \
    ../src/addressbook/RemoveContactCommand.cpp \
    ../src/Application.cpp \
    ../src/main.cpp \
    ../src/Window.cpp \
    ../src/addressbook/RenameConactCommand.cpp \
    ../src/AddressBookFacade.cpp

QMAKE_CXXFLAGS += -I$$_PRO_FILE_PWD_/../src


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += eth-connector
unix: PKGCONFIG += jsoncpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
