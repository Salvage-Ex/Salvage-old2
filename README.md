# Introduction

Galilel (GALI) is an open-source Proof-of-Work digital cryptocurrency for fast (using SwiftX), private (Zerocoin protocol) and secure microtransactions. Our main goal is to create a decentralized fully secure and anonymous network to run applications which do not rely on any central body control. By having a distributed system, thousands of users will be responsible for maintaining the application and data so that there is no single point of failure.

Galilel Cloud is a service hosting platform. It differentiates from other masternode hosting platforms by its kind of automation. New masternode and proof-of-stake coins can be added automatically to the platform by the coin developer and paying the listing fee in GALI. New coins run in a sandbox mode until they have been verified that no backdoors have been implemented to clear wallets from other coins. Isolation of different users and their wallets are managed via Linux Containers (LXC). Our customers get a fully automated solution to run with simple clicks a fully managed masternode and staking platform. Beside Masternode as a Service (MaaS) and Proof-of-Stake as a Service (PoSaaS) we implement Block Explorer as a Service (BEaaS) to allow new coins and their teams to focus on their important work while we deliver the block explorer to their users.

# Coin Specifications

* Coin Name: Galilel
* Coin Ticker: GALI
* Hash Algo: Quark
* RPC Port: 36002
* P2P Port: 36001
* Type: PoW / PoS / MN
* Minimum Staking Age: 2 Hours
* Rewards (till block 205000): MN 60%, PoS 40%
* Rewards (from block 205001): MN 70%, PoS 30%
* Last PoW Block: 1.500
* Max Coin Supply: 25.000.000
* Masternode Collateral: 15.000
* Premine: 220.000 (0,88%)
* Premine Address (Old Developer): https://explorer.galilel.cloud/address/Uet6x6BHW8a2Ckr2dNfzKgM6VJTgyUGuBZ
* Community Donation Address: https://explorer.galilel.cloud/address/UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX

# Proof-of-Work Rewards

Proof-of-Work is used as instamine protection and will end at block 1500.

<table>
  <tr>
    <td><b>Block Height</b></td>
    <td><b>Reward</b></td>
    <td><b>MN</b></td>
    <td><b>PoW</b></td>
    <td><b>Supply</b></td>
    <td><b>Runtime</b></td>
    <td><b>Stage End</b></td>
  </tr>
  <tr>
    <td>1</td>
    <td>220.000 GALI (premine)</td>
    <td>60%</td>
    <td>40%</td>
    <td>220.000</td>
    <td>0 days</td>
    <td>2018-05-25</td>
  </tr>
  <tr>
    <td>2 - 1500</td>
    <td>1 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>221.499</td>
    <td>1 day</td>
    <td>2018-05-26</td>
  </tr>
</table>

# Proof-of-Stake Rewards

Proof-of-Stake will start at block 1501 until max coin emission is reached.

<table>
  <tr>
    <td><b>Stages</b></td>
    <td><b>Block Height</b></td>
    <td><b>Reward</b></td>
    <td><b>MN</b></td>
    <td><b>PoS</b></td>
    <td><b>Supply</b></td>
    <td><b>Runtime</b></td>
    <td><b>Stage End</b></td>
  </tr>
  <tr>
    <td>Stage 1</td>
    <td>1501-12000</td>
    <td>100 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>1.271.399</td>
    <td>7 days</td>
    <td>2018-06-02</td>
  </tr>
  <tr>
    <td>Stage 2</td>
    <td>12001-22000</td>
    <td>90 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>2.171.309</td>
    <td>7 days</td>
    <td>2018-06-09</td>
  </tr>
  <tr>
    <td>Stage 3</td>
    <td>22001-42000</td>
    <td>80 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>3.771.229</td>
    <td>14 days</td>
    <td>2018-06-23</td>
  </tr>
  <tr>
    <td>Stage 4</td>
    <td>42001-100000</td>
    <td>70 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>7.831.159</td>
    <td>40 days</td>
    <td>2018-08-02</td>
  </tr>
  <tr>
    <td>Stage 5</td>
    <td>100001-160000</td>
    <td>60 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>11.431.099</td>
    <td>42 days</td>
    <td>2018-09-13</td>
  </tr>
  <tr>
    <td>Stage 6</td>
    <td>160001-205000</td>
    <td>50 GALI</td>
    <td>60%</td>
    <td>40%</td>
    <td>13.681.049</td>
    <td>31 days</td>
    <td>2018-10-14</td>
  </tr>
  <tr>
    <td>Stage 7</td>
    <td>205001-250000</td>
    <td>25 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>14.806.024</td>
    <td>31 days</td>
    <td>2018-11-14</td>
  </tr>
  <tr>
    <td>Stage 8</td>
    <td>250001-340000</td>
    <td>15 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>16.156.009</td>
    <td>62 days</td>
    <td>2019-01-15</td>
  </tr>
  <tr>
    <td>Stage 9</td>
    <td>340001-430000</td>
    <td>10 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>17.055.999</td>
    <td>62 days</td>
    <td>2019-03-18</td>
  </tr>
  <tr>
    <td>Stage 10</td>
    <td>430001-956000</td>
    <td>5 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>19.685.994</td>
    <td>365 days</td>
    <td>2020-03-17</td>
  </tr>
  <tr>
    <td>Stage 11</td>
    <td>956001-1482000</td>
    <td>4 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>21.789.990</td>
    <td>365 days</td>
    <td>2021-03-17</td>
  </tr>
  <tr>
    <td>Stage 12</td>
    <td>1482001-2008000</td>
    <td>3 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>23.367.987</td>
    <td>365 days</td>
    <td>2022-03-17</td>
  </tr>
  <tr>
    <td>Stage 13</td>
    <td>2008001-2534000</td>
    <td>2 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>24.419.985</td>
    <td>365 days</td>
    <td>2023-03-17</td>
  </tr>
  <tr>
    <td>Stage 14</td>
    <td>2534001-3114016</td>
    <td>1 GALI</td>
    <td>70%</td>
    <td>30%</td>
    <td>25.000.000</td>
    <td>403 days</td>
    <td>2024-04-23</td>
  </tr>
</table>

# Official Links

Website: https://galilel.cloud/

GitHub (Wallet): https://github.com/Galilel-Project/galilel/

GitHub (Project): https://github.com/Galilel-Project/

Block Explorer: https://explorer.galilel.cloud/

BitcoinTalk Announcement: https://bitcointalk.org/index.php?topic=4238243

Twitter: https://twitter.com/GalilelEN

Discord: https://discord.galilel.cloud

Know Your Developer (KYD): https://review.kydcoin.io/galicoin/

# Exchanges

Graviex: https://graviex.net/markets/galibtc

# Promotions

Masternodes.online: https://masternodes.online/currencies/GALI/
