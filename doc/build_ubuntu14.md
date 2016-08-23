
###install dependecies

```
sudo apt-get svn install git cmake make g++ libboost-all-dev libleveldb-dev libjsoncpp-dev libqt5webkit5-dev libappindicator-dev libnotify-dev libgtk2.0-dev
```


compile [cryptopp](https://www.cryptopp.com/wiki/Linux) library

```
mkdir -p /tmp/xeth_deps
svn checkout https://cryptopp.svn.sourceforge.net/svnroot/cryptopp/trunk/c5 /tmp/xeth_deps/cryptopp
make -C /tmp/xeth_deps/cryptopp static
```

### build Xeth

```
cd /tmp
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
cmake -DBIN_DOWNLOAD=1 -DCRYPTOPP_INCLUDE_DIR=/tmp/xeth_deps -DCRYPTOPP_LIBRARY=/tmp/xeth_deps/cryptopp/libcryptopp.a ..
make
```

to install

```
sudo make install
```
