// Copyright (c) 2009-2009 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Salvage developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0xabc9f92f267fd8f688f28b339a0f19c323142d39cd12076ca0d83a7bc6052b5a"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1530003550, // * UNIX timestamp of last checkpoint block
    0,      // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    720        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000008e4c24baa9a3503e6dc2f3b459843441a0d56677b1e4bd0b9a381ca987f"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1540587600,
    0,
    720};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x7efc7852063bf1df9faa80bcc5a2572a3be0e975d4c35fc7ba82b16b1693052d"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1527217410,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04307320ddf6bb1f1847ed4814515742bda9bb10415ce492f669a7ea7c4590e520b60febafd3a84b3c5528a303017bde0a88bbc7b78eee117ee6c4ba6f7c9e4a7a");
        nDefaultPort = 16999;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // SVG starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60 ; // SVG: 1 day
        nTargetSpacing = 2 * 60;  // SVG: 2 minute block time
        nMaturity = 99;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 25000000 * COIN;
        nRequiredMNCollateral = 10000 * COIN; //Requires 10,000 coin for masternde collateral 

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 1001;           //Check how the block and time works
        nBlockFirstGoodChecksum = 1001;		/* First block with valid Zerocoin checksums ***May need to be updated after first block*/
        nZerocoinStartTime = 1543611600;		/* Fri Nov 30 21:00:00 UTC 2018 */
        nBlockEnforceSerialRange = 2147483646;		/* (disabled) Enforce serial range starting this block */
        nBlockRecalculateAccumulators = 2147483646;	/* (disabled) Trigger a recalculation of accumulators */
        nBlockFirstFraudulent = 2147483646;		/* (disabled) First block that bad serials emerged */
        nBlockLastGoodCheckpoint = 2147483646;		/* (disabled) Last valid accumulator checkpoint */
        nBlockEnforceInvalidUTXO = 2147483646;		/* (disabled) Start enforcing the invalid UTXO's */
        nInvalidAmountFiltered = 0;			/* Amount of invalid coins filtered through exchanges, that should be considered valid */
        nBlockZerocoinV2 = 1001;			/* (disabled) The block that zerocoin v2 becomes active - roughly Sat Dec 15 08:00:00 UTC 2018 */
        nEnforceNewSporkKey = 1527822208;		/* Fri Jun  1 05:03:28 CEST 2018: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1528427008;		/* Fri Jun  8 05:03:28 CEST 2018: after that reject old spork key */

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Some trash is recycled, some is thrown away, some ends up where it shouldn't end up.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0483e3f08209f63c7634ed8f73edba2faa66abf6123578922c0a5f280f8348e4d16545e800ff3e2337ba90006112759f6c2b128e4c3a7bdd041fd925c12f4c3fa7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1535069268;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 3271076;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000049e70db758199bca1a530c68ea0162558b42abba1f60a60d0991ff60314"));
        assert(genesis.hashMerkleRoot == uint256("827768506cc21bf011726794ec9a605829591df56847317bf7a3e458328ffc00"));

        vSeeds.push_back(CDNSSeedData("seed1.salvageproject.org", "seed1.salvageproject.org")); // 1st DNS Seed
        vSeeds.push_back(CDNSSeedData("seed2.salvageproject.org", "seed2.salvageproject.org")); // 2nd DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed3.salvageproject.org", "seed3.salvageproject.org")); // 3rd DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed4.salvageproject.org", "seed4.salvageproject.org")); // 4th DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed5.salvageproject.org", "seed5.salvageproject.org")); // 5th DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed6.salvageproject.org", "seed6.salvageproject.org")); // 6th DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed7.salvageproject.org", "seed7.salvageproject.org")); // 7th DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed8.salvageproject.org", "seed8.salvageproject.org")); // 8th DNS Seed 
        vSeeds.push_back(CDNSSeedData("seed9.salvageproject.org", "seed9.salvageproject.org")); // 9th DNS Seed 


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);		// Start with 'S' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65);		// Start with 'T' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x37).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x3F).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGS'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x92)(0xf0).convert_to_container<std::vector<unsigned char> >(); // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04dd67348b812cc21e43ea9d88517df604b05876330ef325435d29950fb77240da168231abeba65d0ecdecfd4632e821a271c279b9e571dff54039d9fba0fd6284";
        //strSporkKeyOld = "0478c3e932fbe183b2f665de937866cb1cfc5ed4b0bf733b72286f265ffc03ff52dfd669fbb3f77d630e5393da65c721a9a891d2c4c6aa515dfd25ffe545582357";

        strObfuscationPoolDummyAddress = "SYuYowBAuCLdgSUDEvFp9CGzK2isZXHN7r";

        nStartMasternodePayments = 1525192183; // Tue May  1 18:29:43 CEST 2018

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; // high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; // the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; // full security level for accumulators
        nZerocoinHeaderVersion = 4; // block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 240; //The required confirmations for a zsvg to be stakable

        nBudget_Fee_Confirmations = 6; // number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        vAlertPubKey = ParseHex("04abac66ae10ca99a58d2bf464ed97328c69a5c96ddaacae797c595990c86e01d4c9f16d490d047dac06a24c36e1575e6f6ee5e49f3677df12e85ae1ed9c37fa88");
        nDefaultPort = 17888;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // SVG: 2 minute
        nTargetSpacing = 2 * 60;  // SVG: 2 minute
        nLastPOWBlock = 500;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 25000000 * COIN;
        nRequiredMNCollateral = 10000 * COIN; //Requires 10,000 coin for masternde collateral 
        
        nZerocoinStartHeight = 501;
        nZerocoinStartTime = 1541797200;		/* Fri Nov  9 21:00:00 UTC 2018 */
        nBlockFirstGoodChecksum = 501;		/* First block with valid Zerocoin checksums */
        nBlockEnforceSerialRange = 501;		/* Enforce serial range starting this block */
        nBlockRecalculateAccumulators = 2147483646;	/* (disabled) Trigger a recalculation of accumulators */
        nBlockFirstFraudulent = 2147483646;		/* (disabled) First block that bad serials emerged */
        nBlockLastGoodCheckpoint = 2147483646;		/* (disabled) Last valid accumulator checkpoint */
        nBlockEnforceInvalidUTXO = 2147483646;		/* (disabled) Start enforcing the invalid UTXO's */
        nInvalidAmountFiltered = 0;			/* Amount of invalid coins filtered through exchanges, that should be considered valid */
        nBlockZerocoinV2 = 501;     		/* (disabled) The block that zerocoin v2 becomes active */
        nEnforceNewSporkKey = 1540760400;		/* Sun Oct 28 21:00:00 UTC 2018: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1541325600;		/* Sun Nov  4 21:00:00 UTC 2018: after that reject old spork key */

        /* Testnet genesis block. */
        genesis.nTime = 1535069405;			/* Testnet started: Fri Oct 26 21:00:00 UTC 2018 */
        genesis.nNonce = 173831;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000f52e502b6125d83ebd7fb8c8914e1b25f7801e65afbc8a5c6b3e252435d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("seed1t.salvageproject.org", "seed1t.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed2t.salvageproject.org", "seed2t.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed3t.salvageproject.org", "seed3t.salvageproject.org"));
        vSeeds.push_back(CDNSSeedData("seed4t.salvageproject.org", "seed4t.salvageproject.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);	// Start with 's' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 127);	// start with 't' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x41).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGT'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3F)(0x46)(0x25)(0x44).convert_to_container<std::vector<unsigned char> >(); // Start with 'SVGU'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >(); // Testnet Salvage BIP44 coin type is '1' (All coin's testnet default)

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04bb4cc355d8b119f89b3cf9353f2c9e50fbea04276cdd97f4d7a6a9eaeec929e232d4a45431e28a45df5ed5a96162ece24f3b398adfc03544239fd33465d5620f";
        //strSporkKeyOld = "04363509d5c65f5a9ca7ceedad4887007ae85469d249a6f566b788504ee5e105bcf1bbc515f49a7aac3bceb8864bb2ba84bebd92c66ff9022309e2bfbd5f70d11f";
        
		strObfuscationPoolDummyAddress = "sVf63d2gveDQ2AC2CqoW11ZfD7jpqTPzVN";
        
		nStartMasternodePayments = 1540587600; // Fri Oct 26 21:00:00 UTC 2018
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // SVG: 1 day
        nTargetSpacing = 2 * 60;        // SVG: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 17555;

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1535069268;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 3271076;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000049e70db758199bca1a530c68ea0162558b42abba1f60a60d0991ff60314"));
        assert(genesis.hashMerkleRoot == uint256("827768506cc21bf011726794ec9a605829591df56847317bf7a3e458328ffc00"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 58123;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
