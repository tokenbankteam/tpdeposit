#include "tpdeposit.hpp"

using namespace tptpdeposit;
using namespace eosio;

void tpdeposit::transfer(name from, name to, asset quantity, string memo) {
    require_auth(from);
    if (!(from != _self && to == _self)) {
        return;
    }
#if TEST

#else
    check(_code == eosio::name(USDT_CONTRACT) && quantity.amount >= 100 && memo.size() > 0,
          _code.to_string() + " " + quantity.to_string() + " " + memo.c_str() + " too small");
#endif
    eosio::name code = _code;
    asset balance = quantity;
    eosio::name account = from;
    _dodeposit(account, code, balance, memo);
}

void tpdeposit::_dodeposit(eosio::name account, eosio::name code, asset balance, string memo) {
    auto size = transaction_size();
    char buf[size];
    uint32_t read = read_transaction(buf, size);
    check(size == read, "read_transaction failed");
    checksum256 hash = eosio::sha256(buf, read);

    _deposit.emplace(_self, [&](auto &s) {
        s.id = atoll(memo.c_str());
        s.owner = account;
        s.code = code;
        s.balance = balance;
        s.timestamp = now();
        s.hash = hash;
    });
}

void tpdeposit::deldeposit(uint64_t id) {
    require_auth(_self);

    auto it = _deposit.find(id);
    check(it != _deposit.end(), std::to_string(id) + " id not exist");
    _deposit.erase(it);
}

tpdeposit::~tpdeposit() {

}