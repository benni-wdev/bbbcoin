Coin is offline


bbbcoin 1.0.0
=============

What is bbbcoin?
-----------------

[bbbcoin](https://bbbcoin.site/) is an implementation of the "Zerocash" protocol.
Forked from ZCash, based on Bitcoin's code, it intends to offer a far higher standard of privacy
through a sophisticated zero-knowledge proving scheme that preserves
confidentiality of transaction metadata. Technical details are available
in our [Protocol Specification](https://github.com/zcash/zips/raw/master/protocol/protocol.pdf).

This software is the bbbcoin client. It downloads and stores the entire history
of bbbcoin transactions; depending on the speed of your computer and network
connection, the synchronization process could take a day or more once the
blockchain has reached a significant size.

Security Warnings
-----------------

**bbbcoin is experimental and a work-in-progress.** Use at your own risk.


Deprecation Policy
------------------

This release is considered deprecated 16 weeks after the release day. There
is an automatic deprecation shutdown feature which will halt the node some
time after this 16 week time period. The automatic feature is based on block
height and can be explicitly disabled.


Windows release
---------------

coming soon


Building
--------

If you prefer to build bbbcoin from source code, you can do so by running
the following commands in Linux:

    git clone https://github.com/BenniBanker/bbbcoin.git
    cd ./bbbcoin/zcutil
    ./bbbcoin_build_debian.sh # for debian/ubuntu based systems

This will also setup your bbbcoin.conf file in ~/.bbbcoin directory, if the file does not exist yet.


Configuring
-----------

The above mentioned command should configure your bbbcoin already by creating ~/.bbbcoin/bbbcoin.conf for you. The file can be generated manually by running

    mkdir -p ~/.bbbcoin
    echo "addnode=mainnet.bbbcoin.site" >~/.bbbcoin/bbbcoin.conf
    echo "rpcuser=username" >>~/.bbbcoin/bbbcoin.conf
    echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.bbbcoin/bbbcoin.conf


Mining
------

coming soon



Installing
----------

Compiled binaries can be found in ./src directory. Copy them to your working path:

    cp ./src/bbbcoin-cli /usr/bin
    cp ./src/bbbcoind /usr/bin


Running
-------

    $ bbbcoind


Generating Transparent address
------------------------------

Once bbbcoind daemon is running, you may use bbbcoin-cli from another console to send commands to the daemon. For example, to generate new transparent address,
simply call:

    $ bbbcoin-cli getnewaddress
    t14oHp2v54vfmdgQ3v3SNuQga8JKHTNi2a1


Generating Shielded address
---------------------------

    $ bbbcoin-cli z_getnewaddress
    zcBqWB8VDjVER7uLKb4oHp2v54v2a1jKd9o4FY7mdgQ3gDfG8MiZLvdQga8JK3t58yjXGjQHzMzkGUxSguSs6ZzqpgTNiZG


Show balances
-------------

    $ bbbcoin-cli getbalance
    $ bbbcoin-cli z_getbalance t14oHp2v54vfmdgQ3v3SNuQga8JKHTNi2a1
    $ bbbcoin-cli z_getbalance zcBqWB8VDjVER7uLKb4oHp2v54v2a1jKd9o4FY7mdgQ3gDfG8MiZLvdQga8JK3t58yjXGjQHzMzkGUxSguSs6ZzqpgTNiZG


Make transaction
----------------

    $ bbbcoin-cli z_sendmany FROM_ADDR '[{"address": "TO_ADDR", "amount": 123}]' 1 0

In the above mentioned example, both FROM_ADDR and TO_ADDR can be either T addresses or Z addresses or combination.
The last two numbers (1 0) stand for minConf and fee. In the example above, the coins on FROM_ADDR must have
at least 1 confirmation, and fee is set to zero.

Alternatively, if you don't care from which address the coins are sent, you can use:

    $ bbbcoin-cli sendtoaddress TO_ADDR 123

In that case, coins may be combined from multiple addresses.

Remember that coinbase transaction (sending newly mined coins) must be done from a T address to a Z address.
So if you wish to send newly mined coins to a T address, you need to send them to a Z address first and then
make another transaction from that Z address to the T address destination.

After a transaction is executed using z_sendmany, you can check its status by using:

    $ bbbcoin-cli z_getoperationresult



Export wallet to a file (dump private keys)
-------------------------------------------

    $ bbbcoin-cli z_exportwallet exportfilename

You may need to specify export directory path using for example "exportdir=/tmp" in your ~/.bbbcoin/bbbcoin.conf


License
-------

For license information see the file [COPYING](COPYING).
