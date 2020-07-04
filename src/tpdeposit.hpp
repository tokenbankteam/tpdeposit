#ifndef WORK_TPDEPOSIT_H
#define WORK_TPDEPOSIT_H

#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/symbol.hpp>
#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio.system/eosio.system.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/permission.hpp>
#include <iterator>
#include <cstring>
#include <eosio.token/eosio.token.hpp>
#include <vector>

//#define TEST 1
#if TEST
#define EOS_CONTRACT "eosio.token"
#define USDT_CONTRACT "tethertether"
#else
#define EOS_CONTRACT "eosio.token"
#define USDT_CONTRACT "tethertether"
#endif

using namespace eosio;
using namespace std;

namespace tptpdeposit {

    using namespace eosio;
    using eosio::name;
    using eosio::contract;
    using eosio::asset;
    using eosio::symbol_code;
    using std::string;
    using std::vector;
    using eosio::permission_level;
    using eosio::public_key;
    using eosiosystem::wait_weight;
    using eosiosystem::key_weight;
    using eosiosystem::permission_level_weight;
    using eosiosystem::authority;

    class [[eosio::contract]] tpdeposit : public eosio::contract {
    public:

        using eosio::contract::contract;

        tpdeposit(name s, name code, eosio::datastream<const char *> ds) : contract(s, code, ds),
                                                                           _deposit(s, s.value) {
        }

        ~tpdeposit();

        [[eosio::action]]
        void transfer(name from, name to, asset quantity, string memo);

        [[eosio::action]]
        void deldeposit(uint64_t id);

    private:
        static std::vector <std::string> &
        split(const std::string &s, const std::string delim, std::vector <std::string> &result) {
            size_t last = 0;
            size_t index = s.find_first_of(delim, last);
            while (index != std::string::npos) {
                result.push_back(s.substr(last, index - last));
                last = index + 1;
                index = s.find_first_of(delim, last);
            }
            if (index - last > 0) {
                result.push_back(s.substr(last, index - last));
            }
            return result;
        }
        
    private:

        struct [[eosio::table]] deposit {
            uint64_t id;
            uint64_t user_id;
            std::string bus_type;
            eosio::name owner;
            eosio::name code;
            asset balance;
            uint64_t timestamp; //交易时间
            checksum256 hash;

            uint64_t primary_key() const { return id; }

            EOSLIB_SERIALIZE(deposit, (id)(user_id)(bus_type)(owner)(code)(balance)(timestamp)(hash)
            )
        };

        typedef eosio::multi_index<"deposit"_n, deposit> deposit_table;

        //充值
        void _dodeposit(eosio::name account, eosio::name code, asset balance, string memo);

    private:
        deposit_table _deposit;
    };
}

#define EOSIO_DISPATCH_EX(TYPE, MEMBERS) \
            extern "C" { \
                void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
                    auto self = receiver; \
                    if( action == eosio::name("onerror").value) { \
                        /* onerror is only valid if it is for the "enumivo" code account and authorized by "eosio"'s "active permission */ \
                        check(code == eosio::name("eosio").value, "onerror action's are only valid from the \"eosio\" system account"); \
                    } \
                    if((code == self && action != eosio::name("transfer").value) || action == eosio::name("onerror").value || (action == eosio::name("transfer").value && code != self)) { \
                            switch( action ) { \
                            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
                        } \
                    } \
                } \
            } \

EOSIO_DISPATCH_EX(tptpdeposit::tpdeposit, (transfer)(deldeposit))

#endif //WORK_TPDEPOSIT_H
