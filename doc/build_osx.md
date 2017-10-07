### install homebrew package manager
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### install dependecies

```
brew install jsoncpp cmake leveldb boost cryptopp
brew tap homebrew/versions
brew install qt55
brew link --force qt55

```

### install [ipfs](https://ipfs.io/docs/install/)
```
curl -O https://dist.ipfs.io/go-ipfs/v0.4.3/go-ipfs_v0.4.3_darwin-amd64.tar.gz
tar xvzf go-ipfs_v0.4.3_darwin-amd64.tar.gz
sudo cp go-ipfs/ipfs /usr/local/bin
```
alternatively you can compile ipfs [https://github.com/ipfs/go-ipfs#build-from-source](https://github.com/ipfs/go-ipfs#build-from-source)


### install [parity](https://ethcore.io/parity.html)
install RUST
```
curl https://sh.rustup.rs -sSf | sh
cargo install --git https://github.com/paritytech/ethabi.git ethabi-cli
rustup default stable
```
install latest parity
```
cd && git clone https://github.com/paritytech/parity.git
cd parity
cargo build --release
sudo cp target/release/parity /usr/local/bin
```


alternatively you can use this documentation [https://github.com/ethcore/parity](https://github.com/ethcore/parity)



###  get sources and compile project

```
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt55/5.5.1/  ..
make
```

