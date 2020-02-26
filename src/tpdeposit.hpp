#ifndef WORK_TPDEPOSIT_H
#define WORK_TPDEPOSIT_H

#include <eosiolib/eosio.hpp>
#include <eosiolib/name.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/crypto.hpp>
#include <eosiolib/types.h>
#include <eosio.system/eosio.system.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/permission.hpp>
#include <iterator>
#include <cstring>
#include <eosio.token/eosio.token.hpp>
#include <vector>

#define TEST 1
#if TEST
#define EOS_CONTRACT "eosio.token"
#else
#define EOS_CONTRACT "eosio.token"
#endif
#define STOP 1

#define START 0
#define TYPE_DEPOSIT "deposit"

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
        void deldeposit(eosio::name owner);

    private:

        struct [[eosio::table]] deposit {
            uint64_t id;
            eosio::name owner;
            eosio::name code;
            asset balance;
            uint64_t timestamp; //交易时间

            uint64_t primary_key() const { return id; }

            EOSLIB_SERIALIZE(deposit, (id)(owner)(code)(balance)(timestamp)
            )
        };

        typedef eosio::multi_index<"deposit"_n, deposit> deposit_table;

        // code is token contract account, then scope is account
        struct [[eosio::table, eosio::contract("eosio.token")]] account {
            asset balance;

            uint64_t primary_key() const { return balance.symbol.code().raw(); }
        };

        typedef eosio::multi_index<"accounts"_n, account> accounts_table;

        //充值
        void _dodeposit(eosio::name account, eosio::name code, asset balance, string memo);

    private:
        static std::vector <std::string> &
        split(const std::string &s, const std::string delim, std::vector <std::string> &result);

        static constexpr eosio::name active_permission{"active"_n};

    private:
        uint32_t delay_sec = 1;

        deposit_table _deposit;
    };
}

#define EOSIO_DISPATCH_EX(TYPE, MEMBERS) \
            extern "C" { \
                void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
                    auto self = receiver; \
                    if( action == eosio::name("onerror").value) { \
                        /* onerror is only valid if it is for the "enumivo" code account and authorized by "eosio"'s "active permission */ \
                        eosio_assert(code == eosio::name("eosio").value, "onerror action's are only valid from the \"eosio\" system account"); \
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
