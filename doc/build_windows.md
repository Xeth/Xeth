### Install required tools

* Visual Studio Community 2013
	| [official site](https://www.visualstudio.com/en-us/news/vs2013-community-vs.aspx)
	| [direct download](https://go.microsoft.com/fwlink/?LinkId=517284)

* QT 5.5 with MSVC 2013 x64
 | [official site](https://www.qt.io/)
 | [direct download](http://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe)

* Cmake (3.5.2)
 | [official site](https://cmake.org/)
 | [direct download](https://cmake.org/files/v3.5/cmake-3.5.2-win32-x86.msi)

* Install Git
 | [official site](https://git-scm.com/)
 | [direct download](https://github.com/git-for-windows/git/releases/download/v2.9.2.windows.1/Git-2.9.2-64-bit.exe)


### Get dependent libraries

* Boost 1.55.0
 | [official site](http://www.boost.org/)
 | [direct download](https://sourceforge.net/projects/boost/files/boost-binaries/1.55.0/boost_1_55_0-msvc-12.0-64.exe/download)

* JsonCpp
 | [source code](https://github.com/open-source-parsers/jsoncpp)

* LevelDB
 | [official site](http://leveldb.org/)
 | [direct download](https://github.com/google/leveldb/archive/windows.zip)

* Crypto++ (5.6.2)
 | [official site](https://www.cryptopp.com/) 
 | [direct download](https://www.cryptopp.com/cryptopp562.zip)

* IPFS [https://github.com/ipfs/go-ipfs#build-from-source](https://github.com/ipfs/go-ipfs#build-from-source)
* Parity [https://github.com/ethcore/parity](https://github.com/ethcore/parity)

### Get the XETH source code

open the Git Bash and clone the XETH repository
```
git clone --recursive https://github.com/BitProfile/Xeth.git
```

# Build XETH

* open the Qt 5.5 64-bit for Desktop (MSVC 2013)
* navigate to the XETH sources directory
```
cd PATH_TO_XETH
```
* create the "build" directory and navigate into it
```
mkdir build
cd build
```
### Configure
```
cmake -G "Visual Studio 12 2013 Win64" -D Boost_USE_STATIC_LIBS=ON -D Boost_USE_MULTITHREADED=ON  ..
```
You can add the dependent library locations to the System Path or use the following flags with Cmake:
```
BOOST_ROOT

CRYPTOPP_INCLUDE_DIR

CRYPTOPP_LIBRARY

LEVELDB_INCLUDE_DIR

LEVELDB_LIBRARY

JSONCPP_INCLUDE_DIR

JSONCPP_LIBRARY
```
example:
```
cmake -G "Visual Studio 12 2013 Win64" -D Boost_USE_STATIC_LIBS=ON -D Boost_USE_MULTITHREADED=ON -D BOOST_ROOT="c:\local\boost_1_55_0" -D CRYPTOPP_INCLUDE_DIR="d:\xeth_libs\include" -D CRYPTOPP_LIBRARY="d:\xeth_libs\lib\cryptopp.lib" -D LEVELDB_INCLUDE_DIR="d:\xeth_libs\include" -D LEVELDB_LIBRARY="d:\xeth_libs\lib\leveldb.lib" -D JSONCPP_INCLUDE_DIR="d:\xeth_libs\include" -D JSONCPP_LIBRARY="d:\xeth_libs\lib\jsoncpp.lib" ..
```
Additional flags:
```
ENABLE_DEBUG - debug mode [0 or 1]

BIN_DOWNLOAD - download the vendor binaries (geth, ipfs) [0 or 1]
```
### Make
```
MSBuild xeth.sln /p:Configuration=Release
```
The MSBuild must be set in the System Path or you can use the absolute path. For example:
```
"C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" xeth.sln /p:Configuration=Release
```
