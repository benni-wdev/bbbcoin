// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "base58.h"

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "BBB";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("007fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        /**
         * The message start string should be awesome! ⓩ❤
         */
        pchMessageStart[0] = 0x24;
        pchMessageStart[1] = 0xe9;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0x64;
        vAlertPubKey = ParseHex("04b7ecf0baa90495ceb4e4090f6b2fd37eec1e9c85fac68a487f3ce11589692e4a317479316ee814e066638e1db54e37a10689b70286e6315b1087b6615d179264");
        nDefaultPort = 8910;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database (and is in any case of zero value).
      	 */
        const char* pszTimestamp = "BBBC0b9c4eef8b7cc417ee5001e3500984b6fea35683a7cac141a043c42064835d34";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 520617983 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 5000000000;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nTime    = 1516547307;
        genesis.nBits    = 0x1f07ffff;
        genesis.nNonce   = uint256S("0x00000000000000000000000000000000000000000000000000000000000004cd");
        genesis.nSolution = ParseHex("0089f1611fdee42b6458513f5e2098bc653a0edaec092db940a691d2435ef2d1551a7cfdd5211235e5630213223096d2ceab27c2f042175eccbc33bfdbd4cf0b063f25a7051907c89e24ad22ddb6cdfe595ec6f1093ceac04c4386f7ed381218105da46a360c7cedc51f2cb153310a8e43dc88dbc8c2f6358af6991f921b13f5867b0c55169d9b1452747214b616dd4d5712b83855eccb0313f02cad6cb5dc244dbe119a588dd575058099c21acf2e46eea3b3c96bfed871c8583aafbf447963f33a1c5c3bf00d8752a2f307a25bbbf79b6e1994297d0e93c53ee2d0f1feec9760d198afb047363e173644ea166f03c1ba06ecf6f72937c6f7bf3ccf0616961e1ff10879c168479dafc9f1921256b2c87b2a1d4fae23b2775da0e2ca2a1be3281723ba7a50870a03dc6b15d2ec3967c072841dbf42aac3c6ffd2532d3f3663d7157de5aefcc5c70133a3ddee7138a62c0691a8545b1c4523dfd6f36c00d5a5de83fd97dea919858aed140758216ad7019f9c8da4a2268456bf7622d0772e30d0f37927b0d3466674017191613a5a7132599abf71ec4f3165bdd376ee3d4f8d3d544fa4c10d350aea37c4df11e6275202d4700f92b348367bab3dc70568b3922143bbe826d8f855a5ba61c0976ef01634892bedededf797bc736a1d3f7afcdd14d9cefb256a0cf5b70cc63d03249690b278a795d020cf42670794a93cf42dcdc37b3cb52131ff3a72251f71daf2473f5e06e1a0557f700f87eb127a2eeec1d5fe9cdc194104869c20ce9d9985765eed43c13e2fa47c804a278334c3d3cdf087c7f5e773d26931722db2b5824d0ad70986c5ce75aeb237746942f3aef9846e32148e35085a2f6f8f7dae7fe733943b3b87a1261d7f29ac0c6c0d26f4038fe1f874d440614739fba8d39ea6200f2ed368f570a0abd4f2c3851074e9ce85a91b8e2c00f7245fb1ec5239f54953599858345d1fb4588dea0d4fd721a31d0a3dfc1c31b07a739f69daf7b264611df37da061993452f243323eb5d298eccf6b2f7bf64288dc9259abaf95e22b74744ea452362497d3ff7804d53ff7dc49e1aed372d387b9b8512579161bbd3908a8a060db26a9efbddaa66630fdd292faeb7d0bc216a6912562c646b1470a2777ca50d6122cbeb97e211bf7ce44f9ab70039263e5a5abf95dfed078bb03af01b78585498b398e8864e3309aa4f048d72a37788d0a23564f56621e1fa843a5898f77cce16c00ef04b1034ac7baa2d6c1693c0a521c56141faa5b481a052c076d1c89afe1438945078433696399b567f46bfdc703e76ceff401d26eb222923b252e7dfaf8bef81e9514fb7fce4f517c518ed49423c1ea93750c0536ad3f0b5177d5a48ca6d3676813fbb0aa185dab7ab8a3b6227e0e6135aaef6170ed75fce759d5b9ad48326993019042fa66881492cfab523f8899af4202a933f52634778ad7dd0d382de9f03381eb7d24dd8a58b2b847057cbcd5ee505fbb89ca664da847108f4538bc3cac21399663b34beae77ee43aac9fff54eece39f818c9101b352cf4889b7aabf16111985e4460ad59f6936939f874fd5daba8a7f285d92511e126e37d9b5c1d771488979121ab44adf9f492ffe5b183b62200d9882f2c06226296b301f5ea7816b82ee7c02aa1365f54bc03641d8098ea56377bda52da437d1ae255057b094c19e0eb051bcf2856efee243ecb73a9858a38ce31d507a6059caf901a15ea4af378046686bd07b32d85c522c089ade050dd4d3b26a24bd5aadce2070d305aac06cc361a28c8b3428183624d4b74fd212acbb2681a1380172aa9fa6f95f4017241d96b7a3d265b69bb370f60b47171aa53d9c784e1fdf1168521acfc747d63161a07c9288591f03b490348e7231709568cd5f872");
        consensus.hashGenesisBlock = genesis.GetHash();

		/*arith_uint256 tnonce = 0;
		LogPrintf("recalculating params for mainnet.\n");
		LogPrintf("old mainnet genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("old mainnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString().c_str());
		// deliberately empty for loop finds nonce value.
		for(tnonce = 0; UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit); tnonce++){
			genesis.nNonce = ArithToUint256(tnonce);
		}
		LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
		LogPrintf("new mainnet genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
		*/
        assert(consensus.hashGenesisBlock == uint256S("0x"+consensus.hashGenesisBlock.ToString()));
        assert(genesis.hashMerkleRoot == uint256S("0x"+genesis.hashMerkleRoot.ToString()));


        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("mainnet.bbbcoin.site", "mainnet.bbbcoin.site")); // @str4d
        //vSeeds.push_back(CDNSSeedData("znodes.org", "dnsseed.znodes.org")); // @bitcartel

        // guarantees the first 2 characters, when base58 encoded, are "t1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1C,0xB8};
        // guarantees the first 2 characters, when base58 encoded, are "t3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBD};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        vFixedSeeds.clear();

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (0,  uint256S("0004965806e8ccf828486dec85a26e5041f8b3396435d3f28acf33d3c216f95c")),
          //  (10, uint256S("0x003fa6a6bbcea855fb76e478fda40c28b454e74537fbeb889e50b41710d4d41e"))
          //  (10000, uint256S("0x00000fbda97b62268d2eb2ed9e63ae23a9a02c3f6cb7023cd56443a215c9c0ed"))
          //  (16800, uint256S("0x0000009771cf774a233ca47b5ceee89dd9296c82e8c9b0a96d00f57b26d5925c"))
          //  (39555, uint256S("0x0000000bbc03146dfb317de60c346b518e88defa4232db6f64b43a515b6d4df2")),
            1516547307,    // * UNIX timestamp of last checkpoint block
            0,        // * total number of transactions between genesis and last checkpoint
                           //   (the tx=... number in the SetBestChain debug.log lines)
            1000          // * estimated number of transactions per day after checkpoint
                           //   total number of tx / checkpoint block height * 576
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t3Vz22vK5z2LcKEdg16Yv4FFneEL1zg9ojd", /* main-index: 0*/

        };
       // assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "TBB";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.fPowAllowMinDifficultyBlocks = true;
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0xf9;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("044e7a1553392325c871c5ace5d6ad73501c66f4c185d6b0453cf45dec5a1322e705c672ac1a27ef7cdaf588c10effdf50ed5f95f85f2f54a5f6159fca394ed0c6");
        nDefaultPort = 18910;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1516547307;
        genesis.nBits = 0x2007ffff;
        genesis.nNonce = uint256S("0x000000000000000000000000000000000000000000000000000000000000001e");
        genesis.nSolution = ParseHex("0364a12e11aabd49e5fa98297674700f0fe04ab54b685a7c1199646e259a5578");
        consensus.hashGenesisBlock = genesis.GetHash();


       arith_uint256 tnonce = 0;
		LogPrintf("recalculating params for testnet.\n");
		LogPrintf("old testnet genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("old testnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString().c_str());
		// deliberately empty for loop finds nonce value.
		for(tnonce = 0; UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit); tnonce++){
			genesis.nNonce = ArithToUint256(tnonce);
		}
		LogPrintf("new testnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
		LogPrintf("new testnet genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("new testnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());


        assert(consensus.hashGenesisBlock == uint256S("0x" + consensus.hashGenesisBlock.ToString()));


        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet.bbbcoin.site", "testnet.bbbcoin.site")); // Zcash


        // guarantees the first 2 characters, when base58 encoded, are "tm"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        // guarantees the first 2 characters, when base58 encoded, are "t2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        vFixedSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x0364a12e11aabd49e5fa98297674700f0fe04ab54b685a7c1199646e259a5578")),
         //   (38000, uint256S("0x001e9a2d2e2892b88e9998cf7b079b41d59dd085423a921fe8386cecc42287b8")),
            1516547307,  // * UNIX timestamp of last checkpoint block
            0,       // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
            100          //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t2UNzUUx8mWBCRYPRezvA363EYXyEpHokyi", "t2N9PH9Wk9xjqYg9iin1Ua3aekJqfAtE543", "t2NGQjYMQhFndDHguvUw4wZdNdsssA6K7x2", "t2ENg7hHVqqs9JwU5cgjvSbxnT2a9USNfhy",
            "t2BkYdVCHzvTJJUTx4yZB8qeegD8QsPx8bo", "t2J8q1xH1EuigJ52MfExyyjYtN3VgvshKDf", "t2Crq9mydTm37kZokC68HzT6yez3t2FBnFj", "t2EaMPUiQ1kthqcP5UEkF42CAFKJqXCkXC9", 
            "t2F9dtQc63JDDyrhnfpzvVYTJcr57MkqA12", "t2LPirmnfYSZc481GgZBa6xUGcoovfytBnC", "t26xfxoSw2UV9Pe5o3C8V4YybQD4SESfxtp", "t2D3k4fNdErd66YxtvXEdft9xuLoKD7CcVo", 
            "t2DWYBkxKNivdmsMiivNJzutaQGqmoRjRnL", "t2C3kFF9iQRxfc4B9zgbWo4dQLLqzqjpuGQ", "t2MnT5tzu9HSKcppRyUNwoTp8MUueuSGNaB", "t2AREsWdoW1F8EQYsScsjkgqobmgrkKeUkK", 
            "t2Vf4wKcJ3ZFtLj4jezUUKkwYR92BLHn5UT", "t2K3fdViH6R5tRuXLphKyoYXyZhyWGghDNY", "t2VEn3KiKyHSGyzd3nDw6ESWtaCQHwuv9WC", "t2F8XouqdNMq6zzEvxQXHV1TjwZRHwRg8gC", 
            "t2BS7Mrbaef3fA4xrmkvDisFVXVrRBnZ6Qj", "t2FuSwoLCdBVPwdZuYoHrEzxAb9qy4qjbnL", "t2SX3U8NtrT6gz5Db1AtQCSGjrpptr8JC6h", "t2V51gZNSoJ5kRL74bf9YTtbZuv8Fcqx2FH", 
            "t2FyTsLjjdm4jeVwir4xzj7FAkUidbr1b4R", "t2EYbGLekmpqHyn8UBF6kqpahrYm7D6N1Le", "t2NQTrStZHtJECNFT3dUBLYA9AErxPCmkka", "t2GSWZZJzoesYxfPTWXkFn5UaxjiYxGBU2a", 
            "t2RpffkzyLRevGM3w9aWdqMX6bd8uuAK3vn", "t2JzjoQqnuXtTGSN7k7yk5keURBGvYofh1d", "t2AEefc72ieTnsXKmgK2bZNckiwvZe3oPNL", "t2NNs3ZGZFsNj2wvmVd8BSwSfvETgiLrD8J", 
            "t2ECCQPVcxUCSSQopdNquguEPE14HsVfcUn", "t2JabDUkG8TaqVKYfqDJ3rqkVdHKp6hwXvG", "t2FGzW5Zdc8Cy98ZKmRygsVGi6oKcmYir9n", "t2DUD8a21FtEFn42oVLp5NGbogY13uyjy9t", 
            "t2UjVSd3zheHPgAkuX8WQW2CiC9xHQ8EvWp", "t2TBUAhELyHUn8i6SXYsXz5Lmy7kDzA1uT5", "t2Tz3uCyhP6eizUWDc3bGH7XUC9GQsEyQNc", "t2NysJSZtLwMLWEJ6MH3BsxRh6h27mNcsSy", 
            "t2KXJVVyyrjVxxSeazbY9ksGyft4qsXUNm9", "t2J9YYtH31cveiLZzjaE4AcuwVho6qjTNzp", "t2QgvW4sP9zaGpPMH1GRzy7cpydmuRfB4AZ", "t2NDTJP9MosKpyFPHJmfjc5pGCvAU58XGa4", 
            "t29pHDBWq7qN4EjwSEHg8wEqYe9pkmVrtRP", "t2Ez9KM8VJLuArcxuEkNRAkhNvidKkzXcjJ", "t2D5y7J5fpXajLbGrMBQkFg2mFN8fo3n8cX", "t2UV2wr1PTaUiybpkV3FdSdGxUJeZdZztyt", 
            };
      //  assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x5f;
        nMaxTipAge = 24 * 60 * 60;
        const size_t N = 48, K = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;
        genesis.nTime = 1516547307;
        genesis.nBits = 0x200f0f0f;
        genesis.nNonce = uint256S("0x0000000000000000000000000000000000000000000000000000000000000010");
        genesis.nSolution = ParseHex("02462ea1aaa637eb4d1e78db75de575f298c071271e2f65fd27d44a9f7df1e4b");
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18922;
        assert(consensus.hashGenesisBlock == uint256S("0x" + consensus.hashGenesisBlock.ToString()));
        nPruneAfterHeight = 1000;

       /* arith_uint256 tnonce = 0;
		LogPrintf("recalculating params for testnet.\n");
		LogPrintf("old regtest genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("old regtest genesis hash:  %s\n", consensus.hashGenesisBlock.ToString().c_str());
		// deliberately empty for loop finds nonce value.
		for(tnonce = 0; UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit); tnonce++){
			genesis.nNonce = ArithToUint256(tnonce);
		}
		LogPrintf("new regtest genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
		LogPrintf("new regtest genesis nonce: %s\n", genesis.nNonce.ToString().c_str());
		LogPrintf("new regtest genesis hash: %s\n", genesis.GetHash().ToString().c_str());
		*/
        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x02462ea1aaa637eb4d1e78db75de575f298c071271e2f65fd27d44a9f7df1e4b")),
            0,
            0,
            0
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = { "t2FwcEhFdNXuFMv1tcYwaBJtYVtMj8b1uTg" };
       // assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);

    // Some python qa rpc tests need to enforce the coinbase consensus rule
    if (network == CBaseChainParams::REGTEST && mapArgs.count("-regtestprotectcoinbase")) {
        regTestParams.SetRegTestCoinbaseMustBeProtected();
    }
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}


// Block height must be >0 and <=last founders reward block height
// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int maxHeight = consensus.GetLastFoundersRewardBlockHeight();
    assert(nHeight > 0 && nHeight <= maxHeight);

    size_t addressChangeInterval = (maxHeight + vFoundersRewardAddress.size()) / vFoundersRewardAddress.size();
    size_t i = nHeight / addressChangeInterval;
    return vFoundersRewardAddress[i];
}

// Block height must be >0 and <=last founders reward block height
// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    assert(nHeight > 0 && nHeight <= consensus.GetLastFoundersRewardBlockHeight());

    CBitcoinAddress address(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}
