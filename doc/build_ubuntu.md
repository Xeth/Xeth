
install dependecies

```
sudo apt-get install git cmake make g++ libleveldb-dev libjsoncpp-dev libqt5webkit5-dev libappindicator-dev libnotify-dev libgtk2.0-dev
```

for ubuntu 15
```
sudo apt-get install libcrypto++-dev
```

for ubuntu 14 you need to compile cryptopp [https://www.cryptopp.com/wiki/Linux](https://www.cryptopp.com/wiki/Linux)

and use -DCRYPTOPP_INCLUDE_DIR and -DCRYPTOPP_LIBRARY cmake options to specify cryptopp details


next use [linux generic](linux-generic.md) documentation
