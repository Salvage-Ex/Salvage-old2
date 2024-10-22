# Multi masternode config

The multi masternode config allows you to control multiple masternodes from a
single wallet. The wallet needs to have a valid collateral output of 15.000
coins for each masternode. To use this, place a file named masternode.conf in
the data directory of your install:

* Windows: %APPDATA%\Salvage\
* Mac OS: ~/Library/Application Support/Salvage/
* Unix/Linux: ~/.salvage/

The new masternode.conf format consists of a space seperated text file. Each
line consisting of an alias, IP address followed by port, masternode private
key, collateral output transaction id, collateral output index, donation
address and donation percentage (the latter two are optional and should be in
format "address:percentage").

Example:

```
mn1 127.0.0.2:16999 7VnWEzUvVuwAiPwGjHeCzoqyacKQuuRPUftS5iBonJcmi2smjJR 2bcd3c84c84f87eaa86e4e56834c92927a07f9e18718810b92e0d0324456a67c 0
mn2 127.0.0.3:16999 7VPxA81mPeiNGwrsqewUSt3Px3AL17B8KQc23K2HRPH9UFBSKCM aa9f1034d973377a5e733272c3d0eced1de22555ad45d6b24abadff8087948d4 0 UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX:33
mn3 127.0.0.4:16999 7VKkgKhoo16zYPLpJ5EL7Q83UufAj2KuF1sUTZmuhqtNP5QEYnL db478e78e3aefaa8c12d12ddd0aeace48c3b451a8b41c570d0ee375e2a02dfd9 1 UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX
```

In the example above:

* mn1 collateral consists of transaction 2bcd3c84c84f87eaa86e4e56834c92927a07f9e18718810b92e0d0324456a67c, output index 0 has amount 15.000
* mn2 will donate 33% of its income
* mn3 will donate 100% of its income

The following new RPC commands are supported:

* list-conf: shows the parsed masternode.conf
* start-alias \<alias\>
* stop-alias \<alias\>
* start-many
* stop-many
* outputs: list available collateral output transaction ids and corresponding
  collateral output indexes

When using the multi masternode setup, it is advised to run the wallet with
'masternode=0' as it is not needed anymore.
