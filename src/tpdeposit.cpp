#include "tpdeposit.hpp"

using namespace tptpdeposit;
using namespace eosio;

std::vector <std::string> &
tpdeposit::split(const std::string &s, const std::string delim, std::vector <std::string> &result) {
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

void tpdeposit::transfer(name from, name to, asset quantity, string memo) {
    require_auth(from);
    if (!(from != _self && to == _self)) {
        return;
    }
    eosio::name code = _code;
    asset balance = quantity;
    eosio::name account = from;
    _dodeposit(account, code, balance, memo);
}

void tpdeposit::_dodeposit(eosio::name account, eosio::name code, asset balance, string memo) {
    _deposit.emplace(_self, [&](auto &s) {
        s.id = atoll(memo.c_str());
        s.owner = account;
        s.code = code;
        s.balance = balance;
        s.timestamp = now();
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