install dependecies

```
brew install jsoncpp cmake leveldb boost cryptopp
brew tap homebrew/versions
brew install qt55
brew link --force qt55

```


```
git clone --recursive https://github.com/BitProfile/Xeth.git
mkdir -p Xeth/build
cd Xeth/build
cmake -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt55/5.5.1/ -DWITH_QT5=1 ..
make
```

to install

```
sudo make install
```
<!--next use [linux generic](linux_generic.md) documentation-->
