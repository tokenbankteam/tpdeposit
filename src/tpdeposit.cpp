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
    if (_self == eosio::name(USDT_CONTRACT)) {
        check(quantity.amount >= 100 && memo.size() > 0,
              _self.to_string() + " " + quantity.to_string() + " " + memo.c_str() + " too small");
    } else if (_self == eosio::name(EOS_CONTRACT)) {
        check(quantity.amount >= 100 && memo.size() > 0,
              _self.to_string() + " " + quantity.to_string() + " " + memo.c_str() + " too small");
    }
#endif
    eosio::name code = _self;
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

    std::vector <std::string> func_params;
    split(memo, ":", func_params);
    check(func_params.size() >= 1, "memo invalid");

    auto user_id = atoll(func_params[0].c_str());
    std::string bus_type = "";
    if (func_params.size() > 1) {
        bus_type = func_params[1];
    }
    _deposit.emplace(_self, [&](auto &s) {
        s.id = _deposit.available_primary_key();
        s.user_id = user_id;
        s.bus_type = bus_type;
        s.owner = account;
        s.code = code;
        s.balance = balance;
        s.timestamp = current_time_point().time_since_epoch().to_seconds();
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