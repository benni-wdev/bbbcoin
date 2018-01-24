#!/usr/bin/env bash

cd "$(dirname "$(readlink -f "$0")")"    #'"%#@!

sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python python-zmq \
      zlib1g-dev wget bsdmainutils automake

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
