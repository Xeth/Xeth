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
```

install parity  
```
cargo install --git https://github.com/ethcore/parity.git parity
```

alternatively compile parity [https://github.com/ethcore/parity](https://github.com/ethcore/parity)

### get sources and compile
```
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
cmake ..
make
```

to install
```
make install
```
