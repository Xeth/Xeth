
###install dependecies

```
sudo apt-get install subversion git cmake make g++ libboost-all-dev libleveldb-dev libjsoncpp-dev libqt5webkit5-dev libappindicator-dev libnotify-dev libgtk2.0-dev
```


* compile [cryptopp](https://www.cryptopp.com/wiki/Linux) library

```
mkdir -p /tmp/xeth_deps
svn checkout https://cryptopp.svn.sourceforge.net/svnroot/cryptopp/trunk/c5 /tmp/xeth_deps/cryptopp
make -C /tmp/xeth_deps/cryptopp static
```


### install ipfs
```
wget https://dist.ipfs.io/go-ipfs/v0.4.3/go-ipfs_v0.4.3_linux-amd64.tar.gz
tar xvzf go-ipfs_v0.4.3_linux-amd64.tar.gz
sudo cp go-ipfs/ipfs /usr/local/bin
```

alternatively compile ipfs [https://github.com/ipfs/go-ipfs#build-from-source](https://github.com/ipfs/go-ipfs#build-from-source)


### install parity
install stable RUST
```
curl https://sh.rustup.rs -sSf | sh
source $HOME/.cargo/env
```

install parity
```
cargo install --git https://github.com/ethcore/parity.git parity
```

alternatively use [https://github.com/ethcore/parity](https://github.com/ethcore/parity) documentation




### build Xeth

```
cd /tmp
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
cmake -DCRYPTOPP_INCLUDE_DIR=/tmp/xeth_deps -DCRYPTOPP_LIBRARY=/tmp/xeth_deps/cryptopp/libcryptopp.a ..
make
```

to install

```
sudo make install
```
