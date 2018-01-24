#!/usr/bin/env bash

# actually untested, sorry

cd "$(dirname "$(readlink -f "$0")")"    #'"%#@!

sudo dnf install \
      git pkgconfig automake autoconf ncurses-devel python \
      python-zmq wget gtest-devel gcc gcc-c++ libtool patch

./fetch-params.sh || exit 1

./build.sh --disable-tests --disable-rust -j$(nproc) || exit 1

if [ ! -r ~/.bbbcoin/bbbcoin.conf ]; then
   mkdir -p ~/.bbbcoin
   echo "addnode=mainnet.bbbcoin.site" >~/.bbbcoin/bbbcoin.conf
   echo "rpcuser=username" >>~/.bbbcoin/bbbcoin.conf
   echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.bbbcoin/bbbcoin.conf
fi

cd ../src/
cp -f zcashd bbbcoind
cp -f zcash-cli bbbcoin-cli
cp -f zcash-tx bbbcoin-tx

echo ""
echo "--------------------------------------------------------------------------"
echo "Compilation complete. Now you can run ./src/bbbcoind to start the daemon."
echo "It will use configuration file from ~/.bbbcoin/bbbcoin.conf"
echo ""
