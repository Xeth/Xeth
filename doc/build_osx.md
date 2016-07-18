### install dependecies

```
brew install jsoncpp cmake leveldb boost cryptopp
brew tap homebrew/versions
brew install qt55
brew link --force qt55

```

### get sources
```
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
```

### configure project
Xeth requires geth and ipfs binaries. 


To download binaries, use --BIN-DOWNLOAD flag
```
cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt55/5.5.1/ -DWITH_QT5=1 -DBIN-DOWNLOAD ..
```


To specify binary path'es, use --GETH_PATH=path_to_geth --IPFS_PATH=path_to_ipfs. Where path_to_geth is the absolute path to geth binary (ex: /usr/local/bin/geth) and path_to_ipfs is the absolute path to ipfs binary 

```
cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt55/5.5.1/ -DWITH_QT5=1 -DGETH_PATH=path_to_geth -DIPFS_PATH=path_to_ipfs

```


If geth/ipfs is installed in a standard location (ex: /usr/bin, /usr/local/bin), cmake can be used without flags

```
cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt55/5.5.1/ -DWITH_QT5=1 ..
```



### build project

```
make
```

